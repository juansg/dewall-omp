MYFLAGS = -g
CFLAGS = -lm 

all: dewall test

dewall: 
	 $(CC) $(CFLAGS) $(MYFLAGS) simplexio.c simplex.c geometry.c hashlist.c unigrid.c dewall.c  main.c -o dewall

test: test_simplexio test_geometry test_hashlist test_unigrid

test_simplexio: 
	 $(CC) $(CFLAGS) $(MYFLAGS) ./test/simplexio/test_simplexio.c simplex.c geometry.c hashlist.c simplexio.c -o ./test/simplexio/test_simplexio

test_geometry: 
	 $(CC) $(CFLAGS) $(MYFLAGS) ./test/geometry/test_geometry.c geometry.c hashlist.c simplexio.c simplex.c -o ./test/geometry/test_geometry

test_hashlist:  
	 $(CC) $(CFLAGS) $(MYFLAGS) ./test/hashlist/test_hashlist.c simplex.c simplexio.c geometry.c hashlist.c -o ./test/hashlist/test_hashlist

test_unigrid:  
	 $(CC) $(CFLAGS) $(MYFLAGS) ./test/unigrid/test_unigrid.c hashlist.c simplex.c simplexio.c geometry.c unigrid.c -o ./test/unigrid/test_unigrid

clean:  
	- rm -rf *.o dewall
