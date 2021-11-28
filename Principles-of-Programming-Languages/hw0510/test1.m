the = linspace(pi, 100 * pi, 2000);

vx = (1 ./ the) .* sin(the);
vy = (1 ./ the) .* cos(the);

plot3(vx, vy, the);
