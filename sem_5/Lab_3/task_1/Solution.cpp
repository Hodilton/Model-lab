#include "./Differentiation.cpp"
#include "./DerivateComparison.cpp"

#include "./Model-lab/IEquation.h"
#include "./Model-lab/Lab_2/InterpolationFactory.h"

namespace task_1 {

    class F1 : public IEquation {
    public:
        double evaluate(double x) const override {
            return exp(x);
        }

        double derivativeFirst(double x) const override {
            return exp(x);
        }

        double derivativeSecond(double x) const override {
            return exp(x);
        }

        std::string getStrF() const override {
            return "e^x";
        }
    };

    static void solution() {
        std::vector<double> x_vals = { 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5 };
        std::vector<double> y_vals = { 2.7, 4.5, 7.4, 12.2, 20.1, 33.1, 54.6, 90.0, 148.4, 244.7 };

        auto function = std::make_unique<F1>();

        auto interpolationMethod = lab_2::Factory::create<lab_2::Type::Lagrange>(x_vals, y_vals);
        auto differentiationMethod = std::make_unique<Differentiation>();

        DerivativeComparison comparison(x_vals,
                                        std::move(differentiationMethod),
                                        std::move(function),
                                        std::move(interpolationMethod));

        auto [tableFirst, polyFirst, funcFirst] = comparison.calculateFirstOrder();
        auto [tableSecond, polySecond, funcSecond] = comparison.calculateSecondOrder();

        for (size_t i = 0; i < tableFirst.size(); ++i) {
            std::cout << "First-order derivative comparison at interval " << i << ":\n"
                << "Table: " << tableFirst[i]
                << ", Poly: " << polyFirst[i]
                << ", Func: " << funcFirst[i] << "\n\n";
        }

        for (size_t i = 0; i < tableSecond.size(); ++i) {
            std::cout << "Second-order derivative comparison at interval " << i << ":\n"
                << "Table: " << tableSecond[i]
                << ", Poly: " << polySecond[i]
                << ", Func: " << funcSecond[i] << "\n\n";
        }
    }
}