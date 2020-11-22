#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <random>
#include "Problem.h"

using namespace std;

int myrandom (int i) { return std::rand()%i;}

class Solution {
public:
    Solution()
    {
    }

    vector<int> subset_1;
    vector<int> subset_2;
    vector<int> subset_3;

//    vector<int> a;
//    vector<int> b;
//    vector<int> c;

    auto randomize (vector<int> nums) {

        int n = nums.size();

        vector<int> shuffled(n);

        copy(begin(nums), end(nums), shuffled.begin());

        srand (unsigned(time(0)));

        random_shuffle (shuffled.begin(), shuffled.end());

        random_shuffle (shuffled.begin(), shuffled.end(), myrandom);


        vector<int> a(n/3);
        vector<int> b(n/2);
        vector<int> c(n/3);

        copy(begin(shuffled), shuffled.begin()+n/3, a.begin());
        copy(begin(shuffled)+n/3, shuffled.begin()+n/3 + n/2, b.begin());
        copy(begin(shuffled)+n/3 + n/2, shuffled.end(), c.begin());

        cout << "a: ";
        display_vector(a);
        cout << "b: ";
        display_vector(b);
        cout << "c: ";
        display_vector(c);

//        vector <vector<int>> result(a.size());
//        copy(begin(a), end(a), result.begin());
//        copy(begin(b), end(b), result.at(1));
//        copy(begin(b), end(b), result.at(2));
        int sum1 = accumulate(begin(a), end(a), 0);
        int sum2 = accumulate(begin(b), end(b), 0);
        int sum3 = accumulate(begin(c), end(c), 0);

        vector<int> result;
        result.push_back(sum1);
        result.push_back(sum2);
        result.push_back(sum3);

        return result;
    }

    auto random_neighbour() {

    }

    int hill_climbing(vector<int> nums) {
        auto solution = randomize(nums);
        for (int i = 0; i < solution.size(); i++) {
            cout << solution.at(i) << " ";
        }

        for (int i = 0; i<100000; i++) {
            cout << "Solution: " << solution.at(i) << " ";
            auto neighbour = random_neighbour();
        }

        cout << endl;
        return 0;
    }
    void display_vector(const vector<int> &v)
    {
        copy(v.begin(), v.end(),
             std::ostream_iterator<int>(cout, " "));
        int sum = accumulate(begin(v), end(v), 0);
        cout << " sum: " << sum << endl;
        cout << endl;
    }
    void showPartitions(Problem p) {
        cout << "subset_1:\n";
        display_vector(subset_1);

        cout << "subset_2:\n";
        display_vector(subset_2);

        cout << "subset_3:\n";
        display_vector(subset_3);
    }

    bool ifElementInSubArray(int key) {
        if (count(subset_1.begin(), subset_1.end(), key))
            return true;
        else if (count(subset_2.begin(), subset_2.end(), key))
            return true;

        return false;
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

    bool isPartitionIsPossible(Problem p, const vector<int> nums) {

        if (p.nums.size()<3) {
            return false;
        }

        if (p.sum(nums) % 3 != 0) {
            return false;
        }

        return partition(nums, p.targetSum(nums));
    }

};
