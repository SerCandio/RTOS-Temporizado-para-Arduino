#ifndef RTOS_H
#define	RTOS_H

/*Librerias y perifericos para RTOS*/
#include <Arduino.h>

#define MAX_NUM_TASKS           10  /*Numero maximo de tareas del sistema*/
#define MAX_NAME_LEN            16


//#define TASK_DEBUG_MODE     //Imprime Debug de tareas

//#define SLEEP_MODE          

//Bloque de Control de Tareas (Task Control Block) TCB
//Mantiene toda la informacion reelevante de una tarea
typedef struct{
    uint16_t tID;           /*ID de la Tarea*/
    uint16_t priority;      /*prioridad de la tarea*/
    uint32_t tPollRateMs;  /*Poll rate en "ms" de la tarea(cada cuanto se llama)*/
    uint32_t tElapsedMs;   /*Cantidad de "ms" relativos transcurridos de la tarea*/
    uint16_t taskInList;    /*1 si la tarea esta en la lista, caso contrario 0*/
    void (*pvFuncTask)(void);  /*puntero a la funcion de la tarea*/
    char nameTask[MAX_NAME_LEN];  /*Nombre de la tarea*/ 
}TaskControlBlock_t;

/* 
 * Global Variables
 * Access : Public
 */
//TaskControlBlock_t taskList[MAX_NUM_TASKS];  /*Creacion de una lista de tareas*/

//extern void (*pvTask) (void);         //Creacion de un puntero a funcion desde donde se llamaran las tareas
static int length;                  //Cantidad de Tareas que se crean

/* 
 * Function Prototypes
 * Access :Public
 */
//Funcion para agregar tareas a la lista
extern uint8_t xTaskCreate(const char *pcName, uint16_t xPriority, const uint32_t pvTaskRateMs, void (*pvTaskCode)(void));

//Implementacion basica de un scheduler, reordena las tareas e inicia las temporizaciones
extern void vTaskStartScheduler(void);

//Evalua el Task Scheduler, si la tarea ya cumplio su pollrate, hace el swithc a otra tarea
extern void vTaskSchedulerUpdate(void);

//Inicio de perifericos
extern void vHardwareInit(void);


#endif	/* RTOS_H */