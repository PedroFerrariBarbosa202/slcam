#==============================================================================
# STM32F103 SPI Test
#==============================================================================

# Be silent by default. Use `make V=1` to show commands.
ifneq ($(V),1)
Q := @
endif

#------------------------------------------------------------------------------
# Project
#------------------------------------------------------------------------------

BINARY := spi_test

FIRMWARE_DIR    := ../../
SYSTEM_DIR			:= ../../system
CONFIG_DIR      := ../../config
FREERTOS_DIR    := ../../os/include/
SPI_DRIVER_DIR 	:= ../../drivers/spi
OPENCM3_DIR     := ../../hal

#------------------------------------------------------------------------------
# Target
#------------------------------------------------------------------------------

LIBNAME := opencm3_stm32f1

DEFS += -DSTM32F1

ARCH_FLAGS := -mthumb -mcpu=cortex-m3

#------------------------------------------------------------------------------
# Linker script
#------------------------------------------------------------------------------

LDSCRIPT := linkerscript.ld

#------------------------------------------------------------------------------
# Toolchain
#------------------------------------------------------------------------------

PREFIX  ?= arm-none-eabi-

CC      := $(PREFIX)gcc
LD      := $(PREFIX)gcc
AR      := $(PREFIX)ar
OBJCOPY := $(PREFIX)objcopy
OBJDUMP := $(PREFIX)objdump
GDB     := $(PREFIX)gdb

#------------------------------------------------------------------------------
# Compiler flags
#------------------------------------------------------------------------------

OPT   := -Os
DEBUG := -ggdb3
CSTD  := -std=c99

TGT_CFLAGS += $(OPT)
TGT_CFLAGS += $(CSTD)
TGT_CFLAGS += $(DEBUG)
TGT_CFLAGS += $(ARCH_FLAGS)

TGT_CFLAGS += -Wall
TGT_CFLAGS += -Wextra
TGT_CFLAGS += -Wshadow
TGT_CFLAGS += -Wimplicit-function-declaration
TGT_CFLAGS += -Wredundant-decls
TGT_CFLAGS += -Wmissing-prototypes
TGT_CFLAGS += -Wstrict-prototypes

TGT_CFLAGS += -fno-common
TGT_CFLAGS += -ffunction-sections
TGT_CFLAGS += -fdata-sections

#------------------------------------------------------------------------------
# Preprocessor
#------------------------------------------------------------------------------

TGT_CPPFLAGS += -MD
TGT_CPPFLAGS += $(DEFS)

TGT_CPPFLAGS += -I$(OPENCM3_DIR)/include
TGT_CPPFLAGS += -I$(SPI_DRIVER_DIR)
TGT_CPPFLAGS += -I$(FIRMWARE_DIR)
TGT_CPPFLAGS += -I$(FREERTOS_DIR)
TGT_CPPFLAGS += -I$(FREERTOS_DIR)/../portable/GCC/ARM_CM3
TGT_CPPFLAGS += -I$(CONFIG_DIR)
TGT_CPPFLAGS += -I$(SYSTEM_DIR)

#------------------------------------------------------------------------------
# Linker flags
#------------------------------------------------------------------------------

TGT_LDFLAGS += --static
TGT_LDFLAGS += -nostartfiles
TGT_LDFLAGS += -T$(LDSCRIPT)
TGT_LDFLAGS += $(ARCH_FLAGS)
TGT_LDFLAGS += $(DEBUG)

TGT_LDFLAGS += -Wl,-Map=$(BINARY).map
TGT_LDFLAGS += -Wl,--cref
TGT_LDFLAGS += -Wl,--gc-sections

#------------------------------------------------------------------------------
# Libraries
#------------------------------------------------------------------------------

LDFLAGS += -L$(OPENCM3_DIR)/lib

LDLIBS += -l$(LIBNAME)

LDLIBS += -Wl,--start-group
LDLIBS += -lc
LDLIBS += -lgcc
LDLIBS += -lnosys
LDLIBS += -Wl,--end-group

#------------------------------------------------------------------------------
# Source files
#------------------------------------------------------------------------------

OBJS += $(BINARY).o
OBJS += $(SPI_DRIVER_DIR)/spi.o
OBJS += $(SPI_DRIVER_DIR)/spi_stm32f103.o

#------------------------------------------------------------------------------
# Targets
#------------------------------------------------------------------------------

all: elf bin

elf: $(BINARY).elf

bin: $(BINARY).bin

hex: $(BINARY).hex

list: $(BINARY).list

#------------------------------------------------------------------------------
# libopencm3
#------------------------------------------------------------------------------

$(OPENCM3_DIR)/lib/lib$(LIBNAME).a:
	$(Q)$(MAKE) -C $(OPENCM3_DIR)

#------------------------------------------------------------------------------
# Linking
#------------------------------------------------------------------------------

$(BINARY).elf: $(OBJS) $(LDSCRIPT) $(OPENCM3_DIR)/lib/lib$(LIBNAME).a Makefile
	$(Q)$(LD) $(TGT_LDFLAGS) $(LDFLAGS) \
		$(OBJS) \
		$(LDLIBS) \
		-o $@

#------------------------------------------------------------------------------
# Compilation
#------------------------------------------------------------------------------

%.o: %.c
	$(Q)$(CC) \
		$(TGT_CFLAGS) \
		$(TGT_CPPFLAGS) \
		$(CFLAGS) \
		$(CPPFLAGS) \
		-c $< \
		-o $@

#------------------------------------------------------------------------------
# Binary
#------------------------------------------------------------------------------

%.bin: %.elf
	$(Q)$(OBJCOPY) -Obinary $< $@

#------------------------------------------------------------------------------
# Intel HEX
#------------------------------------------------------------------------------

%.hex: %.elf
	$(Q)$(OBJCOPY) -Oihex $< $@

#------------------------------------------------------------------------------
# Disassembly
#------------------------------------------------------------------------------

%.list: %.elf
	$(Q)$(OBJDUMP) -S $< > $@

#------------------------------------------------------------------------------
# Flash
#------------------------------------------------------------------------------

flash: $(BINARY).bin
	st-flash write $(BINARY).bin 0x08000000

#------------------------------------------------------------------------------
# Clean
#------------------------------------------------------------------------------

clean:
	$(Q)$(RM) \
		$(BINARY).elf \
		$(BINARY).bin \
		$(BINARY).hex \
		$(BINARY).list \
		$(BINARY).map \
		$(OBJS) \
		$(OBJS:.o=.d)

#------------------------------------------------------------------------------
# Dependencies
#------------------------------------------------------------------------------

-include $(OBJS:.o=.d)

.PHONY: all elf bin hex list flash clean
