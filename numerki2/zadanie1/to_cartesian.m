function [x, y] = to_cartesian(r, alfa)
% Zadanie 36
% Tymon Tumialis, 344959
%
% Przekształca współrzędne biegunowe na kartezjańskie.
% WEJŚCIE:
% r    - promień
% alfa - kąt w radianach
% WYJŚCIE:
% x, y - współrzędne kartezjańskie

x = r * cos(alfa);
y = r * sin(alfa);

end % function