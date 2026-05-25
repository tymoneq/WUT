function [nowe_wezly] = error_calc(f,wynik_hornera, wezly,aktualne_wezly)
    % Autor Tymon Tumialis
    % funkcja wylicza błąd interpolacji i tworzy wektor z nowymi węzłami

    % wyliczenie błedu
    y = f(wezly);
    a = abs(y- wynik_hornera);
    [a,indx] = maxk(a,2);
    
    % stworzenie nowych węzłów
    nowe_wezly = [aktualne_wezly, wezly(indx(1:2))];
    nowe_wezly = sort(nowe_wezly);

end %function