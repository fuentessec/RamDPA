#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/aes_sub_bytes_output.o \
	${OBJECTDIR}/binary_array.o \
	${OBJECTDIR}/binary_array_matrix.o \
	${OBJECTDIR}/binary_array_vector.o \
	${OBJECTDIR}/consuption_matrix.o \
	${OBJECTDIR}/correlation_coefficient.o \
	${OBJECTDIR}/crypto_computation.o \
	${OBJECTDIR}/hw_power_model.o \
	${OBJECTDIR}/input_data.o \
	${OBJECTDIR}/input_data_set.o \
	${OBJECTDIR}/intermediate.o \
	${OBJECTDIR}/intermediate_matrix.o \
	${OBJECTDIR}/keyhypothesis_16set.o \
	${OBJECTDIR}/keyhypothesis_8set.o \
	${OBJECTDIR}/keyhypothesis_allvalues_16set.o \
	${OBJECTDIR}/keyhypothesis_allvalues_8set.o \
	${OBJECTDIR}/keyhypothesis_set.o \
	${OBJECTDIR}/lbs_power_model.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/matrix_2d.o \
	${OBJECTDIR}/power_model.o \
	${OBJECTDIR}/result_matrix.o \
	${OBJECTDIR}/statistical_analysis.o \
	${OBJECTDIR}/time_slice.o \
	${OBJECTDIR}/trace.o \
	${OBJECTDIR}/trace_set.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/doctoradoaux

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/doctoradoaux: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/doctoradoaux ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/aes_sub_bytes_output.o: aes_sub_bytes_output.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/aes_sub_bytes_output.o aes_sub_bytes_output.cpp

${OBJECTDIR}/binary_array.o: binary_array.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/binary_array.o binary_array.cpp

${OBJECTDIR}/binary_array_matrix.o: binary_array_matrix.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/binary_array_matrix.o binary_array_matrix.cpp

${OBJECTDIR}/binary_array_vector.o: binary_array_vector.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/binary_array_vector.o binary_array_vector.cpp

${OBJECTDIR}/consuption_matrix.o: consuption_matrix.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/consuption_matrix.o consuption_matrix.cpp

${OBJECTDIR}/correlation_coefficient.o: correlation_coefficient.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/correlation_coefficient.o correlation_coefficient.cpp

${OBJECTDIR}/crypto_computation.o: crypto_computation.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/crypto_computation.o crypto_computation.cpp

${OBJECTDIR}/hw_power_model.o: hw_power_model.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hw_power_model.o hw_power_model.cpp

${OBJECTDIR}/input_data.o: input_data.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/input_data.o input_data.cpp

${OBJECTDIR}/input_data_set.o: input_data_set.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/input_data_set.o input_data_set.cpp

${OBJECTDIR}/intermediate.o: intermediate.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/intermediate.o intermediate.cpp

${OBJECTDIR}/intermediate_matrix.o: intermediate_matrix.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/intermediate_matrix.o intermediate_matrix.cpp

${OBJECTDIR}/keyhypothesis_16set.o: keyhypothesis_16set.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/keyhypothesis_16set.o keyhypothesis_16set.cpp

${OBJECTDIR}/keyhypothesis_8set.o: keyhypothesis_8set.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/keyhypothesis_8set.o keyhypothesis_8set.cpp

${OBJECTDIR}/keyhypothesis_allvalues_16set.o: keyhypothesis_allvalues_16set.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/keyhypothesis_allvalues_16set.o keyhypothesis_allvalues_16set.cpp

${OBJECTDIR}/keyhypothesis_allvalues_8set.o: keyhypothesis_allvalues_8set.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/keyhypothesis_allvalues_8set.o keyhypothesis_allvalues_8set.cpp

${OBJECTDIR}/keyhypothesis_set.o: keyhypothesis_set.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/keyhypothesis_set.o keyhypothesis_set.cpp

${OBJECTDIR}/lbs_power_model.o: lbs_power_model.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lbs_power_model.o lbs_power_model.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/matrix_2d.o: matrix_2d.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/matrix_2d.o matrix_2d.cpp

${OBJECTDIR}/power_model.o: power_model.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/power_model.o power_model.cpp

${OBJECTDIR}/result_matrix.o: result_matrix.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/result_matrix.o result_matrix.cpp

${OBJECTDIR}/statistical_analysis.o: statistical_analysis.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/statistical_analysis.o statistical_analysis.cpp

${OBJECTDIR}/time_slice.o: time_slice.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/time_slice.o time_slice.cpp

${OBJECTDIR}/trace.o: trace.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/trace.o trace.cpp

${OBJECTDIR}/trace_set.o: trace_set.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/trace_set.o trace_set.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
