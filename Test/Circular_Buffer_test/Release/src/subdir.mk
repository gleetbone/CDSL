################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Circular_Buffer_test_capacity.c \
../src/Circular_Buffer_test_count.c \
../src/Circular_Buffer_test_dispose.c \
../src/Circular_Buffer_test_forth.c \
../src/Circular_Buffer_test_is_empty.c \
../src/Circular_Buffer_test_is_full.c \
../src/Circular_Buffer_test_item.c \
../src/Circular_Buffer_test_make.c \
../src/Circular_Buffer_test_put.c \
../src/Circular_Buffer_test_wipe_out.c \
../src/i_Circular_Buffer.c \
../src/main.c 

OBJS += \
./src/Circular_Buffer_test_capacity.o \
./src/Circular_Buffer_test_count.o \
./src/Circular_Buffer_test_dispose.o \
./src/Circular_Buffer_test_forth.o \
./src/Circular_Buffer_test_is_empty.o \
./src/Circular_Buffer_test_is_full.o \
./src/Circular_Buffer_test_item.o \
./src/Circular_Buffer_test_make.o \
./src/Circular_Buffer_test_put.o \
./src/Circular_Buffer_test_wipe_out.o \
./src/i_Circular_Buffer.o \
./src/main.o 

C_DEPS += \
./src/Circular_Buffer_test_capacity.d \
./src/Circular_Buffer_test_count.d \
./src/Circular_Buffer_test_dispose.d \
./src/Circular_Buffer_test_forth.d \
./src/Circular_Buffer_test_is_empty.d \
./src/Circular_Buffer_test_is_full.d \
./src/Circular_Buffer_test_item.d \
./src/Circular_Buffer_test_make.d \
./src/Circular_Buffer_test_put.d \
./src/Circular_Buffer_test_wipe_out.d \
./src/i_Circular_Buffer.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Circular_Buffer -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


