#ifndef _TIM_INTERRUPT_H_
#define _TIM_INTERRUPT_H_

#include "main.h"
#include "tim.h"
#include "commond.h"

#define CLAMP(x, min, max) ({          \
    typeof(x) __x = (x);               \
    typeof(min) __min = (min);         \
    typeof(max) __max = (max);         \
    (void)(&__x == &__min);            \
    (void)(&__x == &__max);            \
    (__x < __min) ? __min : ((__x > __max) ? __max : __x); \
})

typedef struct
{
    uint8_t ms_1;
    uint8_t ms_10;
    uint8_t ms_50;
    uint16_t time;
}delay_time;

extern delay_time delay;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void delay_handle(void);


#endif
