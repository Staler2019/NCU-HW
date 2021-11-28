x = linspace(-2,8,200);
y = (x.^2-6.*x+5)./(x-3);
plot(x, y);
axis([-2 8 -10 10]);