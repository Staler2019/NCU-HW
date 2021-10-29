fn = input("file name: ", 's');
[fid, msg] = fopen("./" + fn + ".txt", 'r');

if fid < 0
    error('Cannot open the file.');
end

disp('The file is opened.');
arr = fscanf(fid, '%d');

fclose(fid);
disp('The file is closed.')

[max_y, max_x] = max(arr);
[min_y, min_x] = min(arr);

disp("The max value is " + num2str(max_y) + ". At " + num2str(max_x) + ".");
disp("The min value is " + num2str(min_y) + ". At " + num2str(min_x) + ".");
