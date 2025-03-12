/*
 * sensor.h
 *
 *  Created on: 10 mar. 2025
 *      Author: Sergio R.
 */

#ifndef SENSOR_H_
#define SENSOR_H_

extern void sensor_APP(void *arg);
extern uint32_t sensor_GetData(uint8_t id);
extern void control_ConfigParam(uint8_t id, uint32_t Value);
void control_ActivateStopButton(bool state);

#endif /* SENSOR_H_ */
