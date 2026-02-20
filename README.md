# BlackBox-Game_PG

**Cel** <br>
Implementacja aplikacji konsolowej pozwalającej na rozgrywkę gry Black Box. Aplikacja powinna 
pozwalać na rozegranie kilku etapów o różnym stopniu trudności. Etapy różnią się wielkością planszy i 
liczbą ukrytych atomów. Plansze mogą mieć rozmiary 5×5, 8×8, 10×10. Liczba atomów może wynosić 
od 3 (dla najmniejszej planszy) do 8 dla największej planszy. Atomy ukryte na planszy powinny być 
rozmieszczone w sposób losowy. Dla każdego etapu na ekranie powinna być wyświetlana liczba 
ukrytych atomów. Strzały w kierunku atomów można wykonywać z pozycji każdej ściany. Każdy strzał 
powinien być numerowany. Tym samym numerem powinien być oznaczony wylot promienia. Oprócz 
tego powinno być oznaczone trafienie atomu (H) i odbicie promienia (R). Przypuszczalne położenie 
atomów oznaczamy małą literą o. Powinna być możliwa zmiana/usunięcie przypuszczalnego położenia 
atomów. Gra powinna umożliwić zaznaczenie przypuszczalnej pozycji atomów, równej liczbie ukrytych 
atomów dla danego etapu. Każdy etap jest oceniany pod względem liczby poprawnie zaznaczonych 
atomów. Jeśli gracz stwierdzi, że dalsza rozgrywka nie ma już sensu, może zrestartować aktualny etap. 
Jeśli gracz zaznaczy przypuszczalne położenie wszystkich atomów, powinien użyć klawisza k (koniec), 
wtedy program powinien wyświetlić położenie ukrytych atomów i liczbę. W przypadku poprawnego 
oznaczenia położenia atomu litera o zamienia się na O, w przypadku błędnego oznaczenia położenia, o 
zamienia się na X, a literą O oznaczone jest poprawne położenie atomu na planszy. Dodatkowo na 
ekranie powinna być wyświetlona liczba poprawnie zaznaczonych atomów. Z dowolnego etapu gry 
powinno być możliwe przejście do menu początkowego, w którym można:  
• opuścić grę,  
• rozpocząć nową grę od dowolnego etapu,  
Oprócz tego gracz powinien mieć możliwość cofnięcia oraz ponowienia cofniętych wcześniej ruchów. 
UWAGA: atomy są dla gracza NIEWIDOCZNE podczas rozgrywki! 



**Obsługa programu** <br>
Program powinien wykorzystywać klawiaturę w następujący sposób:  
• w, s, a, d i (W, S, A, D) – poruszanie się po planszy odpowiednio: w górę, w dół, w lewo i 
prawo;  
• q, Q – wyjście do menu głównego;  
• u, U – undo (cofnij ruch);  
• r, R – redo (powtórz cofnięty ruch);  
• spacja oddanie strzału (gdy kursor jest na dowolnej ścianie); 
• o - na planszy umożliwia zaznaczenie przypuszczalnego położenia atomu; 
• k – kończy rozgrywkę i umożliwia wyświetlenie rozwiązania i liczby uzyskanych punktów 
(poprawnie znalezionych atomów); 
• p – umożliwia wyświetlenie rozwiązania (przerywa etap gry, brak możliwości kontynuowania 
tego etapu gry); 
• H – Help/Pomoc – pokazuje na chwilę umieszczenie atomów na planszy 
• pozostałe pozostają do wyboru przez programistę; Klawisze sterujące powinny być 
zatwierdzane klawiszem enter.
