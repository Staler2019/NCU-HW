t = linspace(-2, 2, 2000);
x1 = cos(t ./ pi);
x2 = 2 .* sin(t .* pi ./ 2);

lineList = plot(t, x1, t, x2);
% set(lineList, 'ButtonDownFcn', @myLineCallBack);

k = waitforbuttonpress;

while k == 0

    hline = gco;

    if get(hline, 'type') == "line"
        set(hline, 'color', rand(1, 3));
    end

    k = waitforbuttonpress;

end
