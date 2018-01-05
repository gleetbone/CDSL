################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PQueue_test_count.c \
../src/PQueue_test_dispose.c \
../src/PQueue_test_dispose_with_contents.c \
../src/PQueue_test_is_empty.c \
../src/PQueue_test_item.c \
../src/PQueue_test_keep.c \
../src/PQueue_test_keep_and_dispose.c \
../src/PQueue_test_make.c \
../src/PQueue_test_prune.c \
../src/PQueue_test_prune_and_dispose.c \
../src/PQueue_test_put.c \
../src/PQueue_test_remove.c \
../src/PQueue_test_remove_and_dispose.c \
../src/PQueue_test_wipe_out.c \
../src/PQueue_test_wipe_out_and_dispose.c \
../src/int_PQueue.c \
../src/main.c 

OBJS += \
./src/PQueue_test_count.o \
./src/PQueue_test_dispose.o \
./src/PQueue_test_dispose_with_contents.o \
./src/PQueue_test_is_empty.o \
./src/PQueue_test_item.o \
./src/PQueue_test_keep.o \
./src/PQueue_test_keep_and_dispose.o \
./src/PQueue_test_make.o \
./src/PQueue_test_prune.o \
./src/PQueue_test_prune_and_dispose.o \
./src/PQueue_test_put.o \
./src/PQueue_test_remove.o \
./src/PQueue_test_remove_and_dispose.o \
./src/PQueue_test_wipe_out.o \
./src/PQueue_test_wipe_out_and_dispose.o \
./src/int_PQueue.o \
./src/main.o 

C_DEPS += \
./src/PQueue_test_count.d \
./src/PQueue_test_dispose.d \
./src/PQueue_test_dispose_with_contents.d \
./src/PQueue_test_is_empty.d \
./src/PQueue_test_item.d \
./src/PQueue_test_keep.d \
./src/PQueue_test_keep_and_dispose.d \
./src/PQueue_test_make.d \
./src/PQueue_test_prune.d \
./src/PQueue_test_prune_and_dispose.d \
./src/PQueue_test_put.d \
./src/PQueue_test_remove.d \
./src/PQueue_test_remove_and_dispose.d \
./src/PQueue_test_wipe_out.d \
./src/PQueue_test_wipe_out_and_dispose.d \
./src/int_PQueue.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../PQueue -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


