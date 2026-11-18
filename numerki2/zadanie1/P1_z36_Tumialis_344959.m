function [q] = P1_z36_Tumialis_344959(f, n1, n2)
% Zadanie 36
% Tymon Tumialis, 344959
%
% Obliczanie całki podwójnej na kole jednostkowym przy użyciu 
% 2-punktowej złożonej kwadratury Gaussa-Legendre'a.
% WEJŚCIE:
% f  - uchwyt do funkcji podcałkowej f(x, y)
% n1 - liczba podprzedziałów względem pierwszej współrzędnej (opcjonalnie)
% n2 - liczba podprzedziałów względem drugiej współrzędnej (opcjonalnie)
% WYJŚCIE:
% q  - obliczone przybliżenie całki podwójnej

switch nargin
    case 0
        error('Wymagany jest co najmniej 1 argument (uchwyt do funkcji).');
    case 1
        n1 = 10;
        n2 = 10;
    case 2
        n2 = 10;
end

start_wezly = get_base_nodes();
block_n1_size = 2 / n1;
block_n2_size = 2 / n2;
q = 0;

for row = 1:n1
    for col = 1:n2
        start_x = calc_interval_pos(-1, row-1, 2, n1);
        end_x = calc_interval_pos(-1, row, 2, n1);
        start_y = calc_interval_pos(-1, col-1, 2, n2);
        end_y = calc_interval_pos(-1, col, 2, n2);

        for k = 1:2
            for l = 1:2
                u = rescale_interval(start_x, end_x, start_wezly(k, 2));
                v = rescale_interval(start_y, end_y, start_wezly(l, 2));

                [r, alfa] = to_polar(u, v);
                J = calc_jacobian(u);
                [x, y] = to_cartesian(r, alfa);

                q = q + f(x, y) * J * (block_n1_size / 2 * block_n2_size / 2);
            end
        end
    end
end

end % function