all: switchdev_gentest.c
	gcc switchdev_gentest.c $(shell pkg-config --cflags --libs libnl-3.0 libnl-genl-3.0) -o gentest

