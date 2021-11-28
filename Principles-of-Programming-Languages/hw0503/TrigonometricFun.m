function output = TrigonometricFun(fun, value)
    if (func2str(fun) ~= "sin") && (func2str(fun) ~= "cos")
        error("Error using TrigonometricFun fun must be @sin or @cos");
    end
    output = fun(value);
end