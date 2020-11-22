#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <random>

using namespace std;

class Solution {
public:
    vector<int> subset_1;
    vector<int> subset_2;
    vector<int> subset_3;

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
    void showPartitions(Problem p) {
        cout << "subset_1:\n";
        display_vector(subset_1);

        cout << "subset_2:\n";
        display_vector(subset_2);

        cout << "subset_3:\n";
        display_vector(subset_3);
    }
    bool partition(Problem p, const vector<int> nums, const int targetSum){

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

        return partition(p, nums, p.targetSum(nums));
    }


};
