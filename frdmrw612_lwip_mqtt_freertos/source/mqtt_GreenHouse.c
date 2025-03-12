/*
 * mqtt_greenhouse.c
 *
 *  Created on: 8 mar. 2025
 *      Author: Sergio R.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "board.h"
#include "stdio.h"
#include "lwip/apps/mqtt.h"
#include "lwip/tcpip.h"

#include "mqtt_GreenHouse_cfg.h"
#include "sensor.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define GET_SYSTEM_TIME_S()  (xTaskGetTickCount() / configTICK_RATE_HZ)

typedef struct
{
	char *topic;
	char payload[12];
	bool NewMsg;
}MQTT_MessageRecv;

typedef struct
{
	char *topic;
	char payload[12];
	char LastMsg[12];
}MQTT_MessageSend;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static MQTT_MessageSend mqtt_MsgSend[enMQTT_SENSOR_Total] = MQTT_SENSOR_TOPICS_TABLE_CFG;
static MQTT_MessageRecv mqtt_MsgRecv[enMQTT_CONTROL_Total] = MQTT_CONTROL_TOPICS_TABLE_CFG;

static err_t SubsState = ERR_CONN;

static mqtt_client_t *mqtt_client;
/*******************************************************************************
 * Code
 ******************************************************************************/
static void mqtt_message_published_cb(void *arg, err_t err)
{
    const char *topics = (const char *)arg;

    if (err == ERR_OK)
    {
        PRINTF("Published to the topic \"%s\".\r\n", topics);
    }
    else
    {
        PRINTF("Failed to publish to the topic \"%s\": %d.\r\n", topics, err);
    }
}

static void publish_message(void *ctx)
{
	MQTT_MessageSend *MsgData = (MQTT_MessageSend*)ctx;

    PRINTF("Going to publish to the topic \"%s\"...\r\n", MsgData->topic);
    mqtt_publish(mqtt_client, MsgData->topic, MsgData->payload, strlen(MsgData->payload), 1, 0, mqtt_message_published_cb, (void *)MsgData->topic);
}

static void mqttGreenHouse_UpdateParams(void)
{
	uint8_t MsgIndx;
	uint32_t Value;

	for(MsgIndx = 0; MsgIndx < enMQTT_CONTROL_Total; MsgIndx++)
	{
		if(mqtt_MsgRecv[MsgIndx].NewMsg == true)
		{
			Value = atoi(mqtt_MsgRecv[MsgIndx].payload);
			control_ConfigParam(MsgIndx, Value);
			memset(mqtt_MsgRecv[MsgIndx].payload, 0, sizeof(mqtt_MsgRecv[MsgIndx].payload));
			mqtt_MsgRecv[MsgIndx].NewMsg = false;
		}
	}
}

void mqttGreenHouse_App(void *arg)
{
	mqtt_client = (mqtt_client_t*)arg;
	static uint32_t LastTime = 0U;

	uint8_t SensIndx;
	uint32_t SampleRate;
	uint32_t DeltaTime;
	uint32_t SensData;
	err_t err;

	while(true)
	{
		mqttGreenHouse_UpdateParams();
		SampleRate = sensor_GetData(enMQTT_CONTROL_SampleRate);

		DeltaTime = GET_SYSTEM_TIME_S() - LastTime;

		if(DeltaTime >= SampleRate && SubsState == ERR_OK)
		{
			for(SensIndx = 0; SensIndx < enMQTT_SENSOR_Total; SensIndx++)
			{
				SensData = sensor_GetData(SensIndx);
				snprintf(mqtt_MsgSend[SensIndx].payload, sizeof(mqtt_MsgSend[SensIndx].payload), "%d", SensData);

				if(strcmp(mqtt_MsgSend[SensIndx].payload, mqtt_MsgSend[SensIndx].LastMsg) != 0)
				{
					err = tcpip_callback(publish_message, &mqtt_MsgSend[SensIndx]);
					if (err != ERR_OK)
					{
						PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
					}

					strncpy(mqtt_MsgSend[SensIndx].LastMsg, mqtt_MsgSend[SensIndx].payload, sizeof(mqtt_MsgSend[SensIndx].payload));
				}
			}

			LastTime = GET_SYSTEM_TIME_S();
		}

	vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void mqttGreenHouse_MessageRecv(char* Topic, char* payload, uint16_t payload_lenght)
{
	uint8_t MsgIndx;

	for(MsgIndx = 0; MsgIndx < enMQTT_CONTROL_Total; MsgIndx++)
	{
		if(strcmp(Topic, mqtt_MsgRecv[MsgIndx].topic) == 0)
		{
			memcpy(mqtt_MsgRecv[MsgIndx].payload, payload, payload_lenght);
			mqtt_MsgRecv[MsgIndx].NewMsg = true;
		}
	}
}

void mqttGreenHouse_CheckSubscription(err_t err)
{
	SubsState = err;
}
