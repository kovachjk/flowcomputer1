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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FC_Dev3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FC_Dev3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o ${OBJECTDIR}/Microhip/Graphics/Primitive.o ${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o ${OBJECTDIR}/MMB/LCDTerminal.o ${OBJECTDIR}/MMB/LCDTerminalFont.o ${OBJECTDIR}/MMB/MMB.o ${OBJECTDIR}/MMB/SerialEEPROM.o ${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o ${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o ${OBJECTDIR}/_ext/172443446/configuration_bits.o ${OBJECTDIR}/_ext/172443446/exceptions.o ${OBJECTDIR}/_ext/172443446/interrupts.o ${OBJECTDIR}/_ext/172443446/main.o ${OBJECTDIR}/_ext/1475965122/app_globals.o ${OBJECTDIR}/_ext/1475965122/app_inputs.o ${OBJECTDIR}/_ext/1475965122/app_main.o ${OBJECTDIR}/_ext/1475965122/fluids.o ${OBJECTDIR}/_ext/1475965122/interrupts.o ${OBJECTDIR}/_ext/1475965122/pulsed_in.o ${OBJECTDIR}/_ext/1475965122/report_mgr.o ${OBJECTDIR}/_ext/1475965122/temp_in.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o.d ${OBJECTDIR}/Microhip/Graphics/Primitive.o.d ${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o.d ${OBJECTDIR}/MMB/LCDTerminal.o.d ${OBJECTDIR}/MMB/LCDTerminalFont.o.d ${OBJECTDIR}/MMB/MMB.o.d ${OBJECTDIR}/MMB/SerialEEPROM.o.d ${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o.d ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o.d ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o.d ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o.d ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o.d ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o.d ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o.d ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o.d ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o.d ${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o.d ${OBJECTDIR}/_ext/172443446/configuration_bits.o.d ${OBJECTDIR}/_ext/172443446/exceptions.o.d ${OBJECTDIR}/_ext/172443446/interrupts.o.d ${OBJECTDIR}/_ext/172443446/main.o.d ${OBJECTDIR}/_ext/1475965122/app_globals.o.d ${OBJECTDIR}/_ext/1475965122/app_inputs.o.d ${OBJECTDIR}/_ext/1475965122/app_main.o.d ${OBJECTDIR}/_ext/1475965122/fluids.o.d ${OBJECTDIR}/_ext/1475965122/interrupts.o.d ${OBJECTDIR}/_ext/1475965122/pulsed_in.o.d ${OBJECTDIR}/_ext/1475965122/report_mgr.o.d ${OBJECTDIR}/_ext/1475965122/temp_in.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o ${OBJECTDIR}/Microhip/Graphics/Primitive.o ${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o ${OBJECTDIR}/MMB/LCDTerminal.o ${OBJECTDIR}/MMB/LCDTerminalFont.o ${OBJECTDIR}/MMB/MMB.o ${OBJECTDIR}/MMB/SerialEEPROM.o ${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o ${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o ${OBJECTDIR}/_ext/172443446/configuration_bits.o ${OBJECTDIR}/_ext/172443446/exceptions.o ${OBJECTDIR}/_ext/172443446/interrupts.o ${OBJECTDIR}/_ext/172443446/main.o ${OBJECTDIR}/_ext/1475965122/app_globals.o ${OBJECTDIR}/_ext/1475965122/app_inputs.o ${OBJECTDIR}/_ext/1475965122/app_main.o ${OBJECTDIR}/_ext/1475965122/fluids.o ${OBJECTDIR}/_ext/1475965122/interrupts.o ${OBJECTDIR}/_ext/1475965122/pulsed_in.o ${OBJECTDIR}/_ext/1475965122/report_mgr.o ${OBJECTDIR}/_ext/1475965122/temp_in.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/FC_Dev3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o: Microhip/Graphics/DisplayDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microhip/Graphics 
	@${RM} ${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o.d" -o ${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o Microhip/Graphics/DisplayDriver.c   
	
${OBJECTDIR}/Microhip/Graphics/Primitive.o: Microhip/Graphics/Primitive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microhip/Graphics 
	@${RM} ${OBJECTDIR}/Microhip/Graphics/Primitive.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Microhip/Graphics/Primitive.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/Microhip/Graphics/Primitive.o.d" -o ${OBJECTDIR}/Microhip/Graphics/Primitive.o Microhip/Graphics/Primitive.c   
	
${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o: LIBS/MENUS_LIB/MENU_SOURCE/tMenus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o.d" -o ${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o LIBS/MENUS_LIB/MENU_SOURCE/tMenus.c   
	
${OBJECTDIR}/MMB/LCDTerminal.o: MMB/LCDTerminal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MMB 
	@${RM} ${OBJECTDIR}/MMB/LCDTerminal.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MMB/LCDTerminal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/MMB/LCDTerminal.o.d" -o ${OBJECTDIR}/MMB/LCDTerminal.o MMB/LCDTerminal.c   
	
${OBJECTDIR}/MMB/LCDTerminalFont.o: MMB/LCDTerminalFont.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MMB 
	@${RM} ${OBJECTDIR}/MMB/LCDTerminalFont.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MMB/LCDTerminalFont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/MMB/LCDTerminalFont.o.d" -o ${OBJECTDIR}/MMB/LCDTerminalFont.o MMB/LCDTerminalFont.c   
	
${OBJECTDIR}/MMB/MMB.o: MMB/MMB.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MMB 
	@${RM} ${OBJECTDIR}/MMB/MMB.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MMB/MMB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/MMB/MMB.o.d" -o ${OBJECTDIR}/MMB/MMB.o MMB/MMB.C   
	
${OBJECTDIR}/MMB/SerialEEPROM.o: MMB/SerialEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MMB 
	@${RM} ${OBJECTDIR}/MMB/SerialEEPROM.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MMB/SerialEEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/MMB/SerialEEPROM.o.d" -o ${OBJECTDIR}/MMB/SerialEEPROM.o MMB/SerialEEPROM.c   
	
${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o: LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o.d" -o ${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o: LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o: LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o: LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o: LIBS/SYS_LIB/SYS_SOURCE/spi_memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o LIBS/SYS_LIB/SYS_SOURCE/spi_memory.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o: LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o: LIBS/SYS_LIB/SYS_SOURCE/systime_date.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o LIBS/SYS_LIB/SYS_SOURCE/systime_date.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o: LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o: LIBS/SYS_LIB/SYS_SOURCE/uarts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o LIBS/SYS_LIB/SYS_SOURCE/uarts.c   
	
${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o: LIBS/WIFI_LIB/WIFI_SOURCE/wifi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o.d" -o ${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o LIBS/WIFI_LIB/WIFI_SOURCE/wifi.c   
	
${OBJECTDIR}/_ext/172443446/configuration_bits.o: C:/FC_Dev3/source/configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/172443446 
	@${RM} ${OBJECTDIR}/_ext/172443446/configuration_bits.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172443446/configuration_bits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/172443446/configuration_bits.o.d" -o ${OBJECTDIR}/_ext/172443446/configuration_bits.o C:/FC_Dev3/source/configuration_bits.c   
	
${OBJECTDIR}/_ext/172443446/exceptions.o: C:/FC_Dev3/source/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/172443446 
	@${RM} ${OBJECTDIR}/_ext/172443446/exceptions.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172443446/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/172443446/exceptions.o.d" -o ${OBJECTDIR}/_ext/172443446/exceptions.o C:/FC_Dev3/source/exceptions.c   
	
${OBJECTDIR}/_ext/172443446/interrupts.o: C:/FC_Dev3/source/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/172443446 
	@${RM} ${OBJECTDIR}/_ext/172443446/interrupts.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172443446/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/172443446/interrupts.o.d" -o ${OBJECTDIR}/_ext/172443446/interrupts.o C:/FC_Dev3/source/interrupts.c   
	
${OBJECTDIR}/_ext/172443446/main.o: C:/FC_Dev3/source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/172443446 
	@${RM} ${OBJECTDIR}/_ext/172443446/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172443446/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/172443446/main.o.d" -o ${OBJECTDIR}/_ext/172443446/main.o C:/FC_Dev3/source/main.c   
	
${OBJECTDIR}/_ext/1475965122/app_globals.o: C:/FC_Dev3/app/app_source/app_globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/app_globals.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/app_globals.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/app_globals.o.d" -o ${OBJECTDIR}/_ext/1475965122/app_globals.o C:/FC_Dev3/app/app_source/app_globals.c   
	
${OBJECTDIR}/_ext/1475965122/app_inputs.o: C:/FC_Dev3/app/app_source/app_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/app_inputs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/app_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/app_inputs.o.d" -o ${OBJECTDIR}/_ext/1475965122/app_inputs.o C:/FC_Dev3/app/app_source/app_inputs.c   
	
${OBJECTDIR}/_ext/1475965122/app_main.o: C:/FC_Dev3/app/app_source/app_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/app_main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/app_main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/app_main.o.d" -o ${OBJECTDIR}/_ext/1475965122/app_main.o C:/FC_Dev3/app/app_source/app_main.c   
	
${OBJECTDIR}/_ext/1475965122/fluids.o: C:/FC_Dev3/app/app_source/fluids.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/fluids.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/fluids.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/fluids.o.d" -o ${OBJECTDIR}/_ext/1475965122/fluids.o C:/FC_Dev3/app/app_source/fluids.c   
	
${OBJECTDIR}/_ext/1475965122/interrupts.o: C:/FC_Dev3/app/app_source/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/interrupts.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/interrupts.o.d" -o ${OBJECTDIR}/_ext/1475965122/interrupts.o C:/FC_Dev3/app/app_source/interrupts.c   
	
${OBJECTDIR}/_ext/1475965122/pulsed_in.o: C:/FC_Dev3/app/app_source/pulsed_in.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/pulsed_in.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/pulsed_in.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/pulsed_in.o.d" -o ${OBJECTDIR}/_ext/1475965122/pulsed_in.o C:/FC_Dev3/app/app_source/pulsed_in.c   
	
${OBJECTDIR}/_ext/1475965122/report_mgr.o: C:/FC_Dev3/app/app_source/report_mgr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/report_mgr.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/report_mgr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/report_mgr.o.d" -o ${OBJECTDIR}/_ext/1475965122/report_mgr.o C:/FC_Dev3/app/app_source/report_mgr.c   
	
${OBJECTDIR}/_ext/1475965122/temp_in.o: C:/FC_Dev3/app/app_source/temp_in.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/temp_in.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/temp_in.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/temp_in.o.d" -o ${OBJECTDIR}/_ext/1475965122/temp_in.o C:/FC_Dev3/app/app_source/temp_in.c   
	
else
${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o: Microhip/Graphics/DisplayDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microhip/Graphics 
	@${RM} ${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o.d" -o ${OBJECTDIR}/Microhip/Graphics/DisplayDriver.o Microhip/Graphics/DisplayDriver.c   
	
${OBJECTDIR}/Microhip/Graphics/Primitive.o: Microhip/Graphics/Primitive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Microhip/Graphics 
	@${RM} ${OBJECTDIR}/Microhip/Graphics/Primitive.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Microhip/Graphics/Primitive.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/Microhip/Graphics/Primitive.o.d" -o ${OBJECTDIR}/Microhip/Graphics/Primitive.o Microhip/Graphics/Primitive.c   
	
${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o: LIBS/MENUS_LIB/MENU_SOURCE/tMenus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o.d" -o ${OBJECTDIR}/LIBS/MENUS_LIB/MENU_SOURCE/tMenus.o LIBS/MENUS_LIB/MENU_SOURCE/tMenus.c   
	
${OBJECTDIR}/MMB/LCDTerminal.o: MMB/LCDTerminal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MMB 
	@${RM} ${OBJECTDIR}/MMB/LCDTerminal.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MMB/LCDTerminal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/MMB/LCDTerminal.o.d" -o ${OBJECTDIR}/MMB/LCDTerminal.o MMB/LCDTerminal.c   
	
${OBJECTDIR}/MMB/LCDTerminalFont.o: MMB/LCDTerminalFont.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MMB 
	@${RM} ${OBJECTDIR}/MMB/LCDTerminalFont.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MMB/LCDTerminalFont.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/MMB/LCDTerminalFont.o.d" -o ${OBJECTDIR}/MMB/LCDTerminalFont.o MMB/LCDTerminalFont.c   
	
${OBJECTDIR}/MMB/MMB.o: MMB/MMB.C  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MMB 
	@${RM} ${OBJECTDIR}/MMB/MMB.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MMB/MMB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/MMB/MMB.o.d" -o ${OBJECTDIR}/MMB/MMB.o MMB/MMB.C   
	
${OBJECTDIR}/MMB/SerialEEPROM.o: MMB/SerialEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MMB 
	@${RM} ${OBJECTDIR}/MMB/SerialEEPROM.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MMB/SerialEEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/MMB/SerialEEPROM.o.d" -o ${OBJECTDIR}/MMB/SerialEEPROM.o MMB/SerialEEPROM.c   
	
${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o: LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o.d" -o ${OBJECTDIR}/LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.o LIBS/MODBUS_LIB/MODBUS_SOURCE/modbus.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o: LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.o LIBS/SYS_LIB/SYS_SOURCE/lcd_interface.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o: LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.o LIBS/SYS_LIB/SYS_SOURCE/mem_mgr.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o: LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.o LIBS/SYS_LIB/SYS_SOURCE/msg_mgr.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o: LIBS/SYS_LIB/SYS_SOURCE/spi_memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/spi_memory.o LIBS/SYS_LIB/SYS_SOURCE/spi_memory.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o: LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.o LIBS/SYS_LIB/SYS_SOURCE/sys_inputs.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o: LIBS/SYS_LIB/SYS_SOURCE/systime_date.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/systime_date.o LIBS/SYS_LIB/SYS_SOURCE/systime_date.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o: LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.o LIBS/SYS_LIB/SYS_SOURCE/TouchScreen.c   
	
${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o: LIBS/SYS_LIB/SYS_SOURCE/uarts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o.d" -o ${OBJECTDIR}/LIBS/SYS_LIB/SYS_SOURCE/uarts.o LIBS/SYS_LIB/SYS_SOURCE/uarts.c   
	
${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o: LIBS/WIFI_LIB/WIFI_SOURCE/wifi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE 
	@${RM} ${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o.d 
	@${FIXDEPS} "${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o.d" -o ${OBJECTDIR}/LIBS/WIFI_LIB/WIFI_SOURCE/wifi.o LIBS/WIFI_LIB/WIFI_SOURCE/wifi.c   
	
${OBJECTDIR}/_ext/172443446/configuration_bits.o: C:/FC_Dev3/source/configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/172443446 
	@${RM} ${OBJECTDIR}/_ext/172443446/configuration_bits.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172443446/configuration_bits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/172443446/configuration_bits.o.d" -o ${OBJECTDIR}/_ext/172443446/configuration_bits.o C:/FC_Dev3/source/configuration_bits.c   
	
${OBJECTDIR}/_ext/172443446/exceptions.o: C:/FC_Dev3/source/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/172443446 
	@${RM} ${OBJECTDIR}/_ext/172443446/exceptions.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172443446/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/172443446/exceptions.o.d" -o ${OBJECTDIR}/_ext/172443446/exceptions.o C:/FC_Dev3/source/exceptions.c   
	
${OBJECTDIR}/_ext/172443446/interrupts.o: C:/FC_Dev3/source/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/172443446 
	@${RM} ${OBJECTDIR}/_ext/172443446/interrupts.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172443446/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/172443446/interrupts.o.d" -o ${OBJECTDIR}/_ext/172443446/interrupts.o C:/FC_Dev3/source/interrupts.c   
	
${OBJECTDIR}/_ext/172443446/main.o: C:/FC_Dev3/source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/172443446 
	@${RM} ${OBJECTDIR}/_ext/172443446/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172443446/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/172443446/main.o.d" -o ${OBJECTDIR}/_ext/172443446/main.o C:/FC_Dev3/source/main.c   
	
${OBJECTDIR}/_ext/1475965122/app_globals.o: C:/FC_Dev3/app/app_source/app_globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/app_globals.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/app_globals.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/app_globals.o.d" -o ${OBJECTDIR}/_ext/1475965122/app_globals.o C:/FC_Dev3/app/app_source/app_globals.c   
	
${OBJECTDIR}/_ext/1475965122/app_inputs.o: C:/FC_Dev3/app/app_source/app_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/app_inputs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/app_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/app_inputs.o.d" -o ${OBJECTDIR}/_ext/1475965122/app_inputs.o C:/FC_Dev3/app/app_source/app_inputs.c   
	
${OBJECTDIR}/_ext/1475965122/app_main.o: C:/FC_Dev3/app/app_source/app_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/app_main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/app_main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/app_main.o.d" -o ${OBJECTDIR}/_ext/1475965122/app_main.o C:/FC_Dev3/app/app_source/app_main.c   
	
${OBJECTDIR}/_ext/1475965122/fluids.o: C:/FC_Dev3/app/app_source/fluids.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/fluids.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/fluids.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/fluids.o.d" -o ${OBJECTDIR}/_ext/1475965122/fluids.o C:/FC_Dev3/app/app_source/fluids.c   
	
${OBJECTDIR}/_ext/1475965122/interrupts.o: C:/FC_Dev3/app/app_source/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/interrupts.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/interrupts.o.d" -o ${OBJECTDIR}/_ext/1475965122/interrupts.o C:/FC_Dev3/app/app_source/interrupts.c   
	
${OBJECTDIR}/_ext/1475965122/pulsed_in.o: C:/FC_Dev3/app/app_source/pulsed_in.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/pulsed_in.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/pulsed_in.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/pulsed_in.o.d" -o ${OBJECTDIR}/_ext/1475965122/pulsed_in.o C:/FC_Dev3/app/app_source/pulsed_in.c   
	
${OBJECTDIR}/_ext/1475965122/report_mgr.o: C:/FC_Dev3/app/app_source/report_mgr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/report_mgr.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/report_mgr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/report_mgr.o.d" -o ${OBJECTDIR}/_ext/1475965122/report_mgr.o C:/FC_Dev3/app/app_source/report_mgr.c   
	
${OBJECTDIR}/_ext/1475965122/temp_in.o: C:/FC_Dev3/app/app_source/temp_in.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1475965122 
	@${RM} ${OBJECTDIR}/_ext/1475965122/temp_in.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1475965122/temp_in.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files/Microchip/xc32/v1.11/pic32mx/include" -I"C:/MC_XProjects/Microhip/Include" -I"C:/MC_XProjects/Microhip/Include/Graphics" -I"C:/MC_XProjects/MMB" -I"C:/MC_XProjects/LIBS/SYS_LIB" -MMD -MF "${OBJECTDIR}/_ext/1475965122/temp_in.o.d" -o ${OBJECTDIR}/_ext/1475965122/temp_in.o C:/FC_Dev3/app/app_source/temp_in.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/FC_Dev3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/FC_Dev3.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,--defsym=_min_heap_size=128
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/FC_Dev3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/FC_Dev3.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=128
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/FC_Dev3.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
