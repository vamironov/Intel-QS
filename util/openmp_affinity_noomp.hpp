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
#pragma once
#include "openmp_affinity_v1.hpp"

namespace qhipster {
namespace openmp {

class AffinityNoOmp : public qhipster::openmp::IOmpAffinityV1 {
    private:
        std::string affinity_str;

    public:
        AffinityNoOmp( );
        ~AffinityNoOmp( );

    void set_thread_affinity(int);
    unsigned get_num_threads();
    std::string get_affinity_string();
};

}
}
