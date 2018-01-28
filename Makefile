all: 
	-cd example && $(MAKE) all

clean:
	-cd example && $(MAKE) clean

test: all
	-cd server-over-transistors/test && $(MAKE) test