################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Deque_test_count.c \
../src/Deque_test_dispose.c \
../src/Deque_test_dispose_with_contents.c \
../src/Deque_test_first.c \
../src/Deque_test_is_empty.c \
../src/Deque_test_keep_first.c \
../src/Deque_test_keep_first_and_dispose.c \
../src/Deque_test_keep_last.c \
../src/Deque_test_keep_last_and_dispose.c \
../src/Deque_test_last.c \
../src/Deque_test_make.c \
../src/Deque_test_prune_first.c \
../src/Deque_test_prune_first_and_dispose.c \
../src/Deque_test_prune_last.c \
../src/Deque_test_prune_last_and_dispose.c \
../src/Deque_test_put_first.c \
../src/Deque_test_put_last.c \
../src/Deque_test_remove_first.c \
../src/Deque_test_remove_first_and_dispose.c \
../src/Deque_test_remove_last.c \
../src/Deque_test_remove_last_and_dispose.c \
../src/Deque_test_wipe_out.c \
../src/Deque_test_wipe_out_and_dispose.c \
../src/i_Deque.c \
../src/main.c 

OBJS += \
./src/Deque_test_count.o \
./src/Deque_test_dispose.o \
./src/Deque_test_dispose_with_contents.o \
./src/Deque_test_first.o \
./src/Deque_test_is_empty.o \
./src/Deque_test_keep_first.o \
./src/Deque_test_keep_first_and_dispose.o \
./src/Deque_test_keep_last.o \
./src/Deque_test_keep_last_and_dispose.o \
./src/Deque_test_last.o \
./src/Deque_test_make.o \
./src/Deque_test_prune_first.o \
./src/Deque_test_prune_first_and_dispose.o \
./src/Deque_test_prune_last.o \
./src/Deque_test_prune_last_and_dispose.o \
./src/Deque_test_put_first.o \
./src/Deque_test_put_last.o \
./src/Deque_test_remove_first.o \
./src/Deque_test_remove_first_and_dispose.o \
./src/Deque_test_remove_last.o \
./src/Deque_test_remove_last_and_dispose.o \
./src/Deque_test_wipe_out.o \
./src/Deque_test_wipe_out_and_dispose.o \
./src/i_Deque.o \
./src/main.o 

C_DEPS += \
./src/Deque_test_count.d \
./src/Deque_test_dispose.d \
./src/Deque_test_dispose_with_contents.d \
./src/Deque_test_first.d \
./src/Deque_test_is_empty.d \
./src/Deque_test_keep_first.d \
./src/Deque_test_keep_first_and_dispose.d \
./src/Deque_test_keep_last.d \
./src/Deque_test_keep_last_and_dispose.d \
./src/Deque_test_last.d \
./src/Deque_test_make.d \
./src/Deque_test_prune_first.d \
./src/Deque_test_prune_first_and_dispose.d \
./src/Deque_test_prune_last.d \
./src/Deque_test_prune_last_and_dispose.d \
./src/Deque_test_put_first.d \
./src/Deque_test_put_last.d \
./src/Deque_test_remove_first.d \
./src/Deque_test_remove_first_and_dispose.d \
./src/Deque_test_remove_last.d \
./src/Deque_test_remove_last_and_dispose.d \
./src/Deque_test_wipe_out.d \
./src/Deque_test_wipe_out_and_dispose.d \
./src/i_Deque.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Deque -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


