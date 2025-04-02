################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/hwh40/STM32Cube/Repository/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Source/BayesFunctions/BayesFunctions.c \
C:/Users/hwh40/STM32Cube/Repository/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Source/BayesFunctions/BayesFunctionsF16.c \
C:/Users/hwh40/STM32Cube/Repository/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.c \
C:/Users/hwh40/STM32Cube/Repository/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.c 

OBJS += \
./Source/BayesFunctions/BayesFunctions.o \
./Source/BayesFunctions/BayesFunctionsF16.o \
./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.o \
./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.o 

C_DEPS += \
./Source/BayesFunctions/BayesFunctions.d \
./Source/BayesFunctions/BayesFunctionsF16.d \
./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.d \
./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Source/BayesFunctions/BayesFunctions.o: C:/Users/hwh40/STM32Cube/Repository/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Source/BayesFunctions/BayesFunctions.c Source/BayesFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Source/BayesFunctions/BayesFunctionsF16.o: C:/Users/hwh40/STM32Cube/Repository/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Source/BayesFunctions/BayesFunctionsF16.c Source/BayesFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.o: C:/Users/hwh40/STM32Cube/Repository/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.c Source/BayesFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.o: C:/Users/hwh40/STM32Cube/Repository/Packs/ARM/CMSIS/5.8.0/CMSIS/DSP/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.c Source/BayesFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-BayesFunctions

clean-Source-2f-BayesFunctions:
	-$(RM) ./Source/BayesFunctions/BayesFunctions.cyclo ./Source/BayesFunctions/BayesFunctions.d ./Source/BayesFunctions/BayesFunctions.o ./Source/BayesFunctions/BayesFunctions.su ./Source/BayesFunctions/BayesFunctionsF16.cyclo ./Source/BayesFunctions/BayesFunctionsF16.d ./Source/BayesFunctions/BayesFunctionsF16.o ./Source/BayesFunctions/BayesFunctionsF16.su ./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.cyclo ./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.d ./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.o ./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.su ./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.cyclo ./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.d ./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.o ./Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.su

.PHONY: clean-Source-2f-BayesFunctions

