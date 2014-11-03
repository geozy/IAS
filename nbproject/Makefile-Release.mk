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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2137252208/endPoint.o \
	${OBJECTDIR}/_ext/2137252208/iaServiceDistributor.o \
	${OBJECTDIR}/_ext/2137252208/iasErrors.o \
	${OBJECTDIR}/_ext/2137252208/iasResponse.o \
	${OBJECTDIR}/_ext/2137252208/iasServer.o \
	${OBJECTDIR}/_ext/2137252208/iasServiceManager.o \
	${OBJECTDIR}/_ext/2137252208/session.o \
	${OBJECTDIR}/_ext/2137252208/syncController.o \
	${OBJECTDIR}/_ext/2137252208/task.o \
	${OBJECTDIR}/_ext/2137252208/taskFactory.o \
	${OBJECTDIR}/_ext/2137252208/task_impl.o \
	${OBJECTDIR}/_ext/2137252208/threadpool.o \
	${OBJECTDIR}/_ext/2137252208/transAct.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libiaservices.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libiaservices.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libiaservices.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libiaservices.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libiaservices.a

${OBJECTDIR}/_ext/2137252208/endPoint.o: /home/georgez/NetBeansProjects/iaservices/endPoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/endPoint.o /home/georgez/NetBeansProjects/iaservices/endPoint.cpp

${OBJECTDIR}/_ext/2137252208/iaServiceDistributor.o: /home/georgez/NetBeansProjects/iaservices/iaServiceDistributor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/iaServiceDistributor.o /home/georgez/NetBeansProjects/iaservices/iaServiceDistributor.cpp

${OBJECTDIR}/_ext/2137252208/iasErrors.o: /home/georgez/NetBeansProjects/iaservices/iasErrors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/iasErrors.o /home/georgez/NetBeansProjects/iaservices/iasErrors.cpp

${OBJECTDIR}/_ext/2137252208/iasResponse.o: /home/georgez/NetBeansProjects/iaservices/iasResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/iasResponse.o /home/georgez/NetBeansProjects/iaservices/iasResponse.cpp

${OBJECTDIR}/_ext/2137252208/iasServer.o: /home/georgez/NetBeansProjects/iaservices/iasServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/iasServer.o /home/georgez/NetBeansProjects/iaservices/iasServer.cpp

${OBJECTDIR}/_ext/2137252208/iasServiceManager.o: /home/georgez/NetBeansProjects/iaservices/iasServiceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/iasServiceManager.o /home/georgez/NetBeansProjects/iaservices/iasServiceManager.cpp

${OBJECTDIR}/_ext/2137252208/session.o: /home/georgez/NetBeansProjects/iaservices/session.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/session.o /home/georgez/NetBeansProjects/iaservices/session.cpp

${OBJECTDIR}/_ext/2137252208/syncController.o: /home/georgez/NetBeansProjects/iaservices/syncController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/syncController.o /home/georgez/NetBeansProjects/iaservices/syncController.cpp

${OBJECTDIR}/_ext/2137252208/task.o: /home/georgez/NetBeansProjects/iaservices/task.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/task.o /home/georgez/NetBeansProjects/iaservices/task.cpp

${OBJECTDIR}/_ext/2137252208/taskFactory.o: /home/georgez/NetBeansProjects/iaservices/taskFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/taskFactory.o /home/georgez/NetBeansProjects/iaservices/taskFactory.cpp

${OBJECTDIR}/_ext/2137252208/task_impl.o: /home/georgez/NetBeansProjects/iaservices/task_impl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/task_impl.o /home/georgez/NetBeansProjects/iaservices/task_impl.cpp

${OBJECTDIR}/_ext/2137252208/threadpool.o: /home/georgez/NetBeansProjects/iaservices/threadpool.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/threadpool.o /home/georgez/NetBeansProjects/iaservices/threadpool.cpp

${OBJECTDIR}/_ext/2137252208/transAct.o: /home/georgez/NetBeansProjects/iaservices/transAct.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2137252208
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2137252208/transAct.o /home/georgez/NetBeansProjects/iaservices/transAct.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libiaservices.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
