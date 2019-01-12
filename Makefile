ifeq ($(shell uname), Linux)
all:
	make -f src/Makefile.nix

address:
	make -f src/Makefile.nix address

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
