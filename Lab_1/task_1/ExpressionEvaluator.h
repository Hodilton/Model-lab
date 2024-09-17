#ifndef TASK_1_EXPRESSIONEVALUATOR_H
#define TASK_1_EXPRESSIONEVALUATOR_H

#include <stack>
#include <sstream>

#include "./Value.h"

//class ExpressionEvaluator {
//public:
//    static Value<double> evaluate(const std::string& expression, const std::map<std::string, Value<double>>& letters) {
//        std::stack<Value<double>> values;
//        std::stack<char> ops;
//
//        auto tokens = tokenize(expression);
//
//        for (const auto& token : tokens) {
//            if (token == "(") {
//                ops.push('(');
//            }
//            else if (token == ")") {
//                while (!ops.empty() && ops.top() != '(') {
//                    char op = ops.top();
//                    ops.pop();
//
//                    Value<double> right = values.top();
//                    values.pop();
//
//                    Value<double> left = values.top();
//                    values.pop();
//
//                    values.push(applyOperator(left, right, op));
//                }
//                ops.pop(); // ������� '(' �� �����
//            }
//            else if (token == "+" || token == "*") {
//                while (!ops.empty() && (ops.top() == '+' || ops.top() == '*')) {
//                    char op = ops.top();
//                    ops.pop();
//
//                    Value<double> right = values.top();
//                    values.pop();
//
//                    Value<double> left = values.top();
//                    values.pop();
//
//                    values.push(applyOperator(left, right, op));
//                }
//                ops.push(token[0]);
//            }
//            else {
//                // ���������, �������� �� token ����������
//                if (letters.find(token) != letters.end()) {
//                    Value<double> varValue = letters.at(token);
//                    values.push(varValue);
//                }
//                else {
//                    throw std::runtime_error("Variable '" + token + "' not found in the provided data.");
//                }
//            }
//        }
//
//        // ��������� ����������, ���� �������� ���������
//        while (!ops.empty()) {
//            char op = ops.top();
//            ops.pop();
//
//            Value<double> right = values.top();
//            values.pop();
//
//            Value<double> left = values.top();
//            values.pop();
//
//            values.push(applyOperator(left, right, op));
//        }
//
//        return values.top();
//    }
//
//    private:
//        static std::vector<std::string> tokenize(const std::string& expression) {
//            std::vector<std::string> tokens;
//            std::string currentToken;
//
//            for (char ch : expression) {
//                if (std::isspace(ch)) {
//                    continue; // ���������� �������
//                }
//                else if (ch == '(' || ch == ')') {
//                    // ���� ��� ������, ��������� ������� ����� (���� �� ����) � ���� ������
//                    if (!currentToken.empty()) {
//                        tokens.push_back(currentToken);
//                        currentToken.clear();
//                    }
//                    tokens.push_back(std::string(1, ch)); // ��������� ������ ��� �����
//                }
//                else if (ch == '+' || ch == '*') {
//                    // ���� ��� ��������, ��������� ������� ����� (���� �� ����) � ��������
//                    if (!currentToken.empty()) {
//                        tokens.push_back(currentToken);
//                        currentToken.clear();
//                    }
//                    tokens.push_back(std::string(1, ch)); // ��������� �������� ��� �����
//                }
//                else {
//                    // ���� ��� ����� (����������), ��������� � � �������� ������
//                    currentToken += ch;
//                }
//            }
//
//            // ���� ������� ������� �����, ��������� ��� � ������
//            if (!currentToken.empty()) {
//                tokens.push_back(currentToken);
//            }
//
//            return tokens;
//        }
//
//private:
//    static Value<double> applyOperator(const Value<double>& left, const Value<double>& right, char op) {
//        switch (op) {
//        case '+':
//            return Value<double>(left + right);
//        case '*':
//            return Value<double>(left * right);
//        default:
//            return Value<double>();
//        }
//    }
//};

template <typename T>
class IOperator {
public:
    virtual Value<T> apply(Value<T>& left, const Value<T>& right) const = 0;
    virtual char symbol() const = 0;
    virtual ~IOperator() = default;
};

template <typename T>
class PlusOperator : public IOperator<T> {
public:
    Value<T> apply(Value<T>& left, const Value<T>& right) const override {
        return left + right;
    }
    char symbol() const override {
        return '+';
    }
};

template <typename T>
class MinusOperator : public IOperator<T> {
public:
    Value<T> apply(Value<T>& left, const Value<T>& right) const override {
        return left - right;
    }
    char symbol() const override {
        return '-';
    }
};

template <typename T>
class MultiplyOperator : public IOperator<T> {
public:
    Value<T> apply(Value<T>& left, const Value<T>& right) const override {
        return left * right;
    }
    char symbol() const override {
        return '*';
    }
};

template <typename T>
class DivideOperator : public IOperator<T> {
public:
    Value<T> apply(Value<T>& left, const Value<T>& right) const override {
        return left / right;
    }
    char symbol() const override {
        return '/';
    }
};

// ����� ��� ���������� ���������
template <typename T>
class ExpressionEvaluator {
public:
    Value<T> evaluate(const std::string& expression, const std::map<std::string, Value<T>>& letters) {
        std::stack<Value<T>> values;
        std::stack<char> ops;

        auto tokens = tokenize(expression);

        for (const auto& token : tokens) {
            if (token == "(") {
                ops.push('(');
            }
            else if (token == ")") {
                while (!ops.empty() && ops.top() != '(') {
                    char op = ops.top();
                    ops.pop();
                    applyTopOperator(values, op);
                }
                ops.pop(); // ������� '(' �� �����
            }
            else if (isOperator(token[0])) {
                while (!ops.empty() && precedence(ops.top()) >= precedence(token[0])) {
                    char op = ops.top();
                    ops.pop();
                    applyTopOperator(values, op);
                }
                ops.push(token[0]);
            }
            else {
                // ���������, �������� �� token ����������
                if (letters.find(token) != letters.end()) {
                    values.push(letters.at(token));
                }
                else {
                    throw std::runtime_error("Variable '" + token + "' not found in the provided data.");
                }
            }
        }

        // ��������� ����������, ���� �������� ���������
        while (!ops.empty()) {
            char op = ops.top();
            ops.pop();
            applyTopOperator(values, op);
        }

        return values.top();
    }

    void addOperator(std::shared_ptr<IOperator<T>> op) {
        operators[op->symbol()] = op;
    }

private:
    std::map<char, std::shared_ptr<IOperator<T>>> operators;

    // ����� ��� ����������� ������
    std::vector<std::string> tokenize(const std::string& expression) {
        std::vector<std::string> tokens;
        std::string currentToken;

        for (char ch : expression) {
            if (std::isspace(ch)) {
                continue; // ���������� �������
            }
            else if (ch == '(' || ch == ')') {
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
                tokens.push_back(std::string(1, ch)); // ��������� ������ ��� �����
            }
            else if (isOperator(ch)) {
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
                tokens.push_back(std::string(1, ch)); // ��������� �������� ��� �����
            }
            else {
                currentToken += ch;
            }
        }

        if (!currentToken.empty()) {
            tokens.push_back(currentToken);
        }

        return tokens;
    }

    // ���������� ��������� �� �����
    void applyTopOperator(std::stack<Value<T>>& values, char op) {
        if (values.size() < 2) throw std::runtime_error("Invalid expression");

        Value<T> right = values.top();
        values.pop();
        Value<T> left = values.top();
        values.pop();

        if (operators.find(op) == operators.end()) {
            throw std::runtime_error("Unknown operator: " + std::string(1, op));
        }

        values.push(operators[op]->apply(left, right));
    }

    // ��������, �������� �� ������ ����������
    bool isOperator(char ch) const {
        return operators.find(ch) != operators.end();
    }

    // ��������� ����������
    int precedence(char op) const {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
};

#endif // !TASK_1_EXPRESSIONEVALUATOR_H