#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>

using namespace std;

vector<int> nums;

bool isPartitionIsPossible(vector<int> nums) {

    // nie możemy podzielić na 3 podzbiory i zwrócimy false.
    if (nums.size()<3) {
        return false;
    }

	int sum = accumulate(begin(nums), end(nums), 0);

    cout << "Suma: " << sum << endl;

	return !(sum % 3);
}

int targetSum(vector<int> nums) {
    int sum = accumulate(begin(nums), end(nums), 0);
    return sum/3;
}

void readFile() {

    string str;

    ifstream coeff("testt.txt");

    if (coeff.is_open()) {
        while (!coeff.eof()) {
            getline(coeff, str, ',');
            nums.push_back(stof(str));
        }
        cout << "Ilość elementów = " << nums.size() << endl;
        coeff.close();
    }
    else {
        cout << "Błąd odczytu pliku";
    }
}

int main() {

//    bool used[10];
    string wynik;

    readFile();

    cout << "Czy 3-partition jest możliwa dla " << "[ ";

    for (int j = 0; j < nums.size(); j++) {
        cout << nums[j] << " ";
    }

    cout << "] ?" << endl;

    if (isPartitionIsPossible(nums))
        wynik = "Tak";
    else
        wynik = "Nie";

    cout << wynik << endl;
    cout << "TargetSum każdego podzbioru: " << targetSum(nums) << endl;

    ofstream out("output.txt");

    out << wynik;

    out.close();

    return 0;
}