n1 = input("Please input n1: ");
n2 = input("Please input n2: ");
theta1 = input('Please input theta1: ');

check = n1 / n2 * sind(theta1);
theta2 = 0;

if abs(check) <= 1
    theta2 = asind(check);
    disp("theta2: " + num2str(theta2));
    plot(-10:10, 0 .* (-10:10), 'k');
    hold on;
    plot(-10:0, -tand(90 - theta1) .* (-10:0), 'r')
    plot(0:10, -tand(90 - theta2) .* (0:10), 'b')
    hold off;
    legend("介面", "入射線", "折射線", 'Location', 'northeastoutside');
else
    disp("全反射發生!");
    plot(-10:10, 0 .* (-10:10), 'k');
    hold on;
    plot(-10:0, -tand(90 - theta1) .* (-10:0), 'r')
    plot(0:10, tand(90 - theta1) .* (0:10), 'b')
    hold off;
    legend("介面", "入射線", "反射線", 'Location', 'northeastoutside');

end

axis([-10 10 -10 10])
