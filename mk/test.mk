ifeq ($(TOP_DIRECTORY),)
  $(error <test.mk> TOP_DIRECTORY must be defined)
endif

ifeq ($(TEST_SOURCES),)
  $(error <test.mk> TEST_SOURCES must be defined)
endif

-include $(TOP_DIRECTORY)/mk/tools.mk
-include $(TOP_DIRECTORY)/mk/configuration.mk
-include $(TOP_DIRECTORY)/mk/build.mk

all:

test: build-directories $(BUILD_OUTPUT_DIRECTORY)/runner 
	$(BUILD_OUTPUT_DIRECTORY)/runner

$(BUILD_OUTPUT_DIRECTORY)/runner: $(BUILD_OUTPUT_DIRECTORY)/runner.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $< $(CXX_LDFLAGS)

$(BUILD_OUTPUT_DIRECTORY)/runner.cpp: $(TEST_SOURCES)
	$(CXXTESTGEN) -o $@ --error-printer $^

