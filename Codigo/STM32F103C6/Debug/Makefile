###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = STM32F103C6
COMPILER = "Keil for ARM"
TARGET = Debug
SHELL = C:\WINDOWS\system32\cmd.exe

## Tools general options
ASMFLAGS=--cpu=cortex-m3 --thumb -g
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -I../../../../../../../../Keil_v5/ARM/CMSIS/Include -g -O0
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/Debug/main.o: TOOL=CC
#        C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/main.c
#     C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/Debug/SYSTEM~1.o: TOOL=CC
#        C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/system_stm32f1xx.c
#     C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/Debug/STARTU~1.o: TOOL=ASM
#        C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/startup_stm32f103.s
#     C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/Debug/remoto.o: TOOL=CC
#        C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/remoto.c
#     C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/Debug/motor.o: TOOL=CC
#        C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/motor.c
#     C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/Debug/sEOS.o: TOOL=CC
#        C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/sEOS.c
#     C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/Debug/cortina.o: TOOL=CC
#        C:/Users/Nicol/Desktop/Taller de Proyecto-Cortina Automatica-/Cortina-automatica/Codigo/STM32F103C6/cortina.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o SYSTEM~1.o STARTU~1.o remoto.o motor.o sEOS.o cortina.o 
	$(LD)  $(LDFLAGS)  "main.o" "SYSTEM~1.o" "STARTU~1.o" "remoto.o" "motor.o" "sEOS.o" "cortina.o" --output "Debug.elf"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

SYSTEM~1.o:	../system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "../system_stm32f1xx.c" -c -o "SYSTEM~1.o"

STARTU~1.o:	../startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f103.s" -o "STARTU~1.o"

remoto.o:	../remoto.c 
	$(CC) $(CCFLAGS)  "../remoto.c" -c -o "remoto.o"

motor.o:	../motor.c 
	$(CC) $(CCFLAGS)  "../motor.c" -c -o "motor.o"

sEOS.o:	../sEOS.c 
	$(CC) $(CCFLAGS)  "../sEOS.c" -c -o "sEOS.o"

cortina.o:	../cortina.c 
	$(CC) $(CCFLAGS)  "../cortina.c" -c -o "cortina.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf SYSTEM~1.o
	rm -rf STARTU~1.o
	rm -rf remoto.o
	rm -rf motor.o
	rm -rf sEOS.o
	rm -rf cortina.o
