#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>

using namespace std;

bool subsetSum(vector<int> S, int n, int a, int b, int c) {
	// return true if subset is found
	if (a == 0 && b == 0 && c == 0)
		return true;

	// base case: no items left
	if (n < 0)
		return false;

	// Case 1. current item becomes part of first subset
	bool A = false;
	if (a - S[n] >= 0)
		A = subsetSum(S, n - 1, a - S[n], b, c);

	// Case 2. current item becomes part of second subset
	bool B = false;
	if (!A && (b - S[n] >= 0))
		B = subsetSum(S, n - 1, a, b - S[n], c);

	// Case 3. current item becomes part of third subset
	bool C = false;
	if ((!A && !B) && (c - S[n] >= 0))
		C = subsetSum(S, n - 1, a, b, c - S[n]);

	// return true if we get solution
	return A || B || C;
}

//int sum(vector<int> target) {
//    int total = 0;
//    for (int i = 0; i < target.size(); i++) {
//        total += target[i];
//    }
//    return total;
//}

// Zwraca prawdę, jeśli dany zbiór S [0..n-1] można podzielić na trzy podzbiory o równej sumie
static bool partition(vector<int> S, int n) {
	if (n < 3)
		return false;

	// suma wszystkich elementów w zestawie
	int sum = accumulate(begin(S), end(S), 0);

	// zwraca prawdę, jeśli suma jest podzielna przez 3, a zbiór S można podzielić na trzy podzbiory o równej sumie
	return !(sum % 3) && subsetSum(S, n - 1, sum/3, sum/3, sum/3);

//    int value = S[n];
//
//    for (int k = 0; k < (sizeof(target) / sizeof(target[0])) && n < S.size(); k++) {
//        if (target[k] >= value) {
//            target[k] -= value;
//
//            if (partition(S, n+1, target, p)) {
//                p[k] += value;
//                break;
//            } else {
//                target[k] += value;
//            }
//        }
//    }
//    return sum(target) == 0;
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
    cout << "Czy 3-partition jest możliwa dla " << "[ ";

    for (int j = 0; j < S.size(); j++) {
        cout << S[j] << " ";
    }

    cout << "] ?" << endl;

    if (partition(S, S.size()))
        cout << "Tak";

    else
        cout << "Nie";


	return 0;
}