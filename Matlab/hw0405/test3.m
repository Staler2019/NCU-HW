income = input("Please input the income: ");
inc_tax = 0;
hel_tax = income * .022;

if income > 60000
    inc_tax = 18000 + (income - 60000) * .51;
elseif income > 50000
    inc_tax = 13300 + (income - 50000) * .47;
elseif income > 20000
    inc_tax = 2800 + (income - 20000) * .35;
elseif income > 6000
    inc_tax = (income * 6000) * .2;
else
    inc_tax = 0;
end

inc_str = "    所得稅: " + num2str(inc_tax);
hel_str = "    健保稅: " + num2str(hel_tax);
total_str = "總共需繳納: " + num2str(inc_tax + hel_tax);
disp("分類:")
disp(inc_str);
disp(hel_str);
disp(total_str);
