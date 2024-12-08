#include "./Dependencies/random.h"

#include <iostream>
#include <vector>
#include <Windows.h>

constexpr int n_sensor = 15; // Количество входов, которые перцептрон принимает для анализа
constexpr int b = 7;  // Порог функции активации

class Perceptron {
public:
    Perceptron(int numSensors) : weights(numSensors, 0) {}

    bool predict(const std::vector<int>& sensorInput) {
        int sum = 0;

        for (int i = 0; i < n_sensor; ++i) {
            sum += sensorInput[i] * weights[i];
        }

        return sum >= b;
    }

    void train(const std::vector<int>& sensorInput, bool isTarget) {
        bool result = predict(sensorInput);

        if (isTarget) {
            if (!result) {
                increase(sensorInput);
            }
        }
        else {
            if (result) {
                decrease(sensorInput);
            }
        }
    }

private:
    std::vector<int> weights;
    void decrease(const std::vector<int>& number) {
        for (int i = 0; i < n_sensor; ++i) {
            if (number[i] == 1) {
                weights[i] -= 1;
            }
        }
    }

    void increase(const std::vector<int>& number) {
        for (int i = 0; i < n_sensor; ++i) {
            if (number[i] == 1) {
                weights[i] += 1;
            }
        }
    }
};

int main() {
    SetConsoleOutputCP(1251);

    // Образцы цифр (идеальные изображения от 0 до 9)
    std::vector<std::vector<int>> nums = {
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, // 0
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1}, // 1
        {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1}, // 2
        {1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}, // 3
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1}, // 4
        {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1}, // 5
        {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1}, // 7
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}  // 9
    };

    Perceptron perceptron(n_sensor);

    int targetDigit = 5; // Цифра, которую нужно распознать
    int iterations = 100000; // Количество тренировочных итераций

    // Тренировка перцептрона
    for (int i = 0; i < iterations; ++i) {

        auto gen = random::Factory::create<random::Type::Integer>();
        int randomDigit = gen->Get(0, 9);

        bool isTarget = (randomDigit == targetDigit);
        perceptron.train(nums[randomDigit], isTarget);
    }

    // Тестовые выборки
    std::vector<std::vector<int>> testSamples = {
       {1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1}, // Вариант 1
       {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1}, // Вариант 2
       {1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1}, // Вариант 3
       {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1}, // Вариант 4
       {1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1}, // Вариант 5
       {1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1}, // Вариант 6
    };

    std::cout << "Результаты" << std::endl;
    for (size_t i = 0; i < testSamples.size(); ++i) {
        std::cout << "Узнал " << targetDigit << " в тесте " << i + 1 << "? "
            << (perceptron.predict(testSamples[i]) ? "Да" : "Нет") << std::endl;
    }

    return 0;
}