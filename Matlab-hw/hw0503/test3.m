while true
    f_str = input("function: ", 's');
    n = input("value: ");

    disp(f_str + " = " + num2str(TrigonometricFun(str2func(f_str), n), "%.6f"));
end
