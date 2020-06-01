
/*
 * CO2Handler.c
 *
 * Created: 23.5.2020 г. 10:49:34
 *  Author: Borislav Aleksiev
 */ 
#include <stddef.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <lora_driver.h>
#include <iled.h>
#include "bits.h"
#include "event_groups.h"
	float templevel;
	float humLevel;

	
void hum_temp_task( void *pvParameters );

void Hum_Temp_Handler_create(){
	hih8120Create(); 
	xTaskCreate(
	hum_temp_task
	,  (const portCHAR *)"HumTempTask"  // A name just for humans
	,  configMINIMAL_STACK_SIZE+200  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
	
	
}
uint16_t get_hum_lvl(){

	if ( hih8120IsReady()==true){
	humLevel = hih8120GetHumidity();
	}
else{
	vTaskDelay(2000);
humLevel= hih8120GetHumidity();
	}
	printf("%s%i\n","Arduino humidity level: ",humLevel);
	return humLevel;
}


int16_t get_temp_lvl(){
if ( hih8120IsReady()==true){
	templevel = hih8120GetTemperature();
	}
else{
	vTaskDelay(2000);
templevel= hih8120GetTemperature();
	}
	
	printf("%s%i\n","Arduino temperature level: ",templevel);
	return templevel;
}
void hum_temp_task( void *pvParameters ){

		for (;;) {
			extern xCreatedEventGroup;
			//xEventGroupSetBits(xCreatedEventGroup, BIT_1);
			puts("humidityTask");
			hih8120Meassure();
			
			vTaskDelay(150);
			get_temp_lvl();
			get_hum_lvl();
		}
	
}
