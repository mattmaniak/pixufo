ifeq ($(shell uname), Linux)
all:
	$(MAKE) -f src/Makefile.nix

.PHONY: clean

clean:
	$(MAKE) -f src/Makefile.nix clean

else # TODO: ONLY WINDOWS
	$(MAKE) -f src/Makefile.win

.PHONY: clean

clean:
	$(MAKE) -f src/Makefile.win clean

endif
