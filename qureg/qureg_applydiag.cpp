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
#include "highperfkernels.hpp"

template <class Type>
void QbitRegister<Type>::applyDiagSimp(unsigned qubit1, unsigned qubit2,  TM4x4<Type> const &m)
{
  int myrank = openqu::mpi::Environment::rank();
  int nprocs = openqu::mpi::Environment::size();
  Type d00 = m[0][0],
              d11 = m[1][1],
              d22 = m[2][2],
              d33 = m[3][3];


  std::size_t src_glb_start = UL(myrank) * localSize();
  for (std::size_t i = 0;  i < localSize(); i++)
  {
    if(check_bit(src_glb_start + i, qubit1) == 0 &&
       check_bit(src_glb_start + i, qubit2) == 0 )
       state[i] *= d00;
    else if(check_bit(src_glb_start + i, qubit1) == 0 &&
            check_bit(src_glb_start + i, qubit2) == 1 )
       state[i] *= d11;
    else if(check_bit(src_glb_start + i, qubit1) == 1 &&
            check_bit(src_glb_start + i, qubit2) == 0 )
       state[i] *= d22;
    else 
       state[i] *= d33;
  }
}

template <class Type>
void QbitRegister<Type>::applyDiag(unsigned qubit1_, unsigned qubit2_,  TM4x4<Type> const &m)
{
 // flush fusion buffers
  if (fusion == true) {
    applyFusedGates();
  }

  assert(qubit1_ < nqbits);
  unsigned qubit1 = (*permutation)[qubit1_];
  assert(qubit1 < nqbits);
  assert(qubit2_ < nqbits);
  unsigned qubit2 = (*permutation)[qubit2_];
  assert(qubit2 < nqbits);

  int myrank = openqu::mpi::Environment::rank();
  int nprocs = openqu::mpi::Environment::size();
  unsigned log2_nprocs = openqu::ilog2(openqu::mpi::Environment::size());
  std::size_t M = nqbits - log2_nprocs;
  std::size_t delta1 = 1 << qubit1;
  std::size_t delta2 = 1 << qubit2;

  Type d00 = m[0][0],
              d11 = m[1][1],
              d22 = m[2][2],
              d33 = m[3][3];
  std::size_t src_glb_start = UL(myrank) * localSize();
  bool controlled = (d00 == 1. && d11 == 1.);

  
  #if 0
  // currently disabled. controlled part is done inline inside controlled gate
  if (controlled == true) {
    // controlled 2-qubit diagonal gate
    if (qubit1 < M && qubit2 < M) {
      printf("here1\n");
      unsigned delta1_ = std::min(delta1, delta2);
      unsigned delta2_ = std::max(delta1, delta2);
      TM2x2<Type> m2x2;
      m2x2[0][0] = d22;
      m2x2[0][1] = 0.;
      m2x2[1][0] = 0.;
      m2x2[1][1] = d33;
      Loop_TN(state, 
              0UL, localSize(), 2UL * delta2_,
              0UL, delta2_,     2UL * delta1_,
              delta1_, 2UL*delta1_, delta2_,
              m2x2, NULL);
                
    } else if (qubit1 >= M && qubit2 < M) {
      printf("here2\n");
      if (check_bit(src_glb_start, qubit1) != 0) {
        for (std::size_t j = 0; j < localSize(); j += 2 * delta2) {
          for (std::size_t k = 0; k < delta2; ++k) {
             state[j + k                 ] *= d22;
             state[j + k + delta2        ] *= d33;
          }
        }
      } 
    } else if (qubit1 < M && qubit2 >= M) {
      Type d0, d1;
      printf("here3\n");
      d1 = (check_bit(src_glb_start, qubit2) == 0) ? d22 : d33;
      for (std::size_t j = 0; j < localSize(); j += 2 * delta1) {
        for (std::size_t k = 0; k < delta1; ++k) {
           state[j + k + delta1        ] *= d1;
        }
      }
    } else if (qubit1 >= M && qubit2 >= M) {
      printf("here4\n");
      if (check_bit(src_glb_start, qubit1) == 1 &&
          check_bit(src_glb_start, qubit2) == 0 ) {
        for (std::size_t i = 0;  i < localSize(); i++)
          state[i] *= d22;
      } else if (check_bit(src_glb_start, qubit1) == 1 &&
                 check_bit(src_glb_start, qubit2) == 1 ) {
        for (std::size_t i = 0;  i < localSize(); i++)
          state[i] *= d33;
      }
    }

  } else 
  #endif
  {
    // general 2-qubit diagonal gate
    if (qubit1 < M && qubit2 < M) {
       unsigned delta1_ = std::min(delta1, delta2);
       unsigned delta2_ = std::max(delta1, delta2);
       for (std::size_t i = 0; i < localSize(); i += 2 * delta2_)
         for (std::size_t j = 0; j < delta2_; j += 2 * delta1_)
           for (std::size_t k = 0; k < delta1_; ++k) {
              state[i + j + k                 ]  *= d00;
              state[i + j + k + delta2        ]  *= d11;
              state[i + j + k + delta1        ]  *= d22;
              state[i + j + k + delta1 + delta2] *= d33;
           }

    } else if (qubit1 >= M && qubit2 < M || qubit1 < M && qubit2 >= M) {
      Type d0, d1;
      unsigned delta;
      if (qubit1 >= M && qubit2 < M)  {
        d0 = (check_bit(src_glb_start, qubit1) == 0) ? d00 : d22;
        d1 = (check_bit(src_glb_start, qubit1) == 0) ? d11 : d33;
        delta = delta2;
      } else {
        d0 = (check_bit(src_glb_start, qubit2) == 0) ? d00 : d11;
        d1 = (check_bit(src_glb_start, qubit2) == 0) ? d22 : d33;
        delta = delta1;
      }
      for (std::size_t j = 0; j < localSize(); j += 2 * delta) {
        for (std::size_t k = 0; k < delta; ++k) {
           state[j + k                 ] *= d0;
           state[j + k + delta         ] *= d1;
        }
      } 
    } else if (qubit1 >= M && qubit2 >= M) {
      if (check_bit(src_glb_start, qubit1) == 0 &&
          check_bit(src_glb_start, qubit2) == 0 ) {
        for (std::size_t i = 0;  i < localSize(); i++)
          state[i] *= d00;
      } else if (check_bit(src_glb_start, qubit1) == 0 &&
                 check_bit(src_glb_start, qubit2) == 1 ) {
        for (std::size_t i = 0;  i < localSize(); i++)
          state[i] *= d11;
      } else if (check_bit(src_glb_start, qubit1) == 1 &&
                 check_bit(src_glb_start, qubit2) == 0 ) {
        for (std::size_t i = 0;  i < localSize(); i++)
          state[i] *= d22;
      } else {
        for (std::size_t i = 0;  i < localSize(); i++)
          state[i] *= d33;
      }
    }
  }

}

template class QbitRegister<ComplexSP>;
template class QbitRegister<ComplexDP>;
