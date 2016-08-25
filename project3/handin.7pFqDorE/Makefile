# Makefile for CPSC 221, Programming Project #1.
# With many thanks to: http://wiki.osdev.org/Makefile


# Names of projects for handin.
# Needs to be changed for different projects!
# It might be reasonable to pull these directly from the handin -l command.
HANDIN_NAMES = proj3-milestone1 proj3

# The full list of source files and header files in the project.
SRCFILES := $(wildcard *.$(CPP_EXTENSION))  

# The patsubst at the start generates a list of targets that look like
# handin-proj1.  The remainder is a little shell script that makes a
# temporary directory, storing its value in a temporary variable.
# Copies all the files (not directories.. done sloppily) into the
# temporary directory, goes into the temporary directory and cleans,
# zips up a handin archive, hands it in, checks the handin listing,
# and finally destroys the temporary directory.
$(patsubst %,handin-%,$(HANDIN_NAMES)):
	@$(eval $@_TMP_DIR := $(shell mktemp -d handin.XXXXXXXX))
	@cp `ls -p | grep -v '/'` $($@_TMP_DIR)
	@cd $($@_TMP_DIR); \
	  $(RMF) $(wildcard $(OBJFILES) $(DEPFILES) $(MAINS) *~ *.bak *.old)
	@cd $($@_TMP_DIR); \
	  zip handin.zip *
	@cd $($@_TMP_DIR); \
	  handin -o -f handin.zip cs221 $(patsubst handin-%,%,$@)
	handin -c cs221 $(patsubst handin-%,%,$@)
	@rm -Rf $($@_TMP_DIR)

.PHONY: all clean todolist

