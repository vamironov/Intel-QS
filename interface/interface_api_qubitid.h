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
 * @file interface_api_qubitid.h
 *
 * This header file contains functions for conveniently handling the assignment
 * of qubit identifiers to qubit strings passed in as operands to QASM instructions.
 */


/**
 * query_qubit_id()
 * @param qubit_name The string name passed from the QASM instruction.
 * @return An integer representing the the qubit identifier that matches the
 *         qubit name string. If the qubit name is not found then an id is generated, 
 *         added to an internal tracking table, and the id is returned.
 */
int query_qubit_id(std::string qubit_name);

/** @}*/
