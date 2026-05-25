function [srodki] = kolejnewezly(wezly)
    % Autor Tymon Tumialis
    % Dodajemy wektor bez ostatniego elementu do wektora bez pierwszego ...
    % i dzielimy na 2
    srodki = (wezly(1:end-1) + wezly(2:end)) / 2;
end