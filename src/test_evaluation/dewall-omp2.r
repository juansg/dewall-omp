#disable scientific notation
options(scipen=999);
  
#got from run2n.R
o1 = 0.00362543447971781

#Get time for parallel 2 threads
list_n = array();
list_ser = array();
list_2t = array();
list_4t = array();
list_8t = array();

sec = 1000000;
i = 1;

for (n in seq(100000,500000,100000)){
   list_n[i] = n;
   file_ser =  paste("data/test_time", n, sep = "");
   file_2t = paste("data/test_time2t", n, sep = "");
   file_4t = paste("data/test_time4t", n, sep = "");
   file_8t = paste("data/test_time8t", n, sep = "");

   table_ser = read.table(file_ser);
   table_2t = read.table(file_2t);
   table_4t = read.table(file_4t);
   table_8t = read.table(file_8t);

   time_ser = mean(table_ser$V1);
   time_2t = mean(table_2t$V1);
   time_4t = mean(table_4t$V1);
   time_8t = mean(table_8t$V1);

   list_ser[i] = time_ser/sec;
   list_2t[i] = time_2t/sec;
   list_4t[i] = time_4t/sec;
   list_8t[i] = time_8t/sec;

   i = i+1;
}

plot(list_n, list_ser, type="l", col="red", main="Comparação Serial x Paralelo", xlab="Número de pontos", ylab="Tempo (sec)");
points(list_n, list_2t, type="l", col="green");
points(list_n, list_4t, type="l", col="blue");
points(list_n, list_8t, type="l", col="orange");
