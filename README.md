Wieloprocesowy system realizujący komunikację w języku komunikacyjnym Linda
==========================================================================

Projekt został napisany wspólnie z trzema kolegami - Łukaszem Neumannem, Maciejem Kulawikiem i Andrzejem Dawdziukiem.
Użyto języka C++. Komunikacja międzyprocowa została zrealizowana przy pomocy unixowych kolejek komunikatów.
Moje zadanie polegało na stworzeniu parsera i leksera, potrafiącego przekształać napisy (C-stringi) na obiekty krotek i zapytań
o krotki.

Założenia projektu
------------------
Wieloprocesowy system realizujący komunikację w języku komunikacyjnym Linda. Linda realizuje trzy operacje:
output(krotka)
input(wzorzec-krotki, timeout)
read(wzorzec-krotki, timeout)
Komunikacja między-procesowa ma być zrealizowana przez wspólną dla wszystkich procesów przestrzeń krotek. Krotki są tablicami dowolnej długości składającymi się z elementów 3 typów podstawowych: string, integer, float. Przykłady krotek: (1. “abc”, 3.1415, “d”), (10, “abc”, 3.145) lub (2, 3, 1, “Ala ma kota”). Funkcja output umieszcza krotkę w przestrzeni. Funkcja input pobiera i atomowo usuwa krotkę z przestrzeni - wybór krotki następuje poprzez dopasowanie wzorca-krotki. Wzorzec jest krotką, w której dowolne składniki mogą być niewyspecyfikowane: “*” (podany jest tylko typ), lub zadane warunkiem logicznym. Przyjąć warunki: ==, <, <=, >, >=. Przykład input (integer:1, string:*, float:*, string:”d”) - pobierze pierwszą krotkę z przykładu wyżej zaś: input (integer:>0, string:”abc”, float:*, string:*) drugą. Read działa tak samo jak input, lecz nie usuwa krotki z przestrzeni. Read i input zwracają jedną krotkę. Jeśli szukana krotka nie istnieje read i input zawieszają się do czasu pojawienia się danej krotki. 


Interpretacja 
-------------
Końcowy użytkownik biblioteki klienta będzie korzystał z języka C++, natomiast metody, które będzie wywoływał będą przypominały język Linda (w granicach narzuconych przez C++). Dlatego propozycja API:

class LindaClient {
public:
	void init(const std::string& path_to_key);
    std::string read(const std::string query, struct timeval timeout);
    std::string input(const std::string query, struct timeval timeout);
	void output(const std::string tuple);
	void close();
};
gdzie:
path_to_key - ścieżka do pliku w którym znajdują się klucze identyfikujące kolejki komunikatów (wyjaśnione przy serwerze)
query - wzorzec krotki w języku Linda, który będzie wyszukiwany w przestrzeni krotek, np. “integer:1, string:*”
tuple - krotka w języku Linda, która będzie wpisana do przestrzeni krotek, np.
	“1, \“abc\”, 2.12”
napisy zwracane w metodach read i input będą miały format analogiczny do tuple (dla zachowania symetryczności operacji read, input/output), np. “2, \“ijk\”, 5”
Klient może operować na krotkach o liczbie elementów nie większej niż 32
Przykład kodu
LindaClient clientA;
clientA.init(“path/to/key”)
clientA.output(“1, 2, 4.127”)
std::string tuple_read = clientA.read(“int:*, int:>1, float:*”)
clientA.close()

Po takich operacjach, jeśli clientA jest jedynym klientem, to w tuple_read zostanie wpisany napis “1, 2, 4.127”

Architektura
------------
System zostanie zaprojektowany w oparciu o architekturę klient - serwer. Serwer oraz każdy klient uruchamiany jest jako osobny proces. Serwer jest jednowątkowy. System wymaga, żeby użytkownik końcowy najpierw uruchomił proces serwera (dostarczany przez autorów dokumentacji), a następnie napisane przez siebie procesy klientów (wykorzystujące API LindaClient).

Protokół komunikacyjny
---------------------
Klient
------
Klient podpisuje swoim PID wszystkie komunikaty umieszczane w kolejce. Wszystkie komunikaty skierowane do danego klienta (w odpowiedzi na jego zapytanie) są podpisane jego PID (dba o to serwer). Dzięki temu wystarczą tylko dwie kolejki, bo każdy klient może odróżnić komunikaty skierowanego do niego od pozostałych.

Klient umieszcza w kolejce wejściowej nagłówek o stałej długości, w którym podany jest rozmiar właściwego zapytania, czas systemowy wysłania wiadomości oraz ewentualny czas ważności wiadomości (timeout, tylko dla read i input), a następnie umieszcza tam właściwe zapytanie,
w przypadku operacji read i input klient oczekuje aż w kolejce wyjściowej pojawi się nagłówek o stałej długości informujący o rozmiarze właściwej wiadomości lub o przekroczeniu timeout. W przypadku nagłówka informującego o rozmiarze wiadomości Klient oczekuje i pobiera właściwą wiadomość - napis opisujący krotkę w języku Linda.

Idea nagłówka i właściwej wiadomości opiera się na założeniu (spełnionym przez kolejki komunikatów), że jeśli umieścimy w kolejce sekwencyjnie (w jednym wątku) dwie wiadomości, to mamy możliwość odczytania ich po drugiej stronie w takiej samej kolejności (mogą być oczywiście przeplecione wiadomościami od innych procesów). Właściwe wiadomości w tym przypadku to C-stringi, parsowane po stronie serwera na odpowiednie obiekty.

W związku z tym, że komunikaty podpisywane są PID procesu, to klienci powinni wykonywać operacje read, input, output w jednym wątku (lub w swoim programie synchronizować obiekt klasy ClientLinda).


Serwer:
-------
serwer odczytuje kolejne komunikaty z kolejki wejściowej
jeśli napotka nagłówek z danym PID, to wie, że kolejna wiadomość o takim PID będzie zawierała zapytanie właściwe (C-string) o konkretnej długości
jeśli napotka właściwe zapytanie, to sprawdza czy od czasu wysłania wiadomości nie upłynął timeout, jeśli tak to wysyła wiadomość o przekroczeniu tego czasu. W przeciwnym wypadku:
dla zapytania read lub input serwer przesyła do kolejki wyjściowej pasującą krotkę podpisaną PID procesu pytającego. Kiedy nie może znaleźć pasującej krotki, dodaje ją do listy krotek poszukiwanych wraz z PID klienta, który czeka na daną krotkę. Czas od wysłania zapytań oczekujących jest cyklicznie sprawdzany, jeśli przekroczy timeout to wysyłany jest odpowiedni komunikat do klienta
dla zapytania output serwer sprawdza czy krotka jest na liście krotek poszukiwanych, jeśli tak to przesyła ją do kolejki i podpisuje PID poszukującego klienta, jeśli nie to wpisuje do przestrzeni krotek. Zapytanie output nie zwraca odpowiedzi klientowi wykonującemu output

Krotki są umieszczane w kolejce wyjściowej jako C-string i poprzedzane nagłówkiem z informacją o rozmiarze C-string.


Analiza poprawności
-------------------
integralność wiadomości
dzięki strukturze kolejki komunikatów mamy pewność, że serwer zawsze odczyta nagłówek wiadomości albo wiadomość, dla której wcześniej otrzymał nagłówek
określenie nadawcy
wiadomości w kolejce wejściowej są podpisywane przez klientów ich numerem PID (w polu type) --- umożliwia to jednoznaczne określenie nadawcy wiadomości
brak aktywnego oczekiwania po stronie klienta
klient przy zapytaniach input, read zostaje zawieszony na kolejce wyjściowej serwera oczekując na wiadomość o polu type równym numerowi PID tego klienta --- nie występuje aktywne oczekiwanie po stronie klienta
brak “zagłodzenia” procesów
serwer obsługuje po kolei wszystkie komunikaty z kolejki wejściowej, buforując niekompletne wiadomości dla wszystkich procesów --- kolejność obsługi procesów zależy od kolejności przesłania wiadomości
brak aktywnego oczekiwania po stronie serwera
serwer obsługuje nadchodzące komunikaty i zawiesza się jeśli ich nie ma kolejnych, budzony po czasie równym najkrótszemu czasu “przeterminowania” oczekujących zapytań. W szczególności, gdy nie ma oczekujących zapytań serwer nie będzie budzony aż do nadejścia nowych komunikatów. --- Po stronie serwera nie występuje aktywne oczekiwanie, a wiadomości o “przeterminowaniu” zapytań będą dostarczane w odpowiednim czasie
zapewnienie czasu “przeterminowania” (timeout)
klient zostaje “obudzony” po czasie nie większym niż t_pesymistyczne = timeout + czas oczekiwania wiadomości w kolejce wejściowej + czas obsługi zapytania + czas przeszukania zapytań oczekujących + czas wysłania komunikatu “wakeup” do klienta. Zakładając, że timeout jest dużo większą wartością od reszty składników, średni czas oczekiwania będzie w przybliżeniu równy wartości timeout  

Jeszcze raz o serwerze
----------------------
Przy uruchomieniu serwer korzystając z api systemowego tworzy dwie kolejki komunikatów:
Jedną kolejkę "wejściową" (channel_in) - za jej pomocą klienci przesyłają komunikaty dla serwera
Drugą kolejkę "wyjściową" (channel_out) - za jej pomocą serwer przesyła komunikaty dla klientów
Numery identyfikacyjne kolejek otrzymane od systemu serwer zapisuje do pliku o ustalonej lub ustawionej w konfiguracji ścieżce.

Następnie serwer przechodzi w tryb obsługi komunikacji międzyprocesowej. Podczas realizacji głównej pętli, serwer korzysta z modułu parsującego, który zamienia C-stringi na odpowiednie obiekty klasy Tuple lub Query. 
