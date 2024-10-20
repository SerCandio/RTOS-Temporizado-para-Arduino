#include "RTOS.h"

/* 
 * Global Variables
 * Access : Public
 */
TaskControlBlock_t taskList[MAX_NUM_TASKS];  /*Creacion de una lista de tareas*/


//Funcion para agregar tareas a la lista
extern uint8_t xTaskCreate(const char *pcName, uint16_t xPriority, const uint32_t pvTaskRateMs, void (*pvTaskCode)(void)){

    uint8_t i=1;
    
    uint8_t ret =0;
    
//    TCB_t temp;
    
//    int length = sizeof(taskList)/sizeof(taskList[0]) ; 
    
    Serial.print("Creando Tarea\r\n");
    
    while(i <=MAX_NUM_TASKS)
    {
        if(strlen(pcName) > MAX_NAME_LEN)
        {
            Serial.print("Error -> Nombre de la Tarea muy grande\r\n");
            return ret;
        }
        
        
        if (taskList[i].taskInList != 1)
        {
           // printf("Tarea creada #: %d\r\n\r\n", i);
            Serial.print("Tarea creada #: ");
            Serial.print(i, DEC);
            Serial.print("\r\n\r\n");

            taskList[i].tID =i;
            strcpy(taskList[i].nameTask,pcName);
            taskList[i].priority = xPriority;
            taskList[i].tPollRateMs = pvTaskRateMs;
            //taskList[i].tElapsedMs = millis(); 
            taskList[i].pvFuncTask=pvTaskCode;
            taskList[i].taskInList =1;
            ret =1;
            break;
        }
        
        i++; //Si el espacio ya esta reservado, incrementa a otro

   }

    length=i;
      
    return ret ;   
}

//Implementacion basica de un scheduler
/*Las Tareas son reordenadas por prioridad*/
extern void vTaskStartScheduler(void){
    uint16_t i = 1;
    //int length = 3 ;                  //Ver RTOS.h
    TaskControlBlock_t temp;
    
    /*  
     * Reordenar la lista de tareas segun su prioridad. 
     * Nota: Numero 'priority' mas bajo tiene prioridad de ejecucion mas alta
     */
    for (int j = 0; j <=length; j++) {     
        for (int k = j+1; k <=length; k++) {     
           if(taskList[j].priority > taskList[k].priority) {    
               temp = taskList[j];    
               taskList[j] = taskList[k];    
               taskList[k] = temp;    
           }     
        }     
    }  

  /*
    Inicio de las temporizaciones de cada tarea, punto de partida de tiempo
  */
    for(int i=1; i<=length;i++){
      taskList[i].tElapsedMs = millis(); 
    }
    
}

//Evalua el Task Scheduler, si la tarea ya cumplio su pollrate, hace el swithc a otra tarea
extern void vTaskSchedulerUpdate(void){

  void (*pvTask) (void);         //Creacion de un puntero a funcion desde donde se llamaran las tareas

  for(int i = 0; i<=MAX_NUM_TASKS; i++)
        {
            if(taskList[i].taskInList ==1)
            {
                if(millis()>=(taskList[i].tElapsedMs + taskList[i].tPollRateMs))
                {
                    taskList[i].tElapsedMs = millis();
#if defined(TASK_DEBUG_MODE)
                    printf("\r\n%s ,order: %u", taskList[i].nameTask, taskList[i].priority);
#endif
                    pvTask = (void *) taskList[i].pvFuncTask;
                    (*pvTask) (); //Llalmado indirecto a funcion de la tarea
                }
                
            }
            
        }  

}

//Inicio de perifericos
void vHardwareInit(void){

  //Declara pines I/O e inicia estados
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  //Inicia la consola serie a 9600 bps
  Serial.begin(9600);
}