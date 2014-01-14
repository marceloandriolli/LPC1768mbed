#############################################################################################
#    Mbed LPC1768 Makefile    
#
#    By Marcelo Andriolli, Brazil
#    <marcelorsa@gmail.com>
#
##############################################################################################
# 
# On command line:
#
# make all = Create APP
#
# make clean = Clean APP files.
#
# make size = Shows size of bin file.
#
# make install = Copy the bin file to the serial Mbeb.  

##############################################################################################


#Toolschain Configuration
ARCH = arm-none-eabi-

# Install Volume
MBED_VOLUME = /Volumes/MBED

# CPU Configuration
THUMB = -mthumb
MCU  = cortex-m3

# List all default C defines here, like -D_DEBUG=1
DDEFS = 

# List all default ASM defines here, like -D_DEBUG=1
DADEFS = 

# List all default directories to look for include files here
DINCDIR = 

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS = 

# Define APP name here
APP = BlinkLedFreeRTOS

# Define linker script file here
LDSCRIPT_FLASH = ./sys/rtosdemo_Debug.ld

# List all user C define here, like -D_DEBUG=1
UDEFS = 

# Define ASM defines here
UADEFS = 

#FreeRTOS sources directories
FRTDIRSRC = ../../FreeRTOS/list.c \
       		  ../../FreeRTOS/queue.c \
              ../../FreeRTOS/tasks.c \
              ../../FreeRTOS/portable/GCC/ARM_CM3/port.c \
              ../../FreeRTOS/portable/MemMang/heap_2.c

# CMSIS sources directories
CMSISDIRSRC = ../../CMSIS/CM3/DeviceSupport/LPC17xx/system_LPC17xx.c 

# System directories directories
SYSDIRSRC = ./sys/startup_lpc17.c \
         ./sys/syscalls.c 

# Aplication source
C_SRC = ./src/main.c 

#All C source files
SRC = $(SYSDIRSRC) $(FRTDIRSRC) $(CMSISDIRSRC) $(C_SRC) 

# List ASM source files here
ASRC = 

# FreeRTOS Includes
FRTDIRINC = ../../FreeRTOS/include \
           ../../FreeRTOS/portable/GCC/ARM_CM3 

# CMSIS includes
CMSISDIRINC = ../../CMSIS/CM3/CoreSupport \
              ../../CMSIS/CM3/DeviceSupport/LPC17xx 

# System includes
SYSDIRINC = ./include

# All include directories
UINCDIR = $(SYSDIRINC) $(CMSISDIRINC) $(FRTDIRINC) 
           
# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS = 

# Define optimisation level here
OPT = -O0

# Include directories
INCDIR  = $(patsubst %,-I%,$(DINCDIR) $(UINCDIR))

# Lib directories
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))
DEFS    = $(DDEFS) $(UDEFS)
ADEFS   = $(DADEFS) $(UADEFS)
OBJS    = $(ASRC:.s=.o) $(SRC:.c=.o)
LIBS    = $(DLIBS) $(ULIBS)
MCFLAGS = -mcpu=$(MCU)

# Assembler flags
ASFLAGS = $(MCFLAGS) -g -gdwarf-2 $(THUMB) -Wa,-amhls=$(<:.s=.lst) $(ADEFS)

# C flags
CPFLAGS = $(MCFLAGS) $(OPT) -gdwarf-2 $(THUMB) -fomit-frame-pointer -Wall -Wstrict-prototypes -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) $(DEFS)

# Linker flags
LDFLAGS_FLASH = $(MCFLAGS) $(THUMB) -nostartfiles -T$(LDSCRIPT_FLASH) -Wl,-Map=$(APP).map,--cref,--no-warn-mismatch $(LIBDIR)

# Define programs and commands.
CC   = $(ARCH)gcc
CP   = $(ARCH)objcopy
AS   = $(ARCH)gcc -x assembler-with-cpp
GDB  = $(ARCH)gdb
BIN  = $(CP) -O ihex 
SIZE	= $(ARCH)size

# Generate dependency information
CPFLAGS += -MD -MP -MF .dep/$(@F).d


# Makefile Rules

all: FLASH
	
FLASH: $(OBJS) $(APP).elf $(APP).bin $(APP).hex

%o : %c
	$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

%o : %s
	$(AS) -c $(ASFLAGS) -I . $(INCDIR) $< -o $@
%elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS_FLASH) $(LIBS) -o $@

%hex: %elf
	$(BIN) $< $@

%bin: %elf
	$Q $(CP) -O binary $< $*bin

size: $(APP).elf
	@$(SIZE) $<	

install: $(APP).bin
	cp -av $(APP).bin $(MBED_VOLUME)/

# Program the device.  
# program:
#	arm-none-eabi-gdb --batch -x sys/gdbflashdownload.jlink
#	@$(GDB) --batch -x "sys/gdbflashdownload.jlink"


clean:
	-rm -f $(OBJS)
	-rm -f $(APP).elf
	-rm -f $(APP).map
	-rm -f $(APP).hex
	-rm -f $(APP).bin
	-rm -f $(SRC:.c=.c.bak)
	-rm -f $(SRC:.c=.lst)
	-rm -f $(ASRC:.s=.s.bak)
	-rm -f $(ASRC:.s=.lst)
	-rm -fR .dep

# 
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***