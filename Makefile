include makefiles/compiler.mk
include makefiles/files.mk

binary := $(PATH_BIN)libkore.a
files := $(OBJ_FILES_SRC) $(OBJ_FILES_$(arch)_$(sys))

global: log $(binary)

log: 
	@echo Init Log >> log.txt
ifeq ($(mode), release)
	@echo Release Compilation > log.txt
else
	@echo Debug Compilation > log.txt
endif
	@echo System: $(sys) $(arch) >> log.txt
	@echo Binary: $(binary) >> log.txt
	@echo ---------------------------- >> log.txt
	@echo Tools and Flags >> log.txt
	@echo AR: $(AR) >> log.txt
	@echo AS: $(AS) >> log.txt
	@echo CC: $(CC) >> log.txt
	@echo AFLAGS: $(AFLAGS) >> log.txt
	@echo CFLAGS: $(CFLAGS) >> log.txt
	@echo ---------------------------- >> log.txt
	@echo Kore Compilation Configurations >> log.txt
	@echo use_std: $(use_std) >> log.txt
	@echo sys_use_std: $(sys_use_std) >> log.txt 

$(binary): $(files)
	@$(AR) rcs $@ $^
ifeq ($(mode), release)
	@echo Release Compilation
else
	@echo Debug Compilation
endif
	@echo System: $(sys) $(arch)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(PATH_OBJ_X86_LINUX)%.o: $(PATH_CDECL)%.s
	@$(AS) $(AFLAGS) -felf32 $< -o $@

$(PATH_OBJ_X86_WINDOWS)%.o: $(PATH_CDECL)%.s
	@$(AS) $(AFLAGS) -fwin32 $< -o $@

$(PATH_OBJ_X86_64_LINUX)%.o: $(PATH_SYSTEM_V_AMD64)%.s
	@$(AS) $(AFLAGS) -felf64 $< -o $@

$(PATH_OBJ_X86_64_WINDOWS)%.o: $(PATH_MICROSOFT_X64)%.s
	@$(AS) $(AFLAGS) -fwin64 $< -o $@

ifeq ($(sys), WINDOWS) 
include makefiles/windows.mk
else
ifeq ($(sys), LINUX)
include makefiles/linux.mk
endif
endif