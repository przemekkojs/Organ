# Organ
Projekt ten ma na celu próbę stworzenia własnego kompletnego systemu wirtualnych organów - bazujących na samplach (sample-based). Składa się z dwóch części:
1. Część wbudowana - zajmować się będzie sprawami sprzętowymi - żeby organy działały. Tutaj znajdują się wszelkie informacje nt. działania manuałów, pedału, pistonów itd. Na wyjściu będą jedynie zdarzenia MIDI.
2. Część aplikacji - potrzebna jest aplikacja na komputer, która umożliwiałaby czytanie wychodzących zdarzeń MIDI (MIDI-events), wysyłanie własnych oraz reagowaniem na nie. Również żaden mikro-kontroler nie jest na tyle potężny, żeby *udźwignąć* kilkadziesiąt GB sampli, potężnej polifonii itd.

O każdym z podsystemów można przeczytać w odpowiednim katalogu. **Embedded** - część wbudowana, **App** - część aplikacji.

Ze względu na charakterystykę działania (wysyłanie i czytanie komunikatów MIDI), część wbudowana możne komunikować się bez problemu z takimi aplikacjami jak GrandOrgue czy Hauptwerk.

## Cel projektu
Celem projektu jest stworzenie częściowo open-source'owej alternatywy dla wymienionego wyżej oprogramowania, wraz z całym dedykowanym sprzętem. Takie rozwiązanie z pewnością sprawdzi się w wielu sytuacjach, w których cena może być problematyczna.

Mam zamiar korzystać przede wszystkim ze sprawdzonych rozwiązań, w przystępnej cenie - tak, by wyszło porządnie i tanio zarazem.

## Technologie
W rozwiązaniach tego typu liczy się przede wszystkim szybkość oraz odporność na błędy. Część wbudowana aplikacji będzie zatem operować w języku C, a część aplikacji w C/C++. Przy odpowiednim zarządzaniu pamięcią oraz zastosowaniu odpowiednich technik programowania, będzie to aplikacja *nie do zdarcia*.

Jednym z moich celów jest postawienie na lekkość aplikacji, w połączeniu z nowoczesnym oraz intuicyjnym UI. Pozwoli to na działanie nawet na starszym sprzęcie, tym bardziej w połączeniu ze lżejszymi zestawami instrumentów.

## Inne informacje
Po więcej informacji nt. projektu zapraszam o plików *Changelog.md* oraz *Release Notes.md*. Pierwszy zawiera informacje o zmianach w każdym z ważniejszych commitów, a drugi o zmianach w każdym działającym wydaniu.
