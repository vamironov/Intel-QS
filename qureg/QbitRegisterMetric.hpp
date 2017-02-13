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

#include <vector>
using namespace std;

template <class Type = ComplexDP>
class QbitRegisterMetric: public QbitRegister<Type> {
  int iTotalQubitGateCount=0;
  int iOneQubitGateCount=0;
  int iTwoQubitGateCount=0;
  std::vector<int> vParallelDepth;
  void OneQubitIncrements(int);
  void TwoQubitIncrements(int,int);

public:
  //Constructor
  QbitRegisterMetric<Type>(int iNQbits):QbitRegister<Type>(iNQbits){
    vParallelDepth.resize(iNQbits);
  }

  //Get stats
  int GetTotalQubitGateCount();
  int GetOneQubitGateCount();
  int GetTwoQubitGateCount();
  int GetParallelDepth();

  //Perform gates
  void applyHadamard(int);
  void applyRotationX(int, double);
  void applyRotationY(int, double);
  void applyRotationZ(int, double);
  void applyCPauliX(int, int);
  void applyControlled1QubitGate(int, int, openqu::TinyMatrix<Type, 2, 2, 32>);
};

template <class Type>
int QbitRegisterMetric<Type>::GetOneQubitGateCount(){
  return iOneQubitGateCount;
}

template <class Type>
int QbitRegisterMetric<Type>::GetTwoQubitGateCount(){
  return iTwoQubitGateCount;
}

template <class Type>
int QbitRegisterMetric<Type>::GetTotalQubitGateCount(){
  return iTotalQubitGateCount;
}

template <class Type>

int QbitRegisterMetric<Type>::GetParallelDepth(){
  return *std::max_element(std::begin(vParallelDepth), std::end(vParallelDepth));
}

template <class Type>
void QbitRegisterMetric<Type>::OneQubitIncrements(int q){
  iTotalQubitGateCount++;
  iOneQubitGateCount++;
  vParallelDepth[q]++;
}

template <class Type>
void QbitRegisterMetric<Type>::TwoQubitIncrements(int q1, int q2){
  iTotalQubitGateCount++;
  iTwoQubitGateCount++;
  int iNewDepth = max(vParallelDepth[q1],vParallelDepth[q2])+1;
  vParallelDepth[q1]=iNewDepth;
  vParallelDepth[q2]=iNewDepth;
}

template <class Type>
void QbitRegisterMetric<Type>::applyHadamard(int q){
  QbitRegister<Type>::applyHadamard(q);
  OneQubitIncrements(q); 
}

template <class Type>
void QbitRegisterMetric<Type>::applyRotationX(int q, double theta){
  QbitRegister<Type>::applyRotationX(q,theta);
  OneQubitIncrements(q); 
}

template <class Type>
void QbitRegisterMetric<Type>::applyRotationY(int q, double theta){
  QbitRegister<Type>::applyRotationY(q,theta);
  OneQubitIncrements(q); 
}

template <class Type>
void QbitRegisterMetric<Type>::applyRotationZ(int q, double theta){
  QbitRegister<Type>::applyRotationZ(q,theta);
  OneQubitIncrements(q); 
}

template <class Type>
void QbitRegisterMetric<Type>::applyCPauliX(int q1, int q2){
  QbitRegister<Type>::applyCPauliX(q1,q2);
  TwoQubitIncrements(q1,q2); 
}

template <class Type>
void QbitRegisterMetric<Type>::applyControlled1QubitGate(int q1, int q2, openqu::TinyMatrix<Type, 2, 2, 32> V){
  QbitRegister<Type>::applyControlled1QubitGate(q1,q2,V);
  TwoQubitIncrements(q1,q2); 
}
