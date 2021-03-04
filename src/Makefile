# --------------------------------------------------------------------------
# Name      : Makefile                                                   ***
# Purpose   : Generate the ArcheryCompetitionSimulation program          ***
# Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
# Copyright : 2013-2021                                                  ***
#                                                                        ***
# This file is part of ArcheryCompetitionSimulation.                     ***
#                                                                        ***
# ArcheryCompetitionSimulation is free software: you can redistribute it ***
# and/or modify it under the terms of the GNU General Public License as  ***
# published by the Free Software Foundation, either version 3 of the     ***
# License, or (at your option) any later version.                        ***
#                                                                        ***
# ArcheryCompetitionSimulation is distributed in the hope that it will   ***
# be useful, but WITHOUT ANY WARRANTY; without even the implied warranty ***
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the       ***
# GNU General Public License for more details.                           ***
#                                                                        ***
# You should have received a copy of the GNU General Public License      ***
# along with ArcheryCompetitionSimulation.  If not,                      ***
# see <https://www.gnu.org/licenses/>.                                   ***
#**************************************************************************/

# When using the GNU Scientific Library, set -DWITH_GSL and link with the libgsl.a
# For preset/non-interactive populations, choose from
# 
# ASL_RM  		= Performance distribution for Recurve Men (2019 World Championships 's Hertogenbosch)
# ASL_RW  		= Performance distribution for Recurve Women (2019 World Championship 's Hertogenbosch)
# ASL_CM_INDOOR 	= Performance distribution for Compound Men Indoor (from Nimes 2017)
# ASL_CM_OUTDOOR 	= Performance distribution for Compound Men Outdoor (2019 World Championships 's Hertogenbosch)
# ASL_CW_INDOOR 	= Performance distribution for Compound Women Indoor (from Nimes 2017)
#
# Or use --interactive to choose own performance distribution
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

