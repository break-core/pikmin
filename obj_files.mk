# Linker order for every file, passed to the Metrowerks linker.

INIT_O_FILES :=									\
    $(BUILD_DIR)/asm/init.o						\

EXTAB_O_FILES :=								\
    $(BUILD_DIR)/asm/extab.o					\

EXTABINDEX_O_FILES :=							\
    $(BUILD_DIR)/asm/exidx.o					\

TEXT_O_FILES :=									\
    $(BUILD_DIR)/asm/text_0.o					\
    $(BUILD_DIR)/src/sysCommon/shpRoutes.o		\
    $(BUILD_DIR)/asm/text_1.o					\
    $(BUILD_DIR)/src/sysCommon/matMath.o		\
    $(BUILD_DIR)/asm/text_2.o					\
    $(BUILD_DIR)/src/sysCommon/timers.o	    	\
    $(BUILD_DIR)/asm/text_800409B0.o			\
    $(BUILD_DIR)/src/gx/GXStubs.o				\
    $(BUILD_DIR)/asm/text_802140E8.o			\
    $(BUILD_DIR)/asm/text_8021C4CC.o			\
    $(BUILD_DIR)/src/amcnotstub/amcnotstub.o	\
    $(BUILD_DIR)/asm/text_3.o					\
    $(BUILD_DIR)/src/odenotstub/odenotstub.o	\

CTORS_O_FILES :=								\
    $(BUILD_DIR)/asm/ctors.o					\

DTORS_O_FILES :=								\
    $(BUILD_DIR)/asm/dtors.o					\

RODATA_O_FILES :=								\
    $(BUILD_DIR)/asm/rodata.o					\

DATA_O_FILES :=									\
    $(BUILD_DIR)/asm/data.o						\

BSS_O_FILES :=									\
    $(BUILD_DIR)/asm/bss.o						\

SDATA_O_FILES :=								\
    $(BUILD_DIR)/asm/sdata.o					\

SBSS_O_FILES :=									\
    $(BUILD_DIR)/asm/sbss.o						\

SDATA2_O_FILES :=								\
    $(BUILD_DIR)/asm/sdata2.o					\
	
