CC=msp430-gcc
LD=msp430-gcc
MCU=msp430g2553
CFLAGS= -mmcu=$(MCU) -Wall -Os -c -x c++ -o0

TARGET=main.elf

$(TARGET): main.o uart.o pump.o temperature.o
	$(LD) -mmcu=$(MCU) main.o uart.o pump.o temperature.o -o $(TARGET)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

uart.o: uart.c uart.h
	$(CC) $(CFLAGS) uart.c -o uart.o

pump.o: pump.c pump.h
	$(CC) $(CFLAGS) pump.c -o pump.o

temperature.o: temperature.c temperature.h
	$(CC) $(CFLAGS) temperature.c -o temperature.o

prog:
	mspdebug rf2500 "prog $(TARGET)"

clean:
	rm -f *.o *.elf

