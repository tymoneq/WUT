function c = div_diff(x, y)
% Autor: Szymon Straszak
% Funkcja oblicza wspolczynniki wielomianu Newtona.
% x wektor wezlow, y wektor wartosci funkcji w wezlach
% c wektor obliczonych wspolczynnikow wielomianu

N = length(x);
tab = zeros(N, N);
tab(:,1) = y(:);

for j = 2:N
    for i = j:N
        tab(i,j) = (tab(i,j-1) - tab(i-1,j-1)) / (x(i) - x(i-j+1));
    end
end

c = diag(tab);
c = c.';