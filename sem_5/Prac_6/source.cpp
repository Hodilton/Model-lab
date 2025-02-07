#include "./Dependencies/random.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <memory>
#include <iomanip>

class Individual {
public:
    double a, b; // Коэффициенты линейной функции
    double fitness; // Приспособленность

    Individual() : a(0), b(0), fitness(0) {}

    void randomize(std::unique_ptr<random::IRandomDoubleGenerator>& randGen) {
        a = randGen->Get(-3.0, 3.0, 2); // Более узкий диапазон [-3, 3]
        b = randGen->Get(-3.0, 3.0, 2);
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

    std::unique_ptr<random::IRandomDoubleGenerator> randGen;
    std::unique_ptr<random::IRandomIntGenerator> randIntGen;

    double evaluateFitness(const Individual& ind) {
        double error = 0.0;
        for (const auto& point : data) {
            double yPredicted = ind.a * point.first + ind.b;
            error += std::pow(yPredicted - point.second, 2); // MSE
        }
        return -error; // Отрицательное значение для максимизации
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

    void validateFitness(const Individual& best) {
        double manualError = 0.0;
        for (const auto& point : data) {
            double yPredicted = best.a * point.first + best.b;
            manualError += std::pow(yPredicted - point.second, 2);
        }
        std::cout << "Manual MSE: " << manualError << ", Fitness: " << -best.fitness << '\n';
    }

public:
    GeneticAlgorithm(size_t popSize, double crossRate, double mutRate, size_t gens,
        std::vector<std::pair<double, double>> inputData)
        : populationSize(popSize), crossoverRate(crossRate), mutationRate(mutRate),
        generations(gens), data(std::move(inputData)) {
        randGen = random::Factory::create<random::Type::Double>();
        randIntGen = random::Factory::create<random::Type::Integer>();
    }

    void run() {
        population.resize(populationSize);
        for (auto& ind : population) {
            ind.randomize(randGen);
        }

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

            std::cout << std::scientific << std::setprecision(8);
            std::cout << "Generation " << gen << ": Best fitness = " << -best.fitness
                << ", a = " << best.a << ", b = " << best.b << '\n';

            validateFitness(best);
            std::cout << std::endl;
        }
    }
};

/*
   ЗАДАЧА
       Найти такие коэффициенты 𝑎 (угол наклона) и 𝑏 (сдвиг), чтобы линейная функция
                   𝑦(𝑥) = 𝑎 * 𝑥 + 𝑏
         минимизировала ошибку между предсказанными значениями 𝑦(𝑥) и исходными значениями 𝑦 из данных.

   ЦЕЛЬ
       Минимизировать среднеквадратичную ошибку (MSE) между значениями 𝑦(𝑥) = 𝑎 * 𝑥 + 𝑏 и заданными точками.

   ДАННЫЕ
       20 - (размер популяции): Количество особей в популяции, которые будут эволюционировать
       0.7 - (вероятность кроссовера): Шанс, что потомки будут создаваться путём смешивания генов родителей
       0.1 - (вероятность мутации): Шанс изменения параметров 𝑎 и 𝑏 у каждой особи
       50 - (количество поколений): Число итераций эволюции, на протяжении которых популяция будет улучшаться
       data - Исходные точки (𝑥,𝑦), которые должны быть аппроксимированы
   */

int main() {
    std::vector<std::pair<double, double>> data = {
        {1, 2}, {2, 4.1}, {3, 6.2}, {4, 8.1}, {5, 10.2}
    };

    GeneticAlgorithm ga(20, 0.7, 0.1, 50, data);
    ga.run();

    return 0;
}