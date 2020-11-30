#include "Solution.hpp"
#include <map>
#include <sstream>
#include <string>

auto goal_func(const vector<int> nums, Solution sol, int max_iterations) {
    using namespace chrono;
    bool canPartition;

    canPartition = sol.isPartitionIsPossible(nums, max_iterations);

    ostringstream oss;
    if (canPartition) {
        sol.showPartitions();
    }
    else {
        writeToFile("Partycja niemożliwa.");
    }

    return sol.merge_vectors(sol.subset_1, sol.subset_2, sol.subset_3);
}

map<std::string, std::string> process_args(int argc, char **argv)
{
    map<string, string> args;
    string argname = "-p";
    args[argname] = "2";
    for (auto arg : vector<string>(argv + 1, argv + argc))
    {
        if (arg.size() && arg[0] == '-')
            argname = arg;
        else
            args[argname] = arg;
    }
    return args;
}

auto experiment_run = [](auto method_f, std::map<std::string, std::string> args) {
    using namespace chrono;
    steady_clock::time_point start = steady_clock::now();
    auto ret_list = method_f(args);
    steady_clock::time_point end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);
    duration<double, milli> fp_ms = time_span;
    cout << "duration: " << time_span.count() << " sec or " << fp_ms.count() << " ms\n";
};

int main(int argc, char **argv) {

    Problem p;
    Solution sol;
    map<string, string> args = process_args(argc, argv);

    cout << "1Execute:\n1 - with random array\n2 - with array from file\n";
    cout << "Execute:\n1 - goal function\n2 - hill-climbing\n3 - tabu function\n\n";

    if (args["-g"] == "1")
    {
        generateNums();
    }
    else
    {
        readFile("test_1.txt");
    }

    if (args["-p"] == "1") {
        experiment_run([&](auto args) {
            return goal_func(nums, sol, (args.count("-n") ? stoi(args["-n"]) : 10));}, args);
    }
    if (args["-p"] == "2") {
        experiment_run([&](auto args) {
                           return sol.hill_climbing(nums, (args.count("-n") ? stoi(args["-n"]) : 10000)); }, args);
    }

    if (args["-p"] == "3") {
        experiment_run([&](auto args) {
            return sol.tabu(nums, (args.count("-n") ? stoi(args["-n"]) : 10000), (args.count("-tb") ? stoi(args["-tb"]) : 5000)); }, args);
    }

    if (args["-p"] == "123") {
        experiment_run([&](auto args) {
            return goal_func(nums, sol, (args.count("-n") ? stoi(args["-n"]) : 100));}, args);
        experiment_run([&](auto args) {
            return sol.hill_climbing(nums, (args.count("-n") ? stoi(args["-n"]) : 100)); }, args);
        experiment_run([&](auto args) {
            return sol.tabu(nums, (args.count("-n") ? stoi(args["-n"]) : 100), (args.count("-tb") ? stoi(args["-tb"]) : 500)); }, args);
    }


    cout << "[ ";
    showArray();
    cout << "]\n";

    cout << "Suma elementów: " << sum(nums) << endl;

    sol.subset_1.clear();
    sol.subset_2.clear();
    sol.subset_3.clear();


    return 0;
}