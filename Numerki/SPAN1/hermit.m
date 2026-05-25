function values = hermit(X, Y, k1, dFL, dFR)
% Autor: Yegor Nepokulchytskyi
% Funkcja wyznacza tabelę ilorazów różnicowych dla węzłów wielokrotnych
% X wektor węzłów, Y wektor wartości funkcji w węzłach
% k1 liczba pochodnych w lewym skrajnym węźle
% dFL i DFR wektory kolejnych pochodnych w lewym i prawym skrajnym węźle
% values wyznaczona macierz ilorazów różnicowych

len = length(X);
values = zeros(len, len);
values(:, 1) = Y(:);
factorial_v = 1;

for i = 2:len
    for j = len:-1:i
        if X(j) == X(j-i+1) % Obsługa pochodnych
            if j <= k1 + 1
                values(j, i) = dFL(i-1) ./ factorial_v;
            else
                values(j, i) = dFR(i-1) ./ factorial_v;
            end
        else % Standardowy wzór Newtona
            values(j, i) = (values(j, i-1) - values(j-1, i-1)) ./ ...
                (X(j) - X(j-i+1));
        end
    end
    
    factorial_v = i * factorial_v;
end