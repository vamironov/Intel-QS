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

#if !defined(STANDALONE)
#include "openqu/util/mpi.hpp"
#else
#include "util/mpi.hpp"
#endif
#include <immintrin.h>
#include <climits>
#include <complex>
#include <iomanip>
#include <getopt.h>
#include <algorithm>
#include <cctype>
#include <functional>
#include <string>


// defines
#define DO_PRAGMA(x) _Pragma(#x)
#define TODO(x) DO_PRAGMA(message("TODO - " #x))
#define D(x) ((double)(x))
#define UL(x) ((std::size_t)(x))
#define sec() time_in_seconds()
#define xstr(s) __str__(s)
#define __str__(s) #s

// template<class Type>
// using ComplexType = std::complex<Type>;
using ComplexSP = std::complex<float>;
using ComplexDP = std::complex<double>;

double time_in_seconds(void);

#if 0
int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                int dest, int sendtag,
                void *recvbuf, int recvcount, MPI_Datatype recvtype,
                int source, int recvtag,
                MPI_Comm comm, MPI_Status *status)
{
  MPI_Request send_request,  recv_request;

  MPI_Irecv(recvbuf, recvcount, recvtype, source, recvtag, comm, &recv_request);
  MPI_Isend(sendbuf, sendcount, sendtype, dest,   sendtag, comm, &send_request);

  MPI_Waitall(1, &send_request, status);
  MPI_Waitall(1, &recv_request, status);

  return 0;
}
#endif

static int MPI_Allreduce_x(float *sendbuf, float *recvbuf,
                           MPI_Op op, MPI_Comm comm)
{
   return MPI_Allreduce((void*)sendbuf, (void *)recvbuf, 1,
                        MPI_FLOAT, op, comm);
}

static int MPI_Allreduce_x(double *sendbuf, double *recvbuf,
                            MPI_Op op, MPI_Comm comm)
{
   return MPI_Allreduce((void*)sendbuf, (void *)recvbuf, 1,
                        MPI_DOUBLE, op, comm);
}

static
int MPI_Sendrecv_x(ComplexSP *sendbuf, int sendcount,
                   int dest, int sendtag,
                   ComplexSP *recvbuf, int recvcount,
                   int source, int recvtag,
                   MPI_Comm comm, MPI_Status *status)
{
  return
  MPI_Sendrecv((void *)sendbuf, sendcount, MPI_COMPLEX, dest, sendtag, 
               (void *)recvbuf, recvcount, MPI_COMPLEX, source, recvtag, comm, status);
}

static
int MPI_Sendrecv_x(ComplexDP *sendbuf, int sendcount,
                   int dest, int sendtag,
                   ComplexDP *recvbuf, int recvcount,
                   int source, int recvtag,
                   MPI_Comm comm, MPI_Status *status)
{
  return
  MPI_Sendrecv((void *)sendbuf, sendcount, MPI_DOUBLE_COMPLEX, dest, sendtag,
               (void *)recvbuf, recvcount, MPI_DOUBLE_COMPLEX, source, recvtag, comm, status);
}

