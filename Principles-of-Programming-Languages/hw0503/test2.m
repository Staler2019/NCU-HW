[xmin, min_value, xmax, max_value] = find_value(-1, 3, 200, @(x) x.^3-5.*x.^2+5.*x+2);
disp("Maximum value is "+num2str(max_value, '%.6f')+ " when x is "+num2str(xmax, '%.6f'));
disp("Minimum value is "+num2str(min_value, '%.6f')+ " when x is "+num2str(xmin, '%.6f'));