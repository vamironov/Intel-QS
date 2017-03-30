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
#include "openmp_affinity_noomp.hpp"

using namespace qhipster::openmp;

AffinityNoOmp::AffinityNoOmp( ) { }
AffinityNoOmp::~AffinityNoOmp( ){ }

void AffinityNoOmp::set_thread_affinity(int thread_count) { 
    return; 
}

unsigned AffinityNoOmp::get_num_threads() { 
    return 1; 
}

std::string AffinityNoOmp::get_affinity_string() {
    return "";
}

#ifndef _OPENMP
qhipster::openmp::AffinityNoOmp glb_affinity;
#endif
