#include "pwm.h"

uint32_t _oscillator_freq;

void portPWM_begin() {
    portPWM_begin(0);
}

void portPWM_begin(uint8_t prescale) {
    portI2C_begin();
    portPWM_reset();
    // set the default internal frequency
    portPWM_setOscFreq(FREQUENCY_OSCILLATOR);
    
    if (prescale) {
        portPWM_setExtClk(prescale);
    } else {
        portPWM_setFrecuency(1000);
    }
}

void portPWM(uint8_t pin, uint8_t percent) {
    if (percent <= 100 && pin < 17) {
        uint16_t ton = map(percent, 0, 100, 0, 4095);
        uint16_t toff = 4095 - ton;
        uint8_t buffer[5];
        buffer[0] = PCA9685_LED0_ON_L + 4 * pin;
        buffer[1] = ton;
        buffer[2] = ton >> 8;
        buffer[3] = toff;
        buffer[4] = toff >> 8;
        portI2C_writeBytes(PCA9685_I2C_ADDRESS, buffer, 5);
    }
}

uint16_t portPWM(uint8_t pin) {
    uint8_t buffer[2] = {0};
    portI2C_write8(PCA9685_I2C_ADDRESS, uint8_t(PCA9685_LED0_ON_L + 4 * pin));
    portI2C_readBytes(PCA9685_I2C_ADDRESS, buffer, 2);
    return uint16_t(buffer[0]) | (uint16_t(buffer[1]) << 8);
}

void portPWM_setFrecuency(float frecuency) {
    // Range output modulation frequency is dependant on oscillator
    if (frecuency < 1) frecuency = 1;
    if (frecuency > 3500) frecuency = 3500; // Datasheet limit is 3052=50MHz/(4*4096)

    float prescaleval = ((_oscillator_freq / (frecuency * 4096.0)) + 0.5) - 1;
    if (prescaleval < PCA9685_PRESCALE_MIN) prescaleval = PCA9685_PRESCALE_MIN;
    if (prescaleval > PCA9685_PRESCALE_MAX) prescaleval = PCA9685_PRESCALE_MAX;
    uint8_t prescale = (uint8_t)prescaleval;

    uint8_t oldmode = portPWM_getMode(PCA9685_MODE1);
    uint8_t newmode = ((oldmode & ~MODE1_RESTART) | MODE1_SLEEP); // sleep
    portPWM_setMode(PCA9685_MODE1, newmode);                    // go to sleep
    portPWM_setMode(PCA9685_PRESCALE, prescale); // set the prescaler
    portPWM_setMode(PCA9685_MODE1, oldmode);
    delay(5);
    // This sets the MODE1 register to turn on auto increment.
    portPWM_setMode(PCA9685_MODE1, (oldmode | MODE1_RESTART | MODE1_AI));
}

void portPWM_reset() {
    portPWM_setMode(PCA9685_MODE1, MODE1_RESTART);
    delay(10);
}

void portPWM_sleep() {
    uint8_t sleep = portPWM_getMode(PCA9685_MODE1);
    sleep |= MODE1_SLEEP; // set sleep bit high
    portPWM_setMode(PCA9685_MODE1, sleep);
    delay(5); // wait until cycle ends for sleep to be active
}

void portPWM_wakeup() {
    uint8_t wakeup = portPWM_getMode(PCA9685_MODE1);
    wakeup &=~ MODE1_SLEEP; // set sleep bit low
    portPWM_setMode(PCA9685_MODE1, wakeup);
}

void portPWM_setOscFreq(uint32_t freq) {
    _oscillator_freq = freq;
}

void portPWM_setExtClk(uint8_t prescale) {
    uint8_t newmode = portPWM_getMode(PCA9685_MODE1);
    newmode = (newmode & ~MODE1_RESTART) | MODE1_SLEEP;
    portPWM_setMode(PCA9685_MODE1, newmode);

    // This sets both the SLEEP and EXTCLK bits of the MODE1 register to switch to
    // use the external clock.
    portPWM_setMode(PCA9685_MODE1, (newmode |= MODE1_EXTCLK));

    portPWM_setMode(PCA9685_PRESCALE, prescale); // set the prescaler

    delay(5);
    // clear the SLEEP bit to start
    portPWM_setMode(PCA9685_MODE1, (newmode & ~MODE1_SLEEP) | MODE1_RESTART | MODE1_AI);
}

uint8_t portPWM_readPrescale() {
    return portPWM_getMode(PCA9685_PRESCALE);
}

uint8_t portPWM_getMode(uint8_t mode) {
    portI2C_write8(PCA9685_I2C_ADDRESS, mode);
    return portI2C_read8(PCA9685_I2C_ADDRESS);
}

void portPWM_setMode(uint8_t mode, uint8_t value) {
    uint8_t buffer[2] = {mode, value};
    portI2C_writeBytes(PCA9685_I2C_ADDRESS, buffer, 2);
}