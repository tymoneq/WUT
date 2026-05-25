function max_error = calc_max_error(T7_7, T8_8, G17)
    % Autor Tymon Tumialis
    % Funkcja oblicza maksymalny błąd 
    % T7_7, T8_8, G_17 = wartości kwadratur 
    a = max(1,abs(T8_8));

    P1 = abs(T8_8 - T7_7) / a;
    P2 = abs(T8_8 - G17) / a;
    max_error = max(P1,P2);
   
end % function