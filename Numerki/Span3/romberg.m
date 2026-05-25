function [T7_7, T8_8] = romberg(f, a, b)
    % Autor Tymon Tumialis
    % Funkcja oblicza kwadraturę Romberga na przedziale a,b
    % a,b = granice przedziały
    % f = funkcja 
    % T7_7 i T8_8 = wartości kwadratury
    n = 8;

    R = zeros(n,n);
    R(1,1) = (b-a)/2 * (f(a) + f(b));
    
    % Liczenie pierwszej kolumny
    power_of_two = 2;
    for k = 2:n
        h = (b - a) / power_of_two;
        sum_f = 0;
        for j = 1:power_of_two/2
            sum_f = sum_f + f(a + (2*j - 1) * h);
        end
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
    T7_7 = R(7,7);
    T8_8 = R(8,8);
    
end % function