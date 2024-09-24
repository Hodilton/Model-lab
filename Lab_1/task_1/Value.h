#ifndef TASK_1_VALUE_H
#define TASK_1_VALUE_H

#include <./file_work/include/json/json.hpp> 
using json = nlohmann::json;

template <typename T>
class Value {
public:
    T value;
    double absoluteError;
    double relativeError;

    Value();
    Value(T value, double absErr, double relErr);

    void calcAbsoluteError();
    void calcRelatError();

    Value operator+(const Value& other);
    Value operator-(const Value& other);

    Value operator*(const Value& other);
    Value operator/(const Value& other);

    friend void to_json(json& j, const Value<T>& v) {
        j = json{ {"value", v.value},
                  {"absoluteError", v.absoluteError},
                  {"relativeError", v.relativeError}
        };
    }
    friend void from_json(const json& j, Value<T>& v) {
        j.at("value").get_to(v.value);
        j.at("relativeError").get_to(v.relativeError);

        v.absoluteError = 0;
        v.calcAbsoluteError();
    }

    using Data = std::map<std::string, std::map<std::string, Value<double>>>;

    /*void to_json(json& j, const typename Value<T>::Data& data) {

        for (const auto& text : data) {

            json jsonData;
            for (const auto& letterPair : text.second) {
                to_json(jsonData[letterPair.first], letterPair.second);
            }

            j[text.first] = jsonData;
        }
    }*/
    void from_json(const json& j, typename Value<T>::Data& data) {

        for (auto it = j.begin(); it != j.end(); ++it) {

            typename Value<T>::Data lettersMap;
            for (auto letterIt = it->begin(); letterIt != it->end(); ++letterIt) {
                Value<T> value;

                from_json(letterIt.value(), value);

                lettersMap[letterIt.key()] = value;
            }

            data[it.key()] = lettersMap;
        }
    }
};

#include "Value.cpp"
#endif // !TASK_1_VALUE_H