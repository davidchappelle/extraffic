TOP_DIRECTORY=../..
 
LOCAL_LIBS= \
	-lextraffic_packet \
	-lextraffic_common \
	-lextraffic_dissect \

SYSTEM_LIBS= \
	-lpcap \
	-lstdc++ \
	-ljsoncpp \
	-lboost_program_options-mt \

CXX_LDFLAGS+= \
	$(LOCAL_LIBS) \
	$(SYSTEM_LIBS) \

EXECUTABLE=extraffic-dissect

SOURCES=$(EXECUTABLE).cpp

-include $(TOP_DIRECTORY)/mk/executable.mk

