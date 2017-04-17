//------------------------------------------------------------------------------
// Copyright (C) 2017 Intel Corporation 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//------------------------------------------------------------------------------
#include <vector>

using namespace std;

template <class Type = ComplexDP>
class NoisyQureg : public QbitRegister<Type> {

  private :

    typedef typename QbitRegister<Type>::BaseType BaseType;

    std::vector<BaseType> TimeFromLastGate;

    unsigned OneQubitLogicalGateCount=0;
    unsigned TwoQubitLogicalGateCount=0;


  public :

    // Constructor
    NoisyQureg<Type>(unsigned Nqubits) : QbitRegister<Type>(Nqubits)
    {
      TimeFromLastGate.assign(Nqubits,0.);
    }

    // Default destructor
    ~NoisyQureg<Type>() {};

    // Get stats
    unsigned GetTotalQubitLogicalGateCount();
    unsigned GetOneQubitLogicalGateCount();
    unsigned GetTwoQubitLogicalGateCount();

    // Reset decoherence time and implement noise gate
    void AddNoiseOneQubitGate(unsigned const);
    void AddNoiseTwoQubitGate(unsigned const, unsigned const);

    // Perform gates
    void applyHadamard(unsigned const);
    void applyRotationX(unsigned const, BaseType);
    void applyRotationY(unsigned const, BaseType);
    void applyRotationZ(unsigned const, BaseType);
    void applyCPauliX(unsigned const, unsigned const);
    void applyControlled1QubitGate(unsigned const, unsigned const, openqu::TinyMatrix<Type, 2, 2, 32>);

};


// ----------------------------------------------------------
// -------- implementation of the class methods -------------
// ----------------------------------------------------------


template <class Type>
unsigned NoisyQureg<Type>::GetOneQubitLogicalGateCount()
{
  return OneQubitLogicalGateCount;
}

template <class Type>
unsigned NoisyQureg<Type>::GetTwoQubitLogicalGateCount()
{
  return TwoQubitLogicalGateCount;
}

template <class Type>
unsigned NoisyQureg<Type>::GetTotalQubitLogicalGateCount()
{
  return OneQubitLogicalGateCount + TwoQubitLogicalGateCount;
}

template <class Type>
void NoisyQureg<Type>::AddNoiseOneQubitGate(unsigned const qubit)
{
  BaseType decoh_time=TimeFromLastGate[qubit];
  TimeFromLastGate[qubit]=0.;
  OneQubitLogicalGateCount++;
//TODO : generate angle and direction of Pauli rotation for Pauli-twirld noise channel
}

template <class Type>
void NoisyQureg<Type>::AddNoiseTwoQubitGate(unsigned const q1, unsigned const q2)
{
  BaseType decoh_time_1 = TimeFromLastGate[q1];
  BaseType decoh_time_2 = TimeFromLastGate[q2];
  TimeFromLastGate[q1]=0.;
  TimeFromLastGate[q2]=0.;
  TwoQubitGateCount++;
//TODO : generate angle and direction of Pauli rotation for Pauli-twirld noise channel
}


// ----------------------------------------------------------
// -------- list of modified gates --------------------------
// ----------------------------------------------------------


template <class Type>
void NoisyQureg<Type>::applyHadamard(unsigned const q)
{
  AddNoiseOneQubitGate(q); 
  QbitRegister<Type>::applyHadamard(q);
}

template <class Type>
void NoisyQureg<Type>::applyRotationX(unsigned const q, BaseType theta)
{
  AddNoiseOneQubitGate(q); 
  QbitRegister<Type>::applyRotationX(q,theta);
}

template <class Type>
void NoisyQureg<Type>::applyRotationY(unsigned const q, BaseType theta)
{
  AddNoiseOneQubitGate(q); 
  QbitRegister<Type>::applyRotationY(q,theta);
}

template <class Type>
void NoisyQureg<Type>::applyRotationZ(unsigned const q, BaseType theta)
{
  AddNoiseOneQubitGate(q); 
  QbitRegister<Type>::applyRotationZ(q,theta);
}

template <class Type>
void NoisyQureg<Type>::applyCPauliX(unsigned const q1, unsigned const q2)
{
  AddNoiseTwoQubitGate(q1,q2); 
  QbitRegister<Type>::applyCPauliX(q1,q2);
}

template <class Type>
void NoisyQureg<Type>::applyControlled1QubitGate(unsigned const q1, unsigned const q2,
                                                 openqu::TinyMatrix<Type, 2, 2, 32> V)
{
  AddNoiseTwoQubitGate(q1,q2); 
  QbitRegister<Type>::applyControlled1QubitGate(q1,q2,V);
}
