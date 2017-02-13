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

#include "qureg.hpp"


template <class Type>
bool QbitRegister<Type>::operator==(const QbitRegister &rhs)
{
  assert(rhs.globalSize() == globalSize());
  for (std::size_t i = 0; i < rhs.localSize(); i++) {
    if (state[i] != rhs.state[i]) {
      printf("[%lf %lf] [%lf %lf]\n", state[i].real(), state[i].real(), rhs.state[i].imag(), rhs.state[i].imag());
      return false;
    }
  }

  return true;
}

template <class Type>
QbitRegister<Type>::BaseType QbitRegister<Type>::maxabsdiff(QbitRegister &x, Type sfactor)
{
  MPI_Comm comm = openqu::mpi::Environment::comm();
  assert(localSize() == x.localSize());
  BaseType lcl_maxabsdiff = -1.0;

  std::size_t lcl = localSize();
#if defined(__ICC) || defined(__INTEL_COMPILER)
#pragma omp parallel for simd reduction(max : lcl_maxabsdiff)
#else
   TODO(Remember to find 'omp parallel for simd reduction' equivalent for gcc)
#endif
  for (std::size_t i = 0; i < lcl; i++) {
    lcl_maxabsdiff = std::max(lcl_maxabsdiff, std::abs(state[i] - sfactor*x.state[i]));
  }

  BaseType glb_maxabsdiff;
#ifdef OPENQU_HAVE_MPI
  // MPI_Allreduce(&lcl_maxabsdiff, &glb_maxabsdiff, 1, MPI_DOUBLE, MPI_MAX, comm);
  MPI_Allreduce_x(&lcl_maxabsdiff, &glb_maxabsdiff,  MPI_MAX, comm);
#else
  glb_maxabsdiff = lcl_maxabsdiff;
#endif

  return glb_maxabsdiff;
}

template <class Type>
QbitRegister<Type>::BaseType QbitRegister<Type>::maxl2normdiff(QbitRegister &x)
{
  MPI_Comm comm = openqu::mpi::Environment::comm();
  assert(localSize() == x.localSize());
  BaseType lcl_diff = 0.0;
  // #pragma omp parallel for simd reduction(+:lcl_diff)
  std::size_t lcl = localSize();
#if defined(__ICC) || defined(__INTEL_COMPILER)
#pragma omp parallel for reduction(+ : lcl_diff)
#else
   TODO(Remember to find 'omp parallel for simd reduction' equivalent for gcc)
#endif
  for (std::size_t i = 0; i < lcl; i++) {
    Type r = state[i] - x.state[i];
    lcl_diff += pow(std::abs(r), 2);
  }

  BaseType glb_diff;
#ifdef OPENQU_HAVE_MPI
  // MPI_Allreduce(&lcl_diff, &glb_diff, 1, MPI_DOUBLE, MPI_MAX, comm);
  MPI_Allreduce_x(&lcl_diff, &glb_diff,  MPI_MAX, comm);
#else
   glb_diff = lcl_diff;
#endif

  return glb_diff;
}

template <class Type>
void QbitRegister<Type>::normalize() 
{
  MPI_Comm comm = openqu::mpi::Environment::comm();

  BaseType global_norm = computenorm();
  std::size_t lcl = localSize();
#pragma omp parallel for 
  for(std::size_t i = 0; i < lcl; i++)
     state[i] = state[i] / global_norm;

}

template <class Type>
QbitRegister<Type>::BaseType QbitRegister<Type>::computenorm()
{

  MPI_Comm comm = openqu::mpi::Environment::comm();
  BaseType local_normsq = 0;
  std::size_t lcl = localSize();
#if defined(__ICC) || defined(__INTEL_COMPILER)
#pragma omp parallel for reduction(+ : local_normsq)
#else
   TODO(Remember to find 'omp parallel for simd reduction' equivalent for gcc)
#endif
  for(std::size_t i = 0; i < lcl; i++)
  {
     local_normsq += std::abs(state[i]) * std::abs(state[i]);
  }
  BaseType global_normsq;
  // MPI_Allreduce(&local_normsq, &global_normsq, 1, MPI_DOUBLE, MPI_SUM, comm);
  MPI_Allreduce_x(&local_normsq, &global_normsq,  MPI_SUM, comm);

  return sqrt(global_normsq);
}

template <class Type>
double QbitRegister<Type>::entropy()
{

  MPI_Comm comm = openqu::mpi::Environment::comm();
  std::size_t lcl = localSize();
  double local_Hp = 0;

  if(timer) timer->Start("ENT", 0);

  double ttot = 0., ttmp1 = sec();
#if defined(__ICC) || defined(__INTEL_COMPILER)
#pragma omp parallel for reduction(+ : local_Hp)
#else
   TODO(Remember to find 'omp parallel for simd reduction' equivalent for gcc)
#endif
  for (std::size_t i = 0; i < lcl; i++) {
    double pj = std::abs(state[i]) * std::abs(state[i]);
    if (pj != double(0.)) {
      local_Hp -= pj * std::log(pj);
    }
  }

  double global_Hp;
  // MPI_Allreduce(&local_Hp, &global_Hp, 1, MPI_DOUBLE, MPI_SUM, comm);
  MPI_Allreduce_x(&local_Hp, &global_Hp,  MPI_SUM, comm);
  
  ttot = sec() - ttmp1;

 
  if(timer) {
    double datab = D(sizeof(state[0])) * D(lcl) / ttot;
    timer->record_sn(ttot, datab / ttot);
    timer->Stop();
  }

  return global_Hp / (double)log(double(2.0));
}

template <class Type>
std::vector<double> QbitRegister<Type>::googleStats()
{
  std::vector <double> stats;

  MPI_Comm comm = openqu::mpi::Environment::comm();
  std::size_t lcl = localSize();
  double two2n = D(globalSize());
  
  double entropy = 0, avgselfinfo=0,
         m2 = 0, m3 = 0, m4 = 0, m5 = 0, m6 = 0, 
         m7 = 0, m8 = 0, m9 = 0, m10 = 0; 

  if(timer) timer->Start("ENT", 0);

  double ttot = 0., ttmp1 = sec();

#if defined(__ICC) || defined(__INTEL_COMPILER)
#pragma omp parallel for reduction(+ : entropy, avgselfinfo, m2, m3, m4, m5, m6, m7, m8, m9, m10)
#else
   TODO(Remember to find 'omp parallel for simd reduction' equivalent for gcc)
#endif
  #pragma simd reduction(+ : entropy, avgselfinfo, m2, m3, m4, m5, m6, m7, m8, m9, m10)
  // #pragma novector
  for (std::size_t i = 0; i < lcl; i++) {
    double pj = std::abs(state[i]) * std::abs(state[i]);
    if (pj != double(0.)) {
      double nl = log(pj);
      // double nl = pj*pj;
      entropy -= pj * nl;
      avgselfinfo -= nl;
    }
    double pj2  = pj *  pj,
           pj3  = pj2 * pj,
           pj4  = pj2 * pj2,
           pj5  = pj3 * pj2,
           pj6  = pj3 * pj3,
           pj7  = pj4 * pj3,
           pj8  = pj4 * pj4,
           pj9  = pj5 * pj4,
           pj10 = pj5 * pj5;
    m2  += pj2;
    m3  += pj3;
    m4  += pj4;
    m5  += pj5;
    m6  += pj6;
    m7  += pj7;
    m8  += pj8;
    m9  += pj9;
    m10 += pj10;
  }
  double global_entropy;
  MPI_Allreduce_x(&entropy, &global_entropy,  MPI_SUM, comm);
  global_entropy /= (double)std::log(double(2.0));
  stats.push_back(global_entropy);

  double global_avgselfinfo;
  MPI_Allreduce_x(&avgselfinfo, &global_avgselfinfo,  MPI_SUM, comm);
  global_avgselfinfo /= (double)log(double(2.0));
  global_avgselfinfo /= two2n;
  stats.push_back(global_avgselfinfo);

  // compute moments
  std::vector <double> m = {m2, m3, m4, m5, m6, m7, m8, m9, m10},
                       factor(m.size()), 
                       global_m(m.size());
  double factorial = 1.0;
  for(auto i = 0; i < m.size(); i++) {
    auto k = i + 2;
    factorial *= D(k);
    factor[i] = pow(two2n, D(k - 1)) / factorial;

    m[i] *= factor[i];
    MPI_Allreduce_x(&(m[i]), &(global_m[i]),  MPI_SUM, comm);
    stats.push_back(global_m[i]);
  }

  ttot = sec() - ttmp1;


  if(timer) {
    double datab = D(sizeof(state[0])) * D(lcl) / ttot;
    timer->record_sn(ttot, datab / ttot);
    timer->Stop();
  }

  return stats;
}


template <class Type, class BaseType>
std::string printvec(Type *state, std::size_t size, std::size_t nqbits, BaseType &pcum,
                     Permutation *permutation)
{
  std::string str;
  int rank = openqu::mpi::Environment::rank();
  for (std::size_t i = 0; i < size; i++) {
    // std::string bin = dec2bin(rank * size + i, nqbits, false);
    std::string bin = permutation->lin2perm(rank * size + i);
    char s[4096];
    sprintf(s, "\t%-13.8lf + i * %-13.8lf   %% |%s> p=%lf\n", real(state[i]), imag(state[i]),
            bin.c_str(), std::abs(state[i]) * std::abs(state[i]));
    str = str + s;
    pcum += std::abs(state[i]) * std::abs(state[i]);
  }
  return std::string(str);
}

template <class Type>
void QbitRegister<Type>::Print(std::string x, std::vector<std::size_t> qbits)
{
  BaseType pcum = 0;
  int rank = openqu::mpi::Environment::rank();
  int nprocs = openqu::mpi::Environment::size();
  MPI_Comm comm = openqu::mpi::Environment::comm();
  openqu::mpi::barrier();
  if (rank == 0) {
    // print permutation
    assert(permutation);
    printf("permutation: %s\n", permutation->GetMapStr().c_str());
    std::string s = printvec<Type, BaseType>(state, localSize(), nqbits, pcum, permutation);
    printf("%s=[\n", x.c_str());
    printf("%s", s.c_str());
#ifdef OPENQU_HAVE_MPI
    for (std::size_t i = 1; i < nprocs; i++) {
      std::size_t len;
      MPI_Recv(&len, 1, MPI_LONG, i, 1000 + i, comm, MPI_STATUS_IGNORE);
      s.resize(len);
      MPI_Recv((void *)(s.c_str()), len, MPI_CHAR, i, i, comm, MPI_STATUS_IGNORE);
      printf("%s", s.c_str());
    }
#endif

  } else {
#ifdef OPENQU_HAVE_MPI
    std::string s = printvec(state, localSize(), nqbits, pcum, permutation);
    std::size_t len = s.length() + 1;
    MPI_Send(&len, 1, MPI_LONG, 0, 1000 + rank, comm);
    MPI_Send(const_cast<char *>(s.c_str()), len, MPI_CHAR, 0, rank, comm);
#endif
  }

  BaseType glb_pcum;
#ifdef OPENQU_HAVE_MPI
  MPI_Reduce(&pcum, &glb_pcum, 1, MPI_DOUBLE, MPI_SUM, 0, comm);
#else
  glb_pcum = pcum;
#endif
  if (rank == 0) {
    printf("]; %% pcum = %lf\n", glb_pcum);
  }

  openqu::mpi::barrier();
}

template <class Type>
void QbitRegister<Type>::dumpbin(std::string fn)
{
  MPI_Comm comm = openqu::mpi::Environment::comm();
#ifdef OPENQU_HAVE_MPI
  MPI_Status status;
  MPI_File fh;
  MPI_File_open(comm, (char *)fn.c_str(), MPI_MODE_CREATE | MPI_MODE_WRONLY,
                MPI_INFO_NULL, &fh);
  std::size_t size = localSize();
  assert(size < INT_MAX);
  MPI_Offset offset = size * UL(openqu::mpi::Environment::rank() * sizeof(Type));

  double t0 = sec();
  openqu::mpi::barrier();
  MPI_File_write_at(fh, offset, (void *)(&(state[0])), size, MPI_DOUBLE_COMPLEX, &status);
  openqu::mpi::barrier();
  double t1 = sec();
  MPI_File_close(&fh);
  if (openqu::mpi::Environment::rank() == 0) {
    double bw = D(UL(sizeof(state[0])) * size) / (t1 - t0) / 1e6;
    printf("Dumping state to %s took %lf sec (%lf MB/s)\n", fn.c_str(), t1 - t0, bw);
  }
#else
  assert(0);
#endif
}

template <class Type>
void QbitRegister<Type>::EnbStat()
{
  unsigned myrank = openqu::mpi::Environment::rank();
  unsigned nprocs = openqu::mpi::Environment::size();

  assert(timer == NULL);
  timer = new Timer(nqbits, myrank, nprocs);
}

template <class Type>
void QbitRegister<Type>::GetStat()
{
  assert(timer);
  timer->Breakdown();
  // delete timer;
  // timer = NULL;
}


template class QbitRegister<ComplexSP>;
template class QbitRegister<ComplexDP>;

