#include "can.h"
int8_t countError = 0;

void Error_Handler()
{
    countError++;
}
void canDeInit()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* Configure CAN pin: TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
    
    CAN_InitTypeDef canInit;

    CAN_DeInit(CAN1);
    CAN_StructInit(&canInit);
    
    canInit.CAN_Prescaler = 18;
    canInit.CAN_Mode = CAN_Mode_Normal;
    canInit.CAN_SJW = CAN_SJW_1tq;
    canInit.CAN_BS1 = CAN_BS1_2tq;
    canInit.CAN_BS2 = CAN_BS2_1tq;
    canInit.CAN_TTCM = DISABLE;
    canInit.CAN_ABOM = ENABLE;
    canInit.CAN_AWUM = DISABLE;
    canInit.CAN_NART = DISABLE;
    canInit.CAN_RFLM = DISABLE;
    canInit.CAN_TXFP = DISABLE;

    if (CAN_Init(CAN1, &canInit) != CAN_InitStatus_Success)
    {
        Error_Handler();
    }

    canFilterDeInit();
    NVIC_Config();
}

void canFilterDeInit()
{
    CAN_FilterInitTypeDef canFilterInit;

    canFilterInit.CAN_FilterActivation = ENABLE;

    canFilterInit.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    canFilterInit.CAN_FilterIdHigh = 0x446 << 5;
    canFilterInit.CAN_FilterIdLow = 0;
    canFilterInit.CAN_FilterMaskIdHigh = 0x446 << 5;
    canFilterInit.CAN_FilterMaskIdLow = 0x0000;
    canFilterInit.CAN_FilterMode = CAN_FilterMode_IdMask;
    canFilterInit.CAN_FilterScale = CAN_FilterScale_32bit;
    canFilterInit.CAN_FilterNumber = 0;

    CAN_FilterInit(&canFilterInit);
}

void NVIC_Config(void)
{
    NVIC_InitTypeDef  NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn; //USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    SET_BIT(CAN1->IER, CAN_IER_FMPIE0); //Set FIFO0 message pending IT enable
 
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0x01);   
}

void USB_LP_CAN1_RX0_IRQHandler(void)
//void CAN1_RX0_IRQHandler(void)
{
    CanRxMsg RxMessage;
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
    if ((RxMessage.StdId == 0x446)&&(RxMessage.IDE == CAN_ID_STD) && (RxMessage.DLC == 1))
    {
        switchState();
    }
}
