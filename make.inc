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

HOST = $(shell hostname)

ifneq ($(HOST),ccefw-desktop)
CC = g++
CC = mpicxx 
CC = CC -mkl -no-ipo
CC = mpiicpc 
else
########### Modified for the ccefw-desktop.jf.intel.com environment ############
CC = g++
CC = /opt/intel/impi/2017.2.174/bin64/mpicxx
CC = CC -mkl -no-ipo
CC = /opt/intel/impi/2017.2.174/bin64/mpiicpc
PATH := ${PATH}:/opt/intel/bin
################################################################################
endif


OPTS = -g
OPTS = -O3
VECS = -qopt-report-phase=vec -qopt-report=2
DEFS = -DUSE_MM_MALLOC -DSTANDALONE -DOPENQU_HAVE_MPI -DMKL_ILP64

CFLAGS = ${OPTS} ${DEFS} \
         -Wall -std=c++11 -fasm-blocks -qopenmp -restrict

CFLAGS += ${OPTFLAGS}  

ifneq ($(HOST),ccefw-desktop)
INC = -I./ -I../
else
########### Modifications to find performance libraries on ccefw-desktop. ######
INC = -I./ -I../ -I/opt/intel/mkl/include/
MKLROOT = /opt/intel/mkl/
################################################################################
endif


########### added by Gian for PCL mini-cluster #################################
ifeq ($(HOST),pcl-hsw1.sc.intel.com)
INC += -I/home/gian/matsuura_bay-qhipster
MKLROOT = /swtools/intel/mkl
CFLAGS += -mkl
endif
################################################################################



