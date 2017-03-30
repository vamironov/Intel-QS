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
//
#include "openmp_affinity_corei7.hpp"
#include <string>

using namespace qhipster::openmp;

AffinityCoreI7::AffinityCoreI7(){ }
AffinityCoreI7::~AffinityCoreI7(){ }

void AffinityCoreI7::set_thread_affinity(int thread_count) { 

    // Core I7 processors generally have 2 HW threads per processor core. So,
    // we'll set that here.
    omp_set_dynamic(0);       // Explicitly disable dynamic teams.
    omp_set_num_threads(thread_count);

#if defined(__ICC) || defined(__INTEL_COMPILER)
    affinity_str = "KMP_AFFINITY=compact,1,0,granularity=fine";
    kmp_set_defaults(affinity_str.c_str());
#else
#pragma message("No kmp_set_defaults() function currently implemented for GNU g++")
#endif

}


unsigned AffinityCoreI7::get_num_threads( ) { 
    int th = 3;
#pragma omp parallel
#pragma omp master
    {
        th = omp_get_num_threads();
    }
    return th;
}


std::string AffinityCoreI7::get_affinity_string() {
    return affinity_str;
}

