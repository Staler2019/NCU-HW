weight = input("輸入包裹的重量: ");
fee = 150;

if weight > 2
    fee = fee + (weight - 2) * 50;
end

if weight > 10
    fee = fee + 150;
end

str = "運送費用: " + num2str(fee);
disp(str);
