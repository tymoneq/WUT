function y = hermitek(t, x, F, dFL, dFR)
% Autor: Yegor Nepokulchytskyi
% Funkcja oblicza wartości wielomianu interpolacyjnego Hermite'a.
% t wektor punktów, w których obliczamy wartość wielomianu
% x wektor węzłów interpolacji, F wartości funkcji w węzłach
% dFL i DFR wektory kolejnych pochodnych w lewym i prawym skrajnym węźle 
% y wartości otrzymanego wielomianu dla t

k1 = length(dFL);
kn = length(dFR);

% Robimy tak, żeby każdy wektor był wektorem wierszowym
F = F(:).';
x = x(:).';
dFL = dFL(:).';
dFR = dFR(:).';

% Budowa rozszerzonych wektorów węzłów i wartości
X = [ones(1, k1) .* x(1), x, ones(1, kn) .* x(end)];
Y = [ones(1, k1) .* F(1), F, ones(1, kn) .* F(end)];

values = hermit(X, Y, k1, dFL, dFR);
b = diag(values); % Wyzanczamy współczynniki

% Obliczanie wartości wielomianu w punktach t
y = count_p(t, X, b);