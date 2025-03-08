# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Project name
TARGET = test

# Directories
SRC_DIR = src
SYNERGY_DIR = synergy
BUILD_DIR = Build
SCRIPT_DIR = script

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/synergy_gen/*.c) \
       $(wildcard $(SYNERGY_DIR)/board/s7g2_sk/*.c) \
       $(wildcard $(SYNERGY_DIR)/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source/*.c) \
       $(wildcard $(SYNERGY_DIR)/ssp/src/bsp/mcu/all/*.c) \
       $(wildcard $(SYNERGY_DIR)/ssp/src/bsp/mcu/s7g2/*.c) \
       $(wildcard $(SYNERGY_DIR)/ssp/src/driver/r_cgc/*.c) \
       $(wildcard $(SYNERGY_DIR)/ssp/src/driver/r_elc/*.c) \
       $(wildcard $(SYNERGY_DIR)/ssp/src/driver/r_ioport/*.c)

# Object files
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

# Include paths
INCLUDES = -I$(SRC_DIR) \
           -I$(SRC_DIR)/synergy_gen \
           -I$(SYNERGY_DIR)/board/s7g2_sk \
           -I$(SYNERGY_DIR)/ssp/inc/bsp \
           -I$(SYNERGY_DIR)/ssp/inc/bsp/cmsis/Include \
           -I$(SYNERGY_DIR)/ssp/inc/driver/api \
           -I$(SYNERGY_DIR)/ssp/inc/driver/instances \
           -I$(SYNERGY_DIR)/ssp/inc

# Compiler flags
CFLAGS = -mcpu=cortex-m4 -mthumb -Og -g3 -Wall -ffunction-sections -fdata-sections \
         -std=gnu11 $(INCLUDES)

# Linker flags
LDFLAGS = -mcpu=cortex-m4 -mthumb -Wl,--gc-sections -T$(SCRIPT_DIR)/r7fs7g27h3a01cfc.ld \
          -Wl,-Map=$(BUILD_DIR)/$(TARGET).map \
          $(OBJS) \
          /home/nicko/work/Renesas-SK-S7G2_devel/synergy/ssp/src/driver/r_fmi/libs/libfmi_cm4_s7g2_gcc.a \
	  /home/nicko/work/Renesas-SK-S7G2_devel/synergy/ssp/src/bsp/mcu/s7g2/libfmi_R7FS7G27H3A01CFC_gcc.a

##enable VFP vector floating point registers.
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

# Default target
all: $(BUILD_DIR)/$(TARGET).elf

# Create Build directory structure
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/src
	mkdir -p $(BUILD_DIR)/src/synergy_gen
	mkdir -p $(BUILD_DIR)/synergy/board/s7g2_sk
	mkdir -p $(BUILD_DIR)/synergy/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source
	mkdir -p $(BUILD_DIR)/synergy/ssp/src/bsp/mcu/all
	mkdir -p $(BUILD_DIR)/synergy/ssp/src/bsp/mcu/s7g2
	mkdir -p $(BUILD_DIR)/synergy/ssp/src/driver/r_cgc
	mkdir -p $(BUILD_DIR)/synergy/ssp/src/driver/r_elc
	mkdir -p $(BUILD_DIR)/synergy/ssp/src/driver/r_ioport

# Compile source files into object files
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into final ELF file
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@
	$(SIZE) $@

# Generate HEX file from ELF
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
