hfigure = figure('Name', 'Main figure', 'unit', 'normalized', 'position', [0 0.25 0.5 0.5]);
x = linspace(0, 2 * pi, 2000);
s = sin(x);
c = cos(x);
sc = sin(x) + cos(x);

plot(x, s, 'DisplayName', 'sin(x)');
hold on;
plot(x, c, 'DisplayName', 'cos(x)');
plot(x, sc, 'DisplayName', 'sin(x)+cos(x)');
hold off;
title("sin(x),cos(x),sin(x)+cos(x)");
xlabel('x');
ylabel('y');

k = waitforbuttonpress;

while k == 0

    subFigure(gco, x, s, c, sc);
    figure(hfigure); % get focus
    k = waitforbuttonpress;

end

function subFigure(hline, x, s, c, sc)

    if get(hline, 'type') == "line"
        figure('unit', 'normalized', 'position', [0.5 0.25 0.5 0.5], 'Name', get(hline, 'DisplayName'));

        switch (get(hline, 'SeriesIndex'))
            case 1
                % set(hfigure, 'Name', 'sin(x)');
                plot(x, s, 'color', get(hline, 'color'));
            case 2
                % set(hfigure, 'Name', 'cos(x)');
                plot(x, c, 'color', get(hline, 'color'));
            otherwise
                % set(hfigure, 'Name', 'sin(x)+cos(x)');
                plot(x, sc, 'color', get(hline, 'color'));
        end

        title(get(hline, 'DisplayName'));
        xlabel('x');
        ylabel('y');
    end

end
