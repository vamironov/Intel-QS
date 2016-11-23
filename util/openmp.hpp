// Copyright (C) 2016 Theoretical Physics, ETHZ Zurich

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

#pragma once
#include <string>

/** \addtogroup util
 *  @{
 */

/** @file openmp.hpp
 *
 *  This header includes the OpenMP header if it exists and provides
 *  convenience functions that are implemented even if OpenMP is not provided
 */

#ifdef _OPENMP
#include "omp.h"
#else
/// return the number of threads. This is one by default if OpenMP is not present.
inline int omp_get_num_threads() { return 1; }
/// return the number of the current thread. This is zero by default if OpenMP is not present.
inline int omp_get_thread_num() { return 0; }
#endif

namespace openqu {
namespace openmp {
/** initialize OpenMp with the optimal settings for the specific hardware
 *
 * This sets optimal affinity settings, etc. on NUMA machines. Optionally the number of threads
 * can be specified. If OpenMp is not present this has no effect.
 *
 * @param numthreads the number of threads to use
 */

std::string init(unsigned numthreads = 0);

/** returns number of OpenMP threads, set inside out outside simulator
 *
 * \return number of set threads
 */

unsigned omp_get_set_num_threads();

}
}

/** @}*/
