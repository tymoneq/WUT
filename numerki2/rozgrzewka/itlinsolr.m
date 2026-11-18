function x = itlinsolr(riA, virA, b)
% Zadanie ZC
% Tymon Tumialis, 344959
%
% Rozwiązuje układ równań liniowych metodą iteracyjną
% dla macierzy z dominującą przekątną kolumnowo.
%
% WEJŚCIE
% riA  - indeksy wierszy dla niezerowych wartości kolumn (n x d)
% virA - niezerowe wartości macierzy A (n x d)
% b    - wektor prawych stron (n x 1)
% WYJŚCIE
% x    - wyliczony wektor rozwiązań (n x 1)

tolerance = 1e-10;
max_iterations = 500;
n = size(riA, 1);
x = zeros(n, 1);
diag_A = get_diag(riA, virA, n);
inv_d = 1 ./ diag_A;
norm_b = sum(abs(b));

if norm_b == 0
    return;
end

for it = 1:max_iterations
    V = virA .* x;
    Ax = accumarray(riA(:), V(:), [n, 1]);

    r = b - Ax;
    norm_r = sum(abs(r));

    if norm_r <= tolerance * norm_b
        return;
    end

    x = x + inv_d .* r;
end

end % function