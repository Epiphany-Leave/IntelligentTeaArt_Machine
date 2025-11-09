#ifndef __COMMOND_H__
#define __COMMOND_H__

#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "beep_bsp.h"
#include "lcd_bsp.h"

#include "key_driver.h"
#include "adc_driver.h"
#include "pwm_driver.h"
#include "lcd_driver.h"
#include "vofa.h"

#include "app.h"

//#include <stdio.h>
#include <string.h>

#define CCMRAM  __attribute__((section("ccmram")))

#endif /* __COMMOND_H__ */

