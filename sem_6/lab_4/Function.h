#pragma once
#include "./CPlusPlus-File/include/json.h"
#include "./Calculates-expressions/src/Calculator.h"

class Function {
private:
    std::map<std::string, std::string> f;
    std::pair<double, double> range;

    std::vector<size_t> n_values;
    double p;

    const calc::Calculator<double> clc;

private:
    auto evaluate(const std::string& func, double x = 0.0) const {
        calc::types::VariableMap<double> var;
        var["x"] = x;
        var["p"] = p;
        return clc.evaluate(func, var);
    }

public:
    double fx(const double x) const { return *evaluate(f.at("f(x)"), x); }
    double I_T() const { return *evaluate(f.at("I_T"), { }); }

    const auto getF() const { return f.at("f(x)"); }
    const auto getRange() const { return range; }
    const auto getP() const { return p; }
    const auto& getNValues() const { return n_values; }

    friend void to_json(json& j, const Function& v) {
        j = json{
            {"f(x)", v.f.at("f(x)")},
            {"f(x)'", v.f.at("f(x)'")},
            {"range", {v.range.first, v.range.second}},
            { "n_values", v.n_values },
            { "p", v.p }
        };
    }
    friend void from_json(const json& j, Function& v) {
        v.f["f(x)"] = j.at("f(x)").get<std::string>();
        v.f["I_T"] = j.at("I_T").get<std::string>();
        j.at("range").get_to(v.range);
        j.at("n_values").get_to(v.n_values);
        j.at("p").get_to(v.p);

        if (v.p <= -1 || v.p >= 1) {
            throw std::invalid_argument("The parameter p must be in the range (-1, 1).");
        }
    }
};