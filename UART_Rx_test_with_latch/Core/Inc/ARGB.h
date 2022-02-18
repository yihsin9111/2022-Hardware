
#ifndef ARGB_H_
#define ARGB_H_

#include "libs.h"

#define WS2812

// #define NUM_PIXELS 144 ///< Pixel quantity

#define TIM_HANDLE htim1  ///< Timer Channel
#define APB1    /// Timer's RCC Bus
#define TIM_CH	   TIM_CHANNEL_1  ///< Timer's PWM channel
#define DMA_HANDLE hdma_tim1_ch1  ///< DMA Channel
// DMA channel can be found in main.c / tim.c

typedef enum ARGB_STATE {
    ARGB_BUSY = 0,  ///< DMA Transfer in progress
    ARGB_READY = 1, ///< DMA Ready to transfer
    ARGB_OK = 2,    ///< Function execution success
    ARGB_PARAM_ERR = 3, ///< Error in input parameters
} ARGB_STATE;

ARGB_STATE ARGB_Init(void);   // Initialization

//ARGB_STATE ARGB_SetBrightness(u8_t br); // Set global brightness
// ARGB_STATE ARGB_SetRGB(u16_t i, u8_t r, u8_t g, u8_t b);  // Set single LED by RGB

ARGB_STATE ARGB_Fire(u8_t*, u16_t); // Push data to the strip

#endif /* ARGB_H_ */
