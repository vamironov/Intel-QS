##------------------------------------------------------------------------------
## INTEL CONFIDENTIAL
## Copyright 2017 Intel Corporation                                          
##
## The source code contained or described herein and all documents related to 
## the source code ("Material") are owned by Intel Corporation or its suppliers 
## or licensors. Title to the Material remains with Intel Corporation or its 
## suppliers and licensors. The Material contains trade secrets and proprietary 
## and confidential information of Intel or its suppliers and licensors.
## The Material is protected by worldwide copyright and trade secret laws and 
## treaty provisions. No part of the Material may be used, copied, reproduced,
## modified, published, uploaded, posted, transmitted, distributed, or disclosed 
## in any way without Intel's prior express written permission.
##
## No license under any patent, copyright, trade secret or other intellectual 
## property right is granted to or conferred upon you by disclosure or delivery 
## of the Materials, either expressly, by implication, inducement, estoppel or 
## otherwise. Any license under such intellectual property rights must be 
## express and approved by Intel in writing.
##------------------------------------------------------------------------------

include ../../make.inc

LDFLAGS =   -L${MKLROOT}/lib/intel64 -lmkl_cdft_core -lmkl_intel_ilp64 -lmkl_core -lmkl_intel_thread -lmkl_blacs_intelmpi_ilp64 -lpthread -lirc

ifdef VECTORIZATION_REPORT
OPTS:=-qopt-report3 -qopt-report-phase=loop,vec
endif

SRC  = $(wildcard *.cpp)
OBJS = $(addsuffix .o, $(basename $(SRC)))

%.o : %.cpp makefile
	        $(CC) ${CFLAGS} ${INC} -c $< -o $@

all: mpi_test1.exe omp_test1.exe naive_integral_base.exe omp_integral_base.exe

mpi_test1.exe: mpi_test1.o ../openmp_affinity_corei7.o ../openmp_affinity_noomp.o makefile
	$(CC) ${CFLAGS} ${LDFLAGS} mpi_test1.o ../openmp_affinity_corei7.o ../openmp_affinity_noomp.o -o mpi_test1.exe

omp_test1.exe: omp_test1.o ../openmp_affinity_corei7.o ../openmp_affinity_noomp.o makefile
	$(CC) ${CFLAGS} ${LDFLAGS} omp_test1.o ../openmp_affinity_corei7.o ../openmp_affinity_noomp.o -o omp_test1.exe

naive_integral_base.exe: naive_integral_base.o makefile
	$(CC) ${CFLAGS} ${LDFLAGS} naive_integral_base.o -o naive_integral_base.exe

omp_integral_base.exe: omp_integral_base.o ../openmp_affinity_corei7.o ../openmp_affinity_noomp.o makefile
	$(CC) ${CFLAGS} ${LDFLAGS} omp_integral_base.o ../openmp_affinity_corei7.o ../openmp_affinity_noomp.o -o omp_integral_base.exe

clean:
	        rm -f *.o *.s *.d *~ *.exe

depend:
	        makedepend -Y ${DEFS} ${SRC} ${INC}

# DO NOT DELETE

mpi_test1.o: ../mpi_wrapper.hpp ../openmp_affinity_corei7.hpp
mpi_test1.o: ../openmp_affinity_v1.hpp
omp_test1.o: ../openmp_affinity_corei7.hpp ../openmp_affinity_v1.hpp
omp_test1.o: ../openmp_affinity_noomp.hpp
omp_integral_base.o: ../openmp_affinity_noomp.hpp ../openmp_affinity_v1.hpp
omp_integral_base.o: ../openmp_affinity_corei7.hpp
naive_integral_base.o: ../openmp_affinity_corei7.hpp
naive_integral_base.o: ../openmp_affinity_v1.hpp
