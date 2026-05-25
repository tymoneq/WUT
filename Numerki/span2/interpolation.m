function [Values] = interpolation(f, aktualne_wezly)
    % Autor Tymon Tumialis
    % Funkcja liczy interpolacje Newtona na aktualnych węzłach
    N = size(aktualne_wezly,2);
    Values = zeros(N,N);
    val = f(aktualne_wezly);
    Values(:,1) = val(:);

    % liczenie interpolacji Newtona

    for step=2:N
        for it=N:-1:step
            gorny_index = it-(step-1);            
            wynik = (Values(it,step-1) - Values(it-1,step-1));
            wynik = wynik / (aktualne_wezly(it) - aktualne_wezly(gorny_index));
            Values(it,step) = wynik;
        end
    end
    % odzyskanie współczynników
    Values = diag(Values);
    Values = Values(:).';

end %function