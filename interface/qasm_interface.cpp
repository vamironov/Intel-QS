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

#if !defined(STANDALONE)
#include "openqu/engines/distrwavefunctionsimulator/qHiPSTER_backend/src/qureg.hpp"
#else
#include "qureg/qureg.hpp"
#endif

using namespace std;


int main(int argc, char*argv[]) {
    openqu::mpi::Environment env(argc, argv);
    string line = "";
    string token = "";

    if (env.is_usefull_rank() == false) 
        return 0;

    int myid = env.rank();
    using Type = ComplexSP;
    QbitRegister<Type> *psi1;

    while(true) {
        getline(cin,line);

        if(line.length() > 1) {
            token = line.substr(0,line.find_first_of(' '));
            if(token.length() > 1) {
                cout << token << ',';
            }
        } else
          break;
    }

return 0;
}
