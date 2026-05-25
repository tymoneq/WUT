% =========================================================================
% SPRAWDZARKA: TEST SZYBKOŚCI I POPRAWNOŚCI FUNKCJI LOGSIN
% =========================================================================
clear; clc; close all;

disp('--- ROZPOCZYNAM TESTY ---');
for iteration = 1:10
    %% 1. TEST POPRAWNOŚCI (DLA DUŻYCH X)
    % Sprawdzamy, czy dla bezpiecznych wartości funkcje zwracają to samo.
    x_safe = linspace(1.5, 4, 1000); % Wartości z dala od zera
    y_opt_safe = logsin(x_safe);
    y_nai_safe = logsin_naiwny(x_safe);

    max_blad = max(abs(y_opt_safe - y_nai_safe));
    fprintf('1. Zgodność matematyczna dla |x| > 1: \n');
    fprintf('   Maksymalna różnica między kodami wynosi: %e\n', max_blad);
    if max_blad < 1e-14
        fprintf('   -> SUKCES: Obie funkcje liczą to samo!\n\n');
    else
        fprintf('   -> BŁĄD: Różnica jest zbyt duża!\n\n');
    end


    %% 2. TEST STABILNOŚCI NUMERYCZNEJ (DLA MALUTKICH X)
    % Tu naiwny wzór powinien się zepsuć, a nasz działać idealnie.
    x_tiny = linspace(-1e-3, 1e-3, 10000);
    y_opt_tiny = logsin(x_tiny);
    y_nai_tiny = logsin_naiwny(x_tiny);

    % Rysujemy wykres, aby udowodnić "catastrophic cancellation"
    % figure('Name', 'Dowód na wyższość zoptymalizowanego kodu');
    % plot(x_tiny, y_nai_tiny, 'r-', 'LineWidth', 1); hold on;
    % plot(x_tiny, y_opt_tiny, 'b-', 'LineWidth', 2);
    % grid on;
    % legend('Wzór naiwny (szum i błędy)', 'Wzór zoptymalizowany (idealnie płaski)', 'Location', 'best');
    % title('Zachowanie funkcji bardzo blisko zera (x \in [-0.001, 0.001])');
    % xlabel('x'); ylabel('f(x)');

    fprintf('2. Stabilność numeryczna: \n');
    fprintf('   Wygenerowano wykres. Zobaczysz na nim, jak naiwny wzór "wariuje"\n');
    fprintf('   blisko zera (kolor czerwony), podczas gdy Twój kod działa stabilnie (niebieski).\n\n');


    %% 3. TEST SZYBKOŚCI (BENCHMARK WIDELCOWY)
    N = 10000000; % 10 milionów punktów testowych
    x_speed = (rand(1, N) - 0.5) * 8; % Losowe liczby z zakresu [-4, 4]

    fprintf('3. Test szybkości dla wektora %d elementów...\n', N);

    % Mierzymy czas wzoru naiwnego
    tic;
    logsin_naiwny(x_speed);
    czas_naiwny = toc;

    % Mierzymy czas Twojego zoptymalizowanego kodu
    tic;
    logsin(x_speed);
    czas_zoptymalizowany = toc;

    fprintf('   Czas wykonania wzoru naiwnego:     %.4f sekund\n', czas_naiwny);
    fprintf('   Czas wykonania Twojego kodu:       %.4f sekund\n', czas_zoptymalizowany);
    disp('-------------------------');
end
% =========================================================================
% LOKALNE FUNKCJE UŻYWANE W SKRYPCIE
% =========================================================================

% Zwykły, bezpośredni wzór (psuje się blisko zera)
function y = logsin_naiwny(x)
    y = (9*log(1+ x.^2/9) - x.*sin(x))./x.^4;
end
