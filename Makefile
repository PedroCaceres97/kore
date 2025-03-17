include makefiles/compiler.mk
include makefiles/files.mk

sys := WINDOWS
arch := X86_64

global: $(binary)

ifeq ($(sys), WINDOWS) 
include makefiles/windows.mk
else
	ifeq ($(sys), LINUX)
include makefiles/linux.mk
	endif
endif

CFLAGS := $(CFLAGS) -DKORE_OS_$(sys) -DKORE_ARCH_$(arch)

files := $(OBJ_FILES_SRC) $(OBJ_FILES_$(arch)_$(sys))

$(binary): $(files)
	@echo Linking Target: $(binary)
	@echo Mode: $(mode)
	@echo System: $(sys)
	@echo Architecture: $(arch)
	@echo AR: $(AR)
	@echo AS: $(AS)
	@echo CC: $(CC)
	@echo CFLAGS: $(CFLAGS)
	@$(AR) rcs $@ $^

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@echo Compiling C file: $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(PATH_OBJ_X86_LINUX)%.o: $(PATH_CDECL)%.s
	@echo Compiling S file: $<
	@$(AS) -felf32 $< -o $@

$(PATH_OBJ_X86_WINDOWS)%.o: $(PATH_CDECL)%.s
	@echo Compiling S file: $<
	@$(AS) -fwin32 $< -o $@

$(PATH_OBJ_X86_64_LINUX)%.o: $(PATH_SYSTEM_V_AMD64)%.s
	@echo Compiling S file: $<
	@$(AS) -felf64 $< -o $@

$(PATH_OBJ_X86_64_WINDOWS)%.o: $(PATH_MICROSOFT_X64)%.s
	@echo Compiling S file: $<
	@$(AS) -fwin64 $< -o $@