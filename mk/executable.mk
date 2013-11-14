ifeq ($(TOP_DIRECTORY),)
  $(error <executable.mk> TOP_DIRECTORY must be defined)
endif

ifneq ($(EXECUTABLE),)
  ifneq ($(EXECUTABLES),)
    $(error <executable.mk> Only one of EXECUTABLE or EXECUTABLES can be defined)
  endif
endif
ifeq ($(EXECUTABLES),)
ifneq ($(EXECUTABLE),)
  EXECUTABLES=$(EXECUTABLE)
endif
endif
ifeq ($(EXECUTABLES),)
  $(error <executable.mk> EXECUTABLE or EXECUTABLES must be defined)
endif
ifeq ($(SOURCES),)
  $(error <executable.mk> SOURCES must be defined)
endif

-include $(TOP_DIRECTORY)/mk/configuration.mk

OBJECTS=$(addprefix $(BUILD_OUTPUT_DIRECTORY)/,$(addsuffix .o,$(basename $(SOURCES))))
DEPENDENCIES=$(addprefix $(BUILD_OUTPUT_DIRECTORY)/,$(addsuffix .d,$(basename $(SOURCES))))
EXECUTABLE_TARGETS=$(addprefix $(BUILD_OUTPUT_DIRECTORY)/, $(EXECUTABLES))
BUILD_OUTPUT_FILES=$(OBJECTS) $(DEPENDENCIES) $(EXECUTABLE_TARGETS)

define compile_executable_target
  @cmd="$(CXX) $(CXX_FLAGS) $@.o -o $@ $(CXX_LDFLAGS)" ; \
  if test ! "$(BUILD_VERBOSE)" -eq 1; then \
    echo "Compiling $@"; \
  else \
    echo "$$cmd"; \
  fi; \
  $$cmd
endef

all: build-directories $(OBJECTS) $(EXECUTABLE_TARGETS)

$(EXECUTABLE_TARGETS): $(OBJECTS)
	@$(compile_executable_target)

-include $(TOP_DIRECTORY)/mk/target.mk
-include $(TOP_DIRECTORY)/mk/build.mk
-include $(TOP_DIRECTORY)/mk/dependency.mk
-include $(DEPENDENCIES)

