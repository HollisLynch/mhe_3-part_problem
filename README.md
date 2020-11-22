# mhe_3-part_problem

3-partition problem\
Dany jest zbiór liczb dodatnich długości n, trzeba się zastanowić czy da się podzielić ten zbiór na 3 podzbiory z sumą elementów sobie równych.\
Problem jest NP-trudny, ponieważ istnieje łącznie 2 ^ n podzbiorów (n - rozmiar tablicy).

Możemy dodać liczbę do podzbioru jeżeli:
1) element jeszcze nie był sprawdzany
2) bieżący element + bieżąca suma <= target bucket targetSum

Musimy też utworzyć nową tablice bool, która będzie śledzić elementy, które są używane do tej pory, abyśmy nie użyli je ponownie.
Zdefuniujemy też funkcję Partition, która pokaże czy da się podzielić dany zbiór liczb na 3 podzbiory z elementami sumy których są sobie równe.
