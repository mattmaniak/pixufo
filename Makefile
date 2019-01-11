ifeq ($(shell uname), Linux)
all:
	$(MAKE) -f src/Makefile.nix

.PHONY: clean

clean:
	make -f src/Makefile.nix clean

else
all:
	mingw32-make -f src/Makefile.win

.PHONY: clean

clean:
	mingw32-make -f src/Makefile.win clean

endif
