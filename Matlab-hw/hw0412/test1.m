n = input("Please input n: ");

fans = 1;
one = 1;
two = 1;
count = 2;

while count < n
    fans = one + two;
    one = two;
    two = fans;
    count = count + 1;
end

disp("f(" + num2str(n) + ")=" + num2str(fans));
