#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>

using namespace std;

bool isPartitionIsPossible(vector<int> nums) {

    // nie możemy podzielić na 3 podzbiory i zwrócimy false.
    if (nums.size()<3) {
        return false;
    }

	int sum = accumulate(begin(nums), end(nums), 0);

    cout << "Suma: " << sum << endl;

	return !(sum % 3);
}

int main() {

    string str;

    vector<int> nums;

    string file = "test.txt";

    ifstream coeff(file);

    if (coeff.is_open()) {
        while (!coeff.eof()) {
            getline(coeff, str, ',');
            nums.push_back(stof(str));

        }
        coeff.close();
    }
    else {
        cout << "Błąd odczytu pliku";
    }

    cout << "Ilość elementów = " << nums.size() << endl;
    cout << "Czy 3-partition jest możliwa dla " << "[ ";

    for (int j = 0; j < nums.size(); j++) {
        cout << nums[j] << " ";
    }

    cout << "] ?" << endl;

    string wynik;

    if (isPartitionIsPossible(nums))
        wynik = "Tak";
    else
        wynik = "Nie";

    cout << wynik;

    ofstream out("output.txt");
    out << wynik;
    out.close();

    return 0;
}