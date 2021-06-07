in = input("Please your numberic array in a matrix: ")
out = mysorting(in);
str = num2str(out(1));
disp(num2str(size(out)));

for ii = 2:size(out,2)
    str = str + " " + num2str(out(ii));
end

disp("Array: " + str);
