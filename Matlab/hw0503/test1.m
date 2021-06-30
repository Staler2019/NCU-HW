f = @func;

x = -2*pi: pi/10: 2*pi;
y = feval(f,x);
plot(x,y);

function y = func(x)
    y = tan(x).^2 + x - 2;
end