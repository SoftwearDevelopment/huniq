CXXFLAGS ?= -O3

huniq: huniq.cc
	$(CXX)  $(CXXFLAGS) $(LDFLAGS) -Wextra -Wpedantic -Werror -std=c++11 \
		-I"$(PWD)/vendor/tsl-sparse-map/" -I"$(PWD)/vendor/metrohash/src/" \
		huniq.cc vendor/metrohash/src/metrohash128.cpp -o huniq


.PHONY: clean test

test: huniq
	./test

clean:
	rm -vf huniq
