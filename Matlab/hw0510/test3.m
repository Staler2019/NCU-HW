t = linspace(0, 10, 1000);

v = 10 * exp((-0.2 + 1i * pi) * t);

figure(1);
plot(t, v);
title('plot(t,v)');

figure(2);
plot(v);
title('plot(v)');

figure(3);
polarplot(t, v);
title('polar(t,v)');
