# Organ - Część aplikacji

Część aplikacji to oprogramowanie przede wszystkim dedykowane do mojego rozwiązania, ale również bez problemu działające z innymi (konsole *Johannus*, *Tonus* itp., również zwykłe kontrolery MIDI).

Czego nie ma w dostępnych obecnie aplikacjach (*Hauptwerk*, *GrandOrgue*, *GreatOrgan*, *Sweelinq*)? Modułowości. Każda paczka organów to osobny byt, bez możliwości zmian. Również sama aplikacje są często bardzo złożone, posiadają mnóstwo funkcji z których się nie korzysta.

Chcę, by moja aplikacja ma na celu dostarczyć tę modułowość - użytkownicy będą mogli pobrać tylko to, czego potrzebują:
1. Głosy organowe - potrzebujesz do grania tylko pryncypału 8' oraz Subbasu 16'? Nie ma sprawy
2. Efekty dźwiękowe - EQ, Pogłos - będzie można pobrać tylko w razie potrzeby
3. Liczba klawiatur, połączenia, ilość żaluzji, inne pomoce, głosy w danym manuale, które głosy obsługuje żaluzja - wszystko z możliwością łatwej konfiguracji

Dodatkowo chcę dać możliwość tworzenia własnych paczek konfiguracyjnych do zapisania czy udostępniania oraz możliwość dodania głosu jako paczkę we własnym zakresie.

## Technologie
Ważna jest optymalizacja i szybkość działania, zatem postawię na:
- **C/C++** - język programowania
- **Python** - GUI, konkretnie z modułem `PySide6` - innymi słowy, `Qt`.


## Inne informacje

W tej sekcji zawarłem wszystkie dodatkowe informacje, które mogą okazać się przydatne przy odkrywaniu aplikacji:
- W folderze `code/Organ/gui` jest plik `.html`, który służy jako wirtualny designer - takie samo GUI będę chciał stworzyć w samej aplikacji, więc może w przyszłości wykorzysta się to jako niejakie _demo_ produktu.