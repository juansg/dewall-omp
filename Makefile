MYFLAGS = 
CFLAGS = -lm 

all: 
	 $(CC) $(CFLAGS) $(MYFLAGS) simplexio.c simplex.c dewall.c  main.c -o dewall

test_simplexio: 
	 $(CC) $(CFLAGS) $(MYFLAGS) ./test/simplexio/test_simplexio.c simplexio.c -o ./test/simplexio/test_simplexio

test_geometry: 
	 $(CC) $(CFLAGS) $(MYFLAGS) ./test/geometry/test_geometry.c simplexio.c simplex.c -o ./test/geometry/test_geometry

clean: 
	- rm -rf *.o 
