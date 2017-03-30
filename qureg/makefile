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

SRC := $(wildcard *.cpp)
OBJ := $(addsuffix .o, $(basename $(SRC)))

%.o : %.cpp makefile
	$(CC) ${CFLAGS} ${INC} -c $< -o $@


all: qHiPSTER.a
qHiPSTER.a: $(OBJ) ../util/openmp.o ../util/utils.o ../util/mpi.o ../util/openmp_affinity_corei7.o ../makefile
	ar rcs $@ $^

depend:
	makedepend -Y ${DEFS} ${SRC} ${INC}

clean:
	rm -f *.o *.s *.d *~ ./qHiPSTER.a

# DO NOT DELETE

qureg_utils.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_utils.o: ../util/conversion.hpp ../util/timer.hpp
qureg_utils.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_utils.o: ../util/bitops.hpp ../util/openmp.hpp ../util/tinymatrix.hpp
qureg_utils.o: QbitRegisterMetric.hpp
qureg_applyctrl1qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_applyctrl1qubitgate.o: ../util/mpi.hpp ../util/conversion.hpp
qureg_applyctrl1qubitgate.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_applyctrl1qubitgate.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_applyctrl1qubitgate.o: ../util/openmp.hpp ../util/tinymatrix.hpp
qureg_applyctrl1qubitgate.o: QbitRegisterMetric.hpp highperfkernels.hpp
qureg_measure.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_measure.o: ../util/conversion.hpp ../util/timer.hpp
qureg_measure.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_measure.o: ../util/bitops.hpp ../util/openmp.hpp ../util/tinymatrix.hpp
qureg_measure.o: QbitRegisterMetric.hpp
qureg_permute.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_permute.o: ../util/conversion.hpp ../util/timer.hpp
qureg_permute.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_permute.o: ../util/bitops.hpp ../util/openmp.hpp ../util/tinymatrix.hpp
qureg_permute.o: QbitRegisterMetric.hpp
qureg_init.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_init.o: ../util/conversion.hpp ../util/timer.hpp
qureg_init.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_init.o: ../util/bitops.hpp ../util/openmp.hpp ../util/tinymatrix.hpp
qureg_init.o: QbitRegisterMetric.hpp
qureg_applytoffoli.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_applytoffoli.o: ../util/conversion.hpp ../util/timer.hpp
qureg_applytoffoli.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_applytoffoli.o: ../util/bitops.hpp ../util/openmp.hpp
qureg_applytoffoli.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_applytoffoli.o: highperfkernels.hpp
highperfkernels.o: highperfkernels.hpp qureg.hpp permute.hpp
highperfkernels.o: ../util/utils.hpp ../util/mpi.hpp ../util/conversion.hpp
highperfkernels.o: ../util/timer.hpp ../util/prng_engine.hpp
highperfkernels.o: ../util/alignedallocator.hpp ../util/bitops.hpp
highperfkernels.o: ../util/openmp.hpp ../util/tinymatrix.hpp
highperfkernels.o: QbitRegisterMetric.hpp
qureg_apply1qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_apply1qubitgate.o: ../util/mpi.hpp ../util/conversion.hpp
qureg_apply1qubitgate.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_apply1qubitgate.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_apply1qubitgate.o: ../util/openmp.hpp ../util/tinymatrix.hpp
qureg_apply1qubitgate.o: QbitRegisterMetric.hpp highperfkernels.hpp
qureg_apply2qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_apply2qubitgate.o: ../util/mpi.hpp ../util/conversion.hpp
qureg_apply2qubitgate.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_apply2qubitgate.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_apply2qubitgate.o: ../util/openmp.hpp ../util/tinymatrix.hpp
qureg_apply2qubitgate.o: QbitRegisterMetric.hpp highperfkernels.hpp
qureg_applydiag.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_applydiag.o: ../util/conversion.hpp ../util/timer.hpp
qureg_applydiag.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_applydiag.o: ../util/bitops.hpp ../util/openmp.hpp
qureg_applydiag.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_applydiag.o: highperfkernels.hpp
qureg_fusion.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_fusion.o: ../util/conversion.hpp ../util/timer.hpp
qureg_fusion.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_fusion.o: ../util/bitops.hpp ../util/openmp.hpp ../util/tinymatrix.hpp
qureg_fusion.o: QbitRegisterMetric.hpp
qureg_applyswap.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_applyswap.o: ../util/conversion.hpp ../util/timer.hpp
qureg_applyswap.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_applyswap.o: ../util/bitops.hpp ../util/openmp.hpp
qureg_applyswap.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_applyswap.o: highperfkernels.hpp
qureg_version.o: qureg_version.hpp
qureg_expectval.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_expectval.o: ../util/conversion.hpp ../util/timer.hpp
qureg_expectval.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_expectval.o: ../util/bitops.hpp ../util/openmp.hpp
qureg_expectval.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
