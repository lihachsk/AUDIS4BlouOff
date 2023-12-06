#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <stdio.h>

typedef struct
{
  GPIO_TypeDef *GPIOx;
  uint16_t pin;
}blinkingPin;

void initPis_out(blinkingPin pins[], uint32_t RCC_APB2Periph_GPIOx, int length);
void initB13_Out();
void switchState();
void lightPin(blinkingPin obj);
void offPin(blinkingPin obj);
