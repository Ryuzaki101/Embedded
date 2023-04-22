# MPLAB IDE generated this makefile for use with GNU make.
# Project: _LCD-Ausgabe.mcp
# Date: Thu Nov 20 15:01:18 2014

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

_LCD-Ausgabe.cof : LCD-Ausgabe.o
	$(LD) /p18F452 /l"C:\Program Files\Microchip\mplabc18\v3.37.01\lib" /k"C:\Program Files\Microchip\mplabc18\v3.37.01\bin\LKR" "18f452.lkr" "LCD-Ausgabe.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"_LCD-Ausgabe.cof" /M"_LCD-Ausgabe.map" /W

LCD-Ausgabe.o : LCD-Ausgabe.c lcd.h LCD-Ausgabe.c p18f452.h
	$(CC) -p=18F452 /i"C:\Program Files\Microchip\mplabc18\v3.37.01\h" "LCD-Ausgabe.c" -fo="LCD-Ausgabe.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "LCD-Ausgabe.o" "_LCD-Ausgabe.cof" "_LCD-Ausgabe.hex"

