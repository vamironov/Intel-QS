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

OBJS = qasm_interface.o interface_api_qubitid.o interface_api_version.o interface_api_memory.o

#LDFLAGS = -L${MKLROOT}/lib/intel64 -lmkl_cdft_core -lmkl_intel_lp64 -lmkl_core -lmkl_intel_thread -lmkl_blacs_intelmpi_lp64 -lpthread \

EXEC = qasm_interface.exe

$(EXEC): makefile ${OBJS}
	$(CC) -o $(EXEC) ${CFLAGS} ${LDFLAGS} ${OBJS} ../qureg/qHiPSTER.a

interface_api_qubitid.o: interface_api_qubitid.h interface_api_qubitid.cpp makefile
	$(CC) ${CFLAGS} ${INC} -c interface_api_qubitid.cpp


interface_api_version.o: interface_api_version.h interface_api_version.cpp makefile
	$(CC) ${CFLAGS} ${INC} -c interface_api_version.cpp


interface_api_memory.o: interface_api_memory.h interface_api_memory.cpp makefile
	$(CC) ${CFLAGS} ${INC} -c interface_api_memory.cpp

qasm_interface.o: qasm_interface.cpp makefile
	$(CC) ${CFLAGS} ${INC} -c qasm_interface.cpp

clean:
	rm -f *.o *.s *.d *~
	rm -f $(EXEC)

depend:
	makedepend -Y ${SRC} ${INC}
# DO NOT DELETE
