/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "GC9A01.h"
#include "MAX30102.h"
#include "pic.h"

#include "i2c.h"
#include "arm_math.h"
#include "arm_const_structs.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define TEST_LENGTH_SAMPLES 256
#define TEST_LENGTH_SAMPLES 1024
#define BLOCK_SIZE 1
//#define NUM_TAPS 31
#define NUM_TAPS 29
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void arm_fir_f32_lp(void);
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
//const float32_t firCoeffs32LP[NUM_TAPS] = {
//        -0.0004462581419, 0.0002078039979, 0.001277646632, 0.003248555353, 0.006549410056,
//        0.0114874132, 0.01819461212, 0.02659362927, 0.03638776392, 0.04707768187,
//        0.05800359696, 0.06840851903, 0.0775154531, 0.08460960537, 0.08911559731,
//        0.0906606093, 0.08911559731, 0.08460960537, 0.0775154531, 0.06840851903,
//        0.05800359696, 0.04707768187, 0.03638776392, 0.02659362927, 0.01819461212,
//        0.0114874132, 0.006549410056, 0.003248555353, 0.001277646632, 0.0002078039979,
//        -0.0004462581419};
const float32_t firCoeffs32BP[NUM_TAPS] = {
        0.003531039227f, 0.0002660876198f, -0.001947779674f, 0.001266813371f, -0.008019094355f,
        -0.01986379735f, 0.01018396299f, 0.03163734451f, 0.00165955862f, 0.03312643617f,
        0.0622616075f, -0.1229852438f, -0.2399847955f, 0.07637182623f, 0.3482480049f,
        0.07637182623f, -0.2399847955f, -0.1229852438f, 0.0622616075f, 0.03312643617f,
        0.00165955862f, 0.03163734451f, 0.01018396299f, -0.01986379735f, -0.008019094355f,
        0.001266813371f, -0.001947779674f, 0.0002660876198f, 0.003531039227f
};
uint32_t blockSize = BLOCK_SIZE;
uint32_t numBlocks = TEST_LENGTH_SAMPLES / BLOCK_SIZE;

static float32_t testInput_f32[TEST_LENGTH_SAMPLES];
static float32_t testOutput[TEST_LENGTH_SAMPLES];
static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
        .name = "defaultTask",
        .stack_size = 128 * 4,
        .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for signalTask */
osThreadId_t signalTaskHandle;
const osThreadAttr_t signalTask_attributes = {
        .name = "signalTask",
        .stack_size = 128 * 4,
        .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void StartSignalTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of defaultTask */
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    /* creation of signalTask */
    signalTaskHandle = osThreadNew(StartSignalTask, NULL, &signalTask_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument) {
    /* USER CODE BEGIN StartDefaultTask */
//    uint8_t i, j;
//    float t = 0;
//    LCD_Init();
//    LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
    /* Infinite loop */
    for (;;) {
//        LCD_ShowChinese32x32(30, 40, "ï¿??", RED, WHITE, 32, 0);
//        LCD_ShowChinese32x32(62, 40, "ï¿??", RED, WHITE, 32, 0);
//        LCD_ShowChinese32x32(94, 40, "ï¿??", RED, WHITE, 32, 0);
//        LCD_ShowString(32, 80, "LCD_Diameter:", RED, WHITE, 16, 0);
//        LCD_ShowIntNum(134, 80, LCD_W, 3, RED, WHITE, 16);
//        LCD_ShowString(32, 100, "Increaseing Nun:", RED, WHITE, 16, 0);
//        LCD_ShowFloatNum1(160, 100, t, 4, RED, WHITE, 16);
//        t += 0.11;
//        for(j=0;j<3;j++) {
//            for(i=0;i<6;i++) {
//                LCD_ShowPicture(40*i,120+j*40,40,40,gImage_1);
//            }
//        }
        osDelay(1);
    }
    /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartSignalTask */
/**
* @brief Function implementing the signalTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSignalTask */
void StartSignalTask(void *argument) {
    /* USER CODE BEGIN StartSignalTask */
    char UartBuffer[32];
    Max30102_Init(&hi2c4);
    /* Infinite loop */
    for (;;) {
        Max30102_Task();
//        sprintf(UartBuffer, "%c[2J%c[H", 27, 27);
//        printf(UartBuffer);
//        sprintf(UartBuffer, "HR: %d\n\rSpO2: %d\n\r", Max30102_GetHeartRate(), Max30102_GetSpO2Value());
        printf("HR: %d\r\nSpO2: %d\r\n", Max30102_GetHeartRate(), Max30102_GetSpO2Value());
        osDelay(1);
    }
    /* USER CODE END StartSignalTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void arm_fir_f32_lp(void) {
    uint32_t i;
    arm_fir_instance_f32 S;
    float32_t *inputF32, *outputF32;

    inputF32 = &testInput_f32[0];
    outputF32 = &testOutput[0];

    arm_fir_init_f32(&S, NUM_TAPS, (float32_t *) &firCoeffs32BP[0], &firStateF32[0], blockSize);

    for (i = 0; i < numBlocks; i++) {
        arm_fir_f32(&S, inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
    }

    for (i = 0; i < TEST_LENGTH_SAMPLES; i++) {
        printf("%f, %f\r\n", testOutput[i], inputF32[i]);
    }
}
/* USER CODE END Application */

