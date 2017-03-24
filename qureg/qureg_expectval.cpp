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

#define __ONLY_NORMALIZED_STATES__

#include "qureg.hpp"


//------------------------------------------------------------------------------
template <class Type>
void QbitRegister<Type>::expectationValueX(unsigned qubit, BaseType &sum)
{
// compute the iexpectation value <psi|X|psi> = <psi|H.Z.H|psi>
  applyHadamard(qubit);
  sum += 1. - 2.*getProbability(qubit);
// recover the initial state |psi>
  applyHadamard(qubit);
}


#if 0
//------------------------------------------------------------------------------
template <class Type>
void QbitRegister<Type>::expectationValueX(unsigned qubit, BaseType &sum)
{
#ifdef __ONLY_NORMALIZED_STATES__
  BaseType initial_norm = 1.;
#else
  BaseType initial_norm = computenorm();
#endif

// given initial qureg state in |psi>
// compute the non-normalized vector corresponding to (2+X)|psi>
  openqu::TinyMatrix<Type, 2, 2, 32> x_plus_2id;
  x_plus_2id(0, 1) = x_plus_2id(1, 0) = Type(1., 0.);
  x_plus_2id(0, 0) = x_plus_2id(1, 1) = Type(2., 0.);
  apply1QubitGate(qubit, x_plus_2id);

// update sum adding <psi|X|psi>
  BaseType final_norm = computenorm();
  sum += (final_norm*final_norm - 5.*initial_norm*initial_norm)/4.;

// undo the computation to recover the initial state |psi>
  openqu::TinyMatrix<Type, 2, 2, 32> inverse;
  inverse(0, 1) = inverse(1, 0) = Type(-1./3., 0.);
  inverse(0, 0) = inverse(1, 1) = Type( 2./3., 0.);
  apply1QubitGate(qubit, inverse);
}
#endif

//------------------------------------------------------------------------------
template <class Type>
void QbitRegister<Type>::expectationValueY(unsigned qubit, BaseType &sum)
{
// G is matrix from change of basis Y --> Z , such that G^dagger.Z.G=Y
  openqu::TinyMatrix<Type, 2, 2, 32> G;
  BaseType f = 1. / std::sqrt(2.);
  G(0, 0) = G(1, 0) = Type(f, 0.);
  G(0, 1) = Type(0.,-f);
  G(1, 1) = Type(0., f);
// compute the iexpectation value <psi|Y|psi> = <psi|G^dagger.Z.G|psi>
  apply1QubitGate(qubit,G);
  sum += 1. - 2.*getProbability(qubit);
// recover the initial state |psi> by applying G^dagger
  G(0, 0) = G(0, 1) = Type(f, 0.);
  G(1, 0) = Type(0., f);
  G(1, 1) = Type(0.,-f);
  apply1QubitGate(qubit,G);
}



//------------------------------------------------------------------------------
template <class Type>
void QbitRegister<Type>::expectationValueZ(unsigned qubit, BaseType &sum)
{
  sum += 1. - 2.*getProbability(qubit);
}


//------------------------------------------------------------------------------
template <class Type>
void QbitRegister<Type>::expectationValueXX(unsigned qubit, unsigned qubit2, BaseType &sum)
{
#ifdef __ONLY_NORMALIZED_STATES__
  BaseType initial_norm = 1.;
#else
  BaseType initial_norm = computenorm();
#endif

// given initial qureg state in |psi>
// compute the non-normalized vector corresponding to (2+XX)|psi>
  openqu::TinyMatrix<Type, 4, 4, 32> xx_plus_2id;
  xx_plus_2id(0, 1) = xx_plus_2id(0, 2) = xx_plus_2id(1, 0) = xx_plus_2id(1, 3) = Type(0., 0.);
  xx_plus_2id(2, 0) = xx_plus_2id(2, 3) = xx_plus_2id(3, 1) = xx_plus_2id(3, 2) = Type(0., 0.);
  xx_plus_2id(0, 3) = xx_plus_2id(1, 2) = xx_plus_2id(2, 1) = xx_plus_2id(3, 0) = Type(1., 0.);
  xx_plus_2id(0, 0) = xx_plus_2id(1, 1) = xx_plus_2id(2, 2) = xx_plus_2id(3, 3) = Type(2., 0.);
  apply2QubitGate(qubit, qubit2, xx_plus_2id);

// update sum adding <psi|XX|psi>
  BaseType final_norm = computenorm();
  sum += (final_norm*final_norm - 5.*initial_norm*initial_norm)/4.;

// undo the computation to recover the initial state |psi>
  openqu::TinyMatrix<Type, 4, 4, 32> inverse;
  inverse(0, 1) = inverse(0, 2) = inverse(1, 0) = inverse(1, 3) = Type(0., 0.);
  inverse(2, 0) = inverse(2, 3) = inverse(3, 1) = inverse(3, 2) = Type(0., 0.);
  inverse(0, 3) = inverse(1, 2) = inverse(2, 1) = inverse(3, 0) = Type(-1./3., 0.);
  inverse(0, 0) = inverse(1, 1) = inverse(2, 2) = inverse(3, 3) = Type( 2./3., 0.);
  apply2QubitGate(qubit, qubit2, inverse);
}


//------------------------------------------------------------------------------
// TODO : check how the basis is it is: 00-01-10-11 or 00-10-01-11 !!!!
//        this code uses the standard 00-01-10-11 despite this being opposite to backend storage convention
template <class Type>
void QbitRegister<Type>::expectationValueYX(unsigned qubit, unsigned qubit2, BaseType &sum)
{
#ifdef __ONLY_NORMALIZED_STATES__
  BaseType initial_norm = 1.;
#else
  BaseType initial_norm = computenorm();
#endif

// given initial qureg state in |psi>
// compute the non-normalized vector corresponding to (2+XY)|psi>
  openqu::TinyMatrix<Type, 4, 4, 32> xy_plus_2id;
  xy_plus_2id(0, 1) = xy_plus_2id(0, 2) = xy_plus_2id(1, 0) = xy_plus_2id(1, 3) = Type(0., 0.);
  xy_plus_2id(2, 0) = xy_plus_2id(2, 3) = xy_plus_2id(3, 1) = xy_plus_2id(3, 2) = Type(0., 0.);
  xy_plus_2id(0, 3) = xy_plus_2id(1, 2) = Type(0.,-1.);
  xy_plus_2id(2, 1) = xy_plus_2id(3, 0) = Type(0., 1.);
  xy_plus_2id(0, 0) = xy_plus_2id(1, 1) = xy_plus_2id(2, 2) = xy_plus_2id(3, 3) = Type(2., 0.);
  apply2QubitGate(qubit, qubit2, xy_plus_2id);

// update sum adding <psi|XY|psi>
  BaseType final_norm = computenorm();
  sum += (final_norm*final_norm - 5.*initial_norm*initial_norm)/4.;

// undo the computation to recover the initial state |psi>
  openqu::TinyMatrix<Type, 4, 4, 32> inverse;
  inverse(0, 1) = inverse(0, 2) = inverse(1, 0) = inverse(1, 3) = Type(0., 0.);
  inverse(2, 0) = inverse(2, 3) = inverse(3, 1) = inverse(3, 2) = Type(0., 0.);
  inverse(0, 3) = inverse(1, 2) = Type(0., 1./3.);
  inverse(2, 1) = inverse(3, 0) = Type(0.,-1./3.);
  inverse(0, 0) = inverse(1, 1) = inverse(2, 2) = inverse(3, 3) = Type( 2./3., 0.);
  apply2QubitGate(qubit, qubit2, inverse);
}


//------------------------------------------------------------------------------
// TODO : check how the basis is it is: 00-01-10-11 or 00-10-01-11 !!!!
//        this code uses the standard 00-01-10-11 despite this being opposite to backend storage convention
template <class Type>
void QbitRegister<Type>::expectationValueZX(unsigned qubit, unsigned qubit2, BaseType &sum)
{
#ifdef __ONLY_NORMALIZED_STATES__
  BaseType initial_norm = 1.;
#else
  BaseType initial_norm = computenorm();
#endif

// given initial qureg state in |psi>
// compute the non-normalized vector corresponding to (2+XZ)|psi>
  openqu::TinyMatrix<Type, 4, 4, 32> xz_plus_2id;
  xz_plus_2id(0, 2) = xz_plus_2id(0, 3) = xz_plus_2id(1, 2) = xz_plus_2id(1, 3) = Type(0., 0.);
  xz_plus_2id(2, 0) = xz_plus_2id(2, 1) = xz_plus_2id(3, 0) = xz_plus_2id(3, 1) = Type(0., 0.);
  xz_plus_2id(0, 1) = xz_plus_2id(1, 0) = Type( 1., 0.);
  xz_plus_2id(2, 3) = xz_plus_2id(3, 2) = Type(-1., 0.);
  xz_plus_2id(0, 0) = xz_plus_2id(1, 1) = xz_plus_2id(2, 2) = xz_plus_2id(3, 3) = Type(2., 0.);
  apply2QubitGate(qubit, qubit2, xz_plus_2id);

// update sum adding <psi|XZ|psi>
  BaseType final_norm = computenorm();
  sum += (final_norm*final_norm - 5.*initial_norm*initial_norm)/4.;

// undo the computation to recover the initial state |psi>
  openqu::TinyMatrix<Type, 4, 4, 32> inverse;
  inverse(0, 2) = inverse(0, 3) = inverse(1, 2) = inverse(1, 3) = Type(0., 0.);
  inverse(2, 0) = inverse(2, 1) = inverse(3, 0) = inverse(3, 1) = Type(0., 0.);
  inverse(0, 1) = inverse(1, 0) = Type(-1./3., 0.);
  inverse(2, 3) = inverse(3, 2) = Type( 1./3., 0.);
  inverse(0, 0) = inverse(1, 1) = inverse(2, 2) = inverse(3, 3) = Type( 2./3., 0.);
  apply2QubitGate(qubit, qubit2, inverse);
}


//------------------------------------------------------------------------------
// TODO : check how the basis is it is: 00-01-10-11 or 00-10-01-11 !!!!
//        this code uses the standard 00-01-10-11 despite this being opposite to backend storage convention
template <class Type>
void QbitRegister<Type>::expectationValueXY(unsigned qubit, unsigned qubit2, BaseType &sum)
{
  expectationValueYX(qubit2, qubit, sum);
}


//------------------------------------------------------------------------------
template <class Type>
void QbitRegister<Type>::expectationValueYY(unsigned qubit, unsigned qubit2, BaseType &sum)
{
#ifdef __ONLY_NORMALIZED_STATES__
  BaseType initial_norm = 1.;
#else
  BaseType initial_norm = computenorm();
#endif

// given initial qureg state in |psi>
// compute the non-normalized vector corresponding to (2+YY)|psi>
  openqu::TinyMatrix<Type, 4, 4, 32> yy_plus_2id;
  yy_plus_2id(0, 1) = yy_plus_2id(0, 2) = yy_plus_2id(1, 0) = yy_plus_2id(1, 3) = Type(0., 0.);
  yy_plus_2id(2, 0) = yy_plus_2id(2, 3) = yy_plus_2id(3, 1) = yy_plus_2id(3, 2) = Type(0., 0.);
  yy_plus_2id(0, 3) = yy_plus_2id(3, 0) = Type(-1., 0.);
  yy_plus_2id(1, 2) = yy_plus_2id(2, 1) = Type( 1., 0.);
  yy_plus_2id(0, 0) = yy_plus_2id(1, 1) = yy_plus_2id(2, 2) = yy_plus_2id(3, 3) = Type(2., 0.);
  apply2QubitGate(qubit, qubit2, yy_plus_2id);

// update sum adding <psi|YY|psi>
  BaseType final_norm = computenorm();
  sum += (final_norm*final_norm - 5.*initial_norm*initial_norm)/4.;

// undo the computation to recover the initial state |psi>
  openqu::TinyMatrix<Type, 4, 4, 32> inverse;
  inverse(0, 1) = inverse(0, 2) = inverse(1, 0) = inverse(1, 3) = Type(0., 0.);
  inverse(2, 0) = inverse(2, 3) = inverse(3, 1) = inverse(3, 2) = Type(0., 0.);
  inverse(0, 3) = inverse(3, 0) = Type( 1./3., 0.);
  inverse(1, 2) = inverse(2, 1) = Type(-1./3., 0.);
  inverse(0, 0) = inverse(1, 1) = inverse(2, 2) = inverse(3, 3) = Type( 2./3., 0.);
  apply2QubitGate(qubit, qubit2, inverse);
}


//------------------------------------------------------------------------------
// TODO : check how the basis is it is: 00-01-10-11 or 00-10-01-11 !!!!
//        this code uses the standard 00-01-10-11 despite this being opposite to backend storage convention
template <class Type>
void QbitRegister<Type>::expectationValueZY(unsigned qubit, unsigned qubit2, BaseType &sum)
{
#ifdef __ONLY_NORMALIZED_STATES__
  BaseType initial_norm = 1.;
#else
  BaseType initial_norm = computenorm();
#endif

// given initial qureg state in |psi>
// compute the non-normalized vector corresponding to (2+YZ)|psi>
  openqu::TinyMatrix<Type, 4, 4, 32> yz_plus_2id;
  yz_plus_2id(0, 2) = yz_plus_2id(0, 3) = yz_plus_2id(1, 2) = yz_plus_2id(1, 3) = Type(0., 0.);
  yz_plus_2id(2, 0) = yz_plus_2id(2, 1) = yz_plus_2id(3, 0) = yz_plus_2id(3, 1) = Type(0., 0.);
  yz_plus_2id(0, 1) = yz_plus_2id(3, 2) = Type( 0.,-1.);
  yz_plus_2id(1, 0) = yz_plus_2id(2, 3) = Type( 0., 1.);
  yz_plus_2id(0, 0) = yz_plus_2id(1, 1) = yz_plus_2id(2, 2) = yz_plus_2id(3, 3) = Type(2., 0.);
  apply2QubitGate(qubit, qubit2, yz_plus_2id);

// update sum adding <psi|YZ|psi>
  BaseType final_norm = computenorm();
  sum += (final_norm*final_norm - 5.*initial_norm*initial_norm)/4.;

// undo the computation to recover the initial state |psi>
  openqu::TinyMatrix<Type, 4, 4, 32> inverse;
  inverse(0, 2) = inverse(0, 3) = inverse(1, 2) = inverse(1, 3) = Type(0., 0.);
  inverse(2, 0) = inverse(2, 1) = inverse(3, 0) = inverse(3, 1) = Type(0., 0.);
  inverse(0, 1) = inverse(3, 2) = Type(0., 1./3.);
  inverse(1, 0) = inverse(2, 3) = Type(0.,-1./3.);
  inverse(0, 0) = inverse(1, 1) = inverse(2, 2) = inverse(3, 3) = Type( 2./3., 0.);
  apply2QubitGate(qubit, qubit2, inverse);
}


//------------------------------------------------------------------------------
// TODO : check how the basis is it is: 00-01-10-11 or 00-10-01-11 !!!!
//        this code uses the standard 00-01-10-11 despite this being opposite to backend storage convention
template <class Type>
void QbitRegister<Type>::expectationValueXZ(unsigned qubit, unsigned qubit2, BaseType &sum)
{
  expectationValueZX(qubit2, qubit, sum);
}


//------------------------------------------------------------------------------
// TODO : check how the basis is it is: 00-01-10-11 or 00-10-01-11 !!!!
//        this code uses the standard 00-01-10-11 despite this being opposite to backend storage convention
template <class Type>
void QbitRegister<Type>::expectationValueYZ(unsigned qubit, unsigned qubit2, BaseType &sum)
{
  expectationValueZY(qubit2, qubit, sum);
}


//------------------------------------------------------------------------------
template <class Type>
void QbitRegister<Type>::expectationValueZZ(unsigned qubit, unsigned qubit2, BaseType &sum)
{
#ifdef __ONLY_NORMALIZED_STATES__
  BaseType initial_norm = 1.;
#else
  BaseType initial_norm = computenorm();
#endif

// given initial qureg state in |psi>
// compute the non-normalized vector corresponding to (2+ZZ)|psi>
  openqu::TinyMatrix<Type, 4, 4, 32> zz_plus_2id;
  zz_plus_2id(0, 1) = zz_plus_2id(0, 2) = zz_plus_2id(0, 3) = Type(0., 0.);
  zz_plus_2id(1, 0) = zz_plus_2id(1, 2) = zz_plus_2id(1, 3) = Type(0., 0.);
  zz_plus_2id(2, 0) = zz_plus_2id(2, 1) = zz_plus_2id(2, 3) = Type(0., 0.);
  zz_plus_2id(3, 0) = zz_plus_2id(3, 1) = zz_plus_2id(3, 2) = Type(0., 0.);
  zz_plus_2id(0, 0) = zz_plus_2id(3, 3) = Type(3., 0.); 
  zz_plus_2id(1, 1) = zz_plus_2id(2, 2) = Type(1., 0.);
  apply2QubitGate(qubit, qubit2, zz_plus_2id);

// update sum adding <psi|ZZ|psi>
  BaseType final_norm = computenorm();
  sum += (final_norm*final_norm - 5.*initial_norm*initial_norm)/4.;

// undo the computation to recover the initial state |psi>
  openqu::TinyMatrix<Type, 4, 4, 32> inverse;
  inverse(0, 1) = inverse(0, 2) = inverse(0, 3) = Type(0., 0.);
  inverse(1, 0) = inverse(1, 2) = inverse(1, 3) = Type(0., 0.);
  inverse(2, 0) = inverse(2, 1) = inverse(2, 3) = Type(0., 0.);
  inverse(3, 0) = inverse(3, 1) = inverse(3, 2) = Type(0., 0.);
  inverse(0, 0) = inverse(3, 3) = Type( 1./3., 0.);
  inverse(1, 1) = inverse(2, 2) = Type(  1.  , 0.);
  apply2QubitGate(qubit, qubit2, inverse);
}


//------------------------------------------------------------------------------
// Hamming weight function
std::size_t Hamming_weight(std::size_t x)
{
  std::size_t count=0;
  for (count=0; x; count++)
    x &= x-1;
  return count;
}


//------------------------------------------------------------------------------
// observable:  1==PauliX , 2==PauliY , 3==PauliZ
template <class Type>
void QbitRegister<Type>::expectationValue(std::vector<unsigned> &qubits, std::vector<unsigned> &observables, BaseType &sum)
{
  assert( qubits.size() == observables.size() );

// G is matrix from change of basis Y --> Z, such that Ginv.Z.G = Y 
  openqu::TinyMatrix<Type, 2, 2, 32> G;
  BaseType f = 1. / std::sqrt(2.);
  G(0, 0) = G(1, 0) = Type(f , 0.);
  G(0, 1) = Type(0.,-f);
  G(1, 1) = Type(0., f);
// G^dagger = G^-1
  openqu::TinyMatrix<Type, 2, 2, 32> Ginv;
  Ginv(0, 0) = Ginv(0, 1) = Type(f , 0.);
  Ginv(1, 0) = Type(0., f);
  Ginv(1, 1) = Type(0.,-f);

  for (std::size_t i=0; i<qubits.size(); i++)
  {
    if (observables[i]==1)
      applyHadamard(qubits[i]);
    else if (observables[i]==2)
      apply1QubitGate(qubits[i],G);
    else if (observables[i]==3)
      continue;
    else
      assert(0);	// should never be called
  }  

// compute the expectation value
  MPI_Comm comm = openqu::mpi::Environment::comm();
  std::size_t myrank = openqu::mpi::Environment::rank();
  BaseType local_value = 0;
  std::size_t glb_start = UL(myrank) * localSize();
// integer in binary notation with 1 located at the position of the qubits
  std::size_t y=0;
  for (std::size_t i=0; i<qubits.size(); i++)
    y += 1 << qubits[i];

#pragma omp parallel
{
  std::size_t x;
  #pragma omp for reduction(+ : local_value)
  for(std::size_t i = 0; i < localSize(); i++)
  {
     x = glb_start + i;
     if ( Hamming_weight( x & y ) & 1 )	// odd number of 1 in the qubits involved
       local_value -= std::abs(state[i]) * std::abs(state[i]);
     else
       local_value += std::abs(state[i]) * std::abs(state[i]);
  }
}
  BaseType global_value;
  // MPI_Allreduce(&local_value, &global_value, 1, MPI_DOUBLE, MPI_SUM, comm);
  MPI_Allreduce_x(&local_value, &global_value,  MPI_SUM, comm);

// update sum
  sum += global_value;

// undo the iquantum gates to recover the initial state |psi>
  for (std::size_t i=0; i<qubits.size(); i++)
  {
    if (observables[i]==1)
      applyHadamard(qubits[i]);
    else if (observables[i]==2)
      apply1QubitGate(qubits[i],Ginv);
    else if (observables[i]==3)
      continue;
    else
      assert(0);	// should never be called
  }  
}


template class QbitRegister<ComplexSP>;
template class QbitRegister<ComplexDP>;
