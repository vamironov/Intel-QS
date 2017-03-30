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

depend:
	cd util; make depend
	cd util/tests; make depend
	cd qureg; make depend
	cd tests; make depend
	cd interface; make depend

docs-clean:
	rm -fr docs/html/

docs-doxy:
	doxygen -s docs/doxy-html.config
