%use function_dst(function_dst()) back to A
DD_A = 2/(length(A)+1)*function_dst(function_dst(A))

%conpare Dst(Dst()) with A and find error
E_A = max(abs(DD_A-A))

