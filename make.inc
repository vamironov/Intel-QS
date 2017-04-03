##------------------------------------------------------------------------------
## Copyright (C) 2017 Intel Corporation 
##
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
## http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
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



