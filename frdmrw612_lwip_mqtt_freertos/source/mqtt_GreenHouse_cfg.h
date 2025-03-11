/*
 * mqtt_GreenHouse_cfg.h
 *
 *  Created on: 10 mar. 2025
 *      Author: Sergio R.
 */

#ifndef MQTT_GREENHOUSE_CFG_H_
#define MQTT_GREENHOUSE_CFG_H_

#define MQTT_CONTROL_TOPICS_TABLE_CFG \
{\
	{"greenhouse/control/temperatura", NULL, NULL, false},\
	{"greenhouse/control/humedad", NULL, NULL, false},\
}

typedef enum
{
	enMQTT_SENSOR_Temperature = 0,
	enMQTT_SENSOR_Humidity,
	enMQTT_SENSOR_Total
}MQTT_SensorID;

#define MQTT_SENSOR_TOPICS_TABLE_CFG \
{\
	"greenhouse/sensor/temperatura",		\
	"greenhouse/sensor/humedad", 			\
}



#endif /* MQTT_GREENHOUSE_CFG_H_ */
