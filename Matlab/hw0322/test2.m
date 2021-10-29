x = 0:10;
y = 2 * exp(-.2 * x);
plot (x, y, 'r-', x, y, 'bo', 'MarkerFaceColor', 'b');
title('y(x) = 2 * e^-0.2x');
xlabel('x');
ylabel('y');
grid on;
