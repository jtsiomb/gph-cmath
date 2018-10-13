obj = test.o
dep = $(obj:.o=.d)
bin = test

CXXFLAGS = -pedantic -Wall -g -I../src
LDFLAGS = -lgmath -lm

$(bin): $(obj)
	$(CXX) -o $@ $(obj) $(LDFLAGS)

-include $(dep)

%.d: %.cc
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) $(bin)

.PHONY: cleandep
cleandep:
	rm -f $(dep)
