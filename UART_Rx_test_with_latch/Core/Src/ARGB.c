/**
 *******************************************
 * @file    ARGB.c
 * @author  Dmitriy Semenov / Crazy_Geeks
 * @version 1.31
 * @date	21-November-2021
 * @brief   Source file for ARGB (Adreassable RGB)
 *******************************************
 *
 * @note Repo: https://github.com/Crazy-Geeks/STM32-ARGB-DMA
 * @note RU article: https://crazygeeks.ru/stm32-argb-lib
 */

/* WS2811 Timings
 * Tolerance: +/- 150ns <-> +/- 0.15us
 * RES: >50us
 *
 * Slow mode:
 * Period: 2.5us <-> 400 KHz
 * T0H: 0.5us
 * T1H: 1.2us
 * T0L: 2.0us
 * T1L: 1.3us
 *
 * Fast mode:
 * Period: 1.25us <-> 800 KHz
 * T0H: 0.25us - 20%
 * T1H: 0.6us  - 48%
 * T0L: 1.0us
 * T1H: 0.65us
 *
 */

/* WS2811 Timings
 * Tolerance: +/- 150ns <-> +/- 0.15us
 * RES: >50us

 * Period: 1.25us <-> 800 KHz
 * T0H: 0.35us - 20%
 * T1H: 0.7us  - 48%
 * T0L: 0.8us
 * T1H: 0.6us
 *
 */

#include "ARGB.h"  // include header file
#include "math.h"

extern TIM_HandleTypeDef (TIM_HANDLE);  ///< Timer handler
extern DMA_HandleTypeDef (DMA_HANDLE);  ///< DMA handler

volatile u8_t PWM_HI;    ///< PWM Code HI Log.1 period
volatile u8_t PWM_LO;    ///< PWM Code LO Log.1 period

volatile u16_t NUM_PIXELS = 0;
#define NUM_BYTES (3 * NUM_PIXELS) ///< Strip size in bytes
#define PWM_BUF_LEN (3 * 8 * 2)    ///< Pack len * 8 bit * 2 LEDs

/// Static LED buffer
// volatile u8_t RGB_BUF[NUM_BYTES] = {0,};
volatile u8_t* RGB_BUF = 0;

/// Timer PWM value buffer
volatile u8_t PWM_BUF[PWM_BUF_LEN] = {0,};
/// PWM buffer iterator
volatile u16_t BUF_COUNTER = 0;

volatile ARGB_STATE ARGB_LOC_ST; ///< Buffer send status

// Callbacks
static void ARGB_TIM_DMADelayPulseCplt(DMA_HandleTypeDef *hdma);
static void ARGB_TIM_DMADelayPulseHalfCplt(DMA_HandleTypeDef *hdma);
/// @} //Private

/**
 * @brief Init timer & prescalers
 * @param none
 * @return #ARGB_STATE enum
 */
ARGB_STATE ARGB_Init(void) {
    /* Auto-calculation! */
    u32_t APBfq; // Clock freq
#ifdef APB1
    APBfq = HAL_RCC_GetPCLK1Freq();
    APBfq *= (RCC->CFGR & RCC_CFGR_PPRE1) == 0 ? 1 : 2;
#endif
    APBfq /= (uint32_t) (800 * 1000);  // 800 KHz - 1.25us

    TIM_HANDLE.Instance->PSC = 0;                        // dummy hardcode now
    TIM_HANDLE.Instance->ARR = (uint16_t) (APBfq - 1);   // set timer prescaler
    TIM_HANDLE.Instance->EGR = 1;                        // update timer registers

#ifdef WS2812
    PWM_HI = (u8_t) (APBfq * 0.56) - 1;     // Log.1 - 56% - 0.70us
    PWM_LO = (u8_t) (APBfq * 0.28) - 1;     // Log.0 - 28% - 0.35us
#endif

    ARGB_LOC_ST = ARGB_READY; // Set Ready Flag
    TIM_CCxChannelCmd(TIM_HANDLE.Instance, TIM_CH, TIM_CCx_ENABLE); // Enable GPIO to IDLE state
    HAL_Delay(1); // Make some delay
    return ARGB_OK;
}

/**
 * @brief Set LED with RGB color by index
 * @param[in] i LED position
 * @param[in] r Red component   [0..255]
 * @param[in] g Green component [0..255]
 * @param[in] b Blue component  [0..255]
 * @return #ARGB_STATE enum
 */
// ARGB_STATE ARGB_SetRGB(u16_t i, u8_t r, u8_t g, u8_t b) {
//     // Subpixel chain order
//     const u8_t subp1 = g;
//     const u8_t subp2 = r;
//     const u8_t subp3 = b;
//     // RGB or RGBW
//     RGB_BUF[3 * i] = subp1;     // subpixel 1
//     RGB_BUF[3 * i + 1] = subp2; // subpixel 2
//     RGB_BUF[3 * i + 2] = subp3; // subpixel 3
//     return ARGB_OK;
// }

/**
 * @brief Update strip
 * @param none
 * @return #ARGB_STATE enum
 */
// ARGB_STATE ARGB_Show(void) {
ARGB_STATE ARGB_Show(u8_t* buf, u16_t num_pixels) {
    RGB_BUF = buf;
    NUM_PIXELS = num_pixels;

    ARGB_LOC_ST = ARGB_BUSY;
    if (BUF_COUNTER != 0 || DMA_HANDLE.State != HAL_DMA_STATE_READY) {
        return ARGB_BUSY;
    } else {
        for (volatile u8_t i = 0; i < 8; i++) {
            // set first transfer from first values
            PWM_BUF[i] = (((RGB_BUF[0] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
            PWM_BUF[i + 8] = (((RGB_BUF[1] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
            PWM_BUF[i + 16] = (((RGB_BUF[2] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
            PWM_BUF[i + 24] = (((RGB_BUF[3] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
            PWM_BUF[i + 32] = (((RGB_BUF[4] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
            PWM_BUF[i + 40] = (((RGB_BUF[5] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
        }

        HAL_StatusTypeDef DMA_Send_Stat = HAL_ERROR;
        while (DMA_Send_Stat != HAL_OK) {

            if (TIM_CHANNEL_STATE_GET(&TIM_HANDLE, TIM_CH) == HAL_TIM_CHANNEL_STATE_BUSY) {
                DMA_Send_Stat = HAL_BUSY;
                continue;
            } else if (TIM_CHANNEL_STATE_GET(&TIM_HANDLE, TIM_CH) == HAL_TIM_CHANNEL_STATE_READY) {
                TIM_CHANNEL_STATE_SET(&TIM_HANDLE, TIM_CH, HAL_TIM_CHANNEL_STATE_BUSY);
            } else {
                DMA_Send_Stat = HAL_ERROR;
                continue;
            }

#define ARGB_TIM_DMA_ID TIM_DMA_ID_CC1
#define ARGB_TIM_DMA_CC TIM_DMA_CC1
#define ARGB_TIM_CCR CCR1
            TIM_HANDLE.hdma[ARGB_TIM_DMA_ID]->XferCpltCallback = ARGB_TIM_DMADelayPulseCplt;
            TIM_HANDLE.hdma[ARGB_TIM_DMA_ID]->XferHalfCpltCallback = ARGB_TIM_DMADelayPulseHalfCplt;
            TIM_HANDLE.hdma[ARGB_TIM_DMA_ID]->XferErrorCallback = TIM_DMAError;
            if (HAL_DMA_Start_IT(TIM_HANDLE.hdma[ARGB_TIM_DMA_ID], (u32_t) PWM_BUF,
                                 (u32_t) &TIM_HANDLE.Instance->ARGB_TIM_CCR,
                                 (u16_t) PWM_BUF_LEN) != HAL_OK) {
                DMA_Send_Stat = HAL_ERROR;
                continue;
            }
            __HAL_TIM_ENABLE_DMA(&TIM_HANDLE, ARGB_TIM_DMA_CC);
            if (IS_TIM_BREAK_INSTANCE(TIM_HANDLE.Instance) != RESET)
                __HAL_TIM_MOE_ENABLE(&TIM_HANDLE);
            if (IS_TIM_SLAVE_INSTANCE(TIM_HANDLE.Instance)) {
                u32_t tmpsmcr = TIM_HANDLE.Instance->SMCR & TIM_SMCR_SMS;
                if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
                    __HAL_TIM_ENABLE(&TIM_HANDLE);
            } else
                __HAL_TIM_ENABLE(&TIM_HANDLE);
            DMA_Send_Stat = HAL_OK;
        }
        BUF_COUNTER = 2;

        return ARGB_OK;
    }
}

/* DMA CALLBACKS */

/**
  * @brief  TIM DMA Delay Pulse complete callback.
  * @param  hdma pointer to DMA handle.
  * @retval None
  */
static void ARGB_TIM_DMADelayPulseCplt(DMA_HandleTypeDef *hdma) {
    TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *) ((DMA_HandleTypeDef *) hdma)->Parent;

    // hdma == htim->hdma[TIM_DMA_ID_CC1]
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;

    if (hdma->Init.Mode == DMA_NORMAL) {
        TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
    }
// if data transfer
    if (BUF_COUNTER < NUM_PIXELS) {
        // fill second part of buffer
        for (volatile u8_t i = 0; i < 8; i++) {
            PWM_BUF[i + 24] = (((RGB_BUF[3 * BUF_COUNTER] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
            PWM_BUF[i + 32] = (((RGB_BUF[3 * BUF_COUNTER + 1] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
            PWM_BUF[i + 40] = (((RGB_BUF[3 * BUF_COUNTER + 2] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
        }
        BUF_COUNTER++;
    } else if (BUF_COUNTER < NUM_PIXELS + 2) { // if RET transfer
        memset((u8_t *) &PWM_BUF[PWM_BUF_LEN / 2], 0, PWM_BUF_LEN / 2); // second part
        BUF_COUNTER++;
    } else { // if END of transfer
        BUF_COUNTER = 0;

        // STOP DMA:
#if TIM_CH == TIM_CHANNEL_1
        __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC1);
        (void) HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC1]);
#endif
        if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET) {
            /* Disable the Main Output */
            __HAL_TIM_MOE_DISABLE(htim);
        }

        /* Disable the Peripheral */
        __HAL_TIM_DISABLE(htim);

        /* Set the TIM channel state */
        TIM_CHANNEL_STATE_SET(htim, TIM_CH, HAL_TIM_CHANNEL_STATE_READY);
        ARGB_LOC_ST = ARGB_READY;
    }

    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
}


/**
  * @brief  TIM DMA Delay Pulse half complete callback.
  * @param  hdma pointer to DMA handle.
  * @retval None
  */
static void ARGB_TIM_DMADelayPulseHalfCplt(DMA_HandleTypeDef *hdma) {
    TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *) ((DMA_HandleTypeDef *) hdma)->Parent;
    // if wrong handlers
    if (hdma != &DMA_HANDLE || htim != &TIM_HANDLE) return;

    // if data transfer
    if (BUF_COUNTER < NUM_PIXELS) {
        // fill first part of buffer
        for (volatile u8_t i = 0; i < 8; i++) {
            PWM_BUF[i] = (((RGB_BUF[3 * BUF_COUNTER] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
            PWM_BUF[i + 8] = (((RGB_BUF[3 * BUF_COUNTER + 1] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
            PWM_BUF[i + 16] = (((RGB_BUF[3 * BUF_COUNTER + 2] << i) & 0x80) > 0) ? PWM_HI : PWM_LO;
        }
        BUF_COUNTER++;
    } else if (BUF_COUNTER < NUM_PIXELS + 2) { // if RET transfer
        memset((u8_t *) &PWM_BUF[0], 0, PWM_BUF_LEN / 2); // first part
        BUF_COUNTER++;
    }
}
