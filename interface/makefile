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

include ../make.inc

LDFLAGS =   -L${MKLROOT}/lib/intel64 -lmkl_cdft_core -lmkl_intel_ilp64 -lmkl_core -lmkl_intel_thread -lmkl_blacs_intelmpi_ilp64 -lpthread

SRC  = $(wildcard *.cpp)
OBJS = $(addsuffix .o, $(basename $(SRC)))
EXEC = qasm_interface.exe

%.o : %.cpp makefile
	$(CC) ${CFLAGS} ${INC} -c $< -o $@

all: $(EXEC)
$(EXEC): ${OBJS} makefile ../qureg/qHiPSTER.a
	$(CC) ${CFLAGS} ${LDFLAGS} ${OBJS} ../qureg/qHiPSTER.a -o $(EXEC) 

clean:
	rm -f *.o *.s *.d *~ $(EXEC)

depend:
	makedepend -Y ${DEFS} ${SRC} ${INC}

# DO NOT DELETE

qhipster_interface_main.o: ../qureg/qureg.hpp ../qureg/permute.hpp
qhipster_interface_main.o: ../util/utils.hpp ../util/mpi.hpp
qhipster_interface_main.o: ../util/openmp_affinity_noomp.hpp
qhipster_interface_main.o: ../util/openmp_affinity_v1.hpp
qhipster_interface_main.o: ../util/conversion.hpp ../util/timer.hpp
qhipster_interface_main.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qhipster_interface_main.o: ../util/tinymatrix.hpp
qhipster_interface_main.o: ../qureg/QbitRegisterMetric.hpp
qhipster_interface_main.o: interface_api_qasm.h
interface_api_memory.o: ../qureg/qureg.hpp ../qureg/permute.hpp
interface_api_memory.o: ../util/utils.hpp ../util/mpi.hpp
interface_api_memory.o: ../util/openmp_affinity_noomp.hpp
interface_api_memory.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
interface_api_memory.o: ../util/timer.hpp ../util/alignedallocator.hpp
interface_api_memory.o: ../util/bitops.hpp ../util/tinymatrix.hpp
interface_api_memory.o: ../qureg/QbitRegisterMetric.hpp
interface_api_qasm.o: ../qureg/qureg.hpp ../qureg/permute.hpp
interface_api_qasm.o: ../util/utils.hpp ../util/mpi.hpp
interface_api_qasm.o: ../util/openmp_affinity_noomp.hpp
interface_api_qasm.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
interface_api_qasm.o: ../util/timer.hpp ../util/alignedallocator.hpp
interface_api_qasm.o: ../util/bitops.hpp ../util/tinymatrix.hpp
interface_api_qasm.o: ../qureg/QbitRegisterMetric.hpp interface_api_qubitid.h
interface_api_qasm.o: interface_api_version.h interface_api_memory.h
interface_api_version.o: ../qureg/qureg_version.hpp interface_api_version.h
