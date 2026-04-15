################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Clock.o: /home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/inc/Clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/hailin/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

FIFO.o: /home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/inc/FIFO.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/hailin/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.o: /home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/inc/LaunchPad.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/hailin/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

UART.o: /home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/inc/UART.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/hailin/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

UARTints.o: /home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/inc/UARTints.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/hailin/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/hailin/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source/third_party/CMSIS/Core/Include" -I"/home/hailin/ti/mspm0_sdk_2_09_00_01/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/home/hailin/chenh/Hailin_stuff/tech_applications/319k/MSPM0_ValvanoWare/UART_ints/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


