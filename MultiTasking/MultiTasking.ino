#include "RTOS.h"

/*Tasks Poll rates in ms*/
#define TASK1_POLLRATE_MS             250UL     
#define TASK2_POLLRATE_MS             500UL       
#define TASK3_POLLRATE_MS             1000UL     

/*Task Priority Order*/
#define TASK1_PRIORITY              1U
#define TASK2_PRIORITY              2U
#define TASK3_PRIORITY              3U

/* 
 * RTOS User Tasks...
 */
void Task1(void);
void Task2(void);
void Task3(void);


/*  
  User Global Variables
*/
static uint8_t ledState=LOW;

void setup() {

  /* 
     * Inicio de perifericos
  */
    vHardwareInit();
    
    /* 
     * Creacion de Tareas RTOS + prioridades
     */
    xTaskCreate("Task 1",                       //Read Temperature sensor  
            TASK1_PRIORITY, 
            TASK1_POLLRATE_MS, 
            Task1);
    
    xTaskCreate("Task 2",                       //Read RTC actual Time & Date ISR
            TASK2_PRIORITY, 
            TASK2_POLLRATE_MS, 
            Task2);
    
    xTaskCreate("Task 3",                   //Process && Decisions for Outputs
            TASK3_PRIORITY, 
            TASK3_POLLRATE_MS, 
            Task3);

  //Reordena las tareasy empeiza la temproizacion
    vTaskStartScheduler();

    Serial.println("Looping....");

}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskSchedulerUpdate();

}


/* 
 * RTOS User Tasks...Implementation code
 */
void Task1(void){
  /*Mensaje al usuario....*/
  Serial.print("Tarea 1, ejecuta cada: ");
  Serial.println(TASK1_POLLRATE_MS, DEC);

}

void Task2(void){
  /*Mensaje al usuario....*/
  Serial.print("Tarea 2, ejecuta cada: ");
  Serial.println(TASK2_POLLRATE_MS, DEC);

}

void Task3(void){

  //Actualizar el estdo del LED
  ledState= ~ledState;

  // set the LED with the ledState of the variable:
  digitalWrite(LED_BUILTIN, ledState);

/*Mensaje al usuario....*/
  Serial.print("Tarea 3, ejecuta cada: ");
  Serial.println(TASK3_POLLRATE_MS, DEC);

}
