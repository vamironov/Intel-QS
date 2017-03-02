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
 * @file interface_api_version.h
 *
 * This header file contains functions for reporting the version of both the
 * QASM interface to qHiPSTER as well as the version of the qHiPSTER library
 * that was linked into the interface and in use.
 */

/**
 * Print out the QASM interface version string. The format will be 
 * major.minor.revision.
 * @param args Unused.
 * @return 0.
 */
unsigned long quiversion(std::string args);


/**
 * Print out the qHiPSTER library version string. The format will be 
 * major.minor.revision.
 * @param args Unused.
 * @return 0.
 */
unsigned long quversion(std::string args);

/** @} */
