function [x, c] = adaptinterp(f, a, b, n, K)
% Autor: Szymon Straszak
% Funkcja wyznacza wezly i wspolczynniki wielomianu adaptacyjnie.
% f - uchwyt do funkcji, a, b - konce przedzialu interpolacji.
% n - poczatkowa liczba wezlow, K - liczba etapow dodawania wezlow.
% Zwraca: x - ostateczny wektor wezlow, c - wspolczynniki Newtona.

x = linspace(a, b, n);

for k = 1:K
    midpts = (x(1:end-1) + x(2:end)) / 2;
    c_temp = div_diff(x, f(x));
    p_vals = eval_newt(midpts, x, c_temp);
    
    errs = abs(f(midpts) - p_vals);
    [~, idx] = sort(errs, 'descend');
    
    x = [x, midpts(idx(1:2))];
    x = sort(x);
end

c = div_diff(x, f(x));