#include <stdint.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include "core/system.h"

/* On NUCLEO-F303K8, Arduino D7 maps to PF0. */
#define LED_PORT GPIOF
#define LED_PIN GPIO0
#define LED_RCC RCC_GPIOF
#define BLINK_INTERVAL_MS 500U


static void gpio_setup(void)
{
    rcc_periph_clock_enable(LED_RCC);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
    gpio_set_output_options(LED_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED_PIN);
}


static void delay_ms(uint32_t milliseconds)
{
    uint32_t start = system_millis;
    while ((uint32_t)(system_millis - start) < milliseconds) {
    }
}

int main(void)
{
    system_setup();
    gpio_setup();

    while (1) {
        gpio_toggle(LED_PORT, LED_PIN);
        delay_ms(BLINK_INTERVAL_MS);
    }
}
