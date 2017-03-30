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
 * @file mpi_test1.cpp
 *
 * This file tests creation/destruction of an MPI session.
 *
 */
#include "../mpi_wrapper.hpp"
#include "openmp_affinity_corei7.hpp"
#include <stdio.h>
#include <stdexcept>

#ifndef _OPENMP
qhipster::openmp::AffinityNoOmp affinity;
#else
qhipster::openmp::AffinityCoreI7 affinity;
#endif


int main(int argc, char **argv) {

    int world_size = 0;
    int world_rank = 0;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

//    kmp_set_defaults("KMP_AFFINITY=scatter, granularity=fine");

    int max_threads = omp_get_max_threads();
    printf("Max available threads %d\n", max_threads);

//    omp_set_num_threads(2);
    affinity.set_thread_affinity(2);

    // Initialize the MPI Framework.
    MPI_Init(NULL,NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Get_processor_name(processor_name, &name_len);

#pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        printf("GlbID: [%d] Thread [%d]\n", world_rank, threadID);

        int a = 0,b=0,c=0;
        for(unsigned long i=0;i<2000000000;i++) {
            unsigned long a = (++b/2) + (++c/2);
        }
    }

    // Clean-up the MPI Framework...we're done.
    MPI_Finalize();

    return 1;
}
