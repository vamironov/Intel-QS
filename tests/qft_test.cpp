#include "qureg/qureg.hpp"


#if (defined(__ICC) || defined(__INTEL_COMPILER))
#include <mkl.h>
#if defined(OPENQU_HAVE_MPI)
#include <mkl_cdft.h>
#endif
#endif


template<typename Type>
void qft(QbitRegister<Type> &psi)
{
  int n = openqu::ilog2(psi.size());

  // main computation
  for (int i = n - 1; i >= 0; i--) {
    for (int j = n - 1; j > i; j--) {
      int k = j - i;
      openqu::TinyMatrix<Type, 2, 2, 32> phaseshift;
      phaseshift(0, 0) = {1, 0};
      phaseshift(0, 1) = {0, 0};
      phaseshift(1, 0) = {0, 0};
      phaseshift(1, 1) = Type(cos(M_PI / D(UL(1) << UL(k))), sin(M_PI / D(UL(1) << UL(k))));
      psi.applyControlled1QubitGate(j, i, phaseshift);
    }
    psi.applyHadamard(i);
  }

  // perform swapping
  for (int i = 0; i < (n / 2); i++) {
    psi.applySwap(i, n - 1 - i);
  }
}



template<typename Type>
static void cfft(QbitRegister<Type> &x)
{
  
  int nprocs = openqu::mpi::Environment::size();
  MPI_Comm comm = openqu::mpi::Environment::comm();
#if (defined(__ICC) || defined(__INTEL_COMPILER))
#ifdef OPENQU_HAVE_MPI
  DFTI_DESCRIPTOR_DM_HANDLE desc;
  MKL_LONG v;

  // Create descriptor for 1D FFT
  MKL_LONG status =
      (sizeof(BaseType<Type>) == 8) ? 
      DftiCreateDescriptorDM(comm, &desc, DFTI_DOUBLE, DFTI_COMPLEX, 1, x.globalSize()) :
      DftiCreateDescriptorDM(comm, &desc, DFTI_SINGLE, DFTI_COMPLEX, 1, x.globalSize());

  // openqu::mpi::barrier(); exit(0);
  DftiGetValueDM(desc, CDFT_LOCAL_SIZE, &v);
  std::vector <Type> work(v);
  DftiSetValueDM(desc, CDFT_WORKSPACE, work.data());

  
  DftiSetValueDM(desc, DFTI_BACKWARD_SCALE, 1.0 / std::sqrt((BaseType<Type>)x.globalSize()));
  DftiCommitDescriptorDM(desc);
  DftiComputeBackwardDM(desc, &(x[0]));
  DftiFreeDescriptorDM(&desc);
#else
  DFTI_DESCRIPTOR_HANDLE descriptor;
  MKL_LONG status;
  status = DftiCreateDescriptor(&descriptor, DFTI_DOUBLE, DFTI_COMPLEX, 1, x.globalSize());  
  status = DftiSetValue(descriptor, DFTI_PLACEMENT, DFTI_INPLACE);  
  status = DftiSetValue(descriptor, DFTI_BACKWARD_SCALE, 1.0 / sqrt((double)x.size()));
  status = DftiCommitDescriptor(descriptor);           // Finalize the descriptor
  status = DftiComputeBackward(descriptor, &(x[0]), NULL);  // Compute the Backward FFT
  status = DftiFreeDescriptor(&descriptor);            // Free the descriptor
#endif
#else
  assert(nprocs == 1);
  std::vector<Type, Alloc> y = x;
  TODO(Replace with distributed FFTW)
  int N = y.size();
  for (int k = 0; k < N; k++) {
    y[k] = {0, 0};
    for (int j = 0; j < N; j++) {
      double arg = 2.0 * M_PI * D(j) * D(k) / D(N);
      Type e = Type(cos(arg), sin(arg));
      y[k] += x[j] * e;
    }
    y[k] /= sqrt(D(N));
  }
  x = y;
#endif
}

int main(int argc, char **argv)
{
  openqu::mpi::Environment env(argc, argv);
  if (env.is_usefull_rank() == false) return 0;
  int myid = env.rank();


  int nqbits = 3;
  if (argc != 2) {
    fprintf(stderr, "usage: %s <nqbits>\n", argv[0]);
    exit(1);
  } else {
    nqbits = atoi(argv[1]);
  }

  if (myid == 0) std::cout << "QFFT\n";

  {
  using Type = ComplexSP;
  QbitRegister<Type> psi1(nqbits, "rand", 0), psi2(psi1);
  cfft<Type>(psi1);
  psi2.EnbStat();
  psi2.specializeon();
  qft<Type>(psi2);
  psi2.GetStat();
  double e1 = psi2.maxabsdiff(psi1);
  double e2 = psi2.maxl2normdiff(psi1);
  if (myid == 0)
    printf("SP::qufft error vs classical max(absdiff: %le l2normdiff: %le)\n", e1, e2);
  }
  {
  using Type = ComplexDP;
  QbitRegister<Type> psi1(nqbits, "rand", 0), psi2(psi1);
  cfft<Type>(psi1);
  psi2.EnbStat();
  psi2.specializeoff();
  qft<Type>(psi2);
  psi2.GetStat();
  double e1 = psi2.maxabsdiff(psi1);
  double e2 = psi2.maxl2normdiff(psi1);
  if (myid == 0)
    printf("DP::qufft error vs classical max(absdiff: %le l2normdiff: %le)\n", e1, e2);
  }
             
  return 0;


}
