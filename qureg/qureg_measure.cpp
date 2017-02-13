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
bool QbitRegister<Type>::isClassicalBit(unsigned qubit, BaseType tolerance) const
{
  int myrank = openqu::mpi::Environment::rank();
  int nprocs = openqu::mpi::Environment::size();
  unsigned log2_nprocs = openqu::ilog2(openqu::mpi::Environment::size());
  std::size_t M = nqbits - log2_nprocs;

  std::size_t delta = 1UL << qubit;

  if (qubit < M) { 
    bool up = false, down = false;
    for (std::size_t i = 0; i < localSize(); i += 2 * delta) {
      for (std::size_t j = 0; j < delta; ++j) {
        up = up || (std::norm(state[i + j]) > tolerance);
        down = down || (std::norm(state[i + j + delta]) > tolerance);
        if (up && down) return false;
      }
    }
  } else {
    int up = 0, down = 0;
    std::size_t src_glb_start = UL(myrank) * localSize();
    if (check_bit(src_glb_start, qubit) == 0) {
      down = 0;
      for (std::size_t j = 0; j < localSize(); ++j) 
        up = up || (std::norm(state[j]) > tolerance);
    } else {
      up = 0;
      for (std::size_t j = 0; j < localSize(); ++j) 
        down = down || (std::norm(state[j]) > tolerance);
    }
    // printf("[%3d] up:%d down:%d\n", myrank, up, down);
    int glb_up, glb_down;
    MPI_Allreduce(&up, &glb_up, 1, MPI_INT, MPI_LOR, MPI_COMM_WORLD);
    MPI_Allreduce(&down, &glb_down, 1, MPI_INT, MPI_LOR, MPI_COMM_WORLD);
    // printf("[%3d] glb_up:%d glb_down:%d\n", myrank, glb_up, glb_down);
    if (glb_up && glb_down) return false;
    openqu::mpi::barrier();
  }
  // printf("[%d] here\n", myrank);
  return true;

}

template <class Type>
void QbitRegister<Type>::collapseQubit(unsigned qubit, bool value)
{
  int myrank = openqu::mpi::Environment::rank();
  int nprocs = openqu::mpi::Environment::size();
  unsigned log2_nprocs = openqu::ilog2(openqu::mpi::Environment::size());
  std::size_t M = nqbits - log2_nprocs;

  std::size_t delta = 1UL << qubit;
  if (qubit < M) { 
    for (std::size_t i = value ? 0 : delta; i < localSize(); i += 2 * delta)
      for (std::size_t j = 0; j < delta; ++j) state[i + j] = 0.;
  } else {
    std::size_t src_glb_start = UL(myrank) * localSize();
    if (check_bit(src_glb_start, qubit) == 0 && value == true) {
      for (std::size_t j = 0; j < localSize(); ++j) state[j] = 0.;
    } else if (check_bit(src_glb_start, qubit) == 1 && value == false) {
      for (std::size_t j = 0; j < localSize(); ++j) state[j] = 0.;
    }
  }
}

template <class Type>
QbitRegister<Type>::BaseType QbitRegister<Type>::getProbability(unsigned qubit)
{
  int myrank = openqu::mpi::Environment::rank();
  int nprocs = openqu::mpi::Environment::size();
  unsigned log2_nprocs = openqu::ilog2(openqu::mpi::Environment::size());
  std::size_t M = nqbits - log2_nprocs;

  std::size_t delta = 1UL << qubit;
  BaseType local_P = 0.;
  if (qubit < M) { // if '0' and '1' for qubit state are witin the same rank
    for (std::size_t i = delta; i < localSize(); i += 2 * delta)
      for (std::size_t j = 0; j < delta; ++j) local_P += std::norm(state[i + j]);

  } else {
    std::size_t src_glb_start = UL(myrank) * localSize();
    if (check_bit(src_glb_start, qubit) == 1) {
      for (std::size_t j = 0; j < localSize(); ++j) local_P += std::norm(state[j]);
    }
  }

  BaseType global_P;
  MPI_Allreduce(&local_P, &global_P, 1,
                MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
  return global_P;

}

template <class Type>
bool QbitRegister<Type>::getClassicalValue(unsigned qubit, BaseType tolerance) const
{
  int myrank = openqu::mpi::Environment::rank();
  int nprocs = openqu::mpi::Environment::size();
  unsigned log2_nprocs = openqu::ilog2(openqu::mpi::Environment::size());
  std::size_t delta = 1UL << qubit;
  std::size_t M = nqbits - log2_nprocs;

  int bit_is_zero = 0, bit_is_one = 0; 
  if (qubit < M) {
    for (std::size_t i = 0; i < localSize(); i += 2 * delta) {
      for (std::size_t j = 0; j < delta; ++j) {
        if (std::norm(state[i + j]) > tolerance) {bit_is_zero = 1; goto done;}
        if (std::norm(state[i + j + delta]) > tolerance) {bit_is_one = 1; goto done;}
      }
    }
  } else {
    std::size_t src_glb_start = UL(myrank) * localSize();
    if (check_bit(src_glb_start, qubit) == 0) {
      for (std::size_t j = 0; j < localSize(); j++)
        if (std::norm(state[j]) > tolerance) {bit_is_zero = 1; break;}
    } else {
      for (std::size_t j = 0; j < localSize(); j++)
        if (std::norm(state[j]) > tolerance) {bit_is_one = 1; break;}
    }
  }

  done:  
  int glb_bit_is_zero, glb_bit_is_one;
  MPI_Allreduce(&bit_is_zero, &glb_bit_is_zero, 1, MPI_INT, MPI_LOR, MPI_COMM_WORLD);
  MPI_Allreduce(&bit_is_one, &glb_bit_is_one, 1, MPI_INT, MPI_LOR, MPI_COMM_WORLD);
  if (glb_bit_is_zero == 1 && glb_bit_is_one == 0) return false;
  else if (glb_bit_is_zero == 0 && glb_bit_is_one == 1) return true;
  else assert(false);  // this should never be called
  return false;   // dummy return
}

template class QbitRegister<ComplexSP>;
template class QbitRegister<ComplexDP>;

