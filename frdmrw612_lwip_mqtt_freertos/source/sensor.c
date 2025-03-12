/*
 * sensor.c
 *
 *  Created on: 10 mar. 2025
 *      Author: Sergio R.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "board.h"
#include "lwip/apps/mqtt.h"

#include "mqtt_GreenHouse_cfg.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint32_t DataSensor[enMQTT_CONTROL_Total] = {10, 50, 10, 30, 0, 1};
static uint32_t DataConfig[enMQTT_CONTROL_Total] = {0};
static bool NewConfig[enMQTT_CONTROL_Total] = {false};

static const uint32_t DefaultValues[enMQTT_CONTROL_Total] = {10, 50, 10, 30, 0, 1};
/*******************************************************************************
 * Code
 ******************************************************************************/
void sensor_APP(void *arg)
{
	LWIP_UNUSED_ARG(arg);

	uint8_t SensIndx = 0U;

	while(true)
	{

		for(SensIndx = 0; SensIndx < enMQTT_SENSOR_Total; SensIndx++)
		{
			if(DataSensor[enMQTT_CONTROL_Button] != true)
			{
				if(DataSensor[SensIndx] != DataConfig[SensIndx] && NewConfig[SensIndx] == true)
				{
					if(DataSensor[SensIndx] < DataConfig[SensIndx])
					{
						DataSensor[SensIndx]++;
					}
					else
					{
						DataSensor[SensIndx]--;
					}
				}
			}
			else
			{
				if(DataSensor[SensIndx] != DefaultValues[SensIndx])
				{
					if(DataSensor[SensIndx] < DefaultValues[SensIndx])
					{
						DataSensor[SensIndx]++;
					}
					else
					{
						DataSensor[SensIndx]--;
					}
				}
			}
		}

		for(SensIndx = enMQTT_SENSOR_Total; SensIndx < enMQTT_CONTROL_Total; SensIndx++)
		{
			if(NewConfig[SensIndx])
			{
				DataSensor[SensIndx] = DataConfig[SensIndx];
			}
		}

	vTaskDelay(pdMS_TO_TICKS(500));
	}
}

uint32_t sensor_GetData(uint8_t id)
{
	return DataSensor[id];
}

void control_ConfigParam(uint8_t id, uint32_t Value)
{
	DataConfig[id] = Value;
	NewConfig[id] = true;
}
