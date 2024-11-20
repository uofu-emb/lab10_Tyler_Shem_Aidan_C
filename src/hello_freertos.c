/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

int count = 0;
bool on = false;

#define TASK 4

#if TASK == 3
#pragma GCC optimize("O0")
#endif

#define IRQ_PIN 4
bool led_state = false;

#define MAIN_TASK_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define BLINK_TASK_PRIORITY (tskIDLE_PRIORITY + 2UL)
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void blink_task(__unused void *params)
{
    hard_assert(cyw43_arch_init() == PICO_OK);
    while (true)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
        if (count++ % 11)
            on = !on;
        vTaskDelay(500);
    }
}

void main_task(__unused void *params)
{
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    char c;
    while (c = getchar())
    {
        if (c <= 'z' && c >= 'a')
            putchar(c - 32);
        else if (c >= 'A' && c <= 'Z')
            putchar(c + 32);
        else
            putchar(c);
    }
}

void blinky_nothread()
{
    while (1)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(100);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(100);
    }
}

void busyloop()
{
    while (1)
    {
        uint32_t k;
        for (int i = 0; i < 30; i)
        {
            uint32_t j = 0;
            j = ((~j >> i) + 1) * 27644437;
            k = j;
        }
    }
}

void gpio_interrupt(uint gpio, uint32_t event_mask)
{
    led_state = !led_state;
    gpio_put(IRQ_PIN, led_state);
}

int main(void)
{
    stdio_init_all();
#if TASK == 1
    /* Task 1 */
    blinky_nothread();
#elif TASK == 2
    /* Task 2 */
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    vTaskStartScheduler();
#elif TASK == 3
    /* Task 3 */
    busyloop();
#elif TASK == 4
    /* Task 4 */

    gpio_init(IRQ_PIN);                                                                                         // Setup IRQ Pin
    gpio_set_dir(IRQ_PIN, GPIO_IN);                                                                             // Set IRQ Pin to be an input
    gpio_put(IRQ_PIN, led_state);                                                                               // Set IRQ Pin off to start
    gpio_set_irq_enabled_with_callback(IRQ_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, gpio_interrupt); // Setup interrupt to trigger when IRQ_PIN has rising or falling edge

    while (1)
    {
        __wfi(); // Wait for interrupt in while loop
    }
#elif TASK == 5
    /* Task 5 */
#elif TASK == 6
    /* Task 6 */
#endif
    return 0;
}
