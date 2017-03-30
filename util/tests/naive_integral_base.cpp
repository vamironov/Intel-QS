//------------------------------------------------------------------------------
// INTEL CONFIDENTIAL
// Copyright 2017 Intel Corporation
//
// The source code contained or described herein and all documents related to
// the source code ("Material") are owned by Intel Corporation or its suppliers
// or licensors. Title to the Material remains with Intel Corporation or its
// suppliers and licensors. The Material contains trade secrets and proprietary
// and confidential information of Intel or its suppliers and licensors.
// The Material is protected by worldwide copyright and trade secret laws and
// treaty provisions. No part of the Material may be used, copied, reproduced,
// modified, published, uploaded, posted, transmitted, distributed, or disclosed
// in any way without Intel's prior express written permission.
//
// No license under any patent, copyright, trade secret or other intellectual
// property right is granted to or conferred upon you by disclosure or delivery
// of the Materials, either expressly, by implication, inducement, estoppel or
// otherwise. Any license under such intellectual property rights must be
// express and approved by Intel in writing.
//------------------------------------------------------------------------------

/**
 * @file omp_test1.cpp
 *
 * This file tests creation/destruction of an OMP session.
 *
 */
#include "openmp_affinity_corei7.hpp"
#include <stdexcept>
#include <stdio.h>


int main(int argc, char **argv) {

    double integral_start = 0.0,
           integral_end   = 1.0;
    unsigned long N = 100000; // number of steps.

    // Compute delta_x of the integral.
    double delta_x = (integral_end - integral_start) / (double)N;
    double sum = 0.0;
    double x;

    // Compute the Riemann sum for the approximate integral.
    for(unsigned long i=0;i<N;i++) {
        x = (i+0.5)*delta_x;
        sum += (4.0 / (1.0+x*x));
    }

    sum *= delta_x;

    printf("Result: %.10f\n", sum);

    return 1;
}
