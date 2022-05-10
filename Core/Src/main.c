#include "stm32wb55xx.h"
#include "core_cm4.h"
#include <stdint.h>

#define _RCC_BASE 0x58000000
#define _RCC_AHB2ENR *(volatile uint32_t*)(_RCC_BASE + 0x04C)

#define _GPIOA_BASE 0x48000000
#define _GPIOA_MODER *(volatile uint32_t*)_GPIOA_BASE
#define _GPIOA_ODR *(volatile uint32_t*)(_GPIOA_BASE + 0x14)

#define _GPIOC_BASE 0x48000800
#define _GPIOC_MODER *(volatile uint32_t*)_GPIOC_BASE
#define _GPIOC_PUPDR *(volatile uint32_t*)(_GPIOC_BASE + 0x0C)

#define _SYSCFG_BASE 0x40010000
#define _SYSCFG_EXTICR1 *(volatile uint32_t*)(_SYSCFG_BASE + 0x008)

#define _EXTI_BASE 0x58000800
#define _EXTI_FTSR1 *(volatile uint32_t*)(_EXTI_BASE + 0x004)
#define _EXTI_PR1 *(volatile uint32_t*)(_EXTI_BASE + 0x00C)
#define _EXTI_IMR1 *(volatile uint32_t*)(_EXTI_BASE + 0x080)

// interrupt implementation
void EXTI2_IRQHandler(void)
{
    _GPIOA_ODR ^= (1 << 1); // toggle PA1
    _EXTI_PR1 = (1 << 2); // reset interrupt state
}

int main(void)
{

    // enable GPIOA and GPIOC port clocks
    _RCC_AHB2ENR &= (0b000 << 0); // reset pin
    _RCC_AHB2ENR |= (0b101 << 0); // enable GPIOA + GPIOC clock

    // set PA1 as output
    _GPIOA_MODER &= (0b00 << 2); // reset pin
    _GPIOA_MODER |= (0b01 << 2); // configure PA1 as output

    // set PC2 as input with pull down
    _GPIOC_MODER &= (0b00 << 4); // configure PC2 as input
    _GPIOC_PUPDR &= (0b00 << 4); // reset pin
    _GPIOC_PUPDR |= (0b10 << 4); // use (weak) internal pull down resistor

    // set PC2 as interrupt
    _SYSCFG_EXTICR1 &= (0b000 << 8); // reset pins
    _SYSCFG_EXTICR1 |= (0b010 << 8); // configure PC2 to allow interrupts

    _EXTI_FTSR1 &= (0 << 2); // reset pin
    _EXTI_FTSR1 |= (1 << 2); // enable falling trigger (1 -> 0) for interrupt

    _EXTI_IMR1 &= (0 << 2); // reset pin
    _EXTI_IMR1 |= (1 << 2); // unmask line 2 for interrupts

    // setup NVIC for interrupts
    NVIC_SetPriority(EXTI2_IRQn, 0x00);
    NVIC_EnableIRQ(EXTI2_IRQn);

    while(1) {}

    return 0;
}