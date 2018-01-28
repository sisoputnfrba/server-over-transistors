RM=rm -rf
CC=gcc -Wall

C_SRCS=$(shell find . -iname "*.c" | tr '\n' ' ')
H_SRCS=$(shell find . -iname "*.h" | tr '\n' ' ')
OBJS=$(C_SRCS:./%.c=build/%.o)

# Clean and compile .so
all: build/libsot.so

create-dirs:
	mkdir -p build/sot/

build/libsot.so: dependents create-dirs $(OBJS)
	$(CC) -L"../../so-commons-library/src/build" -shared -o "build/libsot.so" $(OBJS) -lcommons

build/sot/%.o: sot/%.c
	$(CC) -I"../../so-commons-library/src" -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

# Add debug parameters and compile
debug: CC += -DDEBUG -g
debug: all

# Clean build files
clean:
	$(RM) build

install: all
	cp -u build/libsot.so /usr/lib
	cp --parents -u $(H_SRCS) /usr/include

uninstall:
	rm -f /usr/lib/libsot.so
	rm -rf /usr/include/sot

dependents: install-commons

install-commons: submodules
	-cd ../../so-commons-library && $(MAKE) all

submodules:
	-cd git submodule init && git submodule update

.PHONY: all create-dirs clean install uninstall dependents install-commons submodules