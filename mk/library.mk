ifeq ($(TOP_DIRECTORY),)
  $(error <library.mk> TOP_DIRECTORY must be defined)
endif

ifeq ($(LIBRARY),)
  $(error <library.mk> LIBRARY must be defined)
endif

ifeq ($(SOURCES),)
  $(error <library.mk> SOURCES must be defined)
endif

-include $(TOP_DIRECTORY)/mk/configuration.mk

OBJECTS=$(addprefix $(BUILD_OUTPUT_DIRECTORY)/,$(addsuffix .o,$(basename $(SOURCES))))
DEPENDENCIES=$(addprefix $(BUILD_OUTPUT_DIRECTORY)/,$(addsuffix .d,$(basename $(SOURCES))))
LIBRARY_DIRECTORY=$(TOP_DIRECTORY)/lib
LIBRARY_TARGET=$(LIBRARY_DIRECTORY)/lib$(LIBRARY).a
BUILD_OUTPUT_FILES=$(OBJECTS) $(DEPENDENCIES) $(LIBRARY_TARGET)

all: build-directories $(OBJECTS) $(LIBRARY_TARGET)

$(LIBRARY_TARGET): $(OBJECTS)
	@$(AR) -r $(LIBRARY_TARGET) $(OBJECTS)

-include $(TOP_DIRECTORY)/mk/target.mk
-include $(TOP_DIRECTORY)/mk/build.mk
-include $(TOP_DIRECTORY)/mk/dependency.mk
-include $(DEPENDENCIES)

