/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#endif

#include "rt_hw_led.h"


ALIGN(RT_ALIGN_SIZE)

/* 线程句柄声明*/
static struct rt_thread thread_led1;
static struct rt_thread thread_led2;

/* 线程堆栈声明 */
static rt_uint8_t thread_led1_stack[ 512 ];
static rt_uint8_t thread_led2_stack[ 512 ];

/* led1 线程函数入口 */
static void thread_led1_entry(void* parameter)
{
    rt_hw_led_init();
    while (1)
    {
        /* led1 on */
        rt_hw_led_on(1);
        rt_thread_delay( 100 ); /* sleep 0.5 second and switch to other thread */

        /* led1 off */
        rt_hw_led_off(1);
        rt_thread_delay( 100);
    }
}
/* led1 线程函数入口 */
static void thread_led2_entry(void* parameter)
{

    while (1)
    {
        /* led2 on */
        rt_hw_led_on(2);
        rt_thread_delay( 500 ); /* sleep 0.5 second and switch to other thread */

        /* led2 off */
        rt_hw_led_off(2);
        rt_thread_delay( 500 );
    }
}


int rt_application_init()
{
	rt_err_t result;
    /* 初始化 led1 thread */
	result = rt_thread_init(&thread_led1,
                          "led1",
                          thread_led1_entry, 
                          RT_NULL,
                          (rt_uint8_t*)&thread_led1_stack[0], 
                          sizeof(thread_led1_stack), 
                          20, 
                          5);
	if (result == RT_EOK)
        rt_thread_startup(&thread_led1);
    else
        return -1;
  /* 初始化 led2 thread */
	result = rt_thread_init(&thread_led2,
                          "led2",
                          thread_led2_entry, 
                           RT_NULL,
                          (rt_uint8_t*)&thread_led2_stack[0], 
                          sizeof(thread_led2_stack), 
                          22, 
                          5);
	if (result == RT_EOK)
        rt_thread_startup(&thread_led2);
    else
        return -1;
  
	return 0;
}


/*@}*/
