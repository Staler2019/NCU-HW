mat = zeros(2, 3);

for c = 1:3
    str1 = "Please input x" +num2str(c) + ": ";
    a = input(str1);
    str2 = "Please input y" + num2str(c) + ": ";
    b = input(str2);
    mat(:, c) = [a; b];
end

disp("Area="+num2str(area2d(mat)));
