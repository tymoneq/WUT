function p = eval_newt(t, x, c)
% Autor: Szymon Straszak
% Funkcja oblicza wartosci wielomianu schematem Hornera.
% t punkty, x wezly, c wspolczynniki wielomianu
% p wyznaczone wartosci wielomianu w punktach t

N = length(c);
p = c(N) * ones(size(t));

for i = N-1:-1:1
    p = c(i) + p .* (t - x(i));
end