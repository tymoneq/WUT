function [w] = hornerek(wspolczyniki, kolejne_wezly_k_krok, poprzednie_wezly)
    % Autor Tymon Tumialis
    % funkcja oblicza wyniki w węzłach za pomoca uogolnionego schematu hornera
    
    N = length(wspolczyniki);
    % wektor w trzyma obliczone wartości funkcji 
    w = wspolczyniki(N) * ones(size(kolejne_wezly_k_krok));
    
    % Główna pętla uogólnionego schematu Hornera
    for k = N-1:-1:1
        w = wspolczyniki(k) + (kolejne_wezly_k_krok - poprzednie_wezly(k)) .* w;
    end
    
end %function