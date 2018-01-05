################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Queue_test_count.c \
../src/Queue_test_dispose.c \
../src/Queue_test_dispose_with_contents.c \
../src/Queue_test_is_empty.c \
../src/Queue_test_item.c \
../src/Queue_test_keep.c \
../src/Queue_test_keep_and_dispose.c \
../src/Queue_test_make.c \
../src/Queue_test_prune.c \
../src/Queue_test_prune_and_dispose.c \
../src/Queue_test_put.c \
../src/Queue_test_remove.c \
../src/Queue_test_remove_and_dispose.c \
../src/Queue_test_wipe_out.c \
../src/Queue_test_wipe_out_and_dispose.c \
../src/int_Queue.c \
../src/main.c 

OBJS += \
./src/Queue_test_count.o \
./src/Queue_test_dispose.o \
./src/Queue_test_dispose_with_contents.o \
./src/Queue_test_is_empty.o \
./src/Queue_test_item.o \
./src/Queue_test_keep.o \
./src/Queue_test_keep_and_dispose.o \
./src/Queue_test_make.o \
./src/Queue_test_prune.o \
./src/Queue_test_prune_and_dispose.o \
./src/Queue_test_put.o \
./src/Queue_test_remove.o \
./src/Queue_test_remove_and_dispose.o \
./src/Queue_test_wipe_out.o \
./src/Queue_test_wipe_out_and_dispose.o \
./src/int_Queue.o \
./src/main.o 

C_DEPS += \
./src/Queue_test_count.d \
./src/Queue_test_dispose.d \
./src/Queue_test_dispose_with_contents.d \
./src/Queue_test_is_empty.d \
./src/Queue_test_item.d \
./src/Queue_test_keep.d \
./src/Queue_test_keep_and_dispose.d \
./src/Queue_test_make.d \
./src/Queue_test_prune.d \
./src/Queue_test_prune_and_dispose.d \
./src/Queue_test_put.d \
./src/Queue_test_remove.d \
./src/Queue_test_remove_and_dispose.d \
./src/Queue_test_wipe_out.d \
./src/Queue_test_wipe_out_and_dispose.d \
./src/int_Queue.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Queue -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


