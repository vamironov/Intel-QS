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
#include "mpi_exception.hpp"
#include <string>

qhipster::MpiWrapperException::MpiWrapperException(int ec) {
    char c_err_str[MPI_MAX_ERROR_STRING];
    int str_len = -1;

    // Decode the error string for the error code.
    MPI_Error_string(ec,c_err_str,&str_len);

    // Store the results in our instance variables.
    _ec_text  = c_err_str;
    _ec_text.append("dork");
    _ec_value = ec;
}

qhipster::MpiWrapperException::~MpiWrapperException() throw() { }
