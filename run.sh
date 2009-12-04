export OMP_SET_DYNAMIC=0
export OMP_NUM_THREADS=1

rm -f test_results test_time test_timet
for i in {1000..100000..1000}
do
	for j in {1..10}
	do
		./sample_creator $i
		cp sample.txt sample.$i.$j.i.txt
		{ time ./dewall sample.$i.$j.i.txt sample.$i.$j.o.txt; } 2>> test_timet
		wc -l sample.$i.$j.o.txt >> test_results		
	done
done

#rm -f sample.$i.$j.i.txt sample.$i.$j.o.txt
grep real test_timet | awk '{print $2}' > test_time

