################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Svd_test_dispose.c \
../src/Svd_test_dispose_with_contents.c \
../src/Svd_test_input.c \
../src/Svd_test_inverse.c \
../src/Svd_test_make.c \
../src/Svd_test_reconstructed_input.c \
../src/Svd_test_set_input.c \
../src/Svd_test_set_rotation_error.c \
../src/Svd_test_set_singular_value_threshold.c \
../src/Svd_test_svd.c \
../src/cd_Matvec.c \
../src/cd_Svd.c \
../src/cf_Matvec.c \
../src/cf_Svd.c \
../src/d_Matvec.c \
../src/d_Svd.c \
../src/f_Matvec.c \
../src/f_Svd.c \
../src/main.c 

OBJS += \
./src/Svd_test_dispose.o \
./src/Svd_test_dispose_with_contents.o \
./src/Svd_test_input.o \
./src/Svd_test_inverse.o \
./src/Svd_test_make.o \
./src/Svd_test_reconstructed_input.o \
./src/Svd_test_set_input.o \
./src/Svd_test_set_rotation_error.o \
./src/Svd_test_set_singular_value_threshold.o \
./src/Svd_test_svd.o \
./src/cd_Matvec.o \
./src/cd_Svd.o \
./src/cf_Matvec.o \
./src/cf_Svd.o \
./src/d_Matvec.o \
./src/d_Svd.o \
./src/f_Matvec.o \
./src/f_Svd.o \
./src/main.o 

C_DEPS += \
./src/Svd_test_dispose.d \
./src/Svd_test_dispose_with_contents.d \
./src/Svd_test_input.d \
./src/Svd_test_inverse.d \
./src/Svd_test_make.d \
./src/Svd_test_reconstructed_input.d \
./src/Svd_test_set_input.d \
./src/Svd_test_set_rotation_error.d \
./src/Svd_test_set_singular_value_threshold.d \
./src/Svd_test_svd.d \
./src/cd_Matvec.d \
./src/cd_Svd.d \
./src/cf_Matvec.d \
./src/cf_Svd.d \
./src/d_Matvec.d \
./src/d_Svd.d \
./src/f_Matvec.d \
./src/f_Svd.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Matvec -I../../../Svd -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


