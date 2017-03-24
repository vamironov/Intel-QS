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

SRC := $(wildcard *.cpp ../util/openmp.cpp ../util/mpi.cpp ../util/utils.cpp)
OBJ := $(addsuffix .o, $(basename $(SRC)))

%.o : %.cpp makefile
	$(CC) ${CFLAGS} ${INC} -c $< -o $@


all: qHiPSTER.a
qHiPSTER.a: $(OBJ) makefile
	ar rcs $@ $^

depend:
	makedepend -Y ${SRC} ${INC}

clean:
	rm -f *.o *.s *.d *~ 
# DO NOT DELETE

qureg_utils.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_utils.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_version.o: qureg_version.hpp 
qureg_applyctrl1qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_applyctrl1qubitgate.o: ../util/timer.hpp ../util/mpi.hpp
qureg_applyctrl1qubitgate.o: ../util/prng_engine.hpp highperfkernels.hpp
qureg_measure.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_measure.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_permute.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_permute.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_init.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_init.o: ../util/mpi.hpp ../util/prng_engine.hpp
highperfkernels.o: highperfkernels.hpp qureg.hpp permute.hpp
highperfkernels.o: ../util/utils.hpp ../util/timer.hpp ../util/mpi.hpp
highperfkernels.o: ../util/prng_engine.hpp
qureg_apply1qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_apply1qubitgate.o: ../util/timer.hpp ../util/mpi.hpp
qureg_apply1qubitgate.o: ../util/prng_engine.hpp highperfkernels.hpp
qureg_apply2qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_apply2qubitgate.o: ../util/timer.hpp ../util/mpi.hpp
qureg_apply2qubitgate.o: ../util/prng_engine.hpp highperfkernels.hpp
qureg_applydiag.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_applydiag.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_applydiag.o: highperfkernels.hpp
qureg_fusion.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_fusion.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_applyswap.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/timer.hpp
qureg_applyswap.o: ../util/mpi.hpp ../util/prng_engine.hpp
qureg_applyswap.o: highperfkernels.hpp
../util/utils.o: ../util/timer.hpp ../util/utils.hpp ../util/mpi.hpp

qureg_expectval.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_expectval.o: ../util/timer.hpp ../util/mpi.hpp
qureg_expectval.o: ../util/prng_engine.hpp highperfkernels.hpp
