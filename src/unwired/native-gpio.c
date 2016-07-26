#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define GPIO_ADDR 0x18040000 // base address
#define GPIO_BLOCK 48 // memory block size

volatile unsigned long *gpioAddress;

int gpioSetup()
{
    int  m_mfd;
    if ((m_mfd = open("/dev/mem", O_RDWR)) < 0)
    {
        return -1;
    }
    gpioAddress = (unsigned long*)mmap(NULL, GPIO_BLOCK, PROT_READ|PROT_WRITE, MAP_SHARED, m_mfd, GPIO_ADDR);
    close(m_mfd);

    if (gpioAddress == MAP_FAILED)
    {
        return -2;
    }

    return 0;
}

void gpioDirection(int gpio, int direction)
{
    unsigned long value = *(gpioAddress + 0); // obtain current settings
    if (direction == 1)
    {
        value |= (1 << gpio); // set bit to 1
    }
    else
    {
        value &= ~(1 << gpio); // clear bit
    }
    *(gpioAddress + 0) = value;
}

void gpioSet(int gpio, int value)
{
    if (value == 0)
    {
        *(gpioAddress + 4) = (1 << gpio);
    }
    else
    {
        *(gpioAddress + 3) = (1 << gpio);
    }
}

int gpioRead(int gpio)
{
    unsigned long value = *(gpioAddress + 1);
    return (value & (1 << gpio));
}

int main()
{
	if (gpioSetup() == 0)
	{
		gpioDirection(27, 1);
		while (1)
		{
			gpioSet(27, 1);
			printf("ON\n");
			sleep(1);
			gpioSet(27, 0);
			printf("OFF\n");
			sleep(1);
		}
	}

	return 0;
}
