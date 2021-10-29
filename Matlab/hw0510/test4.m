X = -1:0.1:1;
Y = -2 * pi:0.1:2 * pi;

[x, y] = meshgrid(X, Y);

z = exp(x + 1i .* y);

figure(1)
mesh(x, y, real(z));
title('網格圖');
xlabel('x');
ylabel('y');
zlabel('real part of z');

figure(2)
surf(x, y, real(z));
title('曲面圖');
xlabel('x');
ylabel('y');
zlabel('real part of z');

figure(3)
contour(x, y, real(z));
title('等高線圖');
xlabel('x');
ylabel('y');
