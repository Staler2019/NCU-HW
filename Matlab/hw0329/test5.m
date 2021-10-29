x = linspace(-pi, pi, 200);
y = zeros(length(x),11);
for i = 0:10
    y(:,i+1) = i*(sin(x)+cos(x)) +i;
end
plot(x, y)
axis([-pi pi -10 20])

%% ??
% x=-pi:2*pi/200:pi;
% for i=0:10
%    y=i.*(sin(x)+cos(x))+i;
%    plot(x,y)
%    hold on
%    ylim([-10,20])
% end