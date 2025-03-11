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
#include "mqtt_GreenHouse_cfg.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint32_t DataSensor[enMQTT_SENSOR_Total] = {12, 50};
static uint32_t DataConfig[enMQTT_SENSOR_Total] = {0, 0};
static bool StopButton = false;
static bool NewConfig[enMQTT_SENSOR_Total] = {false};

static const uint32_t DefaultValues[enMQTT_SENSOR_Total] = {12, 50};
/*******************************************************************************
 * Code
 ******************************************************************************/
void sensor_APP(void)
{
	uint8_t SensIndx = 0U;

	for(SensIndx = 0; SensIndx < enMQTT_SENSOR_Total; SensIndx++)
	{
		if(StopButton)
		{
			if(DataSensor[SensIndx] != DataConfig[SensIndx] && NewConfig[SensIndx])
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

void control_ActivateStopButton(bool state)
{
	StopButton = state;
}
