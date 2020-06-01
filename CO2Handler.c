
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
	uint16_t CO2level;

	
void CO2_handler_task( void *pvParameters );
void CO2Handler_create(){
	//void mh_z19_create(e_com_port_t com_port,void(*mh_z19_call_back )(uint16_t ppm)); should make this work out here
	xTaskCreate(
	CO2_handler_task
	,  (const portCHAR *)"CO2HandTask"  // A name just for humans
	,  configMINIMAL_STACK_SIZE+200  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
	
	
}
uint16_t getCO2lvl(){
	mh_z19_get_co2_ppm(CO2level);
	return CO2level;
}

void CO2_handler_task( void *pvParameters ){
		mh_z19_create(ser_USART3,NULL);//Params are a matter of testing
	for (;;) {
		extern xCreatedEventGroup;
		//xEventGroupSetBits(xCreatedEventGroup, BIT_0);
		puts("co2task");
		mh_z19_take_meassuring();
		//printf("CO2 value: >%s<\n", lora_driver_sent_upload_message(true, &_uplink_payload));
		printf("%s%i\n","Arduino measurement CO2: ",getCO2lvl());
		vTaskDelay(1000);
	}
}

//mh_z19_return_code_t