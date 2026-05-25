function [aktualne_wezly,wspolczyniki] = adaptinterp(f,a,b,n,K)
    % Autor Tymon Tumialis
    % funkcja oblicza wartość interpolacji Lagranga w K krokach
    % f-funkcja ciągła, a,b - końce przedziału,
    % n-ilość początkowych punktów interpolacji K-ilość kroków
   
    aktualne_wezly = linspace(a,b,n);
    % iteracja po k krokach
    for k=1:K
        wspolczyniki = interpolation(f,aktualne_wezly);
        kolejne_wezly_k_krok = kolejnewezly(aktualne_wezly);
        wartosci_w_nowych_wezlach = hornerek(wspolczyniki, kolejne_wezly_k_krok,aktualne_wezly);
        aktualne_wezly = error_calc(f,wartosci_w_nowych_wezlach,kolejne_wezly_k_krok,aktualne_wezly);
      
    end
    wspolczyniki = interpolation(f, aktualne_wezly);


end %function