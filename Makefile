CXXFLAGS ?= -O2

huniq:
	$(CXX) huniq.cc $(CXXFLAGS) $(LDFLAGS) -Wextra -Wpedantic -Werror -std=c++11 -o huniq -I"$(PWD)/vendor/tsl-sparse-map/"

.PHONY: clean test

test: huniq
	./test

clean:
	rm -vf huniq
