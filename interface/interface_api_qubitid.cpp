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
#include <unordered_map>

using namespace std;

// Qubits are assigned a unique identifier that starts from this base value.
#define QUBIT_ID_BASE 100


/**
 * Each QASM instruction that comes into the qHiPSTER QASM interface has a
 * unique identifier string for the operand:
 *
 * 	H    qubit0
 * 	CNOT qubit0,qubit1
 * 	...
 * 
 * qHiPSTER applies qubit operations to a register of qubits that are indexed
 * from [0...(N-1)] where N is the total number of qubits. For the QASM snippet
 * above, the qubits will be assigned a unique id in the order they are
 * encountered in the QASM. To explicitly assign qubit identifiers to qHiPSTER
 * register locations you must add the (qubit) instruction to your QASM in the
 * right order as follows:
 *
 * 	qubit qubit0
 * 	qubit qubit1
 * 	H qubit0
 * 	CNOT qubit0,qubit1
 * 	...
 * 
 * This ensures that qubit0 -> qreg[0], qubit1 -> qureg[1] in the qHiPSTER
 * quantum register space.
 *
 **/

// Hash table mapping unique qubit identifiers to each qubit operand.
unordered_map<string,int> qubit_id_table = {};

// Variable to keep track of the next qubit to assign.
int next_qubit_id = QUBIT_ID_BASE;


/**
 * query_qubit_id()
 * 	@qubit_name The string name in the QASM instruction.
 * 	@return The qubit identifier for the qubit string. If it is not found then
 * 	it is created, added to the qubit id table, and returned.
 */
int query_qubit_id(string qubit_name) {

   // Retrieve the qubit_id from the qubit_id_table.
   int& qubit_ref = qubit_id_table[qubit_name];

   // Insert a new qubit_id in the Hash table if we did not get back a valid one.
   if(qubit_ref < QUBIT_ID_BASE)
   {
      qubit_ref = next_qubit_id;
      next_qubit_id++;
   }

   // Translate the Hash encoded ID to a qHiPSTER API relevant ID and return it.
   //cout << "Assigned id: "<<qubit_ref<<endl;
   return (qubit_ref - QUBIT_ID_BASE); 
}

