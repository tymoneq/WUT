function [A] = get_base_nodes()
% Zadanie 36
% Tymon Tumialis, 344959
%
% Zwraca macierz bazowych węzłów i wag kwadratury 2-punktowej.
% WYJŚCIE:
% A - macierz 2x2, gdzie pierwsza kolumna to wagi, druga to węzły

t = 1 / sqrt(3);
A = [1, t; 1, -t];

end % function