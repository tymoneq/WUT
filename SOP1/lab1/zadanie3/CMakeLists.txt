cmake_minimum_required(VERSION 3.15)
project(zadanie3 C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(app main.c)

# Flagi kompilatora do wykrywania wycieków i błędów pamięci
target_compile_options(app PRIVATE 
    -g                       # Generuje symbole debugowania (niezbędne do pokazania numeru linijki z wyciekiem)
    -fsanitize=address       # Włącza AddressSanitizer (wykrywa m.in. wycieki pamięci)
    -fno-omit-frame-pointer  # Poprawia czytelność stosu wywołań (call stack) w logach błędu
)

# Flagi linkera (muszą być takie same jak dla kompilatora przy użyciu sanitizerów)
target_link_options(app PRIVATE 
    -fsanitize=address
)