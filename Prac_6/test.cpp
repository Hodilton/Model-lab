#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>
#include "RANDOM.h"

using json = nlohmann::json;

class Individual {
public:
    double a, b; // Коэффициенты линейной функции
    double fitness; // Приспособленность

    Individual() : a(0), b(0), fitness(0) {}

    void randomize(std::unique_ptr<random::IRandomDoubleGenerator>& randGen, double minRange, double maxRange) {
        a = randGen->Get(minRange, maxRange, 2);
        b = randGen->Get(minRange, maxRange, 2);
    }
};

class GeneticAlgorithm {
private:
    std::vector<Individual> population;
    std::vector<std::pair<double, double>> data; // Набор точек
    size_t populationSize;
    double crossoverRate;
    double mutationRate;
    size_t generations;
    double coefRangeMin;
    double coefRangeMax;
    std::unique_ptr<random::IRandomDoubleGenerator> randGen;
    std::unique_ptr<random::IRandomIntGenerator> randIntGen;

    double evaluateFitness(const Individual& ind) {
        double fitness = 0.0;
        for (const auto& point : data) {
            double yPredicted = ind.a * point.first + ind.b;
            fitness += std::pow(yPredicted - point.second, 2); // MSE
        }
        return -fitness; // Чем меньше ошибка, тем лучше
    }

    void select(std::vector<Individual>& matingPool) {
        std::sort(population.begin(), population.end(),
            [](const Individual& a, const Individual& b) {
                return a.fitness > b.fitness;
            });
        matingPool.assign(population.begin(), population.begin() + populationSize / 2);
    }

    void crossover(Individual& parent1, Individual& parent2, Individual& child1, Individual& child2) {
        if (randGen->Get(0.0, 1.0) < crossoverRate) {
            double alpha = randGen->Get(0.0, 1.0);
            child1.a = alpha * parent1.a + (1 - alpha) * parent2.a;
            child1.b = alpha * parent1.b + (1 - alpha) * parent2.b;

            child2.a = alpha * parent2.a + (1 - alpha) * parent1.a;
            child2.b = alpha * parent2.b + (1 - alpha) * parent1.b;
        }
        else {
            child1 = parent1;
            child2 = parent2;
        }
    }

    void mutate(Individual& ind) {
        if (randGen->Get(0.0, 1.0) < mutationRate) {
            ind.a += randGen->Get(-0.1, 0.1, 2);
            ind.b += randGen->Get(-0.1, 0.1, 2);
        }
    }

public:
    GeneticAlgorithm(size_t popSize, double crossRate, double mutRate, size_t gens,
        std::vector<std::pair<double, double>> inputData, double rangeMin, double rangeMax)
        : populationSize(popSize), crossoverRate(crossRate), mutationRate(mutRate),
        generations(gens), data(std::move(inputData)), coefRangeMin(rangeMin), coefRangeMax(rangeMax) {
        randGen = random::Factory::create<random::Type::Double>();
        randIntGen = random::Factory::create<random::Type::Integer>();
    }

    void run(const std::string& outputFile) {
        population.resize(populationSize);
        for (auto& ind : population) {
            ind.randomize(randGen, coefRangeMin, coefRangeMax);
        }

        json results;

        for (size_t gen = 0; gen < generations; ++gen) {
            for (auto& ind : population) {
                ind.fitness = evaluateFitness(ind);
            }

            std::vector<Individual> matingPool;
            select(matingPool);

            std::vector<Individual> newPopulation;
            while (newPopulation.size() < populationSize) {
                size_t p1 = randIntGen->Get(0, matingPool.size() - 1);
                size_t p2 = randIntGen->Get(0, matingPool.size() - 1);
                Individual child1, child2;
                crossover(matingPool[p1], matingPool[p2], child1, child2);
                mutate(child1);
                mutate(child2);
                newPopulation.push_back(child1);
                newPopulation.push_back(child2);
            }

            population = std::move(newPopulation);

            const auto& best = *std::max_element(population.begin(), population.end(),
                [](const Individual& a, const Individual& b) {
                    return a.fitness < b.fitness;
                });
            results["generation_" + std::to_string(gen)] = {
                {"fitness", best.fitness},
                {"a", best.a},
                {"b", best.b}
            };
        }

        std::ofstream outFile(outputFile);
        outFile << results.dump(4);
        outFile.close();
    }
};

int main() {
    std::ifstream inputFile("config.json");
    json config;
    inputFile >> config;

    size_t populationSize = config["population_size"];
    double crossoverRate = config["crossover_rate"];
    double mutationRate = config["mutation_rate"];
    size_t generations = config["generations"];
    double coefRangeMin = config["coef_range_min"];
    double coefRangeMax = config["coef_range_max"];
    std::vector<std::pair<double, double>> data = config["data"].get<std::vector<std::pair<double, double>>>();

    GeneticAlgorithm ga(populationSize, crossoverRate, mutationRate, generations, data, coefRangeMin, coefRangeMax);
    ga.run("results.json");

    return 0;
}