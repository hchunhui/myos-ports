.PHONY: all mario ocaml
all: mario ocaml

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

mktar:
	rm -f ports.tar
	cd root;tar cvf ../ports.tar *;cd ..
