/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include <stdio.h>
#include <string.h>
#include "usart.h"

#define MSGQUEUE_OBJECTS 200                     // number of Message Queue Objects

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */


/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1000
};
/* Definitions for Green_LED */
osThreadId_t Green_LEDHandle;
const osThreadAttr_t Green_LED_attributes = {
  .name = "Green_LED",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 1000
};
/* Definitions for Red_LED */
osThreadId_t Red_LEDHandle;
const osThreadAttr_t Red_LED_attributes = {
  .name = "Red_LED",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 1000
};
/* Definitions for myUARTMutex */
osMutexId_t myUARTMutexHandle;
const osMutexAttr_t myUARTMutex_attributes = {
  .name = "myUARTMutex"
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
typedef struct {                                // object data type
  uint8_t Buf[32];
  uint8_t Idx;
} MSGQUEUE_OBJ_t;

osMessageQueueId_t mid_MsgQueue;

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Green_LED_task(void *argument);
void Red_LED_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of myUARTMutex */
  myUARTMutexHandle = osMutexNew(&myUARTMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */

  //mid_MsgQueue = osMessageQueueNew(MSGQUEUE_OBJECTS, sizeof(MSGQUEUE_OBJ_t), NULL);

  mid_MsgQueue = osMessageQueueNew(MSGQUEUE_OBJECTS, sizeof(uint8_t), NULL);

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Green_LED */
  Green_LEDHandle = osThreadNew(Green_LED_task, NULL, &Green_LED_attributes);

  /* creation of Red_LED */
  Red_LEDHandle = osThreadNew(Red_LED_task, NULL, &Red_LED_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {

	  osSemaphoreAcquire(myBinarySem01Handle, osWaitForever);
	  osDelay(20);
	  if(GPIOA->IDR & 1<<0) {
		  GPIOD->ODR ^= (1 << 15);
	  }
	  osDelay(20);
	  osSemaphoreAcquire(myBinarySem01Handle, 10);
	// osMutexAcquire(myUARTMutexHandle, osWaitForever);
    //osDelay(1000);
	//osMutexRelease(myUARTMutexHandle);


  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Green_LED_task */
/**
* @brief Function implementing the Green_LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Green_LED_task */
void Green_LED_task(void *argument)
{
  /* USER CODE BEGIN Green_LED_task */
  /* Infinite loop */

 /** MSGQUEUE_OBJ_t msg; **/

  for(;;)
  {
	  osDelay(100);

	 /// 	osMutexAcquire(myUARTMutexHandle, osWaitForever);
	//	osSemaphoreAcquire(myBinarySem01Handle, osWaitForever);

	 /* 	  strcpy(msg.Buf, "RToS");
	      msg.Idx     = 0U;
	      osMessageQueuePut(mid_MsgQueue, &msg, 0U, 0U);   */

	///	printf("In Green Task\n");
	///	osMutexRelease(myUARTMutexHandle);
	//	osSemaphoreRelease(myBinarySem01Handle);

	/*osDelay(1000); */
  }
  /* USER CODE END Green_LED_task */
}

/* USER CODE BEGIN Header_Red_LED_task */
/**
* @brief Function implementing the Red_LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Red_LED_task */
void Red_LED_task(void *argument)
{
  /* USER CODE BEGIN Red_LED_task */
  /* Infinite loop */

  char rx_data[2];
  rx_data[1] = '\0';
  char rx_buf[20];

  memset(rx_buf, 0, sizeof(rx_buf));

  for(;;)
  {


	///osMutexAcquire(myUARTMutexHandle, osWaitForever);
	//osSemaphoreAcquire(myBinarySem01Handle, osWaitForever);

	      if (osMessageQueueGet(mid_MsgQueue, &rx_data[0], NULL, 0U) == osOK) {
	    	   strcat(rx_buf, rx_data);
	    	   if(strstr(rx_buf, "\n") != 0)
	    	   {
	    		   strupr(rx_buf);

	    		   if(strstr(rx_buf, "ON") != 0) {
	    			   GPIOD->ODR |= (1 << 12);
	    			   memset(rx_buf, 0, sizeof(rx_buf));
	    		   }

	    		   if(strstr(rx_buf, "OFF") != 0) {
	    			   GPIOD->ODR &= ~(1 << 12);
	    			   memset(rx_buf, 0, sizeof(rx_buf));
	    		   }


	    	   }



	    	 // printf("%c", rx_data);
	      }

	///osMutexRelease(myUARTMutexHandle);
	//osSemaphoreRelease(myBinarySem01Handle);
//    osDelay(5);
  }
  /* USER CODE END Red_LED_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     


void USART2_IRQHandler(void)
{
	if (LL_USART_IsActiveFlag_RXNE(USART2)&& LL_USART_IsEnabledIT_RXNE(USART2))
	{
		uint8_t bufbyte = LL_USART_ReceiveData8(USART2);

		osMessageQueuePut(mid_MsgQueue, &bufbyte, 0U, 0U);
	}
	/* USER CODE END USART1_IRQn 2 */
}





/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
