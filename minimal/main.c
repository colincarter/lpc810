#include "LPC8xx.h"
#include "core_cmInstr.h"

#define LED             (2)
#define _SYSTEM_CLOCK   (12000000UL)

void delay(uint32_t ticks);

int main(void)
{
    // Enable GPIO clock and reset GPIO
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 6);
    LPC_SYSCON->PRESETCTRL &= ~(1 << 10);
    LPC_SYSCON->PRESETCTRL |= (1 << 10);

    LPC_SWM->PINASSIGN0 = 0xffff0004UL;
    LPC_SWM->PINENABLE0 = 0xffffffbfUL;

    LPC_GPIO_PORT->DIR0 |= (1 << LED);

    // SysTick config
    // Enable, interrupts, use clock
    SysTick->VAL    = 0;
    SysTick->LOAD   = ((_SYSTEM_CLOCK / 1000) * 1) - 1; // 1ms
    SysTick->CTRL   |= (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk);


    while(1)
    {
        LPC_GPIO_PORT->CLR0 = (1 << LED);

        delay(1000);

        LPC_GPIO_PORT->SET0 = (1 << LED);

        delay(1000);
    }
}

void delay(uint32_t ticks)
{
    while(--ticks)
    {
        __WFI();
    }
}

void SysTick_Handler(void)
{
}
