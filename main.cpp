#include "Solution.h"

void goal_func(const vector<int> nums, Problem p, Solution sol) {
    string wynik;
    using namespace chrono;
    bool canPartition;

    steady_clock::time_point start = steady_clock::now();
    canPartition = sol.isPartitionIsPossible(p, nums);
    steady_clock::time_point end = steady_clock::now();

    if (canPartition) {
        wynik = "Można podzielić zbiór na 3 podzbiory z sumą ";
        sol.showPartitions(p);
    }
    else {
        wynik = "Nie można podzielić zbiór na 3 podzbiory z sumą ";
    }

    wynik += to_string(p.targetSum(nums)) + "\n";
    cout << wynik << endl;

    duration<double> time_span = duration_cast<duration<double>>(end - start);
    duration<double, milli> fp_ms = time_span;

    cout << "isPartitionIsPossible(nums) duration: " << time_span.count() << " sec or " << fp_ms.count() << " ms\n";

    wynik += to_string(fp_ms.count()) + " ms";

    p.writeToFile(wynik);
}
bool run(Problem p) {

    Solution sol;

    int arg;

    cout << "Execute:\n1 - with random array\n2 - with array from file\n";
    cin >> arg;

    switch (arg) {
        case 1:
            p.generateNums();
            break;
        case 2:
            p.readFile();
            break;
        default:
            return false;
    }

    cout << "Czy 3-partition jest możliwa dla nums[ ";
    p.showArray();
    cout << "] ?" << endl;

    cout << "Suma elementów: " << p.sum(p.nums) << endl;


    while (true) {
        cout << "Execute:\n1 - goal function\n2 - hill-climbing\n";
        cin >> arg;

        switch (arg) {
            case 1:
                goal_func(p.nums, p, sol);
                break;
            case 2:
                sol.hill_climbing(p.nums);
                break;
            default:
                return false;
        }

        if (arg == 0) {
            return 0;
        }
        sol.subset_1.clear();
        sol.subset_2.clear();
        sol.subset_3.clear();
    }
}

int main() {

    Problem p;

    run(p);

    return 0;
}