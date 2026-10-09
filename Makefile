# Makefile for the nng-c-study project.
#
# Targets:
# 	make clean	- remove every generated .exe from all topic folders
#	make build	- compile every .c file into a .exe next to it
#	make list	- show which .exe files currently exist
#
# Notes:
# 	- Uses the MinGW gcc you already have on PATH.
#	- 'clean' uses PowerShell to recursively delete .exe files, which is the
#	  reliable option in your Windows + PowerShell environment. If you run this
#	  with mingw32-make from a plain cmd.exe it still works, because we invoke
#	  powershell explicitly.

CC		:= gcc
CFLAGS	:= -Wall -Wextra -g

# Find all .c files recursively (works with GNU make's shell function).
SRCS := $(shell powershell -NoProfile -Command "Get-ChildItem -Recurse -Filter *.c | ForEach-Object { $$_.FullName }")
EXES := $(SRCS:.c=.exe)

.PHONY: clean build list

# Remove all generated .exe files anywhere under the project.
clean:
	@powershell -NoProfile -Command "Get-ChildItem -Recurse -Filter *.exe | ForEach-Object { Write-Host ('removing ' + $$_.FullName); Remove-Item $$_.FullName }"
	@echo Clean complete.

# Compile each .c into a matching .exe sitting next to it.
build:
	@powershell -NoProfile -Command "Get-ChildItem -Recurse -Filter *.c | ForEach-Object { $$out = $$_.FullName -replace '\.c$$','.exe'; Write-Host ('compiling ' + $$_.Name); & '$(CC)' $(CFLAGS) $$_.FullName -o $$out }"
	@echo "Build complete."

# List existing .exe files.
list:
	@powershell -NoProfile -Command "Get-ChildItem -Recurse -Filter *.exe | ForEach-Object { $$_.FullName }"