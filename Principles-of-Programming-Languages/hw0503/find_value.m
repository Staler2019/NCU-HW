function [xmin, min_value, xmax, max_value] = find_value(first_value, last_value, num_steps, func)
    % [xmin, min_value] = fminbnd(func, first_value, last_value, optimset('MaxFunEvals', num_steps));
    % [xmax, max_value] = fminbnd(@(x) -func(x), first_value, last_value, optimset('MaxFunEvals', num_steps));
    % max_value = -max_value;
    x = linspace(first_value, last_value, num_steps);
    xmin = first_value;
    min_value = func(first_value);
    xmax = last_value;
    max_value = func(last_value);

    for ii = 2:num_steps
        if func(x(ii)) > max_value
            max_value = func(x(ii));
            xmax = x(ii);
        elseif func(x(ii)) < min_value
            min_value = func(x(ii));
            xmin = x(ii);
        end
    end
end
