function test_P1_z36()
% Zadanie 36
% Tymon Tumialis, 344959
%
% Skrypt testujący dla programu głównego P0_z36_Kowalski_123456.
% Wyświetla opis testów, wartości spodziewane i wyliczone oraz bada
% zbieżność metody całkowania bez dokonywania oceny wyników.
% Funkcja jest bezargumentowa i stronicuje ekrany co max 18 wierszy.

format long;

% ---------------------------------------------------------------------
% EKRAN 1: Test 1 - Funkcja stała f(x, y) = 1 (Pole obszaru)
% ---------------------------------------------------------------------
fprintf('===========================================================\n');
fprintf('  PROGRAM TESTUJĄCY DLA ZADANIA 36 (KWADRATURA GAUSSA)\n');
fprintf('===========================================================\n\n');
fprintf('TEST 1: Całkowanie funkcji stałej f(x, y) = 1\n');
fprintf('Opis: Sprawdzenie poprawności wyliczania pola koła D.\n');
fprintf('Spodziewana wartość dokładna: pi = 3.141592653589793\n\n');

f1 = @(x, y) 1;
q1 = P1_z36_Tumialis_344959(f1, 10, 10);
q1_dokl = pi;
err1 = abs(q1 - q1_dokl);

fprintf('Liczba podprzedziałów (n1 x n2): 10 x 10\n');
fprintf('Wynik obliczony: %.15f\n', q1);
fprintf('Wynik dokładny:   %.15f\n', q1_dokl);
fprintf('Błąd bezwzględny: %.15e\n\n', err1);

fprintf('Naciśnij dowolny klawisz, aby przejść do kolejnego ekranu...');
pause;
fprintf('\n\n');

% ---------------------------------------------------------------------
% EKRAN 2: Test 2 (f = x^2 + y^2) oraz Test 3 (f = x^2)
% ---------------------------------------------------------------------
fprintf('===========================================================\n');
fprintf('TEST 2: Funkcja f(x, y) = x^2 + y^2 (symetria promieniowa)\n');
fprintf('Spodziewana wartość dokładna: pi / 2 = 1.570796326794897\n\n');

f2 = @(x, y) x.^2 + y.^2;
q2 = P1_z36_Tumialis_344959(f2, 10, 10);
q2_dokl = pi / 2;
err2 = abs(q2 - q2_dokl);

fprintf('Wynik obliczony: %.15f\n', q2);
fprintf('Wynik dokładny:   %.15f\n', q2_dokl);
fprintf('Błąd bezwzględny: %.15e\n\n', err2);

fprintf('TEST 3: Funkcja f(x, y) = x^2\n');
fprintf('Spodziewana wartość dokładna: pi / 4 = 0.785398163397448\n\n');

f3 = @(x, y) x.^2;
q3 = P1_z36_Tumialis_344959(f3, 10, 10);
q3_dokl = pi / 4;
err3 = abs(q3 - q3_dokl);

fprintf('Wynik obliczony: %.15f\n', q3);
fprintf('Wynik dokładny:   %.15f\n', q3_dokl);
fprintf('Błąd bezwzględny: %.15e\n\n', err3);

fprintf('Naciśnij dowolny klawisz, aby przejść do kolejnego ekranu...');
pause;
fprintf('\n\n');

% ---------------------------------------------------------------------
% EKRAN 3: Test 4 (Funkcja nieparzysta) oraz Test 5 (Zbieżność)
% ---------------------------------------------------------------------
fprintf('===========================================================\n');
fprintf('TEST 4: Funkcja nieparzysta f(x, y) = x\n');
fprintf('Spodziewana wartość dokładna: 0.0\n\n');

f4 = @(x, y) x;
q4 = P1_z36_Tumialis_344959(f4, 10, 10);
err4 = abs(q4 - 0);

fprintf('Wynik obliczony: %.15e\n', q4);
fprintf('Wynik dokładny:   0.000000000000000e+00\n');
fprintf('Błąd bezwzględny: %.15e\n\n', err4);

fprintf('TEST 5: Badanie zbieżności dla f(x,y) = (x^2 + y^2)^2\n');
fprintf('Opis: Funkcja stopnia 5 (brak dokładności dla kwadratury 2-pt).\n');
fprintf('Spodziewana wartość dokładna: pi / 3 = 1.047197551196598\n\n');
fprintf('Węzły (n1 x n2) |  Wynik obliczony   |  Błąd bezwzględny\n');
fprintf('-----------------------------------------------------------\n');

f5 = @(x, y) (x.^2 + y.^2).^2;
q5_dokl = pi / 3;
N_vec = [1, 2, 4, 8, 16,32,64];

for idx = 1:length(N_vec)
    n_val = N_vec(idx);
    q_conv = P1_z36_Tumialis_344959(f5, n_val, n_val);
    err_conv = abs(q_conv - q5_dokl);
    fprintf('%5d x %-5d | %.14f | %.14e\n', ...
        n_val, n_val, q_conv, err_conv);
end

fprintf('\nKoniec testów. Naciśnij dowolny klawisz...');
pause;
fprintf('\n');