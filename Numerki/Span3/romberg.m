function [T7_7, T8_8] = romberg(f, a, b)
    % Autor Tymon Tumialis
    % Funkcja oblicza kwadraturę Romberga na przedziale a,b
    % a,b = granice przedziały
    % f = funkcja 
    % T7_7 i T8_8 = wartości kwadratury
    n = 9;

    R = zeros(n,n);
    R(1,1) = (b-a)/2 * (f(a) + f(b));
    
    % Liczenie pierwszej kolumny
    power_of_two = 2;
    for k = 2:n
        h = (b - a) / power_of_two;
        
        j_vec = 1:(power_of_two/2);           
        wezly = a + (2*j_vec - 1) * h;        
        sum_f = sum(f(wezly));                
       
        R(k, 1) = 0.5 * R(k-1, 1) + h * sum_f;
        power_of_two = power_of_two * 2;
    end

    % Liczenie reszty tabeli
    power_of_four = 4;
    for col = 2:n
        for row = n:-1:col
            R(row,col) = (power_of_four * R(row,col-1) - R(row-1, col-1)) / (power_of_four - 1);
        end
        power_of_four = power_of_four * 4;
    
    end
    T7_7 = R(8,8);
    T8_8 = R(9,9);
    
end % function