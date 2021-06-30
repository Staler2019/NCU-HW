x = 0:0.05:360;
subplot(2,1,1);
y1 = sind(x);
plot(x, y1);
title('sind(x)');
axis([0 360 -1 1])

subplot(2,1,2);
y2 = sin(x);
plot(x, y2);
title('sin(x)');
axis([0 360 -1 1])
disp('sind(x) has x in degree, and sin(x) has x in rad');