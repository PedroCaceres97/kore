Building and Compiling:
So, the library uses pure Makefile to compile, the default system target is WINDOWS X86_64 in release mode. To change this you have 3 variables:
- mode: set to release by default, any other value will result in a debug compiling.
- sys: set to WINDOWS by default, see available system table.
- arch: set to X86_64 by default, see available architectures table.

Available System Table:
- WINDOWS   = .exe binaries
- LINUX     = elf binaries
- any other value will result in an undefined behavior
- you could try compiling this in macOS by setting it to LINUX, I never tried though.

Available Architectures Table:
- X86       = 32 bits code
- X86_64    = 64 bits code
- any other value will result in an undefined behavior
