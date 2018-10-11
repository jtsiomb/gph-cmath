obj = test.o
bin = test

CXXFLAGS = -pedantic -Wall -g -I../src
LDFLAGS = -lgmath -lm

$(bin): $(obj)
	$(CXX) -o $@ $(obj) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) $(bin)
