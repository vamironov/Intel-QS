HOST = $(shell hostname)

ifneq ($(HOST),ccefw-desktop)
CC = g++
CC = mpicxx 
CC = CC -mkl -no-ipo
CC = mpiicpc 
else
########### Modified for the ccefw-desktop.jf.intel.com environment ############
CC = /etc/local/g++-6.2
CC = /opt/intel/impi_latest/bin64/mpicxx
CC = CC -mkl -no-ipo
CC = /opt/intel/impi_latest/bin64/mpiicpc
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
