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

all:
	cd util; make
	cd util/tests; make
	cd qureg; make
	cd tests; make
	cd interface; make

clean:
	cd util; make clean
	cd util/tests; make clean
	cd qureg; make clean
	cd tests; make clean
	cd interface; make clean
	rm -fr ./build/

depend:
	cd util; make depend
	cd util/tests; make depend
	cd qureg; make depend
	cd tests; make depend
	cd interface; make depend

sdk-release: all sdk-copy-sources sdk-copy-libs sdk-copy-samples sdk-gen-docs 
	@echo Done.

sdk-copy-sources:
	@if [ -d "./build" ]; then \
	    echo Removing pre-existing build directory...; \
	    rm -fr ./build/* ;\
	fi
	@echo Copying SDK source header files...
	@mkdir -p ./build/include/qureg
	@mkdir -p ./build/include/util
	@mkdir -p ./build/lib/ia32
	@mkdir -p ./build/lib/ia32_lin
	@mkdir -p ./build/lib/intel64
	@mkdir -p ./build/lib/intel64_lin
	@mkdir -p ./build/lib/intel64_lin_mic
	@mkdir -p ./build/docs
	@cp ./LICENSE.txt ./build/LICENSE.txt
	@cp ./make.inc ./build/
	@cp ./qureg/highperfkernels.hpp ./build/include/qureg/
	@cp ./qureg/permute.hpp ./build/include/qureg/
	@cp ./qureg/QbitRegisterMetric.hpp ./build/include/qureg/
	@cp ./qureg/qureg.hpp ./build/include/qureg
	@cp ./util/alignedallocator.hpp ./build/include/util/
	@cp ./util/bitops.hpp ./build/include/util/
	@cp ./util/conversion.hpp ./build/include/util/
	@cp ./util/mpi.hpp ./build/include/util/
	@cp ./util/timer.hpp ./build/include/util/
	@cp ./util/tinymatrix.hpp ./build/include/util/
	@cp ./util/utils.hpp ./build/include/util/
	@cp ./util/openmp_affinity_v1.hpp ./build/include/util/
	@cp ./util/openmp_affinity_corei7.hpp ./build/include/util/
	@cp ./util/openmp_affinity_noomp.hpp ./build/include/util/
	@cp ./makefile.sdk ./build/makefile

sdk-copy-libs:
	@cp ./qureg/qHiPSTER.a ./build/lib/intel64/

sdk-copy-samples:
	@echo Copying sample files...
	@mkdir -p ./build/samples/
	@cp tests/qft_test.cpp ./build/samples/qft_test.cpp 
	@cp tests/testgates.cpp ./build/samples/testgates.cpp
	@cp tests/benchgates.cpp ./build/samples/benchgates.cpp

docs-clean:
	rm -fr docs/html/

docs-doxy:
	doxygen -s docs/doxy-html.config

sdk-gen-docs:
	cp docs/doxy-html.config ./build/
	cd build; doxygen -s ./doxy-html.config; rm -f ./doxy-html.config
