function [x] = wezlyStartowe(a,b,n)
    % Autor Tymon Tumialis
    % funkcja zwraca wezly początkowe z przedziału [a,b]

    x = zeros(n+1,0);
    krok = (b-a+1)/n;

    for it=0:n-1
        x(it+1) = krok *it + a;
    end
end %function