x = linspace(0, 4, 2000);
figure;
pause('on');

for ii = 0:0.1:1.1
    y = sin((x + ii) * pi);
    plot((x + ii) * pi, y);
    title("Sine Wave at x = " + num2str(ii) + "pi~" + num2str(ii + 4) + "pi");
    xlabel('x');
    ylabel('sin(x)');
    xlim([0 + ii * pi (4 + ii) * pi]);
    drawnow; % see the doawing immediately
    pause(1);
end
