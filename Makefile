CC=g++

.SECONDEXPANSION:
OBJECT=$(CC) $< -c -I include -Wall -Wextra -o $@
OPTIMIZED=$(CC) $< -c -I include -Wall -Wextra -O2 -D NDEBUG -o $@
LINK=$(CC) $^ -o $@

#################################################

ascii.exe: bin/ascii.o
	$(LINK)

#################################################

bin/ascii.o: src/ascii.cpp | bin
	$(OBJECT)
bin/ascii__opt.o: src/ascii.cpp | bin
	$(OPTIMIZED)

#################################################

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin
	rm -f *.exe
