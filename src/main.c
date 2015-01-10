#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "dma1.h"

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
__IO TestStatus  TransferStatus = FAILED;
const uint32_t SRC_Const_Buffer[BUFFER_SIZE]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
uint32_t DST_Buffer[BUFFER_SIZE];
void DMA_Config(void);
TestStatus Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);

int main(void)
{
	 STM_EVAL_LEDInit(LED4);
	  STM_EVAL_LEDInit(LED3);
	  STM_EVAL_LEDInit(LED5);
	  STM_EVAL_LEDInit(LED6);

	STM_EVAL_LEDOn(LED4); //MEMORY TO MEMORY BASLADIGINDA LED4 YANSIN
	DMA_Config();
	STM_EVAL_LEDOn(LED3); // LED 4 YANICAK VE TRANSFERIN BASLADIGINI GÖRECEGIZ
	 while (DMA_GetCmdStatus(DMA_STREAM) != DISABLE)
	 {

	 }
	 TransferStatus = Buffercmp(SRC_Const_Buffer, DST_Buffer, BUFFER_SIZE);
	 /* TransferStatus = PASSED, if the transmitted and received data
	      are the same */
	   /* TransferStatus = FAILED, if the transmitted and received data
	      are different */
	if(TransferStatus!=FAILED)
	{
		STM_EVAL_LEDOn(LED6); // iletim gerceklestiyse led 6 u yak
	}
	while(1)
	{

	}
}

void DMA_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;
	 __IO uint32_t    Timeout = TIMEOUT_MAX;

	 RCC_AHB1PeriphClockCmd(DMA_STREAM_CLOCK, ENABLE);//DMA CLOCK AKTIF EDÝLDÝ

	DMA_DeInit(DMA_STREAM);

	while(DMA_GetCmdStatus(DMA_STREAM)!=DISABLE)
	{

	}
	//DMA AYARLARINI YAPALIM

	 DMA_InitStructure.DMA_Channel = DMA_CHANNEL;
	  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SRC_Const_Buffer;
	  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)DST_Buffer;
	  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;
	  DMA_InitStructure.DMA_BufferSize = (uint32_t)BUFFER_SIZE;
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	  DMA_Init(DMA_STREAM, &DMA_InitStructure);

	DMA_ITConfig(DMA_STREAM,DMA_IT_TC,ENABLE);

	DMA_Cmd(DMA_STREAM,ENABLE);
	Timeout = TIMEOUT_MAX;

	while((DMA_GetCmdStatus(DMA_STREAM)!=ENABLE)&&(Timeout-->0))
	{

	}

	if(Timeout==0)
	{
		while(1)
		{

		}
	}
	//DMA ÝÇÝN KESMELER AYARLARI
	NVIC_InitStructure.NVIC_IRQChannel=DMA_STREAM_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

TestStatus Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer != *pBuffer1)
    {
      return FAILED;
    }

    pBuffer++;
    pBuffer1++;
  }

  return PASSED;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
    return 0; // ses çipini kullanýyorsanýz tek sample veriyi burada return ile döndürün.
}
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
    return; // ses çipini kullanýyorsanýz  burada çipe veri aktarýmý DMA sona ermiþ
}

