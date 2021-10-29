% fid = fopen("./pic.txt", 'r');
% col = fread(fid);
% col = col(col(:, 1) ~= 10, :);
% col = reshape(col, [256, 160]);
% col = col - 48;

fid=fopen("pic.txt",'r');
input=fscanf(fid,'%c',[1 161]);
for ii=2:256
    tmp=fscanf(fid,'%c',[1 161]);
    input=cat(1,input,tmp);
end
c=double(input);
pic=c-47;
ColorMaps=load("colors.mat").colors;
c1=ColorMaps{1};
c2=ColorMaps{2};
c3=ColorMaps{3};
c4=ColorMaps{4};
c5=ColorMaps{5};
c6=ColorMaps{6};
c7=ColorMaps{7};
c8=ColorMaps{8};
c9=ColorMaps{9};
c10=ColorMaps{10};
Map=[
    c1(1) c1(2) c1(3)
    c2(1) c2(2) c2(3)
    c3(1) c3(2) c3(3)
    c4(1) c4(2) c4(3)
    c5(1) c5(2) c5(3)
    c6(1) c6(2) c6(3)
    c7(1) c7(2) c7(3)
    c8(1) c8(2) c8(3)
    c9(1) c9(2) c9(3)
    c10(1) c10(2) c10(3)
    ];
imshow(pic,Map)