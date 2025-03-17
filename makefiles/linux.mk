mkdir:
	mkdir -p $(PATH_OBJ_X86_LINUX)
	mkdir -p $(PATH_OBJ_X86_WINDOWS)
	mkdir -p $(PATH_OBJ_X86_64_LINUX)
	mkdir -p $(PATH_OBJ_X86_64_WINDOWS)
	
clean:
	rm -rf $(PATH_BIN)
	rm -rf $(PATH_OBJ)
	rm -rf $(PATH_OBJ_X86_LINUX)
	rm -rf $(PATH_OBJ_X86_WINDOWS)
	rm -rf $(PATH_OBJ_X86_64_LINUX)
	rm -rf $(PATH_OBJ_X86_64_WINDOWS)