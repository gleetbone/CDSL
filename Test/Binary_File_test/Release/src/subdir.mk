################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/binary_file_info.c \
../src/binary_file_make.c \
../src/binary_file_movement.c \
../src/binary_file_name.c \
../src/binary_file_open.c \
../src/binary_file_read_put.c \
../src/main.c 

OBJS += \
./src/binary_file_info.o \
./src/binary_file_make.o \
./src/binary_file_movement.o \
./src/binary_file_name.o \
./src/binary_file_open.o \
./src/binary_file_read_put.o \
./src/main.o 

C_DEPS += \
./src/binary_file_info.d \
./src/binary_file_make.d \
./src/binary_file_movement.d \
./src/binary_file_name.d \
./src/binary_file_open.d \
./src/binary_file_read_put.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Binary_File -I../../../String -I../../../Raw_Buffer -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


