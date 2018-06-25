n=1/sqrt(2)*(randn(10,1));
SNR = 1;
SNRv = 10^(SNR/10);
No=1/SNRv;
n = sqrt(No)*n;

save "aux2.txt" n;
