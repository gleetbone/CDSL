################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/RBTree_test_as_array.c \
../src/RBTree_test_as_string.c \
../src/RBTree_test_back.c \
../src/RBTree_test_cursor_back.c \
../src/RBTree_test_cursor_dispose.c \
../src/RBTree_test_cursor_finish.c \
../src/RBTree_test_cursor_forth.c \
../src/RBTree_test_cursor_go.c \
../src/RBTree_test_cursor_index.c \
../src/RBTree_test_cursor_item_at.c \
../src/RBTree_test_cursor_make.c \
../src/RBTree_test_cursor_start.c \
../src/RBTree_test_dispose.c \
../src/RBTree_test_finish.c \
../src/RBTree_test_forth.c \
../src/RBTree_test_go.c \
../src/RBTree_test_has.c \
../src/RBTree_test_height.c \
../src/RBTree_test_index.c \
../src/RBTree_test_item_at.c \
../src/RBTree_test_item_at_index.c \
../src/RBTree_test_make.c \
../src/RBTree_test_p_clonable.c \
../src/RBTree_test_p_diterable.c \
../src/RBTree_test_p_iterable.c \
../src/RBTree_test_print_utility.c \
../src/RBTree_test_put.c \
../src/RBTree_test_remove.c \
../src/RBTree_test_remove_and_dispose.c \
../src/RBTree_test_start.c \
../src/RBTree_test_wipe_out.c \
../src/RBTree_test_wipe_out_and_dispose.c \
../src/i_Clonable.c \
../src/i_DIterable.c \
../src/i_Iterable.c \
../src/i_RBTree.c \
../src/main.c 

OBJS += \
./src/RBTree_test_as_array.o \
./src/RBTree_test_as_string.o \
./src/RBTree_test_back.o \
./src/RBTree_test_cursor_back.o \
./src/RBTree_test_cursor_dispose.o \
./src/RBTree_test_cursor_finish.o \
./src/RBTree_test_cursor_forth.o \
./src/RBTree_test_cursor_go.o \
./src/RBTree_test_cursor_index.o \
./src/RBTree_test_cursor_item_at.o \
./src/RBTree_test_cursor_make.o \
./src/RBTree_test_cursor_start.o \
./src/RBTree_test_dispose.o \
./src/RBTree_test_finish.o \
./src/RBTree_test_forth.o \
./src/RBTree_test_go.o \
./src/RBTree_test_has.o \
./src/RBTree_test_height.o \
./src/RBTree_test_index.o \
./src/RBTree_test_item_at.o \
./src/RBTree_test_item_at_index.o \
./src/RBTree_test_make.o \
./src/RBTree_test_p_clonable.o \
./src/RBTree_test_p_diterable.o \
./src/RBTree_test_p_iterable.o \
./src/RBTree_test_print_utility.o \
./src/RBTree_test_put.o \
./src/RBTree_test_remove.o \
./src/RBTree_test_remove_and_dispose.o \
./src/RBTree_test_start.o \
./src/RBTree_test_wipe_out.o \
./src/RBTree_test_wipe_out_and_dispose.o \
./src/i_Clonable.o \
./src/i_DIterable.o \
./src/i_Iterable.o \
./src/i_RBTree.o \
./src/main.o 

C_DEPS += \
./src/RBTree_test_as_array.d \
./src/RBTree_test_as_string.d \
./src/RBTree_test_back.d \
./src/RBTree_test_cursor_back.d \
./src/RBTree_test_cursor_dispose.d \
./src/RBTree_test_cursor_finish.d \
./src/RBTree_test_cursor_forth.d \
./src/RBTree_test_cursor_go.d \
./src/RBTree_test_cursor_index.d \
./src/RBTree_test_cursor_item_at.d \
./src/RBTree_test_cursor_make.d \
./src/RBTree_test_cursor_start.d \
./src/RBTree_test_dispose.d \
./src/RBTree_test_finish.d \
./src/RBTree_test_forth.d \
./src/RBTree_test_go.d \
./src/RBTree_test_has.d \
./src/RBTree_test_height.d \
./src/RBTree_test_index.d \
./src/RBTree_test_item_at.d \
./src/RBTree_test_item_at_index.d \
./src/RBTree_test_make.d \
./src/RBTree_test_p_clonable.d \
./src/RBTree_test_p_diterable.d \
./src/RBTree_test_p_iterable.d \
./src/RBTree_test_print_utility.d \
./src/RBTree_test_put.d \
./src/RBTree_test_remove.d \
./src/RBTree_test_remove_and_dispose.d \
./src/RBTree_test_start.d \
./src/RBTree_test_wipe_out.d \
./src/RBTree_test_wipe_out_and_dispose.d \
./src/i_Clonable.d \
./src/i_DIterable.d \
./src/i_Iterable.d \
./src/i_RBTree.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../RBTree -I../../../Protocol_Base -I../../../P_Iterable -I../../../P_DIterable -I../../../P_Clonable -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


