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
 * @file interface_api_qasm.h
 *
 * This file contains the interface to the QASM command handler function.  The QASM
 * operation is broken up into a command token and an args token.  The command is
 * mapped to a hash table of functions designed to handle the QASM op and then the
 * function is invoked and a result returned.
 *
 */

/**
 * Handle the execution of a QASM instruction in qHiPSTER.
 * @param op The QASM operation we wish to execute.
 * @param args The operands, if any, for the operation.
 * @return 0 Success - Op Handled\n
 *        >0 Failure - Op not handled or error.
 */
unsigned long ExecuteHandler(std::string op, std::string args);

/** @}*/
