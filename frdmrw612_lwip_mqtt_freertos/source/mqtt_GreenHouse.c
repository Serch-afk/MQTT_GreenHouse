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
typedef struct
{
	char *topic;
	char *payload;
	uint16_t payload_lenght;
	bool NewMsg;
}MQTT_MessageRecv;

typedef struct
{
	uint8_t TopicID;
	char payload[12];
}MQTT_MessageSend;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const char *topic[enMQTT_SENSOR_Total] = MQTT_SENSOR_TOPICS_TABLE_CFG;
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

    PRINTF("Going to publish to the topic \"%s\"...\r\n", topic[MsgData->TopicID]);
    mqtt_publish(mqtt_client, topic[MsgData->TopicID], MsgData->payload, strlen(MsgData->payload), 1, 0, mqtt_message_published_cb, (void *)topic[MsgData->TopicID]);
}



void mqttGreenHouse_App(void *arg)
{
	mqtt_client = (mqtt_client_t*)arg;

	uint8_t SensIndx;
	uint32_t SensData;
	err_t err;

	MQTT_MessageSend MsgData;

	while(true)
	{
		for(SensIndx = 0; SensIndx < enMQTT_SENSOR_Total; SensIndx++)
		{
			SensData = sensor_GetData(SensIndx);
			snprintf(MsgData.payload, sizeof(MsgData.payload), "%d", SensData);
			MsgData.TopicID = SensIndx;

			err = tcpip_callback(publish_message, &MsgData);
			if (err != ERR_OK)
			{
				PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
			}
		}

	vTaskDelay(pdMS_TO_TICKS(10));
	}
}
