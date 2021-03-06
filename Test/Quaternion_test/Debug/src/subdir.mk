################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Quaternion_test_add.c \
../src/Quaternion_test_added.c \
../src/Quaternion_test_as_array.c \
../src/Quaternion_test_as_vector.c \
../src/Quaternion_test_conjugate.c \
../src/Quaternion_test_conjugated.c \
../src/Quaternion_test_dispose.c \
../src/Quaternion_test_get_pitch.c \
../src/Quaternion_test_get_pitch_degrees.c \
../src/Quaternion_test_get_roll.c \
../src/Quaternion_test_get_roll_degrees.c \
../src/Quaternion_test_get_roll_pitch_yaw.c \
../src/Quaternion_test_get_roll_pitch_yaw_degrees.c \
../src/Quaternion_test_get_yaw.c \
../src/Quaternion_test_get_yaw_degrees.c \
../src/Quaternion_test_interpolate.c \
../src/Quaternion_test_interpolated.c \
../src/Quaternion_test_inverse.c \
../src/Quaternion_test_invert.c \
../src/Quaternion_test_is_approximately_equal.c \
../src/Quaternion_test_is_equal.c \
../src/Quaternion_test_magnitude.c \
../src/Quaternion_test_make.c \
../src/Quaternion_test_make_default.c \
../src/Quaternion_test_make_from.c \
../src/Quaternion_test_make_from_array.c \
../src/Quaternion_test_make_from_pitch.c \
../src/Quaternion_test_make_from_pitch_degrees.c \
../src/Quaternion_test_make_from_roll.c \
../src/Quaternion_test_make_from_roll_degrees.c \
../src/Quaternion_test_make_from_roll_pitch_yaw.c \
../src/Quaternion_test_make_from_roll_pitch_yaw_degrees.c \
../src/Quaternion_test_make_from_rotation_about_vector.c \
../src/Quaternion_test_make_from_rotation_about_xyz.c \
../src/Quaternion_test_make_from_rotation_degrees_about_vector.c \
../src/Quaternion_test_make_from_rotation_degrees_about_xyz.c \
../src/Quaternion_test_make_from_vector.c \
../src/Quaternion_test_make_from_yaw.c \
../src/Quaternion_test_make_from_yaw_degrees.c \
../src/Quaternion_test_multiplied.c \
../src/Quaternion_test_multiply.c \
../src/Quaternion_test_normalize.c \
../src/Quaternion_test_normalized.c \
../src/Quaternion_test_qn.c \
../src/Quaternion_test_rotate_vector.c \
../src/Quaternion_test_rotate_xyz.c \
../src/Quaternion_test_rotated_vector.c \
../src/Quaternion_test_scale.c \
../src/Quaternion_test_scaled.c \
../src/Quaternion_test_set.c \
../src/Quaternion_test_set_from.c \
../src/Quaternion_test_set_from_array.c \
../src/Quaternion_test_set_from_pitch.c \
../src/Quaternion_test_set_from_pitch_degrees.c \
../src/Quaternion_test_set_from_roll.c \
../src/Quaternion_test_set_from_roll_degrees.c \
../src/Quaternion_test_set_from_roll_pitch_yaw.c \
../src/Quaternion_test_set_from_roll_pitch_yaw_degrees.c \
../src/Quaternion_test_set_from_rotation_about_vector.c \
../src/Quaternion_test_set_from_rotation_about_xyz.c \
../src/Quaternion_test_set_from_rotation_degrees_about_vector.c \
../src/Quaternion_test_set_from_rotation_degrees_about_xyz.c \
../src/Quaternion_test_set_from_vector.c \
../src/Quaternion_test_set_from_yaw.c \
../src/Quaternion_test_set_from_yaw_degrees.c \
../src/Quaternion_test_set_qn.c \
../src/Quaternion_test_squared_magnitude.c \
../src/Quaternion_test_subtract.c \
../src/Quaternion_test_subtracted.c \
../src/d_Matvec.c \
../src/d_Quaternion.c \
../src/f_Matvec.c \
../src/f_Quaternion.c \
../src/main.c 

OBJS += \
./src/Quaternion_test_add.o \
./src/Quaternion_test_added.o \
./src/Quaternion_test_as_array.o \
./src/Quaternion_test_as_vector.o \
./src/Quaternion_test_conjugate.o \
./src/Quaternion_test_conjugated.o \
./src/Quaternion_test_dispose.o \
./src/Quaternion_test_get_pitch.o \
./src/Quaternion_test_get_pitch_degrees.o \
./src/Quaternion_test_get_roll.o \
./src/Quaternion_test_get_roll_degrees.o \
./src/Quaternion_test_get_roll_pitch_yaw.o \
./src/Quaternion_test_get_roll_pitch_yaw_degrees.o \
./src/Quaternion_test_get_yaw.o \
./src/Quaternion_test_get_yaw_degrees.o \
./src/Quaternion_test_interpolate.o \
./src/Quaternion_test_interpolated.o \
./src/Quaternion_test_inverse.o \
./src/Quaternion_test_invert.o \
./src/Quaternion_test_is_approximately_equal.o \
./src/Quaternion_test_is_equal.o \
./src/Quaternion_test_magnitude.o \
./src/Quaternion_test_make.o \
./src/Quaternion_test_make_default.o \
./src/Quaternion_test_make_from.o \
./src/Quaternion_test_make_from_array.o \
./src/Quaternion_test_make_from_pitch.o \
./src/Quaternion_test_make_from_pitch_degrees.o \
./src/Quaternion_test_make_from_roll.o \
./src/Quaternion_test_make_from_roll_degrees.o \
./src/Quaternion_test_make_from_roll_pitch_yaw.o \
./src/Quaternion_test_make_from_roll_pitch_yaw_degrees.o \
./src/Quaternion_test_make_from_rotation_about_vector.o \
./src/Quaternion_test_make_from_rotation_about_xyz.o \
./src/Quaternion_test_make_from_rotation_degrees_about_vector.o \
./src/Quaternion_test_make_from_rotation_degrees_about_xyz.o \
./src/Quaternion_test_make_from_vector.o \
./src/Quaternion_test_make_from_yaw.o \
./src/Quaternion_test_make_from_yaw_degrees.o \
./src/Quaternion_test_multiplied.o \
./src/Quaternion_test_multiply.o \
./src/Quaternion_test_normalize.o \
./src/Quaternion_test_normalized.o \
./src/Quaternion_test_qn.o \
./src/Quaternion_test_rotate_vector.o \
./src/Quaternion_test_rotate_xyz.o \
./src/Quaternion_test_rotated_vector.o \
./src/Quaternion_test_scale.o \
./src/Quaternion_test_scaled.o \
./src/Quaternion_test_set.o \
./src/Quaternion_test_set_from.o \
./src/Quaternion_test_set_from_array.o \
./src/Quaternion_test_set_from_pitch.o \
./src/Quaternion_test_set_from_pitch_degrees.o \
./src/Quaternion_test_set_from_roll.o \
./src/Quaternion_test_set_from_roll_degrees.o \
./src/Quaternion_test_set_from_roll_pitch_yaw.o \
./src/Quaternion_test_set_from_roll_pitch_yaw_degrees.o \
./src/Quaternion_test_set_from_rotation_about_vector.o \
./src/Quaternion_test_set_from_rotation_about_xyz.o \
./src/Quaternion_test_set_from_rotation_degrees_about_vector.o \
./src/Quaternion_test_set_from_rotation_degrees_about_xyz.o \
./src/Quaternion_test_set_from_vector.o \
./src/Quaternion_test_set_from_yaw.o \
./src/Quaternion_test_set_from_yaw_degrees.o \
./src/Quaternion_test_set_qn.o \
./src/Quaternion_test_squared_magnitude.o \
./src/Quaternion_test_subtract.o \
./src/Quaternion_test_subtracted.o \
./src/d_Matvec.o \
./src/d_Quaternion.o \
./src/f_Matvec.o \
./src/f_Quaternion.o \
./src/main.o 

C_DEPS += \
./src/Quaternion_test_add.d \
./src/Quaternion_test_added.d \
./src/Quaternion_test_as_array.d \
./src/Quaternion_test_as_vector.d \
./src/Quaternion_test_conjugate.d \
./src/Quaternion_test_conjugated.d \
./src/Quaternion_test_dispose.d \
./src/Quaternion_test_get_pitch.d \
./src/Quaternion_test_get_pitch_degrees.d \
./src/Quaternion_test_get_roll.d \
./src/Quaternion_test_get_roll_degrees.d \
./src/Quaternion_test_get_roll_pitch_yaw.d \
./src/Quaternion_test_get_roll_pitch_yaw_degrees.d \
./src/Quaternion_test_get_yaw.d \
./src/Quaternion_test_get_yaw_degrees.d \
./src/Quaternion_test_interpolate.d \
./src/Quaternion_test_interpolated.d \
./src/Quaternion_test_inverse.d \
./src/Quaternion_test_invert.d \
./src/Quaternion_test_is_approximately_equal.d \
./src/Quaternion_test_is_equal.d \
./src/Quaternion_test_magnitude.d \
./src/Quaternion_test_make.d \
./src/Quaternion_test_make_default.d \
./src/Quaternion_test_make_from.d \
./src/Quaternion_test_make_from_array.d \
./src/Quaternion_test_make_from_pitch.d \
./src/Quaternion_test_make_from_pitch_degrees.d \
./src/Quaternion_test_make_from_roll.d \
./src/Quaternion_test_make_from_roll_degrees.d \
./src/Quaternion_test_make_from_roll_pitch_yaw.d \
./src/Quaternion_test_make_from_roll_pitch_yaw_degrees.d \
./src/Quaternion_test_make_from_rotation_about_vector.d \
./src/Quaternion_test_make_from_rotation_about_xyz.d \
./src/Quaternion_test_make_from_rotation_degrees_about_vector.d \
./src/Quaternion_test_make_from_rotation_degrees_about_xyz.d \
./src/Quaternion_test_make_from_vector.d \
./src/Quaternion_test_make_from_yaw.d \
./src/Quaternion_test_make_from_yaw_degrees.d \
./src/Quaternion_test_multiplied.d \
./src/Quaternion_test_multiply.d \
./src/Quaternion_test_normalize.d \
./src/Quaternion_test_normalized.d \
./src/Quaternion_test_qn.d \
./src/Quaternion_test_rotate_vector.d \
./src/Quaternion_test_rotate_xyz.d \
./src/Quaternion_test_rotated_vector.d \
./src/Quaternion_test_scale.d \
./src/Quaternion_test_scaled.d \
./src/Quaternion_test_set.d \
./src/Quaternion_test_set_from.d \
./src/Quaternion_test_set_from_array.d \
./src/Quaternion_test_set_from_pitch.d \
./src/Quaternion_test_set_from_pitch_degrees.d \
./src/Quaternion_test_set_from_roll.d \
./src/Quaternion_test_set_from_roll_degrees.d \
./src/Quaternion_test_set_from_roll_pitch_yaw.d \
./src/Quaternion_test_set_from_roll_pitch_yaw_degrees.d \
./src/Quaternion_test_set_from_rotation_about_vector.d \
./src/Quaternion_test_set_from_rotation_about_xyz.d \
./src/Quaternion_test_set_from_rotation_degrees_about_vector.d \
./src/Quaternion_test_set_from_rotation_degrees_about_xyz.d \
./src/Quaternion_test_set_from_vector.d \
./src/Quaternion_test_set_from_yaw.d \
./src/Quaternion_test_set_from_yaw_degrees.d \
./src/Quaternion_test_set_qn.d \
./src/Quaternion_test_squared_magnitude.d \
./src/Quaternion_test_subtract.d \
./src/Quaternion_test_subtracted.d \
./src/d_Matvec.d \
./src/d_Quaternion.d \
./src/f_Matvec.d \
./src/f_Quaternion.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Quaternion -I../../../Matvec -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


