all: gpio.so

gpio.so: gpio.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)