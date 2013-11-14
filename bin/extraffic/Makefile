TOP_DIRECTORY=../..

LOCAL_LIBS= \
	-lextraffic_database \

SYSTEM_LIBS= \
	-lstdc++ \
	-lboost_program_options-mt \
 
CXX_LDFLAGS+= \
	$(LOCAL_LIBS) \
	$(SYSTEM_LIBS) \

EXECUTABLE=extraffic

SOURCES=$(EXECUTABLE).cpp

-include $(TOP_DIRECTORY)/mk/executable.mk

