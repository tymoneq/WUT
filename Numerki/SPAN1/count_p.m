function p = count_p(t, X, b)
% Autor: Yegor Nepokulchytskyi
% Funkcja oblicza wartości wielomianu korzystając ze schematu Hornera.
% t wektor punktów, w których obliczamy wartość, X wektor węzłów
% b wektor współczynników wielomianu
% p wektor wyznaczonych wartości wielomianu w punktach t

N = length(b);

% Schemat Hornera
p = b(N) .* ones(size(t));
for i = N-1:-1:1
    p = b(i) + p .* (t - X(i));
end