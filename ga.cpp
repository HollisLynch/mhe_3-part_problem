#include <iostream>
#include <random>
#include <sstream>
#include <fstream>
#include <bitset>

using namespace std;
random_device device;
mt19937 rg(device());

vector<int> sum_subvectors(vector<vector<int>> mat) {
    vector<int> result;
    for (int i = 0; i<3; i++) {
        int suma = 0;
        for(int j = 0; j < mat[i].size(); j++)
        {
            cout << mat[i][j] << " ";
            suma += mat[i][j];

        }
        cout << " -> suma: " << suma;
        result.push_back(suma);
        cout << endl;
    }
    return result;
}

namespace ranges
{
    template<typename Range, typename Generator>
    void generate(Range& range, Generator generator)
    {
        return std::generate(begin(range), end(range), generator);
    }
}

auto randomNumberBetween = [](int low, int high)
{
    auto randomFunc = [distribution_ = std::uniform_int_distribution<int>(low, high),
            random_engine_ = std::mt19937{ std::random_device{}() }]() mutable
    {
        return distribution_(random_engine_);
    };
    return randomFunc;
};

auto mutation=[](double p_mut, auto chromosome) {
//    static uniform_real_distribution<double> dist (0, 1.0);
//    for (auto i: chromosome) {
//        if (dist(rg) < p_mut) {
//            i = 1 - i;
//        }
//    }
    return chromosome;
};

auto int_to_string_vector(vector<int> indexes) {
    vector<string> bit_v;
    vector<int> res;

    for (int i = 0; i<indexes.size(); i++) {
        bitset<2> b(indexes.at(i));
        bit_v.push_back(b.to_string());
    }
//    cout << "bits: ";
//    for (int i = 0; i<bit_v.size(); i++) {
//        cout << bit_v.at(i) << " ";
//    }
//    cout << endl;
    return bit_v;
}

auto crossover(vector<string> v, int cross_point) {
    int indexes_list[] = {1,0,0,2,0,1,2,1};
    vector<int> indexes (indexes_list, indexes_list + sizeof(indexes_list) / sizeof(int) );
    vector<string> bit_v = int_to_string_vector(indexes);
    vector<vector<string>> children;
    vector<string> off1;
    vector<string> off2;

    copy(bit_v.begin(), bit_v.begin() + cross_point, back_inserter(off1));
    copy(v.begin() + cross_point, v.end(), back_inserter(off1));
    copy(v.begin(), v.begin() + cross_point, back_inserter(off2));
    copy(bit_v.begin() + cross_point, bit_v.end(), back_inserter(off2));
    children.push_back(off1);
    children.push_back(off2);
    return children;
}

auto selection(vector<string> v) {
    return v;
};

double goal(vector<int> x) {
    sort(x.begin(), x.end(), greater <>());
    return ((double)x.at(0)/(double)x.at(1))/(double) x.at(2);
}

double calculate_pop_fitness(vector<int> x) {
    return 1/1-goal(x);
}

auto decode=[](vector<string> pop) {
    vector<int> res;
    for (int i = 0; i<pop.size(); i++) {
        res.push_back(strtol(pop.at(i).c_str(), nullptr, 2));
    }
    return res;
};

auto generate_init_pop() {
    int nums_list[] =    {0,4,8,3,7,5,2,6};
    int indexes_list[] = {0,1,1,2,0,0,2,3};
    vector<int> nums (nums_list, nums_list + sizeof(nums_list) / sizeof(int) );
    vector<int> indexes (indexes_list, indexes_list + sizeof(indexes_list) / sizeof(int) );
    auto bit_v = int_to_string_vector(indexes);
    string bit_str;
    ostringstream oss;
    copy(bit_v.begin(), bit_v.end()-1,ostream_iterator<string>(oss, ""));
    oss << bit_v.back();
    bit_str = oss.str();
    cout << "chromosome: " << bit_str << "\n";

    return bit_v;
}

auto genetic_alg = [](auto calculate_pop_fitness, auto generate_init_pop, auto selection, auto crossover, auto mutation, auto iterations) {
    vector<string> population = generate_init_pop();
    for (int i = 0; i<population.size(); i++) {
        cout << population.at(i) << " ";
    }
    cout << "\n";
    auto offspring = crossover(population, 3);
    cout << "off1: ";
    for (int i = 0; i<offspring[0].size(); i++) {
        cout << offspring[0][i] << " ";
    }
    cout << "  off2: ";
    for (int i = 0; i<offspring[1].size(); i++) {
        cout << offspring[1][i] << " ";
    }
    for (int iteration = 0; iteration < iterations; iteration++)
    {
        auto parents = selection(population);
        auto offspring = crossover(parents, 3);
        offspring = mutation(0.1, offspring);
        auto pop_fitness = calculate_pop_fitness(offspring);
        population = pop_fitness;
    }
    return population;
};

auto vector_to_subvectors(vector<int> nums, vector<int> indexes) {
    vector<vector<int>> mat;
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;

    for (int j = 0; j < indexes.size(); j++) {
        if (indexes.at(j) == 0) {
            v1.push_back(nums.at(j));
        }
        if (indexes.at(j) == 1) {
            v2.push_back(nums.at(j));
        }
        if (indexes.at(j) == 2) {
            v3.push_back(nums.at(j));
        }
        else if (indexes.at(j) > 2){
            v3.push_back(nums.at(j));
        }
    }
    mat.push_back(v1);
    mat.push_back(v2);
    mat.push_back(v3);

    return mat;
}

int main() {
//    int nums_list[] =    {0,4,8,3,7,5,2,6};
//    int indexes_list[] = {0,1,1,2,0,0,2,3};
//    vector<int> nums (nums_list, nums_list + sizeof(nums_list) / sizeof(int) );
//    vector<int> indexes (indexes_list, indexes_list + sizeof(indexes_list) / sizeof(int) );
//
//    auto string_bit_vector = int_to_string_vector(indexes);
//    auto chromosome = generate_init_pop(string_bit_vector);

//    auto cross = crossover(string_bit_vector);
//
//    cout << "crossover: ";
//    for (int i = 0; i<cross.size(); i++) {
//        cout << cross.at(i) << " ";
//    }

//    auto subvectors = vector_to_subvectors(nums, indexes);
//
//    auto sums = sum_subvectors(subvectors);
//
//    cout << "fitness: " << calculate_pop_fitness(sums) << "\n";

    genetic_alg(calculate_pop_fitness, generate_init_pop, selection, crossover, mutation, 10);
    cout << endl;
    return 0;
}
