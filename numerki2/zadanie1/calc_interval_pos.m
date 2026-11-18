function x = calc_interval_pos(start, current, len, num_of_blocks)
% Zadanie 36
% Tymon Tumialis, 344959
%
% Oblicza położenie punktu podziału przedziału.
% WEJŚCIE:
% start         - początek głównego przedziału
% current       - obecny indeks podprzedziału (od 0)
% len           - długość głównego przedziału
% num_of_blocks - całkowita liczba podprzedziałów
% WYJŚCIE:
% x             - współrzędna punktu podziału

x = start + len * current / num_of_blocks;

end % function