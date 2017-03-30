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

SRC := openmp.cpp mpi.cpp utils.cpp openmp_affinity_noomp.cpp openmp_affinity_corei7.cpp
OBJ := $(addsuffix .o, $(basename $(SRC)))

%.o : %.cpp makefile
	$(CC) ${CFLAGS} ${INC} -c $< -o $@


all: $(OBJ) makefile

depend:
	makedepend -Y ${DEFS} ${SRC} ${INC}

clean:
	rm -f *.o *.s *.d *~

# DO NOT DELETE

openmp.o: ../util/openmp.hpp ../util/mpi.hpp ../util/conversion.hpp
mpi.o: mpi.hpp openmp.hpp ../util/bitops.hpp ../util/conversion.hpp
utils.o: timer.hpp ../util/utils.hpp ../util/mpi.hpp ../util/conversion.hpp
openmp_affinity_noomp.o: openmp_affinity_noomp.hpp openmp_affinity_v1.hpp
openmp_affinity_corei7.o: openmp_affinity_corei7.hpp openmp_affinity_v1.hpp
