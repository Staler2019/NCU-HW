% input
ifn = input("input file name: ", 's');
[ifid, imsg] = fopen("./" + ifn, 'r');

while ifid < 0
    disp("Open file failed.");
    ifn = input("input file name: ", 's');
    [ifid, imsg] = fopen("./" + ifn, 'r');
end

% output
ofn = input("output file name: ", 's');

while exist("./" + ofn,'file')
    disp("Outputfile already exist.");
    cho = input("Keep existing file? (y/n)", 's');

    if cho == "y"
        break;
    end

    ofn = input("output file name: ", 's');
end

[ofid, omsg] = fopen("./" + ofn, 'w');

arr = fscanf(ifid, '%f');
fclose(ifid);

fprintf(ofid, '%d ', round(arr));
fclose(ofid);