#include <Arduino_FreeRTOS.h>
#include<TimerOne.h>

void TaskStudentCheck( void *pvParameters );        // P - 3
void TaskTemepratureRead( void *pvParameters );     // P - 2
void TaskHeartBeatSensorRead(void *pvParameters);   // P - 1
String OUTPUT_FINAL="Attendace of ";
String TEMP="";
String HEARTBEAT="";
String ROLL="";

//volatile int a=0;
void setup() {

  Serial.begin(9600);

 // TimerOne.initialize(15000000);
  
  pinMode(13, INPUT);
  
  xTaskCreate(TaskStudentCheck, "StudentvsvdgvIn"   ,  128  ,  NULL,  3  ,  NULL );
  xTaskCreate(TaskTemepratureRead,    "Temp",  128   ,  NULL ,  2  ,  NULL );
  xTaskCreate(TaskHeartBeatSensorRead,"Heart Beat ",128,NULL,1,NULL);
  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
 
}


void TaskStudentCheck(void *pvParameters)  
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    
    while(1){
      int check = digitalRead(13);
      int a=0;
      if(check ==1){
        Serial.print("Enter your roll  :  ");
        if(Serial.available()>0){
        a=Serial.read();
        }

        Serial.println(a=(a-48)*(-1));

       ROLL=String(a);
                                                         
        vTaskDelay(100);
            break;
   }}
    

    vTaskDelay(10);

}}




void TaskHeartBeatSensorRead(void *pvParameters)
{
  (void) pvParameters;

  for(;;){

  int raw = analogRead(A1);
  int heartbeat=0;
 // double raw1 = 0.75*raw + (1-0.75)*raw;
  Serial.print("Heart Beat Value :");
  raw=0;
  for(int i=0;i<10;i++){
    if(analogRead(A1)!=0){
     
    raw++;
    }
    delay(1);
  }
  Serial.print(raw=raw*6);
  Serial.println("bpm");
 // Serial.println(heartbeat=(0.75*raw+(1-0.75)*raw));
  HEARTBEAT = String(raw);

delay(1000);
//OUTPUT_FINAL.concat(ROLL);
//OUTPUT_FINAL.concat(TEMP);
//OUTPUT_FINAL.concat(HEARTBEAT);
Serial.println("\n");
Serial.print("Attendace & health monitoring of Roll No : "+ROLL+"  is taken.  " + "Health parameters are : \n Heartbeat(BPM) : "+ HEARTBEAT+"\n" + "Temperature : "+TEMP+" deg. celcius");

  while(1);
    vTaskDelay(10);
  }
}



void TaskTemepratureRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;)
  {
    /// Temperature Calculation of Student
    static int a=1;

    if (a==1){
      
    
    double temperature = analogRead(0);
   // vTaskDelay(1);
   temperature = (500*temperature)/1024;
   Serial.print("Temperature is : ");
    Serial.print(temperature);
    Serial.println("deg. celcius");
    TEMP=String(temperature);
    }

    a++;

    
    vTaskDelay(10);  // one tick delay (15ms) in between reads for stability
  }
}
