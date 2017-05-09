// AUTHOR: Gian Giacomo Guerreschi

/* Test for qHiPSTER:
 * proper implementaiton of the methods to compute the expectation value of Pauli strings
 * on single, two or multiple qubitsi.
 */

#if !defined(STANDALONE)
#include "openqu/engines/distrwavefunctionsimulator/qHiPSTER_backend/src/qureg.hpp"
#else
#include "/home/gian/matsuura_bay-qhipster/qureg/qureg.hpp"
#endif

// #include "/home/gian/matsuura_bay-qhipster/qureg/qureg.hpp"

using namespace std;

#if (defined(__ICC) || defined(__INTEL_COMPILER))
#include <mkl.h>
#if defined(OPENQU_HAVE_MPI)
#include <mkl_cdft.h>
#endif
#endif

#include <iostream>	// to use: std::cout, std::cin and std::endl
#include <iomanip>	// to use: setw() in making tables
#include <complex>
//#include <cmath>	// to use: sin(),floor()..
//#include <cstdlib>	// to use: "system()", but it is better to AVOID such command
//#include <fstream>	// to write on a file
//#include <ctime>	// to correctly initialize the seed of the random generator
//#include <cstdlib>	// for the random generator
//#include <vector>
//#include <algorithm>
//#include <numeric>	// std::inner_prod
//#include <stdexcept>
//#include <random>


// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------

int main(int argc, char **argv)
{

  openqu::mpi::Environment env(argc, argv);
  unsigned myrank = openqu::mpi::Environment::rank();
  unsigned nprocs = openqu::mpi::Environment::size();
//  MPI_rank(MPI_COMM_WORLD, &myrank);

  double sum = 0.;

  std::cout << "------------------\n"
            << "   Single qubit   \n"
            << "------------------\n";

  QbitRegister<ComplexDP> psi(1,"base",1);
  psi.EnbStat();  
  psi.applyHadamard(0);

  psi.Print(" initial state |psi>=|-> : ");

  psi.expectationValueX(0,sum);
  std::cout << "<psi|X|psi> = " << sum << "\n";

  psi.Print(" current state should still be |psi>=|-> : ");

// using the general method
  std::vector<unsigned> qubits(1,0);
  std::vector<unsigned> observs(1,1);
  sum=0;
  psi.expectationValue(qubits,observs,sum);
  std::cout << " general method  __  <psi|X|psi> = " << sum << "\n";

  psi.Print(" current state should still be |psi>=|-> : ");

  psi.applyPauliZ(0);
  psi.Print(" current state should be Z|psi>=|+> : ");

  sum=0;
  psi.expectationValueX(0,sum);
  std::cout << " <psi|X|psi> = " << sum << "\n";
  sum=0;
  psi.expectationValue(qubits,observs,sum);
  std::cout << " general method  __  <psi|X|psi> = " << sum << "\n";

  std::cout << "\n ------ repeat the experiment 100 times ---- \n";

  for (int i=0; i<100; i++)
      psi.expectationValueX(0,sum);
  sum=0;
  psi.expectationValueX(0,sum);
  std::cout << "after 100 expectation evaluations <psi|X|psi> = " << sum << "\n";

  std::cout << std::endl;
  psi.GetStat(); 

  if (myrank==0) std::cout << " goodbye \n" << std::endl;

  std::cout << "------------------\n"
            << "     4 qubits     \n"
            << "------------------\n";

  QbitRegister<ComplexDP> phi(4,"base",0);
  phi.applyPauliX(1);
  phi.applyHadamard(2);
  phi.applyPauliX(3);
  phi.applyHadamard(3);

  phi.Print(" initial state |phi> = |0> |1> |+> |-> = |01+-> :\n");

  qubits.assign({0,2});
  observs.assign({3,1});
  sum=0;
  phi.expectationValue(qubits,observs,sum);
  std::cout << " <phi|Z_0 X_2|phi> = " << sum << "\n";

  qubits.assign({0,2});
  observs.assign({3,2});
  sum=0;
  phi.expectationValue(qubits,observs,sum);
  std::cout << " <phi|Z_0 Y_2|phi> = " << sum << "\n";

  qubits.assign({1,2});
  observs.assign({3,1});
  sum=0;
  phi.expectationValue(qubits,observs,sum);
  std::cout << " <phi|Z_1 X_2|phi> = " << sum << "\n";

  qubits.assign({0,3});
  observs.assign({3,1});
  sum=0;
  phi.expectationValue(qubits,observs,sum);
  std::cout << " <phi|Z_0 X_3|phi> = " << sum << "\n";

  return 0;
}

