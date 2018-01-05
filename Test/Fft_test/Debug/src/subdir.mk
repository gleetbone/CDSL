################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Fft_test_dispose.c \
../src/Fft_test_dispose_with_contents.c \
../src/Fft_test_fft.c \
../src/Fft_test_input.c \
../src/Fft_test_inverse_fft.c \
../src/Fft_test_log_psd.c \
../src/Fft_test_make.c \
../src/Fft_test_output.c \
../src/Fft_test_phase.c \
../src/Fft_test_phase_degrees.c \
../src/Fft_test_psd.c \
../src/Fft_test_set_input.c \
../src/Fft_test_set_output.c \
../src/Fft_utility.c \
../src/cd_Fft.c \
../src/cd_Matvec.c \
../src/cf_Fft.c \
../src/cf_Matvec.c \
../src/d_Matvec.c \
../src/f_Matvec.c \
../src/main.c 

OBJS += \
./src/Fft_test_dispose.o \
./src/Fft_test_dispose_with_contents.o \
./src/Fft_test_fft.o \
./src/Fft_test_input.o \
./src/Fft_test_inverse_fft.o \
./src/Fft_test_log_psd.o \
./src/Fft_test_make.o \
./src/Fft_test_output.o \
./src/Fft_test_phase.o \
./src/Fft_test_phase_degrees.o \
./src/Fft_test_psd.o \
./src/Fft_test_set_input.o \
./src/Fft_test_set_output.o \
./src/Fft_utility.o \
./src/cd_Fft.o \
./src/cd_Matvec.o \
./src/cf_Fft.o \
./src/cf_Matvec.o \
./src/d_Matvec.o \
./src/f_Matvec.o \
./src/main.o 

C_DEPS += \
./src/Fft_test_dispose.d \
./src/Fft_test_dispose_with_contents.d \
./src/Fft_test_fft.d \
./src/Fft_test_input.d \
./src/Fft_test_inverse_fft.d \
./src/Fft_test_log_psd.d \
./src/Fft_test_make.d \
./src/Fft_test_output.d \
./src/Fft_test_phase.d \
./src/Fft_test_phase_degrees.d \
./src/Fft_test_psd.d \
./src/Fft_test_set_input.d \
./src/Fft_test_set_output.d \
./src/Fft_utility.d \
./src/cd_Fft.d \
./src/cd_Matvec.d \
./src/cf_Fft.d \
./src/cf_Matvec.d \
./src/d_Matvec.d \
./src/f_Matvec.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Fft -I../../../Matvec -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


