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
#include <omp.h>
#include <stdio.h>
#include <stdexcept>
#include <cassert>


int main(int argc, char **argv) {

    int world_size = 0;
    int world_rank = 0;
    int my_node_size = 0;
    int my_node_rank = 0;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    // Initialize the MPI Framework.
    qhipster::MpiWrapper mpi(argc,argv);

    QH_MPI_STATUS_CHECK((MPI_Comm_size(MPI_COMM_WORLD, &world_size)));
    QH_MPI_STATUS_CHECK((MPI_Comm_rank(MPI_COMM_WORLD, &world_rank)));
    QH_MPI_STATUS_CHECK((MPI_Get_processor_name(processor_name, &name_len)));

    printf("World Rank/Size [%2d:%-2d]\n", world_rank, world_size);

    // Split the communicator into subcommunicators which have the capability of creating
    // shared memory.
    MPI_Comm node_comm;
    QH_MPI_STATUS_CHECK(MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, 
                        world_rank, MPI_INFO_NULL, &node_comm));

    // Determine the number of ranks in the new node we just split and also
    // my rank within it.
    QH_MPI_STATUS_CHECK(MPI_Comm_size(node_comm, &my_node_size));
    QH_MPI_STATUS_CHECK(MPI_Comm_rank(node_comm, &my_node_rank));

    printf("Group Rank/Node#: [%2d/%-2d]\n", my_node_rank, my_node_size / world_size);

    // This should detect non-symmetric partitioning of the processes into
    // uniform sized groups of nodes. For example: World: 16 processes,
    // 4 processes per comm group, 0 left-over processes.
    assert((world_size % my_node_size) == 0);

    // Partition the available global ranks into communication groups that are an even multiple of 2.
    // Left-over ranks stay in the global rank pool.
    





#pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        printf("Node ID/Rank: [%2d/%-2d] Thread [%d] working...\n", my_node_size/world_size, my_node_rank, threadID);

        int a=0,b=0,c=0;
        for(unsigned long i=0;i<2000000000;i++) {
            unsigned long a = (++b/2) + (++c/2);
        }
    }

    return 1;
}
