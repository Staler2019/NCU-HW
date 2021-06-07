% TODO: UNDONE
% [data1,data2] = textread('text3.txt','%f %f');
% % data = [data1 data2];

% % pv = zeros(5, 1);
% plot(data1, data2, 'o');
% hold on;
% for n = 1:5
%     p = polyfit(data1,data2,n);
%     pv = polyval(p,x);
%     plot(data1,pv);
% end

% legend('data','n=1','n=2','n=3','n=4','n=5')
% title("Least Square Regression in different n")
%%
[data1,data2]=textread('text3.txt','%f %f');
plot(data1,data2,'o')
hold on;
for ii=1:5
    p=polyfit(data1,data2,ii);
    pv=polyval(p,data1);
    plot(data1,pv)
end
legend('data','n=1','n=2','n=3','n=4','n=5')
title("Least Square Regression in different n")