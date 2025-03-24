# Organ - Część wbudowana

## Opis
Część wbudowana to wszystkie sprawy sprzętowe - mikrokontrolery, komunikacja między nimi itd.

Graficznie, wszystko opisane jest w folderze *design*. Komunikacja, projekty, matryce, schematy (okablowanie i komunikacja). Będzie to jednak uzupełnianie w trakcie powstawania projektu, więc jeżeli o czymś mowa jest, a nie ma tego nigdzie - wystarczy poczekać.

**WAŻNE!** Aby projekt się skompilował, przenieś wszystkie pliki z folderu `code/lib/` do folderu `Libraries/` z Arduino IDE.

## Technologia
Stawiam przede wszystkim na uniwersalność - dzięki temu produkt znajdzie dużo szersze zastosowanie, bez zamknięcia do własnego ekosystemu.
- **C** - język programowania. Dlaczego? Ma wszystko, co jest potrzebne, jest wspierany przez praktycznie wszystkich producentów mikrokontrolerów, jakich tylko można znaleźć.
- **Standard MIDI** - uniwersalny, umożliwi komunikację z dowolnym innym programem (*GrandOrgue*, *Hauptwerk*).

## Mikrokontrolery + podłączone urządzenia
### Manuał

### Pedał

### Pistony głosów

### Pistony ręczne

### Pistony nożne

### Żaluzje
#### Mikrokontroler
[Arduino Nano](https://botland.com.pl/arduino-nano-oryginalne-plytki/14763-arduino-nano-every-ze-zlaczami-abx00033-7630049201552.html) - 

#### Inne
[10x kondensator `100nF`](https://botland.com.pl/kondensatory-ceramiczne-tht/210-kondensator-ceramiczny-100nf50v-tht-10szt-5903351248198.html?cd=18298825651&ad=&kd=&gad_source=1&gclid=CjwKCAjwp8--BhBREiwAj7og12hvVONJ-0e72-lc_Jn_fhFc_a7XO5Rhh01sOe4hEPLNhBenLXXhnBoCO3gQAvD_BwE) - ma za zadanie zapobiegać drganiom styków potencjometrów, wygładzając przy tym sygnał.

### Główny
#### Mikrokontroler
[Teensy `4.0`](https://botland.com.pl/plytki-zgodne-z-arduino-sparkfun/21647-teensy-40-arm-cortex-m7-zgodny-z-arduino-wersja-ze-zlaczami-sparkfun-dev-16997.html)

[Teensy `4.1`](https://botland.com.pl/plytki-zgodne-z-arduino-sparkfun/20186-teensy-41-arm-cortex-m7-ze-zlaczami-zgodny-z-arduino-sparkfun-dev-16996-714833879473.html)\
[Specyfikacja I/O](https://www.pjrc.com/teensy/card11a_rev4_web.pdf)

Musi być szybki oraz zapewniać MIDI-USB. Dodatkowo, wiele pinów UART jest potrzebnych do obsługi wielu pod-kontrolerów na raz. Teensy `4.0` obsługuje `6`, Teensy `4.1` obsługuje `8`.