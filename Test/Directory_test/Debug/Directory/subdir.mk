################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../../../Directory/Directory.c 

OBJS += \
./Directory/Directory.o 

C_DEPS += \
./Directory/Directory.d 


# Each subdirectory must supply rules for building sources it contributes
Directory/Directory.o: ../../../Directory/Directory.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Directory -I../../../String -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


