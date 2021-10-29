p = input("P_iG=");
i4year = input("i(%)_i=");

fid = fopen("./interest.txt", 'w');

% just by copy
fprintf(fid, ' P: %7.5f\n i: %7.5f\n', p, i4year);
fprintf(fid, ' Month\tInterest\r\n');
fprintf(fid, ' ======\t===========\r\n');

inter = p;

for mon = 1:60
    inter = inter * (1 + i4year / 1200);
    fprintf(fid, ' %3d   \t%7.5f\r\n', mon, inter);
end

% just by copy end

fclose(fid);
disp("第60月帳戶金額:" + num2str(inter, '%7.5f'));
