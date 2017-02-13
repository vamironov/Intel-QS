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

/* 
 * Implements a Toffoli gate courtesy of Sonika Johri.
 *
 * Parameters:
 * 	psi - the wave function to apply the Toffoli gate to.
 * 	  qubit1 - target qubit being NOT'ed
 * 	  qubit2 - control qubit 1
 * 	  qubit3 - control qubit 2
 */
template<typename Type>
void QbitRegister<Type>::applyToffoli(unsigned const qubit1, 
		                        unsigned const qubit2, 
					  unsigned const qubit3) {

  openqu::TinyMatrix<Type, 2, 2, 32> V;
  V(0,0)={1.0/2.0,-1.0/2.0};
  V(0,1)={1.0/2.0,1.0/2.0};
  V(1,0)={1.0/2.0,1.0/2.0};
  V(1,1)={1.0/2.0,-1.0/2.0};

  openqu::TinyMatrix<Type, 2, 2, 32> V_dag;
  V_dag(0,0)={1.0/2.0,1.0/2.0};
  V_dag(0,1)={1.0/2.0,-1.0/2.0};
  V_dag(1,0)={1.0/2.0,-1.0/2.0};
  V_dag(1,1)={1.0/2.0,1.0/2.0};

  applyControlled1QubitGate(qubit2, qubit1, V);
  applyCPauliX(qubit3,qubit2);
  applyControlled1QubitGate(qubit2, qubit1, V_dag);
  applyCPauliX(qubit3,qubit2);
  applyControlled1QubitGate(qubit3, qubit1, V);

  return;
}

template class QbitRegister<ComplexSP>;
template class QbitRegister<ComplexDP>;

