R = randi([0 1],10,1);

for i = 1:length(R)
if R(i) ==0
R(i) = -1;
endif
endfor

save "aux.txt" R;
