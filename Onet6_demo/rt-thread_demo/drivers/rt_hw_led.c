/*
 * File      : led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */
#include <rtthread.h>
#include <stm32f10x.h>


#define led1_rcc                    RCC_APB2Periph_GPIOA
#define led1_gpio                   GPIOA
#define led1_pin                    (GPIO_Pin_8)

#define led2_rcc                    RCC_APB2Periph_GPIOD
#define led2_gpio                   GPIOD
#define led2_pin                    (GPIO_Pin_2)

/* rt_hw_led.c */
void rt_hw_led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin   = led1_pin;
    GPIO_Init(led1_gpio, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = led2_pin;
    GPIO_Init(led2_gpio, &GPIO_InitStructure);
}

void rt_hw_led_on(rt_uint32_t n)
{
    switch (n)
    {
    case 1:
        GPIO_SetBits(led1_gpio, led1_pin);
        break;
    case 2:
        GPIO_SetBits(led2_gpio, led2_pin);
        break;
    default:
        break;
    }
}

void rt_hw_led_off(rt_uint32_t n)
{
    switch (n)
    {
    case 1:
        GPIO_ResetBits(led1_gpio, led1_pin);
        break;
    case 2:
        GPIO_ResetBits(led2_gpio, led2_pin);
        break;
    default:
        break;
    }
}
