
all:
	make -C mlib
	make -C tests

clean:
	make -C mlib clean
	make -C tests clean
