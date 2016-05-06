function [Dst_A] = function_dst (A)

%expansion form A to A_e
A_e = [0 A 0 fliplr(-A)];

%use fft to make dst
fA_e = fft(A_e);
Dst_A = (-1/2)*imag(fA_e(2:length(A)+1));
