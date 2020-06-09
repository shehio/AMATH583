#
# This file is part of the course materials for AMATH 483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
# 

TARGETS := mpi_norm.exe omp_norm.exe sequential_norm.exe


include ../include/Make_mpi.inc


# The following 4 (yes 4) lines must be in all the subdirectory makefiles
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
mpi_norm.o: mpi_norm.cpp /usr/lib/x86_64-linux-gnu/openmpi/include/mpi.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/mpi_portable_platform.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/mpicxx.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/constants.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/functions.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/datatype.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/exception.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/op.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/status.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/request.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/group.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/comm.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/win.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/file.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/errhandler.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/intracomm.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/topology.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/intercomm.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/info.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/datatype_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/functions_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/request_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/comm_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/intracomm_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/topology_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/intercomm_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/group_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/op_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/errhandler_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/status_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/info_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/win_inln.h \
 /usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/ompi/mpi/cxx/file_inln.h \
 /efs/home/public/ps7/include/Timer.hpp \
 /efs/home/public/ps7/include/amath583.hpp \
 /efs/home/public/ps7/include/util.hpp \
 /efs/home/public/ps7/include/Matrix.hpp \
 /efs/home/public/ps7/include/Vector.hpp
omp_norm.o: omp_norm.cpp /efs/home/public/ps7/include/norm_utils.hpp \
 /efs/home/public/ps7/include/Timer.hpp \
 /efs/home/public/ps7/include/Vector.hpp \
 /efs/home/public/ps7/include/amath583.hpp \
 /efs/home/public/ps7/include/util.hpp \
 /efs/home/public/ps7/include/Matrix.hpp \
 /efs/home/public/ps7/include/norms.hpp
sequential_norm.o: sequential_norm.cpp \
 /efs/home/public/ps7/include/norms.hpp \
 /efs/home/public/ps7/include/Timer.hpp \
 /efs/home/public/ps7/include/Vector.hpp \
 /efs/home/public/ps7/include/amath583.hpp \
 /efs/home/public/ps7/include/util.hpp \
 /efs/home/public/ps7/include/Matrix.hpp \
 /efs/home/public/ps7/include/norm_utils.hpp
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
