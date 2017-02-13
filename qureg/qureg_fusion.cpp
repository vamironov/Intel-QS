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
void QbitRegister<Type>::fusionon(unsigned log2llc)
{
  unsigned nprocs = openqu::mpi::Environment::size();
  std::size_t myrank = openqu::mpi::Environment::rank();
  unsigned log2_nprocs = openqu::ilog2(openqu::mpi::Environment::size());
  unsigned M = nqbits - log2_nprocs;

  if (log2llc >= M) {
    if (!myrank) printf("Fusion is not enabled: nqbits (%lu) is too small\n", nqbits);
    fusion = false;
  } else {
    if (!myrank) printf("Fusion is enabled: log2llc = %u nqbits = %lu\n", log2llc, nqbits);
    this->log2llc = log2llc;
    fusion = true;
  }
}


template <class Type>
void QbitRegister<Type>::fusionoff()
{
  if (fwindow.size()) {
    applyFusedGates();
  }
  fusion = false;
}

template <class Type>
bool QbitRegister<Type>::is_fusion_enabled()
{
  return fusion;
}



template <class Type>
void QbitRegister<Type>::applyFusedGates()
{
  std::size_t myrank = openqu::mpi::Environment::rank();

  #if 0
  if (myrank == 0 && fwindow.size() > 1) {
    printf("fused: ");
    for (auto &f : fwindow) {
      std::string &type = std::get<0>(f);
      unsigned qubit1 = std::get<2>(f);
      unsigned qubit2 = std::get<3>(f);
      if (type == "sqg")
        printf("[%s %u] ",  type.c_str(), qubit1);
      else
        printf("[%s %u %u] ",  type.c_str(), qubit1, qubit2);
    }
    printf("\n");
  }
  #endif

  size_t blocksize = (fwindow.size() == 1) ? localSize() : (1L << UL(log2llc));
  for (size_t l = 0; l < localSize(); l += blocksize) {
    for (auto &f : fwindow) {
      // check if work has been done
      std::string &type = std::get<0>(f);
      TM2x2<Type> &m = std::get<1>(f);
      std::size_t qubit1 = std::get<2>(f);
      std::size_t qubit2 = std::get<3>(f);
      if (type == "sqg") {
        apply1QubitGate_helper(qubit1, m, l, l + blocksize);
      } else if (type == "cqg") {
        applyControlled1QubitGate_helper(qubit1, qubit2, m, l, l + blocksize);
      } else {
        assert(0); // not yet implemented
      }

    }
  }
  fwindow.resize(0);
}

template class QbitRegister<ComplexSP>;
template class QbitRegister<ComplexDP>;

