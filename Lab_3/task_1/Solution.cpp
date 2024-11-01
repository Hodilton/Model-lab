#include "./Differentiation.cpp"
#include "./DerivateComparison.cpp"

#include "./Model-lab/IEquation.h"
#include "./Model-lab/Lab_2/InterpolationFactory.h"

namespace task_1 {

    class F1 : public IEquation {
    public:
        double evaluate(double x) const override {
            return x * x;
        }

        double derivativeFirst(double x) const override {
            return 2 * x;
        }

        double derivativeSecond(double x) const override {
            return 2;
        }

        std::string getStrF() const override {
            return "x^2";
        }
    };

    static void solution() {
        std::vector<double> x_vals = { 1, 2, 3, 4 };
        std::vector<double> y_vals = { 1, 4, 9, 16 };

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
                << "Table: " << tableFirst[i] << ", Poly: " << polyFirst[i] << ", Func: " << funcFirst[i] << "\n\n";
        }

        for (size_t i = 0; i < tableSecond.size(); ++i) {
            std::cout << "Second-order derivative comparison at interval " << i << ":\n"
                << "Table: " << tableSecond[i] << ", Poly: " << polySecond[i] << ", Func: " << funcSecond[i] << "\n\n";
        }
    }
}