#disable scientific notation
options(scipen=999);

#got from run2n.R
o1 = 0.00362543447971781

#Get time for seq
list_n = array();
list_ser = array();
list_teo = array();
list_k = array();

sec = 1000000;
i = 1;

for (n in seq(100000,500000,100000)){
   list_n[i] = n;
   file =  paste("data/test_time", n, sep = "");
   test_time = read.table(file);
   time_real = mean(test_time$V1);
   list_ser[i] = time_real/sec;
   time_teor = n*log(n,2)*o1;
   list_teo[i] = time_teor/sec;
   k = log(time_real/(log(n,2)*o1),2)/log(n,2);
   list_k[i] = k;
   i = i+1;
}

plot(list_n, list_ser, type="l", col="green", main="Tempo serial", xlab="Número de pontos", ylab="Tempo (sec)");
x11();
plot(list_n, list_teo, type="l", col="blue", main="Tempo teórico", xlab="Número de pontos", ylab="Tempo (sec)");
print(mean(list_k));
