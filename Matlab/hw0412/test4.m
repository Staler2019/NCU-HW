n =1:7;
T=200*8*8./(n.*sqrt(8*8-n.*n)) ;
d=min(T)
plot(n,T,'o')
title("張力對距離d函數圖")
xlabel("距離d")
ylabel("張力")