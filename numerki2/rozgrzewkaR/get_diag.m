function A = get_diag(ciA, vicA, n)
% Zadanie ZR
% Tymon Tumialis, 344959
%
% Wyciąga wartości z głównej przekątnej z formatu rzadkiego
%
% WEJŚCIE
% ciA  - indeksy niezerowych wartości w wierszach (n x d)
% vicA - niezerowe wartości macierzy (n x d)
% n    - rozmiar macierzy (liczba wierszy)
% WYJŚCIE
% A    - wektor wartości z głównej przekątnej (n x 1)

rows = (1 : n)';
mask = (ciA == rows);
A = sum(vicA .* mask, 2);

end % function