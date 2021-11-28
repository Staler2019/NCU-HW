% TODO: warning
A = input("Please input matrix A: ");
B = input("Please input matrix B: ");
% disp(size(A));
% disp(size(B));
try
    a = A & B
    b = A | B
    c = xor(A, B)
    d = ~(A | a)
catch
    disp("矩陣大小不同");
end
