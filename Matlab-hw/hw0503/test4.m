x = input("x: ");
n = input("n: ");

disp("ans:");
disp("  " + num2str(CaculatCopyFun(x, n, @(a, b) sqrt(a + b))));
