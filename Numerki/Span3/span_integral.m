function [Q,errest] = span_integral(f,a,b,tol,recLev)
    % Autor Tymon Tumialis
    % Funkcja oblicza wartość całki na przedziale a,b z tolerancją tol
    % f = funkcja której całkę chcemy policzyć
    % a,b = początek i koniec przedziału
    % tol = maksymalna tolerancja błędu 
    % recLev = maksymalny poziom rekurencji
    % Q = końcowe przybliżenie całki
    % errest = końcowy błąd 

    % Przypisanie wartości bazowych do tol i recLev 
    arguments
        f        
        a
        b 
        tol = 10000000000
        recLev = 18    
    end

    % liczymy błąd 
    [T7_7, T8_8] = romberg(f, a, b);
    G17 = g17(f,a,b);
    max_error = calc_max_error(T7_7, T8_8, G17);
    % baza rekurencja
    if recLev <= 0
        Q = T8_8;
        errest = max_error;
        return
    end 
    
    % rekurencja
    if max_error <= tol
        Q = T8_8;
        errest = max_error;
    else
        mid = (a+b)/2;
        [Q_left,errest_left] = span_integral(f,a,mid,tol/2,recLev-1);
        [Q_right,errest_right] = span_integral(f,mid,b,tol/2,recLev-1);
        Q = Q_left + Q_right;
        errest = errest_left + errest_right;
    end


end 