function val = rescale_interval(a, b, t)
% Zadanie 36
% Tymon Tumialis, 344959
%
% Przeskalowuje standardowy węzeł z [-1, 1] do przedziału [a, b].
% WEJŚCIE:
% a, b - początek i koniec nowego przedziału
% t    - standardowy węzeł z przedziału [-1, 1]
% WYJŚCIE:
% val  - węzeł przeskalowany do przedziału [a, b]

val = (b - a) / 2 * t + (a + b) / 2;

end % function