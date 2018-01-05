################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BSTree_test_as_array.c \
../src/BSTree_test_back.c \
../src/BSTree_test_balance.c \
../src/BSTree_test_cursor_back.c \
../src/BSTree_test_cursor_dispose.c \
../src/BSTree_test_cursor_finish.c \
../src/BSTree_test_cursor_forth.c \
../src/BSTree_test_cursor_go.c \
../src/BSTree_test_cursor_index.c \
../src/BSTree_test_cursor_item_at.c \
../src/BSTree_test_cursor_make.c \
../src/BSTree_test_cursor_start.c \
../src/BSTree_test_dispose.c \
../src/BSTree_test_finish.c \
../src/BSTree_test_forth.c \
../src/BSTree_test_go.c \
../src/BSTree_test_has.c \
../src/BSTree_test_height.c \
../src/BSTree_test_index.c \
../src/BSTree_test_item_at.c \
../src/BSTree_test_item_at_index.c \
../src/BSTree_test_make.c \
../src/BSTree_test_p_clonable.c \
../src/BSTree_test_p_diterable.c \
../src/BSTree_test_p_iterable.c \
../src/BSTree_test_put.c \
../src/BSTree_test_remove.c \
../src/BSTree_test_remove_and_dispose.c \
../src/BSTree_test_start.c \
../src/BSTree_test_wipe_out.c \
../src/BSTree_test_wipe_out_and_dispose.c \
../src/i_BSTree.c \
../src/i_Clonable.c \
../src/i_DIterable.c \
../src/i_Iterable.c \
../src/main.c 

OBJS += \
./src/BSTree_test_as_array.o \
./src/BSTree_test_back.o \
./src/BSTree_test_balance.o \
./src/BSTree_test_cursor_back.o \
./src/BSTree_test_cursor_dispose.o \
./src/BSTree_test_cursor_finish.o \
./src/BSTree_test_cursor_forth.o \
./src/BSTree_test_cursor_go.o \
./src/BSTree_test_cursor_index.o \
./src/BSTree_test_cursor_item_at.o \
./src/BSTree_test_cursor_make.o \
./src/BSTree_test_cursor_start.o \
./src/BSTree_test_dispose.o \
./src/BSTree_test_finish.o \
./src/BSTree_test_forth.o \
./src/BSTree_test_go.o \
./src/BSTree_test_has.o \
./src/BSTree_test_height.o \
./src/BSTree_test_index.o \
./src/BSTree_test_item_at.o \
./src/BSTree_test_item_at_index.o \
./src/BSTree_test_make.o \
./src/BSTree_test_p_clonable.o \
./src/BSTree_test_p_diterable.o \
./src/BSTree_test_p_iterable.o \
./src/BSTree_test_put.o \
./src/BSTree_test_remove.o \
./src/BSTree_test_remove_and_dispose.o \
./src/BSTree_test_start.o \
./src/BSTree_test_wipe_out.o \
./src/BSTree_test_wipe_out_and_dispose.o \
./src/i_BSTree.o \
./src/i_Clonable.o \
./src/i_DIterable.o \
./src/i_Iterable.o \
./src/main.o 

C_DEPS += \
./src/BSTree_test_as_array.d \
./src/BSTree_test_back.d \
./src/BSTree_test_balance.d \
./src/BSTree_test_cursor_back.d \
./src/BSTree_test_cursor_dispose.d \
./src/BSTree_test_cursor_finish.d \
./src/BSTree_test_cursor_forth.d \
./src/BSTree_test_cursor_go.d \
./src/BSTree_test_cursor_index.d \
./src/BSTree_test_cursor_item_at.d \
./src/BSTree_test_cursor_make.d \
./src/BSTree_test_cursor_start.d \
./src/BSTree_test_dispose.d \
./src/BSTree_test_finish.d \
./src/BSTree_test_forth.d \
./src/BSTree_test_go.d \
./src/BSTree_test_has.d \
./src/BSTree_test_height.d \
./src/BSTree_test_index.d \
./src/BSTree_test_item_at.d \
./src/BSTree_test_item_at_index.d \
./src/BSTree_test_make.d \
./src/BSTree_test_p_clonable.d \
./src/BSTree_test_p_diterable.d \
./src/BSTree_test_p_iterable.d \
./src/BSTree_test_put.d \
./src/BSTree_test_remove.d \
./src/BSTree_test_remove_and_dispose.d \
./src/BSTree_test_start.d \
./src/BSTree_test_wipe_out.d \
./src/BSTree_test_wipe_out_and_dispose.d \
./src/i_BSTree.d \
./src/i_Clonable.d \
./src/i_DIterable.d \
./src/i_Iterable.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../BSTree -I../../../Protocol_Base -I../../../P_Clonable -I../../../P_Iterable -I../../../P_DIterable -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


