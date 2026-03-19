#include <stdint.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#define LED_PORT GPIOB
#define LED_PIN GPIO3
#define LED_RCC RCC_GPIOB
#define BLINK_INTERVAL_MS 2000U

static volatile uint32_t system_millis;

static void clock_setup(void)
{
    rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_48MHZ]);
}

static void gpio_setup(void)
{
    rcc_periph_clock_enable(LED_RCC);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
    gpio_set_output_options(LED_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED_PIN);
}

static void systick_setup(void)
{
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
    systick_set_reload((rcc_ahb_frequency / 8U / 1000U) - 1U);
    systick_interrupt_enable();
    systick_counter_enable();
}

void sys_tick_handler(void)
{
    system_millis++;
}

static void delay_ms(uint32_t milliseconds)
{
    uint32_t start = system_millis;
    while ((uint32_t)(system_millis - start) < milliseconds) {
    }
}

int main(void)
{
    clock_setup();
    gpio_setup();
    systick_setup();

    while (1) {
        gpio_toggle(LED_PORT, LED_PIN);
        delay_ms(BLINK_INTERVAL_MS);
    }
}
