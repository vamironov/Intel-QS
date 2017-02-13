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

#include "qureg.hpp"

template< typename Type >
__attribute__((noinline))
void Loop_SN(std::size_t start, std::size_t end, Type *state0, Type *state1,
             std::size_t indsht0, std::size_t indsht1, TM2x2<Type> const&m, 
             bool specialize, Timer *timer);


template< typename Type >
__attribute__((noinline))
void Loop_DN(std::size_t gstart, std::size_t gend, std::size_t pos,
             Type *state0, Type *state1,
             std::size_t indsht0, std::size_t indsht1,
             TM2x2<Type> const&m,
             bool specialize, Timer *timer);

template< typename Type >
__attribute__((noinline))
void Loop_TN(Type *state, std::size_t c11, std::size_t c12,
             std::size_t c13, std::size_t c21, std::size_t c22, std::size_t c23, 
             std::size_t c31, std::size_t c32, std::size_t ind_shift, 
             TM2x2<Type> const&m, bool specialize, Timer *timer);

template< typename Type >
void ScaleState(std::size_t start, std::size_t end, Type *state,
                const Type &s, Timer *timer);

// for debugging purposes
static __attribute__((noinline)) void LOOP_START() {printf("\n");}
static __attribute__((noinline)) void LOOP_END() {printf("\n");}
