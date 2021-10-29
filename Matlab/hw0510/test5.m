n = input("n:");

A = input("A1:");

for ii = 2:n
    a = input("A" + num2str(ii) + ":");
    A = cat(3, A, a);
end

B = ones(size(A));
C = A + B;

disp("Global Average Pooling of C:");

avp = mean(C, [1 2]);

for ii = 1:size(avp, 3)
    fprintf('   %.4f', avp(ii));
end

fprintf("\n");
