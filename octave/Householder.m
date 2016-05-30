function [B, A] = Householder (A)

% setting
m = size(A,1);
n = size(A,2);
I = eye(max(m,n));
B = I;
V(m,n) = 0.0;

% make R
for k = (1:n)
x = A(k:m,k);
v = sign(x(1)) * norm(x) * I(k:m,k) + x;
v = v / norm(v);
V(k:m,k) = v;
A(k:m,k:n) = A(k:m,k:n) - 2 * v * (v' * A(k:m,k:n));
end

% 1 to n to make Q*
for j = (1:m)
	for k = (1:n)
	B(k:m,j) = B(k:m,j) - 2 * V(k:m,k) * (V(k:m,k)' * B(k:m,j));
	end
end
B = B';


% n to 1 to make Q
%{
for j = (m:-1:1)
	for k = (n:-1:1)
	B(k:m,j) = B(k:m,j) - 2 * V(k:m,k) * (V(k:m,k)' * B(k:m,j));
	end
end
%}
