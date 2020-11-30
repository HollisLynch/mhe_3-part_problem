#include <algorithm>
#include <random>
#include "Problem.hpp"
#include <memory>
#include <set>
#include <list>

using namespace std;

bool myfunction (int i,int j) { return (i<j); }

random_device rd;
mt19937 g(rd());

class Solution : public std::vector<int>{
public:
    Solution()
    {
    }

    vector<int> subset_1;
    vector<int> subset_2;
    vector<int> subset_3;
    int n;

    vector<int> merge_vectors(vector<int> a, vector<int> b, vector<int> c) {
        vector<int> result;
        for  (int i = 0; i < a.size(); i++) {
            result.push_back(a.at(i));
        }
        for  (int i = 0; i < b.size(); i++) {
            result.push_back(b.at(i));
        }
        for  (int i = 0; i < c.size(); i++) {
            result.push_back(c.at(i));
        }
        return  result;
    }

    vector<int> sum_vectors(vector<int> v) {
        vector<int> result;
        int sum1 = accumulate(v.begin(),v.begin()+n/3, 0);
        int sum2 = accumulate(v.begin()+n/3, v.begin()+n/3+n/2, 0);
        int sum3 = accumulate(v.begin()+n/3+n/2, v.end(), 0);

        result.push_back(sum1);
        result.push_back(sum2);
        result.push_back(sum3);

        return result;
    }

    auto get_random_sol (vector<int> nums) {
        n = nums.size();
        vector<int> shuffled(n);
        copy(nums.begin(), nums.end(), shuffled.begin());
        shuffle (shuffled.begin(), shuffled.end(), g);

        vector<int> a(n/3);
        vector<int> b(n/2);
        vector<int> c(n/3);

        copy(shuffled.begin(), shuffled.begin()+n/3, a.begin());
        copy(shuffled.begin()+n/3, shuffled.begin()+n/3 + n/2, b.begin());
        copy(shuffled.begin()+n/3 + n/2, shuffled.end(), c.begin());

        cout << "a: ";
        display_vector(a);
        cout << "b: ";
        display_vector(b);
        cout << "c: ";
        display_vector(c);

        return merge_vectors(a,b,c);
    }

    auto sortVector(vector<int> v) {
        n = v.size();
        vector<int> result_copy(n);
        copy(v.begin(), v.end(), result_copy.begin());

        vector<int> a(n/3);
        vector<int> b(n/2);
        vector<int> c(n/3);

        copy(result_copy.begin(), result_copy.begin()+n/3, a.begin());
        copy(result_copy.begin()+n/3, result_copy.begin()+n/3 + n/2, b.begin());
        copy(result_copy.begin()+n/3 + n/2, result_copy.end(), c.begin());

        sort(a.begin(), a.end(), myfunction);
        sort(b.begin(), b.end(), myfunction);
        sort(c.begin(), c.end(), myfunction);

        return merge_vectors(a,b,c);

    }

    auto showSubsets(vector<int> v) {
        vector<int> a(n/3);
        vector<int> b(n/2);
        vector<int> c(n/3);

        copy(v.begin(), v.begin()+n/3, a.begin());
        copy(v.begin()+n/3, v.begin()+n/3 + n/2, b.begin());
        copy(v.begin()+n/3 + n/2, v.end(), c.begin());

        cout << "a: ";
        display_vector(a);
        cout << "b: ";
        display_vector(b);
        cout << "c: ";
        display_vector(c);
    }

    auto get_random_neighbour(vector<int> result) {
        vector<int> result_copy = sortVector(result);
        shuffle (result_copy.begin(), result_copy.end(), g);
        iter_swap(result_copy.begin()+4, result_copy.begin()+5);

        return result_copy;
    }

    auto hill_climbing(vector<int> nums, int max_iterations) {
        ofstream file("hill.csv");
        vector<int> current_solution = get_random_sol(nums);
        vector<int> next_solutions;

        for (int i = 0; i<max_iterations; i++) {
            next_solutions = get_random_neighbour(current_solution);

            file << i << " ";
            cout << "Suma: " << sum_vectors(next_solutions).at(0) << "  " << sum_vectors(next_solutions).at(1) << "  " << sum_vectors(next_solutions).at(2);
            cout << "\n";
            file << sum_vectors(next_solutions).at(0) << " " << sum_vectors(next_solutions).at(1) << " " << sum_vectors(next_solutions).at(2);
            file << "\n";

            if (sum_vectors(next_solutions).at(0) < sum_vectors(current_solution).at(0) &&
                sum_vectors(next_solutions).at(1) < sum_vectors(current_solution).at(1) &&
                sum_vectors(next_solutions).at(2) < sum_vectors(current_solution).at(2)) {
                current_solution = next_solutions;
            }
        }
        cout << "Best found:\n";
        showSubsets(current_solution);

        cout << "Suma: " << sum_vectors(current_solution).at(0) << "  " << sum_vectors(current_solution).at(1) << "  " << sum_vectors(current_solution).at(2) << "\n";
        file.close();
        return current_solution;
    }

    auto tabu(vector<int> nums, int max_iterations, int tabu_size) {
        ofstream file("tabu.csv");
        auto current_solution = get_random_sol(nums);
        vector<int> next_solution;
        list<int> tabu;
        tabu.insert(tabu.end(), current_solution.begin(), current_solution.end());

        for (int i = 0; i<max_iterations; i++) {
            next_solution = get_random_neighbour(current_solution);
            for (auto &v : next_solution)
                if (find(tabu.begin(), tabu.end(),v)==tabu.end())
                    next_solution.push_back(v);

            file << i << " ";
            cout << "Suma: " << sum_vectors(next_solution).at(0) << "  " << sum_vectors(next_solution).at(1) << "  " << sum_vectors(next_solution).at(2);
            cout << "\n";
            file << sum_vectors(next_solution).at(0) << " " << sum_vectors(next_solution).at(1) << " " << sum_vectors(next_solution).at(2);
            file << "\n";

            if (next_solution.size() == 0) {
                next_solution.push_back(tabu.front());
            }

            if (sum_vectors(next_solution).at(0) < sum_vectors(current_solution).at(0) &&
                sum_vectors(next_solution).at(1) < sum_vectors(current_solution).at(1) &&
                sum_vectors(next_solution).at(2) < sum_vectors(current_solution).at(2)) {
                current_solution = next_solution;
            }

            for (int j = 0; j < current_solution.size(); j++) {
                tabu.push_back(current_solution.at(j));
            }

            if (tabu.size() > tabu_size) {
                tabu.pop_front();
            }
        }
        cout << "Best found:\n";
        showSubsets(current_solution);

        file.close();
        cout << "Suma: " << sum_vectors(current_solution).at(0) << "  " << sum_vectors(current_solution).at(1) << "  " << sum_vectors(current_solution).at(2) << "\n";
        return current_solution;
    }

    void display_vector(const vector<int> &v)
    {
        copy(v.begin(), v.end(),
             std::ostream_iterator<int>(cout, " "));
        int sum = accumulate(v.begin(), v.end(), 0);
        cout << " sum: " << sum << endl;
        cout << endl;
    }

    void showPartitions() {
        cout << "subset_1:\n";
        display_vector(subset_1);

        cout << "subset_2:\n";
        display_vector(subset_2);

        cout << "subset_3:\n";
        display_vector(subset_3);
    }

    bool partition(const vector<int> nums, const int targetSum, int max_iterations){
        ofstream file("goal.csv");
        int currentBucketSum = 0;
        int j = 3;
        const int n = nums.size();
        bool used[n];

        int iterations = 0;

        while (j > 0 && iterations < max_iterations) {
            for (int i = 0; i < nums.size(); i++) {
                file << iterations << " ";
                if ((currentBucketSum + nums[i] <= targetSum) && j == 3) {
                    used[i] = true;
                    currentBucketSum += nums[i];
                    subset_1.push_back(nums[i]);
                    if (targetSum == currentBucketSum) {
                        j -= 1;
                        currentBucketSum = 0;
                        i++;
                    }
                }
                else if (!used[i] && (currentBucketSum + nums[i] <= targetSum) && j == 2) {
                    used[i] = true;
                    currentBucketSum += nums[i];
                    subset_2.push_back(nums[i]);
                    if (targetSum == currentBucketSum) {
                        j -= 1;
                        currentBucketSum = 0;
                    }
                }
                else if (!used[i] && (currentBucketSum + nums[i] <= targetSum) && j == 1) {
                    used[i] = true;
                    currentBucketSum += nums[i];
                    subset_3.push_back(nums[i]);
                    if (targetSum == currentBucketSum) {
                        file << sum(subset_1) << " " << sum(subset_2) << " " << sum(subset_3);
                        return true;
                    }
                }
                else {
                    used[i] = false;
                }
                iterations += 1;
                file << sum(subset_1) << " " << sum(subset_2) << " " << sum(subset_3);
                file << "\n";
            }
        }
        file.close();
        return false;
    }

    bool isPartitionIsPossible(const vector<int> nums , int max_iterations) {
        if (nums.size()<3) {
            return false;
        }
        if (sum(nums) % 3 != 0) {
            return false;
        }

        return partition(nums, targetSum(nums), max_iterations);
    }

};
