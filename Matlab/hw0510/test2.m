the = linspace(0, 2 * pi, 200);

y = exp(the .* 1i);

plot3(real(y), imag(y), the);
title('Euler equation when \theta = 0:0.1:2\pi');
