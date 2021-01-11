#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <random>
#include <sstream>

std::random_device r;
std::default_random_engine e1(r());
std::mt19937 rand_gen(192987432);

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

struct specimen_t
{
    std::vector<int> chromosome;
    double fit;
    specimen_t(int n = 0)
    {
        chromosome.resize(n);
    }
    void randomize()
    {
        ranges::generate(chromosome, randomNumberBetween(0, 1));
    }
    void print()
    {
        using namespace std;
        for (int i = 0; i<chromosome.size(); i++) {
            cout << chromosome.at(i);
            if (i%2!=0) {
                cout << " ";
            }
        }
    }

    std::vector<int> decode() {
        using namespace std;
        int nums_list[] = {0,4,8,3,7,5,2,6};
        vector<int> nums(nums_list, nums_list + sizeof(nums_list)/sizeof(int));
        vector<int> subset_1;
        vector<int> subset_2;
        vector<int> subset_3;

        vector<int> indexes;
        for (int i = 0; i<chromosome.size(); i++) {
            if (i%2!=0) {
                ostringstream oss;
                oss << chromosome.at(i-1);
                oss << chromosome.at(i);
                indexes.push_back(strtol(oss.str().c_str(), nullptr, 2));
            }
        }

        for (int j = 0; j < indexes.size(); j++) {
            if (indexes.at(j) == 0) {
                subset_1.push_back(nums.at(j));
            }
            if (indexes.at(j) == 1) {
                subset_2.push_back(nums.at(j));
            }
            if (indexes.at(j) == 2) {
                subset_3.push_back(nums.at(j));
            }
            else if (indexes.at(j) > 2){
                subset_3.push_back(nums.at(j));
            }
        }

        vector<int> res;
        res.push_back(accumulate(subset_1.begin(), subset_1.end(), 0));
        res.push_back(accumulate(subset_2.begin(), subset_2.end(), 0));
        res.push_back(accumulate(subset_3.begin(), subset_3.end(), 0));
        return res;
    }
};

auto generate_init_pop = []() {
    std::vector<specimen_t> xy;
    for (int i = 0; i < 4; i++)
    {
        xy.push_back(16);
        xy[i].randomize();
    }
    return xy;
};

auto fitness = [](std::vector<int> res) {
    sort(res.begin(), res.end(), std::greater <>());
    auto goal = (double)res.at(0)/(double)res.at(1)/(double) res.at(2);
    return 1/1-goal;
};

std::vector<specimen_t> calculate_pop_fitness(std::vector<specimen_t> population)
{
    std::vector<specimen_t> ret;
    ret.reserve(population.size());
    std::cout << "fit:\n";
    for (int i = 0; i< population.size(); i++)
    {
        population.at(i).fit = fitness(population.at(i).decode());
        ret.push_back(population.at(i));
        std::cout << population.at(i).fit << "\n";
    }
    std::cout << "-------\n";
    return ret;
}

auto genetic_alg = [](auto fitness, auto generate_init_pop, auto selection, auto crossover, auto mutation) {
    using namespace std;
    auto population = generate_init_pop();
    cout << "population:\n";
    for (int i = 0; i< population.size(); i++) {
        population.at(i).print();
        cout << "\n";
    }
    population = calculate_pop_fitness(population);
    for (int iteration = 0; iteration < 10; iteration++)
    {
        auto parents = selection(population);
        auto offspring = crossover(parents);
        offspring = mutation(offspring);
        population = calculate_pop_fitness(offspring);
        auto d =  population.at(1).decode();
        for (int i = 0; i< population.size(); i++) {
            population.at(i).print();
            cout << "\n";
            d = population.at(i).decode();
            for (int j = 0; j< d.size(); j++) {
                cout << j << ": " << d.at(j) << "\n";
            }
        }
    }
    return population;
};

auto selection_tournament = [](auto population) {
    decltype(population) selected;
    std::uniform_int_distribution<int> dist(0, population.size() - 1);
    for (int c = 0; c < population.size(); c++)
    {
        decltype(population) tournament;
        for (int t = 0; t < 2; t++)
        {
            tournament.push_back(population.at(dist(rand_gen)));
        }
        sort(tournament.begin(), tournament.end(), [](auto a, auto b) {
            return fitness(a.decode()) > fitness(b.decode());
        });
        selected.push_back(tournament.at(0));
    }
    return selected;
};

auto selection_roulette = [](auto pop) {
    auto selection_roulette = [](auto population) {
        using namespace std;
        decltype(population) selected_specimens;
        double sum_fitness = accumulate(population.begin(), population.end(), 0.0, [](auto a, auto b) { return a + b.fit; });

        uniform_real_distribution<double> dist(0.0, sum_fitness);
        for (int c = 0; c < population.size(); c++)
        {
            double r = dist(rand_gen);
            double s = 0.0;
            for (unsigned int i = 0; i < population.size(); i++)
            {
                s += population[i].fit;
                if (r < s)
                {
                    selected_specimens.push_back(population.at(i));
                    break;
                }
            }
        }
        return selected_specimens;
    };
    return selection_roulette;
};

auto crossover_one_point = [](auto population, double p = 0.9) {
    using namespace std;
    decltype(population) crossed;
    uniform_real_distribution<double> rr(0.0, 1.0);
    for (int i = 0; i< (population.size()-1); i+=2) {
        auto c_1 = population.at(i);
        auto c_2 = population.at(i+1);
        if (rr(rand_gen) < p) {
            uniform_int_distribution<int> dist(0, c_1.chromosome.size() - 1);
            auto cross_point = dist(rand_gen);

            for (int g = cross_point; g < c_1.chromosome.size(); g++)
            {
                swap(c_1.chromosome[g], c_2.chromosome[g]);
            }
        }
        crossed.push_back(c_1);
        crossed.push_back(c_2);
    }
    return crossed;
};

auto crossover_two_point = [](auto population, double p = 0.9) {
    using namespace std;
    decltype(population) crossed;
    uniform_real_distribution<double> rr(0.0, 1.0);
    for (int i = 0; i< (population.size()-1); i+=2) {
        auto c_1 = population.at(i);
        auto c_2 = population.at(i+1);
        if (rr(rand_gen) < p) {
            uniform_int_distribution<int> dist(0, c_1.chromosome.size() - 1);
            int cross_point1 = dist(rand_gen);
            int cross_point2 = dist(rand_gen);
            if (cross_point1 > cross_point2)
                swap(cross_point1,cross_point2);

            for (int g = cross_point1; g < cross_point2; g++)
            {
                swap(c_1.chromosome[g], c_2.chromosome[g]);
            }
        }
        crossed.push_back(c_1);
        crossed.push_back(c_2);
    }
    return crossed;
};

auto mutate = [](auto population, double p = 0.1) {
    using namespace std;
    decltype(population) mutated;
    uniform_real_distribution<double> rr(0.0, 1.0);
    for (int i = 0; i< population.size(); i++) {
        auto c = population.at(i);
        for (int j = 0; j<c.chromosome.size(); j++) {
            if (rr(rand_gen) < p) {
                c.chromosome[j] = 1 - c.chromosome[j];
            }
        }
        mutated.push_back(c);
    }
    return mutated;
};

int main(int argc, char** argv) {

    genetic_alg(fitness, generate_init_pop, selection, crossover_two_point, mutate);

    return 0;
}
