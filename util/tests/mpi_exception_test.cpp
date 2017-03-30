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
 * @file mpi_exception_test.cpp
 *
 * Test the MPI Wrapper exception handling code.
 */
#include "../mpi_wrapper.hpp"
#include <iostream>
#include <cassert>


using namespace std;


int main(int argc, char** argv)
{
    // Initialize MPI framework.
    qhipster::MpiWrapper mpi(argc,argv);

    try {

        // Set the error handler for C++ framework calls through the MPI_COMM_WORLD communicator.
        QH_MPI_STATUS_CHECK(MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN));

        // do something dumb.
        QH_MPI_STATUS_CHECK((MPI_Bsend(&argc, 1, MPI_INT, 600, 0, MPI_COMM_WORLD)));

        // No more MPI calls allowed after this.
        QH_MPI_STATUS_CHECK(MPI_Barrier(MPI_COMM_WORLD));
        QH_MPI_STATUS_CHECK(MPI_Finalize());
    }
    catch (exception const& e) {
        cerr << e.what() << endl;
    }

  return 0;
}
