function test_gladkosc()
% Zadanie 36
%Tymon Tumialis, 344959
%
% Skrypt badający wpływ gładkości funkcji podcałkowej na
% szybkość zbieżności 2-punktowej kwadratury Gaussa.

format long;

% Funkcje gładkie (klasy C nieskończoność)
f1 = @(x, y) (x.^2 + y.^2).^2;
f2 = @(x, y) exp(x + y);
f3 = @(x, y) sin(x) .* cos(y);
f4 = @(x, y) 1 ./ (x.^2 + y.^2 + 7);

% Funkcje niegładkie (osobliwości lub "ostrza" w obszarze)
f5 = @(x, y) abs(x) + abs(y);
f6 = @(x, y) sqrt(x.^2 + y.^2);
f7 = @(x, y) (x.^2 + y.^2).^(1/3);

% Wywołania testów z nazwami dla czytelności ekranu
test_f(f1, 'f(x,y) = (x^2 + y^2)^2', 'GLADKA');
test_f(f2, 'f(x,y) = exp(x+y)', 'GLADKA');
test_f(f3, 'f(x,y) = sin(x)*cos(y)', 'GLADKA');
test_f(f4, 'f(x,y) = 1 / (x^2 + y^2 + 7)', 'GLADKA');
test_f(f5, 'f(x,y) = |x| + |y|', 'NIEGLADKA (ostrza na osiach)');
test_f(f6, 'f(x,y) = sqrt(x^2 + y^2)', 'NIEGLADKA (szpic w srodku)');
test_f(f7, 'f(x,y) = (x^2 + y^2)^(1/3)', 'NIEGLADKA (osobliwa pochodna)');

end % function

function test_f(f, nazwa, typ)
% Zadanie 36
%Jan Tumialis, 344959
%
% Funkcja pomocnicza wyświetlająca tabelę błędów dla podanej funkcji.

fprintf('===========================================================\n');
fprintf('TEST GLADKOSCI: %s\n', typ);
fprintf('Funkcja: %s\n', nazwa);
fprintf('-----------------------------------------------------------\n');

% Wartość referencyjna (bardzo gęsta siatka) do wyliczenia błędu
q_ref = P1_z36_Tumialis_344959(f, 150, 150);

fprintf('  Siatka  |  Wynik obliczony   | Blad (wzgl. siatki 150x150)\n');
fprintf('-----------------------------------------------------------\n');

% Zamiast siatek 1,2,3,4,5 używamy potęg 2 do analizy zbieżności
N_vec = [2, 4, 8, 16, 32];

for n = N_vec
    q_num = P1_z36_Tumialis_344959(f, n, n);
    err = abs(q_num - q_ref);
    fprintf('%2d x %-2d  | %.14f | %.14e\n', n, n, q_num, err);
end

fprintf('\nNacisnij dowolny klawisz, aby przejsc do kolejnego ekranu...\n');
pause;
fprintf('\n\n');

end % function