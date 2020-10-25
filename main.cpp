#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>

using namespace std;

bool subsetSum(vector<int> S, int n, int a, int b, int c) {
	if (a == 0 && b == 0 && c == 0)
		return true;

	if (n < 0)
		return false;

	// bieżąca pozycja staje się częścią pierwszego podzbioru
	bool A = false;
	if (a - S[n] >= 0)
		A = subsetSum(S, n - 1, a - S[n], b, c);

	// bieżąca pozycja staje się częścią drugiego podzbioru
	bool B = false;
	if (!A && (b - S[n] >= 0))
		B = subsetSum(S, n - 1, a, b - S[n], c);

	bool C = false;
	if ((!A && !B) && (c - S[n] >= 0))
		C = subsetSum(S, n - 1, a, b, c - S[n]);

	// zwraca prawdę, jeśli otrzymamy rozwiązanie
	return A || B || C;
}

// Zwraca prawdę, jeśli dany zbiór S [0..n-1] można podzielić na trzy podzbiory o równej sumie
static bool canPartition(vector<int> S, int n) {
	if (n < 3)
		return false;

	// suma wszystkich elementów w zestawie
	int sum = accumulate(begin(S), end(S), 0);

	// zwraca prawdę, jeśli suma jest podzielna przez 3, a zbiór S można podzielić na trzy podzbiory o równej sumie
	return !(sum % 3) && subsetSum(S, n - 1, sum/3, sum/3, sum/3);


}

int main() {

    string str;
    vector<int> S;
    vector<int> p;
    vector<int> target(3);

    string file = "test.txt";
    ifstream coeff(file);

    if (coeff.is_open()) {
        while (!coeff.eof()) {
            getline(coeff, str, ',');
            S.push_back(stof(str));

        }
        coeff.close();
    }
    else {
        cout << "Błąd otwierania pliku";
    }

    cout << "Ilość elementów = " << S.size() << endl;
    cout << "Czy 3-canPartition jest możliwa dla " << "[ ";

    for (int j = 0; j < S.size(); j++) {
        cout << S[j] << " ";
    }

    cout << "] ?" << endl;

    bool wynik;

    if (canPartition(S, S.size()))
        wynik = true;
    else
        wynik = false;

    cout << wynik;
}