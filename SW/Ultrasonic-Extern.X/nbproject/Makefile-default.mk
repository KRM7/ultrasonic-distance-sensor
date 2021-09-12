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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Ultrasonic-Extern.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Ultrasonic-Extern.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/adc1.c mcc_generated_files/system.c mcc_generated_files/mcc.c mcc_generated_files/spi1.c mcc_generated_files/tmr1.c mcc_generated_files/pin_manager.c mcc_generated_files/interrupt_manager.c mcc_generated_files/clock.c mcc_generated_files/traps.c main.c io_utils.c radio.c temperature.c 7segment.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/spi1.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/main.o ${OBJECTDIR}/io_utils.o ${OBJECTDIR}/radio.o ${OBJECTDIR}/temperature.o ${OBJECTDIR}/7segment.o
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/adc1.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/spi1.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/traps.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/io_utils.o.d ${OBJECTDIR}/radio.o.d ${OBJECTDIR}/temperature.o.d ${OBJECTDIR}/7segment.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/spi1.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/main.o ${OBJECTDIR}/io_utils.o ${OBJECTDIR}/radio.o ${OBJECTDIR}/temperature.o ${OBJECTDIR}/7segment.o

# Source Files
SOURCEFILES=mcc_generated_files/adc1.c mcc_generated_files/system.c mcc_generated_files/mcc.c mcc_generated_files/spi1.c mcc_generated_files/tmr1.c mcc_generated_files/pin_manager.c mcc_generated_files/interrupt_manager.c mcc_generated_files/clock.c mcc_generated_files/traps.c main.c io_utils.c radio.c temperature.c 7segment.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Ultrasonic-Extern.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/1618db501436f6afc09ec95a1285b8cbb779affe.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/3cf7cd964a68d8d3d0d9b6877712111eefce8686.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/6c339f00e33ba19ce6c8ffcb7672f6615c52b4d8.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/spi1.o: mcc_generated_files/spi1.c  .generated_files/960402a771f21c9956c41f78f0aa82c21cce9489.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/spi1.c  -o ${OBJECTDIR}/mcc_generated_files/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi1.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/961894f140bb6d77563a48685768694461867951.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/2fdce9b2e2d65248ede50fc36e115d98346c17cf.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/c6e841794eea8021b070bdeb8a54802faab44390.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/7cc7817ae6a6961fce96c5faf5cb5b785d4c04c0.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/a2b4f9c352445e4ba911cf71ece5957a245f2d7b.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/9a23cc63ae59f948eb83c68937d28ef9c79b08e4.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/io_utils.o: io_utils.c  .generated_files/d53ba94ee0794a90b75e0333520dad8b05874fd0.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io_utils.o.d 
	@${RM} ${OBJECTDIR}/io_utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  io_utils.c  -o ${OBJECTDIR}/io_utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/io_utils.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/radio.o: radio.c  .generated_files/823a84543acb9afd0f1b8bb8c3fa43c943205437.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/radio.o.d 
	@${RM} ${OBJECTDIR}/radio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  radio.c  -o ${OBJECTDIR}/radio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/radio.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/temperature.o: temperature.c  .generated_files/b2ade5b80902b235a73d61596972e626b611bf8f.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/temperature.o.d 
	@${RM} ${OBJECTDIR}/temperature.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  temperature.c  -o ${OBJECTDIR}/temperature.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/temperature.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/7segment.o: 7segment.c  .generated_files/7565c14025bd8c9a335ea884b8f970e7e878ff0e.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/7segment.o.d 
	@${RM} ${OBJECTDIR}/7segment.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  7segment.c  -o ${OBJECTDIR}/7segment.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/7segment.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  .generated_files/b0f5334995e497401c50b20bc21e4d7f5399b437.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/6869721fb631bf05a811f40a1e73cb9e1d8db17f.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/946edbb87d2a5f7c1f1779880ceeb22473aa0fd9.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/spi1.o: mcc_generated_files/spi1.c  .generated_files/cf2152d59558087f1da778c5e3657c2f49041f8c.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/spi1.c  -o ${OBJECTDIR}/mcc_generated_files/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  .generated_files/6225916f41bd70840bd6a6ecaf7fb5fb8f116116.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/bfb64a6d3648fb5b6bcbd5cffb3484daa282569a.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/741739aac08f2744724a0ed80463e840633d3224.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/345b12e233a2030395e2309ea653b2ff91ec9eb2.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/212d3ae21e5a099a232f4141339c2fe1b56a9f46.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/6142b95b24fc1e4a6fe55017a59935941b549c04.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/io_utils.o: io_utils.c  .generated_files/6b952ddf95ab47667ac14b601cd757c8af65305d.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io_utils.o.d 
	@${RM} ${OBJECTDIR}/io_utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  io_utils.c  -o ${OBJECTDIR}/io_utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/io_utils.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/radio.o: radio.c  .generated_files/e415dff94cde6a3d23fffd82f887bf4e0b46702f.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/radio.o.d 
	@${RM} ${OBJECTDIR}/radio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  radio.c  -o ${OBJECTDIR}/radio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/radio.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/temperature.o: temperature.c  .generated_files/f6117fde5b5ce26abc7fa90c4b2b4e93984ddb38.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/temperature.o.d 
	@${RM} ${OBJECTDIR}/temperature.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  temperature.c  -o ${OBJECTDIR}/temperature.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/temperature.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/7segment.o: 7segment.c  .generated_files/23e6038cbb5a452ee1c883fbf3cf3e2a9e259062.flag .generated_files/8a037868bcd381a0152c32f5585b257d4ddd2d8f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/7segment.o.d 
	@${RM} ${OBJECTDIR}/7segment.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  7segment.c  -o ${OBJECTDIR}/7segment.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/7segment.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/Ultrasonic-Extern.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Ultrasonic-Extern.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Ultrasonic-Extern.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Ultrasonic-Extern.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Ultrasonic-Extern.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
