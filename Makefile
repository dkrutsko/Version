################################################################################
## -------------------------------------------------------------------------- ##
##                                                                            ##
##                        (C) 2011-2014  David Krutsko                        ##
##                        See LICENSE.md for copyright                        ##
##                                                                            ##
## -------------------------------------------------------------------------- ##
################################################################################

##----------------------------------------------------------------------------##
## Build                                                                      ##
##----------------------------------------------------------------------------##

.PHONY: build clean

build: Version.c
	gcc -Wall Version.c -o Version

clean:
	rm -f Version
