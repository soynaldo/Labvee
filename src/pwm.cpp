#include "pwm.h"

uint32_t _oscillator_freq;

void PWM_Begin() {
    PWM_Begin(0);
}

void PWM_Begin(uint8_t prescale) {
    I2C_Begin();
    PWM_Reset();
    // set the default internal frequency
    PWM_SetOscFreq(FREQUENCY_OSCILLATOR);
    
    if (prescale) {
        PWM_SetExtClk(prescale);
    } else {
        PWM_SetFrecuency(1000);
    }
}

void PWM(uint8_t pin, uint8_t percent) {
    if (percent <= 100 && pin < 17) {
        uint16_t ton = map(percent, 0, 100, 0, 4095);
        uint16_t toff = 4095 - ton;
        uint8_t buffer[5];
        buffer[0] = PCA9685_LED0_ON_L + 4 * pin;
        buffer[1] = ton;
        buffer[2] = ton >> 8;
        buffer[3] = toff;
        buffer[4] = toff >> 8;
        I2C_WriteBytes(PCA9685_I2C_ADDRESS, buffer, 5);
    }
}

uint16_t PWM(uint8_t pin) {
    uint8_t buffer[2] = {0};
    I2C_Write8(PCA9685_I2C_ADDRESS, uint8_t(PCA9685_LED0_ON_L + 4 * pin));
    I2C_ReadBytes(PCA9685_I2C_ADDRESS, buffer, 2);
    return uint16_t(buffer[0]) | (uint16_t(buffer[1]) << 8);
}

void PWM_SetFrecuency(float frecuency) {
    // Range output modulation frequency is dependant on oscillator
    if (frecuency < 1) frecuency = 1;
    if (frecuency > 3500) frecuency = 3500; // Datasheet limit is 3052=50MHz/(4*4096)

    float prescaleval = ((_oscillator_freq / (frecuency * 4096.0)) + 0.5) - 1;
    if (prescaleval < PCA9685_PRESCALE_MIN) prescaleval = PCA9685_PRESCALE_MIN;
    if (prescaleval > PCA9685_PRESCALE_MAX) prescaleval = PCA9685_PRESCALE_MAX;
    uint8_t prescale = (uint8_t)prescaleval;

    uint8_t oldmode = PWM_GetMode(PCA9685_MODE1);
    uint8_t newmode = ((oldmode & ~MODE1_RESTART) | MODE1_SLEEP); // sleep
    PWM_SetMode(PCA9685_MODE1, newmode);                    // go to sleep
    PWM_SetMode(PCA9685_PRESCALE, prescale); // set the prescaler
    PWM_SetMode(PCA9685_MODE1, oldmode);
    delay(5);
    // This sets the MODE1 register to turn on auto increment.
    PWM_SetMode(PCA9685_MODE1, (oldmode | MODE1_RESTART | MODE1_AI));
}

void PWM_Reset() {
    PWM_SetMode(PCA9685_MODE1, MODE1_RESTART);
    delay(10);
}

void PWM_Sleep() {
    uint8_t sleep = PWM_GetMode(PCA9685_MODE1);
    sleep |= MODE1_SLEEP; // set sleep bit high
    PWM_SetMode(PCA9685_MODE1, sleep);
    delay(5); // wait until cycle ends for sleep to be active
}

void PWM_Wakeup() {
    uint8_t wakeup = PWM_GetMode(PCA9685_MODE1);
    wakeup &=~ MODE1_SLEEP; // set sleep bit low
    PWM_SetMode(PCA9685_MODE1, wakeup);
}

void PWM_SetOscFreq(uint32_t freq) {
    _oscillator_freq = freq;
}

void PWM_SetExtClk(uint8_t prescale) {
    uint8_t newmode = PWM_GetMode(PCA9685_MODE1);
    newmode = (newmode & ~MODE1_RESTART) | MODE1_SLEEP;
    PWM_SetMode(PCA9685_MODE1, newmode);

    // This sets both the SLEEP and EXTCLK bits of the MODE1 register to switch to
    // use the external clock.
    PWM_SetMode(PCA9685_MODE1, (newmode |= MODE1_EXTCLK));

    PWM_SetMode(PCA9685_PRESCALE, prescale); // set the prescaler

    delay(5);
    // clear the SLEEP bit to start
    PWM_SetMode(PCA9685_MODE1, (newmode & ~MODE1_SLEEP) | MODE1_RESTART | MODE1_AI);
}

uint8_t PWM_ReadPrescale() {
    return PWM_GetMode(PCA9685_PRESCALE);
}

uint8_t PWM_GetMode(uint8_t mode) {
    I2C_Write8(PCA9685_I2C_ADDRESS, mode);
    return I2C_Read8(PCA9685_I2C_ADDRESS);
}

void PWM_SetMode(uint8_t mode, uint8_t value) {
    uint8_t buffer[2] = {mode, value};
    I2C_WriteBytes(PCA9685_I2C_ADDRESS, buffer, 2);
}