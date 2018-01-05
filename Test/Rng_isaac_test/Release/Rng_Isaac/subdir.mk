################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../../../Rng_Isaac/Rng_Isaac.c \
../../../Rng_Isaac/Rng_Isaac_gaussian.c 

OBJS += \
./Rng_Isaac/Rng_Isaac.o \
./Rng_Isaac/Rng_Isaac_gaussian.o 

C_DEPS += \
./Rng_Isaac/Rng_Isaac.d \
./Rng_Isaac/Rng_Isaac_gaussian.d 


# Each subdirectory must supply rules for building sources it contributes
Rng_Isaac/Rng_Isaac.o: ../../../Rng_Isaac/Rng_Isaac.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Rng_Isaac -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Rng_Isaac/Rng_Isaac_gaussian.o: ../../../Rng_Isaac/Rng_Isaac_gaussian.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Rng_Isaac -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


