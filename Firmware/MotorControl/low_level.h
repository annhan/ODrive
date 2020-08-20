/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LOW_LEVEL_H
#define __LOW_LEVEL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cmsis_os.h>
#include <stdbool.h>
#include <adc.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define ADC_CHANNEL_COUNT 16
extern const float adc_full_scale;
extern const float adc_ref_voltage;
/* Exported variables --------------------------------------------------------*/
extern float vbus_voltage;
extern float ibus_;
extern bool brake_resistor_armed;
extern bool brake_resistor_saturated;
extern uint16_t adc_measurements_[ADC_CHANNEL_COUNT];
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void safety_critical_arm_motor_pwm(Motor& motor);
bool safety_critical_disarm_motor_pwm(Motor& motor);
void safety_critical_apply_motor_pwm_timings(Motor& motor, uint16_t timings[3]);
void safety_critical_arm_brake_resistor();
void safety_critical_disarm_brake_resistor();
void safety_critical_apply_brake_resistor_timings(uint32_t low_off, uint32_t high_on);

// called from STM platform code
extern "C" {
void pwm_trig_adc_cb(ADC_HandleTypeDef* hadc, bool injected);
void vbus_sense_adc_cb(ADC_HandleTypeDef* hadc, bool injected);
void pwm_in_cb(TIM_HandleTypeDef *htim);
}

// Initalisation
void start_adc_pwm();
void start_pwm(TIM_HandleTypeDef* htim);
void sync_timers(TIM_HandleTypeDef* htim_a, TIM_HandleTypeDef* htim_b,
                 uint16_t TIM_CLOCKSOURCE_ITRx, uint16_t count_offset,
                 TIM_HandleTypeDef* htim_refbase = nullptr);
void start_general_purpose_adc();
float get_adc_voltage(Stm32Gpio gpio);
uint16_t channel_from_gpio(Stm32Gpio gpio);
float get_adc_voltage_channel(uint16_t channel);
void pwm_in_init();
void start_analog_thread();

void update_brake_current();

#ifdef __cplusplus
}
#endif

#endif //__LOW_LEVEL_H
