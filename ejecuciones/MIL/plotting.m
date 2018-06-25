graphics_toolkit("gnuplot");
[a]=load("1.txt");
[b]=load("2.txt");
[c]=load("3.txt");
[d]=load("4.txt");
[e]=load("5.txt");
[ent]=load("input.txt");

[total]=[norm(a-ent)/(2*rows(ent)) norm(b-ent)/(2*rows(ent)) norm(c-ent)/(2*rows(ent)) norm(d-ent)/(2*rows(ent)) norm(e-ent)/(2*rows(ent))]
[snr]=[1:5]

plot(snr,total);
xlabel("SNR");
ylabel("BER");
title("BER - SNR");
print("grafico.png");
