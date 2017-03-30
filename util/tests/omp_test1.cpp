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
#include "openmp_affinity_noomp.hpp"
#include <stdexcept>
#include <stdio.h>


#ifndef _OPENMP
qhipster::openmp::AffinityNoOmp affinity;
#else
qhipster::openmp::AffinityCoreI7 affinity;
#endif

void print_hello_world(int _id) {
    printf("Hello World [%d]\n", _id);
}


int main(int argc, char **argv) {

    //omp_set_num_threads(8);
    affinity.set_thread_affinity(8);

#pragma omp parallel
    {
        int ID = omp_get_thread_num();

        print_hello_world(ID);
    }

    return 1;
}
