/*
 * mqtt_GreenHouse.h
 *
 *  Created on: 10 mar. 2025
 *      Author: Sergio R.
 */

#ifndef MQTT_GREENHOUSE_H_
#define MQTT_GREENHOUSE_H_

extern void mqttGreenHouse_App(void *arg);
extern void mqttGreenHouse_MessageRecv(char* Topic, char* payload, uint16_t payload_lenght);
extern void mqttGreenHouse_CheckSubscription(err_t err);


#endif /* MQTT_GREENHOUSE_H_ */
