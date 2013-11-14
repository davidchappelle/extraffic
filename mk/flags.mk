ifeq ($(TOP_DIRECTORY),)
  $(error <configuration.mk> TOP_DIRECTORY must be defined)
endif

INCLUDE_DIRECTORIES+= \
	-I$(BUILD_INCLUDE_DIRECTORY)

LIBRARY_DIRECTORIES+= \
	-L$(BUILD_LIBRARY_DIRECTORY)

CXX_WARNINGS= \
	-Wall \
	-W \
	-Wredundant-decls \
	-Wpointer-arith \
	-Wno-unused \
        -Wformat-security \
        -Wmissing-format-attribute \
        -Winline \
	-Werror \

CXX_FLAGS+=-g -O0 $(CXX_WARNINGS) $(INCLUDE_DIRECTORIES)

CXX_LDFLAGS+=$(LIBRARY_DIRECTORIES)

