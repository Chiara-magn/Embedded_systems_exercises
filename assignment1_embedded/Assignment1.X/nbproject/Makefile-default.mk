#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Assignment1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Assignment1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Assignment1/IMU_handler.c ../Assignment1/SPI_handler.c ../Assignment1/UART_handler.c ../Assignment1/led_handler.c ../Assignment1/main.c ../Assignment1/timer.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1498301163/IMU_handler.o ${OBJECTDIR}/_ext/1498301163/SPI_handler.o ${OBJECTDIR}/_ext/1498301163/UART_handler.o ${OBJECTDIR}/_ext/1498301163/led_handler.o ${OBJECTDIR}/_ext/1498301163/main.o ${OBJECTDIR}/_ext/1498301163/timer.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1498301163/IMU_handler.o.d ${OBJECTDIR}/_ext/1498301163/SPI_handler.o.d ${OBJECTDIR}/_ext/1498301163/UART_handler.o.d ${OBJECTDIR}/_ext/1498301163/led_handler.o.d ${OBJECTDIR}/_ext/1498301163/main.o.d ${OBJECTDIR}/_ext/1498301163/timer.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1498301163/IMU_handler.o ${OBJECTDIR}/_ext/1498301163/SPI_handler.o ${OBJECTDIR}/_ext/1498301163/UART_handler.o ${OBJECTDIR}/_ext/1498301163/led_handler.o ${OBJECTDIR}/_ext/1498301163/main.o ${OBJECTDIR}/_ext/1498301163/timer.o

# Source Files
SOURCEFILES=../Assignment1/IMU_handler.c ../Assignment1/SPI_handler.c ../Assignment1/UART_handler.c ../Assignment1/led_handler.c ../Assignment1/main.c ../Assignment1/timer.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Assignment1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512MU810
MP_LINKER_FILE_OPTION=,--script=p33EP512MU810.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1498301163/IMU_handler.o: ../Assignment1/IMU_handler.c  .generated_files/flags/default/f60606883bedd7e74db3b0511ef216d3701cba28 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/IMU_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/IMU_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/IMU_handler.c  -o ${OBJECTDIR}/_ext/1498301163/IMU_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/IMU_handler.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1498301163/SPI_handler.o: ../Assignment1/SPI_handler.c  .generated_files/flags/default/8be5dd265e04f0be57f448137cd327f69468c8ec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/SPI_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/SPI_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/SPI_handler.c  -o ${OBJECTDIR}/_ext/1498301163/SPI_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/SPI_handler.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1498301163/UART_handler.o: ../Assignment1/UART_handler.c  .generated_files/flags/default/5d9b62c23211b5392ae61d5585749351e6328cb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/UART_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/UART_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/UART_handler.c  -o ${OBJECTDIR}/_ext/1498301163/UART_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/UART_handler.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1498301163/led_handler.o: ../Assignment1/led_handler.c  .generated_files/flags/default/860d19967f5015683c6a5409e41e3568800538b3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/led_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/led_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/led_handler.c  -o ${OBJECTDIR}/_ext/1498301163/led_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/led_handler.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1498301163/main.o: ../Assignment1/main.c  .generated_files/flags/default/1c6e91795f836092d1c7bcae14e92c3165665719 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/main.c  -o ${OBJECTDIR}/_ext/1498301163/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1498301163/timer.o: ../Assignment1/timer.c  .generated_files/flags/default/b261a7e91d4df5d6c94ca80d49b0eb33bc1aac34 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/timer.c  -o ${OBJECTDIR}/_ext/1498301163/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/timer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1498301163/IMU_handler.o: ../Assignment1/IMU_handler.c  .generated_files/flags/default/713dfc62e596dbee3eb33db50df431e9f2e3f710 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/IMU_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/IMU_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/IMU_handler.c  -o ${OBJECTDIR}/_ext/1498301163/IMU_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/IMU_handler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1498301163/SPI_handler.o: ../Assignment1/SPI_handler.c  .generated_files/flags/default/285bb47cd3722a4d6146df062df88fd6e3b65159 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/SPI_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/SPI_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/SPI_handler.c  -o ${OBJECTDIR}/_ext/1498301163/SPI_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/SPI_handler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1498301163/UART_handler.o: ../Assignment1/UART_handler.c  .generated_files/flags/default/8a5683e2ac4d55066c76abfe709aa1f89bb6f04f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/UART_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/UART_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/UART_handler.c  -o ${OBJECTDIR}/_ext/1498301163/UART_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/UART_handler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1498301163/led_handler.o: ../Assignment1/led_handler.c  .generated_files/flags/default/91995023712c44f3f0dc000f693923f0b2affe8d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/led_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/led_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/led_handler.c  -o ${OBJECTDIR}/_ext/1498301163/led_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/led_handler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1498301163/main.o: ../Assignment1/main.c  .generated_files/flags/default/e411279463366f4db3b563edfc9f21056568d381 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/main.c  -o ${OBJECTDIR}/_ext/1498301163/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1498301163/timer.o: ../Assignment1/timer.c  .generated_files/flags/default/46169789479246d0b7228dabe124279958f621f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1498301163" 
	@${RM} ${OBJECTDIR}/_ext/1498301163/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498301163/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Assignment1/timer.c  -o ${OBJECTDIR}/_ext/1498301163/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1498301163/timer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Assignment1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Assignment1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/Assignment1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Assignment1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/Assignment1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
