#include "i2c.h"

// REGISTER ADDRESSES
#define PCA9685_MODE1 0x00      /**< Mode Register 1 */
#define PCA9685_MODE2 0x01      /**< Mode Register 2 */
#define PCA9685_LED0_ON_L 0x06  /**< LED0 on tick, low byte*/
#define PCA9685_LED0_ON_H 0x07  /**< LED0 on tick, high byte*/
#define PCA9685_LED0_OFF_L 0x08 /**< LED0 off tick, low byte */
#define PCA9685_LED0_OFF_H 0x09 /**< LED0 off tick, high byte */
#define PCA9685_PRESCALE 0xFE     /**< Prescaler for PWM output frequency */
#define PCA9685_TESTMODE 0xFF     /**< defines the test mode to be entered */

// MODE1 bits
#define MODE1_SLEEP 0x10   /**< Low power mode. Oscillator off */
#define MODE1_AI 0x20      /**< Auto-Increment enabled */
#define MODE1_EXTCLK 0x40  /**< Use EXTCLK pin clock */
#define MODE1_RESTART 0x80 /**< Restart enabled */

#define PCA9685_I2C_ADDRESS 0x40      /**< Default PCA9685 I2C Slave Address */
#define FREQUENCY_OSCILLATOR 25000000 /**< Int. osc. frequency in datasheet */

#define PCA9685_PRESCALE_MIN 3   /**< minimum prescale value */
#define PCA9685_PRESCALE_MAX 255 /**< maximum prescale value */


/**
 * @brief Inicializa el módulo PWM con configuración por defecto.
 * 
 * Configura el sistema de PWM listo para su uso.
 */
void portPWM_begin();

/**
 * @brief Inicializa el módulo PWM con un valor de prescaler personalizado.
 * 
 * @param prescale El valor del prescaler para configurar la frecuencia de PWM.
 */
void portPWM_begin(uint8_t prescale);

/**
 * @brief Configura un pin para generar PWM con un porcentaje de ciclo útil.
 * 
 * @param pin El pin donde se generará la señal PWM.
 * @param percent El ciclo útil de PWM en porcentaje (0-100).
 */
void portPWM(uint8_t pin, uint8_t percent);

/**
 * @brief Lee el ciclo útil actual en porcentaje en un pin PWM.
 * 
 * @param pin El pin donde se está generando la señal PWM.
 * @return El ciclo útil de PWM en porcentaje (0-100).
 */
uint16_t portPWM(uint8_t pin);

/**
 * @brief Configura la frecuencia de PWM.
 * 
 * @param frecuency La frecuencia de la señal PWM en Hz.
 */
void portPWM_setFrecuency(float frecuency);

/**
 * @brief Configura la frecuencia del oscilador interno del módulo PWM.
 * 
 * @param freq Frecuencia del oscilador en Hz.
 */
void portPWM_setOscFreq(uint32_t freq);

/**
 * @brief Configura el uso de un reloj externo para el módulo PWM.
 * 
 * @param prescale El valor del prescaler para la señal de reloj externo.
 */
void portPWM_setExtClk(uint8_t prescale);

/**
 * @brief Resetea el módulo PWM a su estado inicial.
 * 
 * Esta función restablece todas las configuraciones del módulo PWM.
 */
void portPWM_reset();

/**
 * @brief Pone el módulo PWM en modo de suspensión.
 * 
 * Esta función reduce el consumo de energía desactivando el PWM hasta que sea reactivado.
 */
void portPWM_sleep();

/**
 * @brief Reactiva el módulo PWM después de haber sido suspendido.
 * 
 * Despierta el módulo PWM y lo pone en funcionamiento.
 */
void portPWM_wakeup();

/**
 * @brief Lee el valor actual del prescaler del módulo PWM.
 * 
 * @return El valor del prescaler configurado.
 */
uint8_t portPWM_readPrescale();

/**
 * @brief Configura el modo del módulo PWM.
 * 
 * @param mode El modo que se desea configurar.
 * @param value El valor correspondiente al modo seleccionado.
 */
void portPWM_setMode(uint8_t mode, uint8_t value);

/**
 * @brief Obtiene el valor actual de un modo específico en el módulo PWM.
 * 
 * @param mode El modo del cual se desea obtener el valor.
 * @return El valor actual del modo seleccionado.
 */
uint8_t portPWM_getMode(uint8_t mode);
