################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AVLTree_test_as_array.c \
../src/AVLTree_test_back.c \
../src/AVLTree_test_cursor_back.c \
../src/AVLTree_test_cursor_dispose.c \
../src/AVLTree_test_cursor_finish.c \
../src/AVLTree_test_cursor_forth.c \
../src/AVLTree_test_cursor_go.c \
../src/AVLTree_test_cursor_index.c \
../src/AVLTree_test_cursor_item_at.c \
../src/AVLTree_test_cursor_make.c \
../src/AVLTree_test_cursor_start.c \
../src/AVLTree_test_dispose.c \
../src/AVLTree_test_finish.c \
../src/AVLTree_test_forth.c \
../src/AVLTree_test_go.c \
../src/AVLTree_test_has.c \
../src/AVLTree_test_height.c \
../src/AVLTree_test_index.c \
../src/AVLTree_test_item_at.c \
../src/AVLTree_test_item_at_index.c \
../src/AVLTree_test_make.c \
../src/AVLTree_test_p_clonable.c \
../src/AVLTree_test_p_diterable.c \
../src/AVLTree_test_p_iterable.c \
../src/AVLTree_test_put.c \
../src/AVLTree_test_remove.c \
../src/AVLTree_test_remove_and_dispose.c \
../src/AVLTree_test_start.c \
../src/AVLTree_test_wipe_out.c \
../src/AVLTree_test_wipe_out_and_dispose.c \
../src/i_AVLTree.c \
../src/i_Clonable.c \
../src/i_DIterable.c \
../src/i_Iterable.c \
../src/main.c 

OBJS += \
./src/AVLTree_test_as_array.o \
./src/AVLTree_test_back.o \
./src/AVLTree_test_cursor_back.o \
./src/AVLTree_test_cursor_dispose.o \
./src/AVLTree_test_cursor_finish.o \
./src/AVLTree_test_cursor_forth.o \
./src/AVLTree_test_cursor_go.o \
./src/AVLTree_test_cursor_index.o \
./src/AVLTree_test_cursor_item_at.o \
./src/AVLTree_test_cursor_make.o \
./src/AVLTree_test_cursor_start.o \
./src/AVLTree_test_dispose.o \
./src/AVLTree_test_finish.o \
./src/AVLTree_test_forth.o \
./src/AVLTree_test_go.o \
./src/AVLTree_test_has.o \
./src/AVLTree_test_height.o \
./src/AVLTree_test_index.o \
./src/AVLTree_test_item_at.o \
./src/AVLTree_test_item_at_index.o \
./src/AVLTree_test_make.o \
./src/AVLTree_test_p_clonable.o \
./src/AVLTree_test_p_diterable.o \
./src/AVLTree_test_p_iterable.o \
./src/AVLTree_test_put.o \
./src/AVLTree_test_remove.o \
./src/AVLTree_test_remove_and_dispose.o \
./src/AVLTree_test_start.o \
./src/AVLTree_test_wipe_out.o \
./src/AVLTree_test_wipe_out_and_dispose.o \
./src/i_AVLTree.o \
./src/i_Clonable.o \
./src/i_DIterable.o \
./src/i_Iterable.o \
./src/main.o 

C_DEPS += \
./src/AVLTree_test_as_array.d \
./src/AVLTree_test_back.d \
./src/AVLTree_test_cursor_back.d \
./src/AVLTree_test_cursor_dispose.d \
./src/AVLTree_test_cursor_finish.d \
./src/AVLTree_test_cursor_forth.d \
./src/AVLTree_test_cursor_go.d \
./src/AVLTree_test_cursor_index.d \
./src/AVLTree_test_cursor_item_at.d \
./src/AVLTree_test_cursor_make.d \
./src/AVLTree_test_cursor_start.d \
./src/AVLTree_test_dispose.d \
./src/AVLTree_test_finish.d \
./src/AVLTree_test_forth.d \
./src/AVLTree_test_go.d \
./src/AVLTree_test_has.d \
./src/AVLTree_test_height.d \
./src/AVLTree_test_index.d \
./src/AVLTree_test_item_at.d \
./src/AVLTree_test_item_at_index.d \
./src/AVLTree_test_make.d \
./src/AVLTree_test_p_clonable.d \
./src/AVLTree_test_p_diterable.d \
./src/AVLTree_test_p_iterable.d \
./src/AVLTree_test_put.d \
./src/AVLTree_test_remove.d \
./src/AVLTree_test_remove_and_dispose.d \
./src/AVLTree_test_start.d \
./src/AVLTree_test_wipe_out.d \
./src/AVLTree_test_wipe_out_and_dispose.d \
./src/i_AVLTree.d \
./src/i_Clonable.d \
./src/i_DIterable.d \
./src/i_Iterable.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../AVLTree -I../../../Protocol_Base -I../../../P_Iterable -I../../../P_DIterable -I../../../P_Clonable -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


