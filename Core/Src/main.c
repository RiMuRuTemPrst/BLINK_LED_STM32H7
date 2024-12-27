#include "stm32h750xx.h"

// Function prototypes
void SystemClock_Config(void);
void GPIO_Init(void);
void delay_ms(uint32_t ms);

int main(void)
{
    SystemClock_Config(); // Cấu hình clock
    GPIO_Init();          // Khởi tạo GPIO

    while (1)
    {
        GPIOE->ODR ^= GPIO_ODR_OD3; // Toggle LED
        delay_ms(500);             // Delay 500ms
    }
}

void GPIO_Init(void)
{
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN; // Bật clock GPIOE

    GPIOE->MODER &= ~GPIO_MODER_MODE3;   // Clear mode bits cho PE3
    GPIOE->MODER |= GPIO_MODER_MODE3_0; // Set PE3 làm output
    GPIOE->OTYPER &= ~GPIO_OTYPER_OT3;  // Push-pull
    GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED3; // High speed
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD3;  // No pull-up, pull-down
}

void delay_ms(uint32_t ms)
{
    uint32_t count = ms * (SystemCoreClock / 20000); // Tính theo tần số thực tế
    for (uint32_t i = 0; i < count; i++)
    {
        __NOP(); // Waste one clock cycle
    }
}

void SystemClock_Config(void)
{
//    RCC->CR |= RCC_CR_HSION;
//    while (!(RCC->CR & RCC_CR_HSIRDY));
//
//    RCC->PLLCKSELR = RCC_PLLCKSELR_PLLSRC_HSI
//                    | (8 << RCC_PLLCKSELR_DIVM1_Pos);
//    RCC->PLLCFGR = 0;
//    RCC->PLL1DIVR = (199 << RCC_PLL1DIVR_N1_Pos)
//                   | (1 << RCC_PLL1DIVR_P1_Pos);
//    RCC->PLLCFGR |= RCC_PLLCFGR_PLL1RGE_2
//                   | RCC_PLLCFGR_PLL1VCOSEL
//                   | RCC_PLLCFGR_DIVP1EN;
//
//    RCC->CR |= RCC_CR_PLL1ON;
//    while (!(RCC->CR & RCC_CR_PLL1RDY));
//
//    RCC->CFGR |= RCC_CFGR_SW_PLL1;
//    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL1);
//
//    SystemCoreClockUpdate();
}
