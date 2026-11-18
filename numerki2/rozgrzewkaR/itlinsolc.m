function x = itlinsolc(ciA, vicA, b)
% Zadanie ZR
% Tymon Tumialis, 344959
%
% Rozwiązuje układ równań liniowych metodą iteracyjną
%
% WEJŚCIE
% ciA  - indeksy niezerowych wartości w wierszach (n x d)
% vicA - niezerowe wartości macierzy A (n x d)
% b    - wektor prawych stron (n x 1)
% WYJŚCIE
% x    - wyliczony wektor rozwiązań (n x 1)

tolerance = 1e-10;
max_iterations = 500;
n = size(ciA, 1);
x = zeros(n, 1);
diag_A = get_diag(ciA, vicA, n);
inv_d = 1 ./ diag_A;
norm_b = sum(abs(b));

if norm_b == 0
    return;
end

for it = 1:max_iterations
    Ax = sum(vicA .* x(ciA), 2);

    r = b - Ax;
    norm_r = sum(abs(r));

    if norm_r <= tolerance * norm_b
        return;
    end

    x = x + inv_d .* r;
end

end % function