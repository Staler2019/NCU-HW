a = 0;

for k = 0:5
    a = a + binomial(k, 20, 1/3);
end

b = a;

for k = 6:10
    b = b + binomial(k, 20, 1/3);
end

disp("(a) " + num2str(a, '%.2f'));
disp("(b) " + num2str(b, '%.2f'));