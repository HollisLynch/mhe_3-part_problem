#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <random>

using namespace std;

vector<int> nums;
vector<int> subset_1;
vector<int> subset_2;
vector<int> subset_3;

int sum(const vector<int> nums) {
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

auto randomNumberBetween = [](int low, int high)
{
    auto randomFunc = [distribution_ = uniform_int_distribution<int>(low, high),
            random_engine_ = mt19937{ random_device{}() }]() mutable
    {
        return distribution_(random_engine_);
    };
    return randomFunc;
};

void generateNums() {
    int n;
    int low;
    int high;

    cout << "Podaj rozmiar wektora: ";
    cin >> n;
    cout << "Podaj przedział: ";
    cin >> low >> high;

    generate_n(back_inserter(nums), n, randomNumberBetween(low, high));

}

auto generate_random_solution (vector<int> numbers){
    generate_n(back_inserter(numbers), nums.size(), randomNumberBetween(1, 12));

    return numbers;
}

auto hill_climbing_alg(const vector<int> nums) {
    vector<int> numbers;
    generate_n(back_inserter(numbers), nums.size(), randomNumberBetween(1, 12));

    cout << nums.size();

    for (int number : numbers)
    {
        cout << number << ' ';
    }

    return numbers;
}
void display_vector(const vector<int> &v)
{
    copy(v.begin(), v.end(),
              std::ostream_iterator<int>(cout, "\n"));
}
void showPartitions() {
    cout << "subset_1:\n";
    display_vector(subset_1);

    cout << "subset_2:\n";
    display_vector(subset_2);

    cout << "subset_3:\n";
    display_vector(subset_3);
}
bool partition(const vector<int> nums, const int targetSum){
    int currentBucketSum = 0;
    int j = 3;
    const int n = nums.size();
    bool used[n];

    while (j > 0) {

        for (int i = 0; i < nums.size(); i++) {

            if ((currentBucketSum + nums[i] <= targetSum) && j == 3) {
                used[i] = true;
                currentBucketSum += nums[i];
                subset_1.push_back(nums[i]);
                cout << "nums[i] for 1 bucket " << nums[i] << "\n";
                cout << "cs = " << currentBucketSum << "\n";
                if (targetSum == currentBucketSum) {
                    j -= 1;
                    currentBucketSum = 0;
                    i++;
                }
            } else if (!used[i] && (currentBucketSum + nums[i] <= targetSum) && j == 2) {
                used[i] = true;
                currentBucketSum += nums[i];
                subset_2.push_back(nums[i]);
                cout << "nums[i] for 2 bucket " << nums[i] << "\n";
                cout << "cs = " << currentBucketSum << "\n";
                if (targetSum == currentBucketSum) {
                    j -= 1;
                    currentBucketSum = 0;
                }
            } else if (!used[i] && (currentBucketSum + nums[i] <= targetSum) && j == 1) {
                used[i] = true;
                currentBucketSum += nums[i];
                subset_3.push_back(nums[i]);
                cout << "nums[i] for 3 bucket " << nums[i] << "\n";
                cout << "cs = " << currentBucketSum << "\n";
                if (targetSum == currentBucketSum) {
                    return true;
                }
            } else {
                used[i] = false;
            }
        }
    }
    return false;
}

bool isPartitionIsPossible(const vector<int> nums) {

    if (nums.size()<3) {
        return false;
    }

    if (sum(nums) % 3 != 0) {
        return false;
    }

    return partition(nums, targetSum(nums));
}

void goal_func(const vector<int> nums) {
    string wynik;
    using namespace chrono;



    bool canPartition;

//    steady_clock::time_point start = steady_clock::now();
    canPartition = isPartitionIsPossible(nums);
//    steady_clock::time_point end = steady_clock::now();

    if (canPartition) {
        wynik = "Można podzielić zbiór na 3 podzbiory z sumą ";
        showPartitions();
    }
    else {
        wynik = "Nie można podzielić zbiór na 3 podzbiory z sumą ";
    }

    wynik += to_string(targetSum(nums)) + "\n";
    cout << wynik << endl;

//    duration<double> time_span = duration_cast<duration<double>>(end - start);
//    duration<double, milli> fp_ms = time_span;
//
//    cout << "isPartitionIsPossible(nums) duration: " << time_span.count() << " sec or " << fp_ms.count() << " ms";
//
//    wynik += to_string(fp_ms.count()) + " ms";

    writeToFile(wynik);
}

bool run() {

    int arg;


    cout << "Execute:\n1 - with random array\n2 - with array from file\n";
    cin >> arg;

    switch (arg) {
        case 1:
            generateNums();
            break;
        case 2:
            readFile();
            break;
        default:
            return false;
    }

    cout << "Czy 3-partition jest możliwa dla nums[ ";
    showArray();
    cout << "] ?" << endl;

    cout << "Suma elementów: " << sum(nums) << endl;

    while (true) {
        cout << "Execute:\n1 - goal function\n2 - hill-climbing\n";
        cin >> arg;

        switch (arg) {
            case 1:
                goal_func(nums);
                break;
            case 2:
                hill_climbing_alg(nums);
                break;
            default:
                return false;
        }

        if (arg == 0) {
            return 0;
        }
        subset_1.clear();
        subset_2.clear();
        subset_3.clear();
    }
}

int main() {

    run();

    return 0;
}