#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <random>

using namespace std;

vector<int> nums;

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

auto generate_random_solution (){
    random_device random_device;
    mt19937 random_engine(random_device());
    uniform_int_distribution<bool> distribution_0_1(false, true);

    auto const randomNumber = distribution_0_1(random_engine);

    return randomNumber;
}

bool hill_climbing_alg() {
    auto best = generate_random_solution();

    cout << best;
}

bool partition(const vector<int> nums, bool *used, int targetSum){
    int k = 3;
    int currentBucketSum = 0;

    while (k>0) {
        if (k == 1) {
            cout << "k (1 if): " << k << endl;
            return true;
        }
        if (currentBucketSum == targetSum) {
            currentBucketSum = 0;
            k -= 1;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (!used[i] && currentBucketSum + nums[i] <= targetSum) {
                cout << "k (2 if): " << k << endl;
                used[i] = true;
                currentBucketSum += nums[i];
            }
                used[i] = false;
        }
    }
    return false;
}

bool partitionRec(int k, const vector<int> nums, bool *used, int targetSum, int currentBucketSum, int start){

    if(k==1) {
        cout << "k (1 if): " << k << endl;
        return true;
    }

    if(currentBucketSum == targetSum)
        return partitionRec(k-1, nums, used, targetSum, 0, 0);

    for(int i=start; i<nums.size(); i++){

        if(!used[i] && currentBucketSum+nums[i]<=targetSum){
            used[i] = true;
            cout << "k (2 if): " << k << endl;
            if(partitionRec(k, nums, used, targetSum, currentBucketSum+nums[i], i+1))
                return true;
            used[i] = false;
        }
    }
    return false;
}

bool isPartitionIsPossible(const vector<int> nums, bool used[]) {

    if (nums.size()<3) {
        return false;
    }

    if (sum(nums) % 3 != 0) {
        return false;
    }

//    return partitionRec(3, nums, used, targetSum(nums), 0, 0);
    return partition(nums, used, targetSum(nums));
}

bool run() {

    using namespace chrono;

    string wynik;
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

    int n = nums.size();
    bool used[n*2];

    steady_clock::time_point start = steady_clock::now();
    bool canPartition = isPartitionIsPossible(nums, used);
    steady_clock::time_point end = steady_clock::now();

    if (canPartition) {
        wynik = "Można podzielić zbiór na 3 podzbiory z sumą ";
    }
    else {
        wynik = "Nie można podzielić zbiór na 3 podzbiory z sumą ";
    }

    wynik += to_string(targetSum(nums)) + "\n";
    cout << wynik << endl;

    duration<double> time_span = duration_cast<duration<double>>(end - start);
    duration<double, milli> fp_ms = time_span;

    cout << "isPartitionIsPossible(nums) duration: " << time_span.count() << " sec or " << fp_ms.count() << " ms";

    wynik += to_string(fp_ms.count()) + " ms";

    writeToFile(wynik);
}

int main() {

    run();
//    hill_climbing_alg();

    return 0;
}