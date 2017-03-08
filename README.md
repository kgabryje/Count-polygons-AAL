Autor: Kamil Gabryjelski

1. Specyfikacja problemu:
Dany jest zbiór odcinków na płaszczyźnie w postaci uporządkowanych czwórek (x1,y1,x2,y2).
Część z odcinków może się między sobą przecinać.
Należy zliczyć liczbę wszystkich zamkniętych wielokątów powstałych na skutek przecinania się odcinków.

2. Uruchamianie:
a) Zliczanie wielokątów utworzonych przez dane odcinki z pliku:
path/to/program/AAL import_segments -i input_file -o output_file -a algorithm
input_file - nazwa pliku z danymi odcinkami
output_file - nazwa pliku, do którego zostanie zapisany wynik działania programu
algorithm - nazwa algorytmu. Dostępne opcje: tarjan LUB dfs

b) Zliczanie wielokątów utworzonych przez losowe odcinki:
path/to/program/AAL random_segments -i input_file -o output_file -a algorithm -q quantity
input_file - nazwa pliku, do którego zostaną wygenerowane odcinki
output_file - nazwa pliku, do którego zostanie zapisany wynik działania programu
algorithm - nazwa algorytmu. Dostępne opcje: tarjan LUB dfs
quantity - ilość odcinków do wygenerowania

c) Zliczanie cykli w losowo wygenerowanym grafie z daną liczbą wierzchołków i krawędzi:
path/to/program/AAL random_graph -v vertices -e edges -o output_file -a algorithm
vertices - ilość wierzchołków
edges - ilość krawędzi
output_file - nazwa pliku, do którego zostanie zapisany wynik działania programu
algorithm - nazwa algorytmu. Dostępne opcje: tarjan LUB dfs

d) Generowanie statystyk. Zostanie wygenerowana dana ilość grafów z daną ilością
krawędzi i wierzchołków. Na ekranie zostanie wyświetlona tabela, której kolumnami
będą czas wykonania i parametr q w zależności od zmiennej, według której liczona jest złożoność.
path/to/program/AAL get_statistics -v vertices -e edges -o output_file -a algorithm -r repetitions
vertices - ilość wierzchołków
edges - ilość krawędzi
output_file - nazwa pliku, do którego zostanie zapisany wynik działania programu
algorithm - nazwa algorytmu. Dostępne opcje: tarjan LUB dfs
repetitions - ilość grafów, na podstawie których wygenerowane będą statystyki

3. Format danych w pliku wejściowym:
Dane odcinków należy podawać w formacie:
x1 y1 x2 y2
gdzie x1, y1 to współrzędne pierwszego punktu, a x2, y2 to współrzędne drugiego punktu.
Dane każdego odcinka należy wprowadzać w nowej linii.

4. Opis metody rozwiązania
Wyliczane są punkty przecięć wszystkich odcinków. Punkty przecięć są wierzchołkami
grafu nieskierowanego. Każde 2 punkty leżące na jednym odcinku obok siebie (między nimi
nie ma innego punktu) tworzą krawędź. W utworzonym w ten sposób grafie zliczane są
cykle. Ilość znalezionych cykli jest odpowiedzią na pytanie, ile wielokątów tworzą odcinki.

Do zliczania cykli zostały użyte zmodyfikowane algorytmy DFS oraz Tarjana, których
działanie opisane jest w dokumentacji.

5. Użyte struktury danych:
Do przechowywania ścieżki pojedynczego cyklu używany jest std::vector. Do przechowywania
wszystkich znalezionych cykli używany jest std::unordered_set. Uzasadnienie użycia
tych struktur znajduje się w dokumentacji.

6. Listing klas i plików
Point.h / Point.cpp - klasa odwzorowująca punkt w przestrzenie 2-wymiarowej
Segment.h / Segment.cpp - klasa odwzorowująca odcinek w przestrzeni 2-wymiarowej,
składający się z dwóch punktów (klasa Point)
Graph_DFS.h / Graph_Tarjan.cpp - klasa odworowująca graf z zaimplementowanymi metodami pozwalającymi
zliczać cykle w grafie algorytmem DFS
Graph_Tarjan.h / Graph_Tarjan.cpp  - klasa odworowująca graf z zaimplementowanymi metodami pozwalającymi
zliczać cykle w grafie algorytmem Tarjana
options_parser.h - zawiera funkcje realizujące interfejs użytkownika, oparte na bibliotece getopt.h
utilities.h - zawiera funkcje służące do generacji zadanej ilości losowych odcinków
oraz do znajdowania wszystkich punktów przecięć (poprzez przetwarzanie wszystkich
kombinacji odcinków i sprawdzaniu, czy dane 2 odcinki się przecinają).
main.cpp - główna funkcja programu

7. Kompilacja
Aby skompilować program, należy wykonać polecenie make. Aby usunąć pliki *.o, należy
wykonać polecenie make clean. Aby usunąc pliki *.o oraz plik wykonywalny, należy wykonać
polecenie make clean_all
