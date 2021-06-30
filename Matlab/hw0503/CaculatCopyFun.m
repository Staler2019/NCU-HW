function output = CaculatCopyFun(x,n,fun)
    a = 0;
    b = 0;
    for ii = 0:n-1
        b = b*10 + x;
        a = fun(a, b);
    end
    output = a;
end