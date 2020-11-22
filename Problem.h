#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <random>

using namespace std;

auto randomNumberBetween = [](int low, int high)
{
    auto randomFunc = [distribution_ = uniform_int_distribution<int>(low, high),
            random_engine_ = mt19937{ random_device{}() }]() mutable
    {
        return distribution_(random_engine_);
    };
    return randomFunc;
};

class Problem {
public:
    vector<int> nums;

    int sum(vector<int> nums) {
        int sum = accumulate(begin(nums), end(nums), 0);
        return sum;
    }

    int targetSum(const vector<int> nums) {
        int sum = accumulate(begin(nums), end(nums), 0);
        return sum/3;
    }

    void showArray() {
        for (int j = 0; j < nums.size(); j++) {
            cout << nums[j] << " ";
        }
    }

    void readFile() {

        string str;
        ifstream f("test.txt");

        if (f.is_open()) {
            while (!f.eof()) {
                getline(f, str, ',');
                nums.push_back(stof(str));
            }
            f.close();
        }
        else {
            cout << "Błąd odczytu pliku";
        }
    }
    void writeToFile(string wynik) {
        ofstream out("output.txt");
        out << wynik;
        out.close();
    }

    void generateNums() {
        int n;
        int low;
        int high;

        cout << "Podaj rozmiar wektora (n/3): ";
        cin >> n;
        cout << "Podaj przedział: ";
        cin >> low >> high;

        generate_n(back_inserter(nums), n/3, randomNumberBetween(low, high));
    }
};