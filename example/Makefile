RM=rm -rf
CC=gcc -Wall


C_SRCS=$(shell find . -iname "*.c" | tr '\n' ' ')
OBJS=$(C_SRCS:./%.c=build/%.o)

all: build/example

create-dirs:
	mkdir -p build

build/example: dependents create-dirs $(OBJS)
	$(CC) -L"../so-commons-library/src/build" -L"../server-over-transistors/src/build" -o "build/example" $(OBJS) -lcommons -lsot

build/%.o: ./%.c
	$(CC) -I"../so-commons-library/src" -I"../server-over-transistors/src" -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

debug: CC += -DDEBUG -g
debug: all

clean:
	$(RM) build

run: all
	LD_LIBRARY_PATH="../server-over-transistors/src/build/:../so-commons-library/src/build" build/example

dependents: install-commons
	-cd ../server-over-transistors/src && $(MAKE) all

install-commons: submodules
	-cd ../so-commons-library && $(MAKE) all

submodules:
	-git submodule init && git submodule update

.PHONY: all create-dirs clean dependents install-commons submodules