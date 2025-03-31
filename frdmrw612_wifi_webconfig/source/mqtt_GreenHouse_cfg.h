/*
 * mqtt_GreenHouse_cfg.h
 *
 *  Created on: 10 mar. 2025
 *      Author: Sergio R.
 */

#ifndef MQTT_GREENHOUSE_CFG_H_
#define MQTT_GREENHOUSE_CFG_H_



typedef enum
{
	enMQTT_SENSOR_Temperature = 0,
	enMQTT_SENSOR_Humidity,
	enMQTT_SENSOR_CO2,
	enMQTT_SENSOR_Light,
	enMQTT_SENSOR_Total
}MQTT_SENSOR_TopicID;

typedef enum
{
	enMQTT_CONTROL_Button = enMQTT_SENSOR_Total,
	enMQTT_CONTROL_SampleRate,
	enMQTT_CONTROL_Total
}MQTT_CONTROL_TopicID;

#define MQTT_CONTROL_TOPICS_TABLE_CFG \
{\
	{"greenhouse/control/temperatura"},\
	{"greenhouse/control/humedad"},\
	{"greenhouse/control/CO2"},\
	{"greenhouse/control/luz"},\
	{"greenhouse/control/boton"},\
	{"greenhouse/control/samplerate"},\
}


#define MQTT_SENSOR_TOPICS_TABLE_CFG \
{\
	{"greenhouse/sensor/temperatura"},		\
	{"greenhouse/sensor/humedad"}, 			\
	{"greenhouse/sensor/CO2"}, 			\
	{"greenhouse/sensor/luz"}, 			\
}



#endif /* MQTT_GREENHOUSE_CFG_H_ */
