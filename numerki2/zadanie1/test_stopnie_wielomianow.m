function test_stopnie_wielomianow

format long;

fprintf('===========================================================\n');
fprintf('TEST: Badanie stopnia dokładności kwadratury (Rząd wielomianów)\n');
fprintf('Opis: Sprawdzamy całkę z f(x,y) = (x^2 + y^2)^m.\n');
fprintf('Po uwzględnieniu jakobianu stopień zmiennej "u" wynosi 2m+1.\n');
fprintf('Dla 2-punktowej kwadratury Gaussa dokładność kończy się na 3.\n\n');
fprintf('   m  | Stopień u | Błąd bezwzględny (dla siatki 1x1)\n');
fprintf('-----------------------------------------------------------\n');

% Generator funkcji testowych zależnych od parametru m
f_gen = @(m) @(x,y) (x.^2 + y.^2).^m;

for m = 0:10
    % 1. Wygenerowanie odpowiedniego wielomianu
    f_test = f_gen(m);

    % 2. Obliczenie całki numerycznej BEZ dzielenia obszaru (siatka 1x1)
    q_num = P1_z36_Tumialis_344959(f_test, 1, 1);

    % 3. Obliczenie wartości dokładnej
    % Analityczna całka z r^(2m) po kole to pi / (m + 1)
    q_dokl = pi / (m + 1);

    % 4. Obliczenie błędu
    err = abs(q_num - q_dokl);
    stopien_u = 2 * m + 1;

    fprintf(' %2d   | %9d | %.14e\n', m, stopien_u, err);
end

fprintf('Naciśnij dowolny klawisz, aby przejść do kolejnego ekranu...');
pause;
fprintf('\n\n');

fprintf('===========================================================\n');
fprintf('TEST: Badanie stopnia dokładności kwadratury (Rząd wielomianów)\n');
fprintf('Opis: Sprawdzamy całkę z f(x,y) = (x^2 + y^2)^m.\n');
fprintf('Po uwzględnieniu jakobianu stopień zmiennej "u" wynosi 2m+1.\n');
fprintf('Dla 2-punktowej kwadratury Gaussa dokładność kończy się na 3.\n\n');



for n=2:10
    fprintf('   m  | Stopień u | Błąd bezwzględny (dla siatki %2d x%2d)\n',n,n);
    fprintf('-----------------------------------------------------------\n');
    for m = 0:10
        % 1. Wygenerowanie odpowiedniego wielomianu
        f_test = f_gen(m);

        % 2. Obliczenie całki numerycznej BEZ dzielenia obszaru (siatka nxn)
        q_num = P1_z36_Tumialis_344959(f_test, n, n);

        % 3. Obliczenie wartości dokładnej
        % Analityczna całka z r^(2m) po kole to pi / (m + 1)
        q_dokl = pi / (m + 1);

        % 4. Obliczenie błędu
        err = abs(q_num - q_dokl);
        stopien_u = 2 * m + 1;

        fprintf(' %2d   | %9d | %.14e\n', m, stopien_u, err);
    end
    fprintf('Naciśnij dowolny klawisz, aby przejść do kolejnego ekranu...');
    pause;
    fprintf('\n\n');
end
    fprintf('   m  | Stopień u | Błąd bezwzględny (dla siatki 100x100)\n');
for m = 0:10
    % 1. Wygenerowanie odpowiedniego wielomianu
    f_test = f_gen(m);

    % 2. Obliczenie całki numerycznej BEZ dzielenia obszaru (siatka nxn)
    q_num = P1_z36_Tumialis_344959(f_test, 100, 100);

    % 3. Obliczenie wartości dokładnej
    % Analityczna całka z r^(2m) po kole to pi / (m + 1)
    q_dokl = pi / (m + 1);

    % 4. Obliczenie błędu
    err = abs(q_num - q_dokl);
    stopien_u = 2 * m + 1;

    fprintf(' %2d   | %9d | %.14e\n', m, stopien_u, err);
end
fprintf('Naciśnij dowolny klawisz, aby przejść do kolejnego ekranu...');
pause;
fprintf('\n\n');


end