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

#include "qureg.hpp"

template <class Type>
void QbitRegister<Type>::Permute(std::vector<std::size_t> permutation_new_vec)
{

  assert(nqbits == permutation_new_vec.size());

  Permutation &permutation_old = *permutation;
  Permutation permutation_new(permutation_new_vec);

#ifndef OPENQU_HAVE_MPI
  std::vector<Type> state_new(localSize(), 0);

  for (std::size_t i = 0; i < localSize(); i++) {
    std::size_t to =
        permutation_old.bin2dec(permutation_new.perm2lin(permutation_old.lin2perm(i)));
    state_new[to] = state[i];
  }
  // state = state_new;
  for (std::size_t i = 0; i < localSize(); i++) state[i] = state_new[i];
#else
  unsigned myrank = openqu::mpi::Environment::rank();
  unsigned nprocs = openqu::mpi::Environment::size();
  MPI_Comm comm = openqu::mpi::Environment::comm();

  // Dummy multi-node permutation code
  std::vector<Type> glb_state(globalSize(), 0);
  MPI_Allgather(&(state[0]), localSize(), MPI_DOUBLE_COMPLEX, &(glb_state[0]), localSize(),
                MPI_DOUBLE_COMPLEX, comm);
  for (std::size_t i = 0; i < glb_state.size(); i++) {
    std::size_t glbind =
        permutation_old.bin2dec(permutation_new.perm2lin(permutation_old.lin2perm(i)));
    std::size_t rank = glbind / localSize();
    if (rank == myrank) {
      std::size_t lclind = glbind - rank * localSize();
      assert(lclind < localSize());
      state[lclind] = glb_state[i];
    }
  }
#endif
  permutation_old = permutation_new;

#if 0
  // do it multinode
  // calculate displacements for other nodes
  std::vector <std::size_t> counts(nprocs, 0), displs(nprocs, 0);
  for(std::size_t i = 0; i < localSize(); i++)
  {
    std::size_t glbind = permutation_old.bin2dec(permutation_new.perm2lin(permutation_old.lin2perm(i)));
    std::size_t rank = glbind / localSize(); 
    assert(rank < nprocs);
    counts[rank]++;
  }
  // compute displacements for each rank
  for(std::size_t i = 1; i < nprocs; i++)
    displs[i] = displs[i-1] + counts[i-1]; 
 
  // fill in outgoing buffer as key value std::pairs
  std::vector<std::pair<std::size_t, Type>> tmp(localSize());
  for(std::size_t i = 0; i < localSize(); i++)
  {
    std::size_t glbind = permutation_old.bin2dec(permutation_new.perm2lin(permutation_old.lin2perm(i)));
    std::size_t rank = glbind / localSize();
    std::size_t lclind = glbind - rank * nprocs;
    tmp[displs[rank]
  }
#endif
}

template class QbitRegister<ComplexSP>;
template class QbitRegister<ComplexDP>;

