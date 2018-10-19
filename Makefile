PREFIX = /usr/local

.PHONY: all
all:
	@echo 'There is nothing to build. Either type "make install" to install the headers'
	@echo 'system-wide, or just copy all files under "src" to your project.'


.PHONY: clean
clean:

.PHONY: install
install:
	mkdir -p $(DESTDIR)$(PREFIX)/include/cgmath
	cp src/*.h src/*.inl $(DESTDIR)$(PREFIX)/include/cgmath

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/include/cgmath/*.h
	rm -f $(DESTDIR)$(PREFIX)/include/cgmath/*.inl
	rmdir $(DESTDIR)$(PREFIX)/include/cgmath
