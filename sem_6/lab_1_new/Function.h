#pragma once

#include "./CPlusPlus-File/include/json.h"

#include <string>

class Function {
private:
    std::map<std::string, std::string> f;
    std::pair<double, double> range;

    std::map<std::string, double> eps;

public:
    const std::string& fx() const { return f.at("f(x)"); }
    const std::string& dfx() const { return f.at("f(x)'"); }
    std::pair<double, double> getRange() const { return range; }

    double getEps() const { return eps.at("eps"); }
    double getCheckEps() const { return eps.at("check_eps"); }

    friend void to_json(json& j, const Function& v) {
        j = json{
            {"f(x)", v.f.at("f(x)")},
            {"f(x)'", v.f.at("f(x)'")},
            {"range", {v.range.first, v.range.second}},
            { "eps", v.eps }
        };
    }
    friend void from_json(const json& j, Function& v) {
        v.f["f(x)"] = j.at("f(x)").get<std::string>();
        v.f["f(x)'"] = j.at("f(x)'").get<std::string>();
        j.at("range").get_to(v.range);
        j.at("eps").get_to(v.eps);
    }
};