ifeq ($(TOP_DIRECTORY),)
  $(error <build.mk> TOP_DIRECTORY must be defined)
endif

ifeq ($(BUILD_OUTPUT_DIRECTORY),)
  $(error <build.mk> BUILD_OUTPUT_DIRECTORY must be defined)
endif

ifeq ($(BUILD_LIBRARY_DIRECTORY),)
  $(error <build.mk> BUILD_LIBRARY_DIRECTORY must be defined)
endif

ifneq ($(BUILD_OUTPUT_FILES),)
  CLEANUP_BUILD_OUTPUT_FILES=1
endif
CLEANUP_BUILD_OUTPUT_FILES?=0

BUILD_DIRECTORIES=$(BUILD_OUTPUT_DIRECTORY) $(BUILD_LIBRARY_DIRECTORY)
BUILD_VERBOSE?=1

-include $(TOP_DIRECTORY)/mk/flags.mk
-include $(TOP_DIRECTORY)/mk/tools.mk

.SUFFIXES: .o .cpp

define create_build_directories
  +@directories='$(BUILD_DIRECTORIES)'; \
  for directory in $$directories; do \
    if [ ! -d $$directory ]; then \
      if test $(BUILD_VERBOSE) -eq 1; then \
        echo "Creating directory $$directory"; \
      fi; \
      $(MKDIR) -p $$directory; \
    fi; \
  done;
endef

define cleanup_build_output
  if [ -d $(BUILD_OUTPUT_DIRECTORY) ]; then \
    if test $(BUILD_VERBOSE) -eq 1; then \
      echo "Removing build output directory: $(BUILD_OUTPUT_DIRECTORY)"; \
    fi; \
    $(RM) -fr $(BUILD_OUTPUT_DIRECTORY); \
  fi; \
  if test $(CLEANUP_BUILD_OUTPUT_FILES) -eq 1; then \
    if test $(BUILD_VERBOSE) -eq 1; then \
      echo "Removing build output files: $(BUILD_OUTPUT_FILES)"; \
    fi; \
    $(RM) -f $(BUILD_OUTPUT_FILES); \
  fi;
endef

define compile_cxx_file
  @cmd="$(CXX) $(CXX_FLAGS) -MMD -MP -c $< -o $@" ; \
  if test $(BUILD_VERBOSE) -eq 1; then \
    echo "Compiling $<"; \
  else \
    echo "$$cmd"; \
  fi; \
  $$cmd
endef

build-directories:
	@$(create_build_directories)

clean:
	@$(cleanup_build_output)
	

$(BUILD_OUTPUT_DIRECTORY)/%.o: %.cpp
	@$(compile_cxx_file)

.PHONY: clean
