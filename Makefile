.PHONY: all mario
all: mario

mario:
	mkdir -p root
	mkdir -p root/bin
	make -C mario/src
	cp mario/src/mario root/bin
