while true
    cc = input("1)°C to °F or 2)°F to °C 3)EXIT ? ");
    if cc == 3
        break;
    end

    temp = input("Temperature? ");

    if cc == 1
        disp("It is " + num2str(c_to_f(temp), '%.2f') + " °F.");
    elseif cc == 2
        disp("It is " + num2str(f_to_c(temp), '%.2f') + " °C.");
    end

end
