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
qHiPSTER.a: $(OBJ) ../util/utils.o ../util/mpi.o ../util/openmp_affinity_corei7.o ../util/openmp_affinity_noomp.o ../makefile
	ar rcs $@ $^

depend:
	makedepend -Y ${DEFS} ${SRC} ${INC}

clean:
	rm -f *.o *.s *.d *~ ./qHiPSTER.a

# DO NOT DELETE

qureg_utils.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_utils.o: ../util/openmp_affinity_noomp.hpp
qureg_utils.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
qureg_utils.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_utils.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_utils.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_applyctrl1qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_applyctrl1qubitgate.o: ../util/mpi.hpp
qureg_applyctrl1qubitgate.o: ../util/openmp_affinity_noomp.hpp
qureg_applyctrl1qubitgate.o: ../util/openmp_affinity_v1.hpp
qureg_applyctrl1qubitgate.o: ../util/conversion.hpp ../util/timer.hpp
qureg_applyctrl1qubitgate.o: ../util/prng_engine.hpp
qureg_applyctrl1qubitgate.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_applyctrl1qubitgate.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_applyctrl1qubitgate.o: highperfkernels.hpp
qureg_measure.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_measure.o: ../util/openmp_affinity_noomp.hpp
qureg_measure.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
qureg_measure.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_measure.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_measure.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_permute.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_permute.o: ../util/openmp_affinity_noomp.hpp
qureg_permute.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
qureg_permute.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_permute.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_permute.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_init.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_init.o: ../util/openmp_affinity_noomp.hpp
qureg_init.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
qureg_init.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_init.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_init.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_applytoffoli.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_applytoffoli.o: ../util/openmp_affinity_noomp.hpp
qureg_applytoffoli.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
qureg_applytoffoli.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_applytoffoli.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_applytoffoli.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_applytoffoli.o: highperfkernels.hpp
highperfkernels.o: highperfkernels.hpp qureg.hpp permute.hpp
highperfkernels.o: ../util/utils.hpp ../util/mpi.hpp
highperfkernels.o: ../util/openmp_affinity_noomp.hpp
highperfkernels.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
highperfkernels.o: ../util/timer.hpp ../util/prng_engine.hpp
highperfkernels.o: ../util/alignedallocator.hpp ../util/bitops.hpp
highperfkernels.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_apply1qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_apply1qubitgate.o: ../util/mpi.hpp ../util/openmp_affinity_noomp.hpp
qureg_apply1qubitgate.o: ../util/openmp_affinity_v1.hpp
qureg_apply1qubitgate.o: ../util/conversion.hpp ../util/timer.hpp
qureg_apply1qubitgate.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_apply1qubitgate.o: ../util/bitops.hpp ../util/tinymatrix.hpp
qureg_apply1qubitgate.o: QbitRegisterMetric.hpp highperfkernels.hpp
qureg_apply2qubitgate.o: qureg.hpp permute.hpp ../util/utils.hpp
qureg_apply2qubitgate.o: ../util/mpi.hpp ../util/openmp_affinity_noomp.hpp
qureg_apply2qubitgate.o: ../util/openmp_affinity_v1.hpp
qureg_apply2qubitgate.o: ../util/conversion.hpp ../util/timer.hpp
qureg_apply2qubitgate.o: ../util/prng_engine.hpp ../util/alignedallocator.hpp
qureg_apply2qubitgate.o: ../util/bitops.hpp ../util/tinymatrix.hpp
qureg_apply2qubitgate.o: QbitRegisterMetric.hpp highperfkernels.hpp
qureg_applydiag.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_applydiag.o: ../util/openmp_affinity_noomp.hpp
qureg_applydiag.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
qureg_applydiag.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_applydiag.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_applydiag.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_applydiag.o: highperfkernels.hpp
qureg_fusion.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_fusion.o: ../util/openmp_affinity_noomp.hpp
qureg_fusion.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
qureg_fusion.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_fusion.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_fusion.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_applyswap.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_applyswap.o: ../util/openmp_affinity_noomp.hpp
qureg_applyswap.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
qureg_applyswap.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_applyswap.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_applyswap.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
qureg_applyswap.o: highperfkernels.hpp
qureg_version.o: qureg_version.hpp
qureg_expectval.o: qureg.hpp permute.hpp ../util/utils.hpp ../util/mpi.hpp
qureg_expectval.o: ../util/openmp_affinity_noomp.hpp
qureg_expectval.o: ../util/openmp_affinity_v1.hpp ../util/conversion.hpp
qureg_expectval.o: ../util/timer.hpp ../util/prng_engine.hpp
qureg_expectval.o: ../util/alignedallocator.hpp ../util/bitops.hpp
qureg_expectval.o: ../util/tinymatrix.hpp QbitRegisterMetric.hpp
