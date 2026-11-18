function [r, alfa] = to_polar(u, v)
% Zadanie 36
% Tymon Tumialis, 344959
%
% Przekształca zmienne z przedziału [-1, 1] na wsp. biegunowe koła.
% WEJŚCIE:
% u, v   - punkty z kwadratu [-1, 1] x [-1, 1]
% WYJŚCIE:
% r      - wyliczony promień (od 0 do 1)
% alfa   - wyliczony kąt (od 0 do 2*pi)

r = (u + 1) / 2;
alfa = (v + 1) * pi;

end % function