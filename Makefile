
all:
	make -C mrt
	make -C tests

clean:
	make -C mrt clean
	make -C tests clean
