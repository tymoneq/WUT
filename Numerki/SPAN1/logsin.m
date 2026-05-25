function y = logsin(x)
    % Autor: Tymon Tumialis
    % Zwraca wynik działania (9log(1+x^2/9) - xsinx)/x^4 dla x w [-4;4]
    
    y = zeros(size(x));
    
    % Dla |x| >= 1 stosujemy standardowy wzór
    maska_zewn = abs(x) >= 1;
    xz = x(maska_zewn);
    y(maska_zewn) = (9 * log(1 + xz.^2/9) - xz.*sin(xz)) ./ xz.^4;
    
    % Dla |x| < 1 stosujemy stabilnie numeryczny szereg Taylora
    maska_wewn = abs(x) < 1;
    xw = x(maska_wewn);
    
    xw2 = xw.^2; % Nasz nowy szereg zależy wyłącznie od potęg x^2
    wynik = zeros(size(xw));
    
    % Schemat Hornera: od najwyższej potęgi (N=15) do najniższej (m=0)
    % 15 wyrazów w zupełności wystarczy, by błąd spadł poniżej 10^-16
    for m = 15:-1:0
        term_log = 1 / ((m + 2) * 9^(m + 1));
        term_sin = 1 / factorial(2 * m + 3);
        C_m = (-1)^(m + 1) * (term_log - term_sin);
        wynik = wynik .* xw2 + C_m;
    end
    y(maska_wewn) = wynik;

end % function