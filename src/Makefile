# When using the GNU Scientific Library, set -DWITH_GSL and link with the libgsl.a
# For populations, choose
# ASL_RM, ASL_RW, ASL_CM_INDOOR, ASL_CM_OUTDOOR, ASL_CW_INDOOR
DEFINES		= -DWITH_GSL -DASL_RM
OPTIONS		= -O2 -Wno-unused-result
#OPTIONS		= -g
CFLAGS		= $(OPTIONS) $(DEFINES)
LDFLAGS		= -static
LIBS		= -lgsl -lgslcblas -lm
CC		= gcc
SOURCES		= $(wildcard *.c)
OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))
EXECUTABLE 	= ../bin/archerystats

all: build $(EXECUTABLE)

$(EXECUTABLE) :$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

$(OBJECTS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

build:
	@mkdir -p ../bin

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
	find . -name "*~" -exec rm {} \;

