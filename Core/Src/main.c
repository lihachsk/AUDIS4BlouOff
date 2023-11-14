#include "main.h"

__INLINE void delay(__IO uint32_t tck)
{
  while (tck)
  {
    tck--;
  }
}

uint8_t buttonState = 0;

int main(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB, GPIO_Pin_13);

  while (1)
  {
    delay(500000);
    buttonState = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);

    if (buttonState == 1)
    {
      GPIO_ResetBits(GPIOB, GPIO_Pin_13);
    }
    else
    {
      GPIO_SetBits(GPIOB, GPIO_Pin_13);
    }
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
