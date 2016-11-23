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

/** @file openmp.cpp
 *
 *  This header implements OpenMp support functionality
 */

#if !defined(STANDALONE)
#include "openqu/util/openmp.hpp"
#else
#include "util/openmp.hpp"
#include "util/mpi.hpp"
#include "util/conversion.hpp"
#endif
#include <cassert>
#include <string>
#include <iostream>

std::string openqu::openmp::init(unsigned numthreads)
{
  // printf("numthreads=%d\n", numthreads);
  std::string aff;
  int myrank = openqu::mpi::Environment::rank();

#ifdef _OPENMP
  if (numthreads) {
    omp_set_num_threads(numthreads);
  }

#if defined(__ICC) || defined(__INTEL_COMPILER)
  char *mv2_string;
  unsigned nodeid = openqu::mpi::Environment::get_nodeid();
  if (!nodeid) aff = "KMP_AFFINITY=compact,1,0,granularity=fine";
  else         aff = "KMP_AFFINITY=compact,1,0,granularity=fine";
  kmp_set_defaults(aff.c_str());
#endif
  // std::string s = openqu::toString(nodeid) + ": " + aff; 
  // openqu::mpi::print(s, MPI_COMM_WORLD);
  

#else
  aff = "";
  assert(numthreads <= 1);
#endif

  return aff;
}

unsigned openqu::openmp::omp_get_set_num_threads()
{
  int nthreads = 1;
#ifdef _OPENMP
  #pragma omp parallel
  #pragma omp master
  {
    nthreads=omp_get_num_threads( );
  }
#endif
  return nthreads;
}
