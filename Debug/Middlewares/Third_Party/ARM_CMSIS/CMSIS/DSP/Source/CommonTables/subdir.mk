################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTables.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTablesF16.c 

OBJS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTables.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTablesF16.o 

C_DEPS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTables.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTablesF16.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/%.o Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/%.su Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/%.cyclo: ../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/%.c Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables

clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables:
	-$(RM) ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTables.cyclo ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTables.d ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTables.o ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTables.su ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTablesF16.cyclo ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTablesF16.d ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTablesF16.o ./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/CommonTables/CommonTablesF16.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables

