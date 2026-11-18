function A = get_diag(riA, virA, n)
% Zadanie ZC
% Tymon Tumialis, 344959 
%
% Wyciąga wartości z głównej przekątnej z formatu kolumnowego
%
% WEJŚCIE
% riA  - indeksy wierszy dla niezerowych wartości kolumn (n x d)
% virA - niezerowe wartości macierzy (n x d)
% n    - rozmiar macierzy (liczba kolumn/wierszy)
% WYJŚCIE
% A    - wektor wartości z głównej przekątnej (n x 1)

rows = (1 : n)'; 
mask = (riA == rows); 
A = sum(virA .* mask, 2);

end % function