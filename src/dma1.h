/*
 * dma1.h
 *
 *  Created on: Mar 17, 2013
 *      Author: Kaan
 */

#ifndef DMA1_H_
#define DMA1_H_

#define DMA_STREAM               DMA2_Stream0
#define DMA_CHANNEL              DMA_Channel_0
#define DMA_STREAM_CLOCK         RCC_AHB1Periph_DMA2
#define DMA_STREAM_IRQ           DMA2_Stream0_IRQn
#define DMA_IT_TCIF              DMA_IT_TCIF0
#define DMA_STREAM_IRQHANDLER    DMA2_Stream0_IRQHandler

#define BUFFER_SIZE              32
#define TIMEOUT_MAX              10000 /* Maximum timeout value */

#endif /* DMA1_H_ */
