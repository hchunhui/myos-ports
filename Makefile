.PHONY: all mario ocaml dash ed busybox
all: mario ocaml dash ed busybox

root:
	mkdir -p root
	mkdir -p root/bin
	mkdir -p root/lib

mario: root
	make -C mario/src
	cp mario/src/mario root/bin

ocaml: root
	make -C ocaml/byterun
	cp ocaml/byterun/ocamlrun root/bin
	cp -r ocaml/lib root/

dash: root
	cd dash; ./configure --host=i686-myos-elf;make;cd ..
	cp dash/src/dash root/bin

ed: root
	cd ed; ./configure CC=i686-myos-elf-gcc;make;cd ..
	cp ed/ed root/bin

busybox: root
	make -C busybox
	cp busybox/busybox root/bin

mktar:
	rm -f ports.tar
	strip root/bin/*
	cd root;tar cvf ../ports.tar *;cd ..
