n=1/sqrt(2)*(randn(5,1));
SNR = 6.8;
SNRv = 10^(SNR/10);
No=1/SNRv;
n = sqrt(No)*n;

save "aux2.txt" n;
