#Get time for 1 operation

#disable scientific notation
options(scipen=999);

lo1 = array();
i = 0;

for (n in seq(10000,100000,10000)) {
   file = paste("data/run2n_time", n, sep = "");
   test_time = read.table(file);
   t = mean(test_time$V1)/n;
   lo1[i] = t;
   i = i+1;   
}
o1 = mean(lo1);

print(lo1);
print(paste("Time for O(1) is",o1,"uSec."));

