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
#pragma once

/**
 * \addtogroup interface
 * @{
 */

/**
 * @file interface_api_memory.h
 *
 * This file provides handlers for malloc/free operations on sets of qubits.
 *
 */


/**
 * Parses the number of qubits to allocate from args and attempts to create a
 * quantum register with that number of qubits.
 * @param args A string representing the number of qubits to allocate (integer 0..inf)
 * @return 0 Success\n 
 *        >0 Error/Warning with message to STDERR.
 *
 * __side effect WARNING__!! Operates on a global wavefunction variable named (@ref psi1)
 */
unsigned long qumalloc(std::string args);


/**
 * Free a qHiPSTER quantum register (wavefunction).
 * @param args Unused...can set to NULL.
 * @return 0 Success\n
 *        >0 Error/Warning with message to STDERR.
 *
 * __side effect WARNING__!! Operates on a global wavefunction variable named (@ref psi1)
 */
unsigned long qufree(std::string args);

/** @}*/
