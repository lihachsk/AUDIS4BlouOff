#include "rcc.h"

void rccDeInit()
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    RCC->CR |= ((uint32_t)RCC_CR_HSEON); 
    do
    {
      HSEStatus = RCC->CR & RCC_CR_HSERDY;
      StartUpCounter++;  
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    FLASH->ACR &= ~FLASH_ACR_PRFTBE;
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    RCC->CFGR &= ~RCC_CFGR_HPRE;
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    RCC->CFGR &= ~RCC_CFGR_PPRE2;
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

    RCC->CFGR &= ~RCC_CFGR_PPRE1;
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL,
    RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9);

    RCC->CR |= RCC_CR_PLLON;

    while((RCC->CR & RCC_CR_PLLRDY) == 0){}
    
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08){}
}