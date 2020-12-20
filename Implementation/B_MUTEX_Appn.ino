#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal_DBIT.h>
#include <semphr.h>

SemaphoreHandle_t LCD_mutex = NULL;
LiquidCrystal_DBIT LCD(2,3,8,9,10,11);  

void setup()
{  
  LCD.begin(16,2);
    
  LCD_mutex = xSemaphoreCreateMutex();
  
  xTaskCreate(HeartBeat_Measurement, "Task1", 100, NULL, 1, NULL);  
  xTaskCreate(Temperature_Measurement, "Task2", 100, NULL, 1, NULL);
}


void loop()
{
  
}


void HeartBeat_Measurement(void* pvParameters)
{
  int count = 0;
            xSemaphoreTake(LCD_mutex,200);      
          
     int heartbeat =0;

    for(int i=0;i<=100;i++){
      heartbeat++;
      delay(1);
    }
                                                
                                                //Blocked state
  LCD.gotoxy(0,0);   //Column_num , Line_num
  LCD.dispString("Heartbeat : ");
  LCD.gotoxy(12,0);   //Column_num , Line_num
  LCD.dispNum(heartbeat*1);
            xSemaphoreGive(LCD_mutex);          //Release Mutex-------------

  while(1)
  {
            xSemaphoreTake(LCD_mutex,200);      //Capture Mutex*************
  LCD.gotoxy(12,0);   //Column_num , Line_num
  LCD.dispNum(heartbeat);
            xSemaphoreGive(LCD_mutex);          //Release Mutex-------------
  //count++;
  vTaskDelay(100);    
  }
}

void Temperature_Measurement(void* pvParameters)
{
  int count = 0;
  float temp=0;

  temp = analogRead(0);
  pinMode(A0,INPUT);
            xSemaphoreTake(LCD_mutex,200);      //Capture Mutex*************
  LCD.gotoxy(0,1);   //Column_num , Line_num
  LCD.dispString("Temperature:");
  LCD.gotoxy(12,1);   //Column_num , Line_num
  LCD.dispNum(temp);
            xSemaphoreGive(LCD_mutex);          //Release Mutex-------------

  while(1)
  {
            xSemaphoreTake(LCD_mutex,200);      //Capture Mutex*************
  
  temp = (500*temp)/1023;
  LCD.gotoxy(12,1);  
  LCD.dispNum(temp);
            xSemaphoreGive(LCD_mutex);          //Release Mutex-------------

  vTaskDelay(200);    
  }
}



//HEX FILES FOR BOTH EXECUTION :  A. PRIORITY WISE     B. MUTEX SEMAPHORE 
//  A.
//  B. 
