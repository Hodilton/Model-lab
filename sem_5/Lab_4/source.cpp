#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <memory>
#include <iomanip>

const double PI = 3.141592653589793;

class ISignalAnalyzer {
public:
    virtual double calculateA0(const std::function<double(double)>& func, double T) = 0;
    virtual double calculateAn(const std::function<double(double)>& func, double T, int n) = 0;
    virtual double calculateBn(const std::function<double(double)>& func, double T, int n) = 0;
    virtual ~ISignalAnalyzer() = default;
};

// Класс для вычисления коэффициентов Фурье
class FourierCoefficientCalculator : public ISignalAnalyzer {
public:
    double calculateA0(const std::function<double(double)>& func, double T) override {
        const int N = 1000; // число разбиений
        double dt = T / N, sum = 0;

        for (int i = 0; i < N; ++i) {
            sum += func(i * dt) * dt;
        }

        return 2 * sum / T;
    }

    double calculateAn(const std::function<double(double)>& func, double T, int n) override {
        const int N = 1000; // число разбиений
        double dt = T / N, sum = 0;

        for (int i = 0; i < N; ++i) {
            double t = i * dt;
            sum += func(t) * std::cos(2 * PI * n * t / T) * dt;
        }

        return 2 * sum / T;
    }

    double calculateBn(const std::function<double(double)>& func, double T, int n) override {
        const int N = 1000; // число разбиений
        double dt = T / N, sum = 0;

        for (int i = 0; i < N; ++i) {
            double t = i * dt;
            sum += func(t) * std::sin(2 * PI * n * t / T) * dt;
        }

        return 2 * sum / T;
    }
};

// Представление гармоники
class Harmonic {
public:
    Harmonic(double amplitude, double frequency, double phase)
        : amplitude(amplitude), frequency(frequency), phase(phase) {
    }

    double valueAt(double t) const {
        return amplitude * std::cos(2 * PI * frequency * t + phase);
    }

private:
    double amplitude;
    double frequency;
    double phase;
};

// Класс для работы с рядом Фурье
class FourierSeries {
public:
    FourierSeries(double a0) : a0(a0 / 2) {}

    void addHarmonic(const Harmonic& harmonic) {
        harmonics.push_back(harmonic);
    }

    double valueAt(double t) const {
        double result = a0;

        for (const auto& harmonic : harmonics) {
            result += harmonic.valueAt(t);
        }

        return result;
    }

private:
    double a0;
    std::vector<Harmonic> harmonics;
};

// Основной анализатор сигнала
class SignalAnalyzer {
public:
    SignalAnalyzer(std::shared_ptr<ISignalAnalyzer> calculator) : calculator(std::move(calculator)) {}

    void analyze(const std::function<double(double)>& func, double T, int harmonicsCount) {
        double a0 = calculator->calculateA0(func, T);

        FourierSeries series(a0);

        for (int n = 1; n <= harmonicsCount; ++n) {
            double an = calculator->calculateAn(func, T, n);
            double bn = calculator->calculateBn(func, T, n);
            double amplitude = std::sqrt(an * an + bn * bn);
            double phase = std::atan2(bn, an);

            series.addHarmonic(Harmonic(amplitude, n / T, phase));
        }

        plot(func, series, T);
    }

private:
    std::shared_ptr<ISignalAnalyzer> calculator;

    void plot(const std::function<double(double)>& func, const FourierSeries& series, double T) {
        const int N = 1000;
        double dt = T / N;

        std::cout << std::fixed << std::setprecision(4);

        for (int i = 0; i <= N; ++i) {
            double t = i * dt;
            std::cout << "t: " << t
                << " Original: " << func(t)
                << " Approximation: " << series.valueAt(t) << '\n';
        }
    }
};

double Function(double t) {
    return std::sin(2 * PI * t) + 0.5 * std::cos(4 * PI * t);
}

int main() {
    auto calculator = std::make_shared<FourierCoefficientCalculator>();
    SignalAnalyzer analyzer(calculator);

    double T = 1.0;
    int harmonicsCount = 5;
    analyzer.analyze(Function, T, harmonicsCount);

    return 0;
}