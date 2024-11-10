#include <hardware/adc.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <print>

int main() {
    stdio_init_all();
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);
    while (1) {
        const float conv_factor = 3.3f / (1 << 12);
        uint16_t result = adc_read();
        std::println("Raw value: {:#05x}, voltage: {:3f} V", result,
                     result * conv_factor);
        sleep_ms(500);
    }
}
