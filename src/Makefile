all: gpio.so

gpio.so: gpio.o native-gpio.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)