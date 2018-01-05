################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Stack_test_count.c \
../src/Stack_test_dispose.c \
../src/Stack_test_dispose_with_contents.c \
../src/Stack_test_is_empty.c \
../src/Stack_test_item.c \
../src/Stack_test_keep.c \
../src/Stack_test_keep_and_dispose.c \
../src/Stack_test_make.c \
../src/Stack_test_prune.c \
../src/Stack_test_prune_and_dispose.c \
../src/Stack_test_put.c \
../src/Stack_test_remove.c \
../src/Stack_test_remove_and_dispose.c \
../src/Stack_test_replace.c \
../src/Stack_test_replace_and_dispose.c \
../src/Stack_test_wipe_out.c \
../src/Stack_test_wipe_out_and_dispose.c \
../src/int_Stack.c \
../src/main.c 

OBJS += \
./src/Stack_test_count.o \
./src/Stack_test_dispose.o \
./src/Stack_test_dispose_with_contents.o \
./src/Stack_test_is_empty.o \
./src/Stack_test_item.o \
./src/Stack_test_keep.o \
./src/Stack_test_keep_and_dispose.o \
./src/Stack_test_make.o \
./src/Stack_test_prune.o \
./src/Stack_test_prune_and_dispose.o \
./src/Stack_test_put.o \
./src/Stack_test_remove.o \
./src/Stack_test_remove_and_dispose.o \
./src/Stack_test_replace.o \
./src/Stack_test_replace_and_dispose.o \
./src/Stack_test_wipe_out.o \
./src/Stack_test_wipe_out_and_dispose.o \
./src/int_Stack.o \
./src/main.o 

C_DEPS += \
./src/Stack_test_count.d \
./src/Stack_test_dispose.d \
./src/Stack_test_dispose_with_contents.d \
./src/Stack_test_is_empty.d \
./src/Stack_test_item.d \
./src/Stack_test_keep.d \
./src/Stack_test_keep_and_dispose.d \
./src/Stack_test_make.d \
./src/Stack_test_prune.d \
./src/Stack_test_prune_and_dispose.d \
./src/Stack_test_put.d \
./src/Stack_test_remove.d \
./src/Stack_test_remove_and_dispose.d \
./src/Stack_test_replace.d \
./src/Stack_test_replace_and_dispose.d \
./src/Stack_test_wipe_out.d \
./src/Stack_test_wipe_out_and_dispose.d \
./src/int_Stack.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Stack -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


