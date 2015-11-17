CC=g++

.SECONDEXPANSION:
OBJECT=$(CC) $< -c -I include -Wall -Wextra -std=c++11 -o $@
OPTIMIZED=$(CC) $< -c -I include -Wall -Wextra -std=c++11 \
		-O2 -D NDEBUG -o $@
UNIT_TEST=$(CC) $< -c -I include -Wall -Wextra -std=c++11 \
		-g -D UNITTEST -o $@
LINK=$(CC) $^ -o $@

#################################################

lastManStanding.exe: \
		bin/main__opt.o \
		bin/gameBoard__opt.o
	$(LINK)

unittestGameBoard.exe: \
		bin/gameBoard__ut.o
	$(LINK)

#################################################

bin/gameBoard.o: \
		src/gameBoard.cpp \
		include/gameBoard.h | bin
	$(OBJECT)
bin/gameBoard__opt.o: \
		src/gameBoard.cpp \
		include/gameBoard.h | bin
	$(OPTIMIZED)
bin/gameBoard__ut.o: \
		src/gameBoard.cpp \
		include/gameBoard.h | bin
	$(UNIT_TEST)

bin/main.o: \
		src/main.cpp \
		include/gameBoard.h | bin
	$(OBJECT)
bin/main__opt.o: \
		src/main.cpp \
		include/gameBoard.h | bin
	$(OPTIMIZED)

#################################################

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin
	rm -f *.exe
