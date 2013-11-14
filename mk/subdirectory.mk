ifeq ($(TOP_DIRECTORY),)
  $(error TOP_DIRECTORY must be set before including library.mk)
endif

ifeq ($(SUB_DIRECTORIES),)
  $(error SUB_DIRECTORIES must be set before including subdir.mk)
endif

-include $(TOP_DIRECTORY)/mk/tools.mk

define recurse-subdirs
  +@subdirs='$(SUB_DIRECTORIES)'; \
  if [ ! -z "$$subdirs" ]; then \
    target=`echo $@ | $(SED) 's/-recursive//'`; \
    for subdir in $$subdirs; do \
      (cd $$subdir && $(MAKE) $$target); \
    done; \
  fi;
endef

all: all-recursive

test: test-recursive

clean: clean-recursive

all-recursive test-recursive clean-recursive:
	$(recurse-subdirs)

