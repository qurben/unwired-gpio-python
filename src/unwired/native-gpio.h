/*
 * native-gpio.h
 *
 *  Created on: Feb 14, 2016
 *      Author: Gerben Oolbekkink
 */

#ifndef NATIVE_GPIO_H_
#define NATIVE_GPIO_H_

int gpioSetup();
void gpioDirection(int gpio, int direction);
void gpioSet(int gpio, int value);
int gpioRead(int gpio);

#endif /* NATIVE_GPIO_H_ */
