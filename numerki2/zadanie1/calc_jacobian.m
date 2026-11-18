function J = calc_jacobian(u)
% Zadanie 36
% Tymon Tumialis, 344959
%
% Oblicza jakobian przekształcenia dla zmiennej u.
% WEJŚCIE:
% u - zmienna przedziału [-1, 1] odpowiadająca promieniowi
% WYJŚCIE:
% J - wartość jakobianu przekształcenia

J = pi * (u + 1) / 4;

end % function