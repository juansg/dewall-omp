export OMP_SET_DYNAMIC=0
#export OMP_NUM_THREADS=8

rm -f test_results test_time
for i in 10 100 1000 10000
do
	for j in {1..10}
	do
		./sample_creator $i
		cp sample.txt sample.$i.$j.i.txt
		{ time ./dewall sample.txt sample.$i.$j.o.txt; } 2>> test_timet
		wc -l sample.$i.$j.o.txt >> test_results
		rm -f sample.$i.$j.i.txt sample.$i.$j.o.txt
	done
done
grep real test_timet | awk '{print $2}' > test_time

