CXXFLAGS ?= -O2

huniq:
	$(CXX) huniq.cc $(CXXFLAGS) $(LDFLAGS) -Wextra -Wpedantic -Werror -std=c++11 -o huniq

.PHONY: clean test

test: huniq
	./test

clean:
	rm -vf huniq
