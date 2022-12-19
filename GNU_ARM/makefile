
#/*---------------------------------------------------------------------------------------------------------*/
#/* Compiler Setting                                                                                        */
#/*---------------------------------------------------------------------------------------------------------*/
ARM_CORE = cortex-m0
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
AR = arm-none-eabi-ar
LD = arm-none-eabi-ld 
SIZE = arm-none-eabi-size
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
#GNU_PATH = C:/Program Files (x86)/GNU Tools Arm Embedded/7 2018-q2-update/


#/*---------------------------------------------------------------------------------------------------------*/
#/* Target Setting                                                                                          */
#/*---------------------------------------------------------------------------------------------------------*/
CHIP_NAME = 52253
STARTUP = startup_ht32f5xxxx_gcc_01
TARGET_NAME = ph_ht32_blynk_fw

#/*---------------------------------------------------------------------------------------------------------*/
#/* Options: CC, Assembeler, Linker                                                                         */
#/*---------------------------------------------------------------------------------------------------------*/
ARCH_OPTION = -mcpu=$(ARM_CORE) -mthumb -mthumb-interwork
C_OPTION = -gdwarf-2 -MD -Wall -Os -mapcs-frame -ffunction-sections -fdata-sections
L_OPTION = -Wl,-Map=$(TARGET_NAME).map -Wl,--gc-sections --specs=nano.specs


#/*---------------------------------------------------------------------------------------------------------*/
#/* Preprocessor Define                                                                                     */
#/*---------------------------------------------------------------------------------------------------------*/
C_OPTION += -DUSE_HT32_DRIVER
C_OPTION += -DUSE_HT32F52253_SK
C_OPTION += -DUSE_HT32F52243_53
C_OPTION += -DUSE_MEM_HT32F52253
S_OPTION = --defsym USE_HT32_CHIP=5


#/*---------------------------------------------------------------------------------------------------------*/
#/* Include Path                                                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
INCLUDE_PATH += -I../Inc \
-I../library/CMSIS/Include \
-I../library/Device/Holtek/HT32F5xxxx/Include \
-I../library/HT32F5xxxx_Driver/inc \
-I../utilities \
-I../utilities/common \
-I../Application
#/*---------------------------------------------------------------------------------------------------------*/
#/* Source files                                                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
SOURCE_NAME_PATH += ../Src/main.c
# SOURCE_NAME_PATH += ../Src/i2c.c 
# SOURCE_NAME_PATH += ../Src/hs3001.c
SOURCE_NAME_PATH += ../Src/ht32f5xxxx_01_it.c
SOURCE_NAME_PATH += ../Src/system_ht32f5xxxx_02.c
# SOURCE_NAME_PATH += ../Src/Uart_User.c
# SOURCE_NAME_PATH += ../Src/RA_ZMOD4410.c
#SOURCE_NAME_PATH += ../ADD_YOUR_C_CODE_FILE_HERE.c

HT32_LIB_PATH = ../library/HT32F5xxxx_Driver/src/
HT32_UTL_PATH = ../utilities/
HT32_App_PATH = ../Application/

SOURCE_NAME_PATH += \
$(HT32_LIB_PATH)ht32_cm0plus_misc.c \
$(HT32_LIB_PATH)ht32f5xxxx_adc.c \
$(HT32_LIB_PATH)ht32f5xxxx_bftm.c \
$(HT32_LIB_PATH)ht32f5xxxx_ckcu.c \
$(HT32_LIB_PATH)ht32f5xxxx_crc.c \
$(HT32_LIB_PATH)ht32f5xxxx_div.c \
$(HT32_LIB_PATH)ht32f5xxxx_exti.c \
$(HT32_LIB_PATH)ht32f5xxxx_flash.c \
$(HT32_LIB_PATH)ht32f5xxxx_gpio.c \
$(HT32_LIB_PATH)ht32f5xxxx_i2c.c \
$(HT32_LIB_PATH)ht32f5xxxx_mctm.c \
$(HT32_LIB_PATH)ht32f5xxxx_pdma.c \
$(HT32_LIB_PATH)ht32f5xxxx_pwrcu.c \
$(HT32_LIB_PATH)ht32f5xxxx_rstcu.c \
$(HT32_LIB_PATH)ht32f5xxxx_rtc.c \
$(HT32_LIB_PATH)ht32f5xxxx_spi.c \
$(HT32_LIB_PATH)ht32f5xxxx_tm.c \
$(HT32_LIB_PATH)ht32f5xxxx_usart.c \
$(HT32_LIB_PATH)ht32f5xxxx_wdt.c \
$(HT32_LIB_PATH)ht32_retarget.c \
$(HT32_LIB_PATH)ht32_serial.c \
$(HT32_LIB_PATH)printf.c \
$(HT32_LIB_PATH)syscalls.c \
$(HT32_UTL_PATH)ht32_board.c \

#/*---------------------------------------------------------------------------------------------------------*/
#/* MISC Setting                                                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
LINK_NAME_PATH = linker.ld
START_NAME_PATH = $(STARTUP).s

C_OBJECT_OPTION = $(ARCH_OPTION) $(C_OPTION) -c
S_OBJECT_OPTION = $(ARCH_OPTION) $(S_OPTION)
LINK_OPTION = $(ARCH_OPTION) $(L_OPTION) 

HEX_OPTION = -O ihex
BIN_OPTION = -O binary -S
TEXT_OPTION = -D
#TEXT_OPTION = -S


#/*---------------------------------------------------------------------------------------------------------*/
#/* Make Targets                                                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
all:$(TARGET_NAME).elf $(TARGET_NAME).hex $(TARGET_NAME).bin
	$(SIZE) $(TARGET_NAME).elf
	@echo ========
	@echo BUILD SUCCESS

$(TARGET_NAME).elf: $(START_NAME_PATH) $(SOURCE_NAME_PATH)
	$(AS) $(S_OBJECT_OPTION) $(START_NAME_PATH) -o $(STARTUP).o
	$(CC) $(C_OBJECT_OPTION) $(INCLUDE_PATH) $(SOURCE_NAME_PATH)
	$(CC) -T$(LINK_NAME_PATH) $(LINK_OPTION) *.o -o $(TARGET_NAME).elf

$(TARGET_NAME).hex: $(TARGET_NAME).elf
	$(OBJCOPY) $(HEX_OPTION) $(TARGET_NAME).elf $(TARGET_NAME).hex

$(TARGET_NAME).bin: $(TARGET_NAME).elf
	$(OBJCOPY) $(BIN_OPTION) $(TARGET_NAME).elf $(TARGET_NAME).bin

#/*---------------------------------------------------------------------------------------------------------*/
#/* Flash device                                                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
device = HT32F52253
#/*---------------------------------------------------------------------------------------------------------*/
#/* Make Jflash - flash device                                                                              */
#/*---------------------------------------------------------------------------------------------------------*/
jflash: $(TARGET_NAME).bin
	@touch $@
	@echo device $(device) > $@
	@echo -e si 1'\n'speed 1000 >> $@
	@echo -e r '\n'LoadFile $< >> $@
	@echo -e r'\n'g'\n'qc >>$@

flash: jflash
	/home/smartth/tools/JLink_Linux_V782c_x86_64/JLinkExe -commanderscript $<
#/*---------------------------------------------------------------------------------------------------------*/
#/* Make eflash - erase chip before flash device                                                            */
#/*---------------------------------------------------------------------------------------------------------*/
eraseflash: $(TARGET_NAME).bin
	@touch $@
	@echo device $(device) > $@
	@echo -e si 1'\n'speed 1000 >> $@
	@echo -e Erase >> $@
	@echo -e r '\n'LoadFile $< >> $@
	@echo -e r'\n'g'\n'qc >>$@

eflash: eraseflash
	/home/smartth/tools/JLink_Linux_V782c_x86_64/JLinkExe -commanderscript $<

#/*---------------------------------------------------------------------------------------------------------*/
#/* Make clean- clean build targets                                                                         */
#/*---------------------------------------------------------------------------------------------------------*/
clean:
	@echo -
	-rm -f *.o *.bin *.elf *.hex *.map *.d 1>nul 2>&1 || (exit 0)
	@echo ========
	@echo CLEAN SUCCESS

