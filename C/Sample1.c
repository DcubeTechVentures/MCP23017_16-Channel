// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP23017_I2CR16G5LE
// This code is designed to work with the MCP23017_I2CR16G5LE_10A I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Relay-Controller?sku=MCP23017_I2CR16G5LE_10A#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, MCP23017 I2C address is 0x20(32)
	ioctl(file, I2C_SLAVE, 0x20);

	// Configure all pins of port-A as output(0x00)
	char config[2] = {0};
	config[0] = 0x00;
	config[1] = 0x00;
	write(file, config, 2);
	// Configure all pins of port-B as output(0x00)
	config[0] = 0x01;
	config[1] = 0x00;
	write(file, config, 2);
	sleep(1);

	// Set all pins of port-A to logic HIGH(0xFF)
	config[0] = 0x12;
	config[1] = 0xFF;
	write(file, config, 2);
	printf("Turning all Relays of Port-A ON \n");
	// Set all pins of port-B to logic HIGH(0xFF)
	config[0] = 0x13;
	config[1] = 0xFF;
	write(file, config, 2);
	printf("Turning all Relays of Port-B ON \n");
}
