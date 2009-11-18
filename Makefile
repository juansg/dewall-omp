MYFLAGS = 
CFLAGS =  

all: 
	 $(CC) $(CFLAGS) $(MYFLAGS) simplexio.c simplex.c main.c -o dewall

test_simplexio: 
	 $(CC) $(CFLAGS) $(MYFLAGS) ./test/simplexio/test_simplexio.c simplexio.c -o ./test/simplexio/test_simplexio

clean: 
	- rm -rf *.o 
