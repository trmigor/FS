CPPFLAGS = -I include -Wall -Wextra -pedantic -std=c++17 -O3 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address,undefined #-fno-sanitize-recover=all -fstack-protector

SOURCES = source/main.cpp source/ps.cpp

BINARIES = build/main.o build/ps.o

RESULT = a.out

.PHONY: all
all: $(BINARIES)
	g++ $(CPPFLAGS) -o $(RESULT) $(BINARIES)

$(BINARIES): $(SOURCES)
	g++ $(CPPFLAGS) -c -o $@ source/$(subst build/,,$(subst .o,,$@)).cpp 

.PHONY: clean
clean:
	rm -rf build/* $(RESULT)