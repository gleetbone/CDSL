/**
 @file Fft_utility.h
 @author Greg Lee
 @version 0.0
 @brief: "utilities for testing Fft"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Fft_make.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "f_Matvec.h"
#include "d_Matvec.h"
#include "cf_Matvec.h"
#include "cd_Matvec.h"


cf_matvec_t *
single_bin_sinusoid_input_f( int32_t length, int32_t i_freq, float phase_fraction );

cf_matvec_t *
single_bin_sinusoid_output_f( int32_t length, int32_t i_freq, float phase_fraction );

cf_matvec_t *
single_bin_sinusoid_output_for_psd_f( int32_t length, int32_t i_freq, float phase_fraction );

f_matvec_t *
single_bin_sinusoid_psd_f( int32_t length, int32_t i_freq, float phase_fraction );

f_matvec_t *
single_bin_sinusoid_log_psd_f( int32_t length, int32_t i_freq, float phase_fraction );

f_matvec_t *
single_bin_sinusoid_phase_f( int32_t length, int32_t i_freq, float phase_fraction );

f_matvec_t *
single_bin_sinusoid_phase_degrees_f( int32_t length, int32_t i_freq, float phase_fraction );


cd_matvec_t *
single_bin_sinusoid_input_d( int32_t length, int32_t i_freq, double phase_fraction );

cd_matvec_t *
single_bin_sinusoid_output_d( int32_t length, int32_t i_freq, double phase_fraction );

cd_matvec_t *
single_bin_sinusoid_output_for_psd_d( int32_t length, int32_t i_freq, double phase_fraction );

d_matvec_t *
single_bin_sinusoid_psd_d( int32_t length, int32_t i_freq, double phase_fraction );

d_matvec_t *
single_bin_sinusoid_log_psd_d( int32_t length, int32_t i_freq, double phase_fraction );

d_matvec_t *
single_bin_sinusoid_phase_d( int32_t length, int32_t i_freq, double phase_fraction );

d_matvec_t *
single_bin_sinusoid_phase_degrees_d( int32_t length, int32_t i_freq, double phase_fraction );


#ifdef __cplusplus
}
#endif

/* End of file */

