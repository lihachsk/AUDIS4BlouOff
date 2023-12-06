#include "blinking.h"

uint8_t buttonState = 0;

void initPis_out(blinkingPin pins[], uint32_t RCC_APB2Periph_GPIOx, int length)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     
  for (int i = 0; i < length; i++)
  {
    GPIO_InitStructure.GPIO_Pin = pins[i].pin;
    GPIO_Init(pins[i].GPIOx, &GPIO_InitStructure);
  }
}
void initB13_Out()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void lightPin(blinkingPin obj)
{
  uint8_t pinState = GPIO_ReadInputDataBit(obj.GPIOx, obj.pin);

  if (pinState == 0)
  {
    GPIO_SetBits(obj.GPIOx, obj.pin);
  }
}
void offPin(blinkingPin obj)
{
  uint8_t pinState = GPIO_ReadInputDataBit(obj.GPIOx, obj.pin);

  if (pinState == 1)
  {
    GPIO_ResetBits(obj.GPIOx, obj.pin);
  }
}
void switchState()
{ 
  buttonState = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);

  if (buttonState == 1)
  {
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
  }
  else
  {
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
  }
}