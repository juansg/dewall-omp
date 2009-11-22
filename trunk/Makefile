MYFLAGS = 
CFLAGS = -lm 

all: 
	 $(CC) $(CFLAGS) $(MYFLAGS) simplexio.c simplex.c hashlist.c dewall.c  main.c -o dewall

test_simplexio: 
	 $(CC) $(CFLAGS) $(MYFLAGS) ./test/simplexio/test_simplexio.c simplexio.c -o ./test/simplexio/test_simplexio

test_geometry: 
	 $(CC) $(CFLAGS) $(MYFLAGS) ./test/geometry/test_geometry.c simplexio.c simplex.c -o ./test/geometry/test_geometry

test_hashlist: 
	 $(CC) $(CFLAGS) $(MYFLAGS) ./test/hashlist/test_hashlist.c simplexio.c simplex.c hashlist.c -o ./test/hashlist/test_hashlist
	 
clean: 
	- rm -rf *.o 
