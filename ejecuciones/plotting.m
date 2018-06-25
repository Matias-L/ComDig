graphics_toolkit("gnuplot");
[a]=load("deco snr1.txt");
[b]=load("deco snr2.txt");
[c]=load("deco snr3.txt");
[d]=load("deco snr4.txt");
[e]=load("deco snr5.txt");
[ent]=load("entrada.txt");

[total]=[norm(a-ent)/(2*rows(ent)) norm(b-ent)/(2*rows(ent)) norm(c-ent)/(2*rows(ent)) norm(d-ent)/(2*rows(ent)) norm(e-ent)/(2*rows(ent))]
[snr]=[1:5]

plot(snr,total);
xlabel("SNR");
ylabel("BER");
title("BER - SNR");
print("grafico.png");
