x = 0: 0.1: 10;
y1 = exp(-.5.*x).*sin(2.*x);
y2 = exp(-.5.*x).*cos(2.*x);
plot(x, y1, 'b-', 'LineWidth', 2.0);
hold on;
plot(x, y2, 'r--', 'LineWidth', 3.0);
hold off;
title('y = exp(-0.5x)*sin(2x)/y = exp(-0.5x)*cos(2x)');
legend('sin(2x)', 'cos(2x)');
