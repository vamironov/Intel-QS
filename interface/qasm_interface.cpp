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
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <functional>
#include <stdexcept>

#if !defined(STANDALONE)
#include "openqu/engines/distrwavefunctionsimulator/qHiPSTER_backend/src/qureg.hpp"
#else
#include "qureg/qureg.hpp"
#endif

using namespace std;


// Global variables related to Psi-function .malloc/.free routines.
using Type = ComplexSP;
QbitRegister<Type> *psi1 = nullptr;
bool fPsiAllocated = false;


unsigned long unk(string args) {
    return 1;
}


unsigned long S_handler(string args) {
    cout << "S"<< " [" << args << "]" <<endl;
    return 0;
}


unsigned long X_handler(string args) {
    cout << "X"<< " [" << args << "]" <<endl;
    return 0;
}


unsigned long T_handler(string args) {
    cout << "T"<< " [" << args << "]" <<endl;
    return 0;
}


unsigned long Tdag_handler(string args) {
    cout << "Tdag"<< " [" << args << "]" <<endl;
    return 0;
}


unsigned long CNOT_handler(string args) {
    cout << "CNOT"<< " [" << args << "]" <<endl;
    return 0;
}


unsigned long H_handler(string args) {
    cout << "H"<< " [" << args << "]" <<endl;
    return 0;
}


unsigned long MeasZ_handler(string args) {
    cout << "MeasZ"<< " [" << args << "]" <<endl;
    return 0;
}


unsigned long PrepZ_handler(string args) {
    cout << "PrepZ"<< " [" << args << "]" <<endl;
    return 0;
}

//
// Allocate a qubit wave function in qHiPSTER.
//
unsigned long qumalloc(string args) {

    int num_qubits = 0;

    // Check for an attempt at a memory leak.
    if (fPsiAllocated) {
        cerr << ".malloc called before .free - memory leak detected."<<endl;
        return 1;
    }

    // Convert the argument to an integer number of qubits.
    try
    {
        num_qubits = stoi(args,nullptr,10);

    } catch(const invalid_argument& inv_arg) {
        cerr << ".malloc (size) - size parameter was not an integer."<<endl;
    } catch(const out_of_range& oor_arg) {
        cerr << ".malloc (size) - size parameter was too large to fit in an integer."<<endl;
    }

    // Ensure wavefunction register is in the allowed range.
    if ((num_qubits > 0) && (num_qubits <= 43)) {
        psi1 = new QbitRegister<Type>(num_qubits);

        if (psi1) {
            fPsiAllocated = true;
            cout << "Allocated ["<<num_qubits<<"] qubits."<<endl;
            return 0;
        } 
    }
    else 
    {
        cerr << ".malloc (size) - allocations in the range from 1..43 only."<<endl;
    }
 

    return 1;
}

//
// Free any qubit allocation.
//
unsigned long qufree(string args) {

    if (fPsiAllocated) {
        delete psi1;
        psi1 = nullptr;
        fPsiAllocated = false;

        cout << "Qubits successfully free."<<endl;
        return 0;
    }

    cerr << "Harmless attempt to .free before .malloc. Nothing done."<<endl;

    return 1;
}


unordered_map<string, function<long(string)>> qufun_table = {\
                                                {".malloc", qumalloc},
                                                {".free", qufree},
                                                {"H", H_handler},
                                                {"CNOT", CNOT_handler},
                                                {"PrepZ",PrepZ_handler},
                                                {"T", T_handler},
                                                {"X", X_handler},
                                                {"Tdag", Tdag_handler},
                                                {"S", S_handler},
                                                {"MeasZ", MeasZ_handler},
                                                {"T", unk},
                                                {"T", unk},
                                                {"T", unk},
                                                {"T", unk},
                                                {"T", unk},
};



int main(int argc, char*argv[]) {
    openqu::mpi::Environment env(argc, argv);
    string line = "";
    string token = "";

    if (env.is_usefull_rank() == false) 
        return 0;

    int myid = env.rank();
    using Type = ComplexSP;

    while(true) {
        getline(cin,line);

        if(line.length() >= 1) {
            int token_end = line.find_first_of(' ');
            unsigned long result = 1;

            token = line.substr(0,token_end);
            if(!token.empty()) {
               function<long(string)> func = qufun_table[token];
               if(func) {
                  result = func(line.substr(token_end+1,line.length()));
               }

               if (result > 0) {
                   cerr << "Qasm Op failed - ["<<token<<"]"<<endl;
               }
            }
        } else
          break;
    }

return 0;
}
