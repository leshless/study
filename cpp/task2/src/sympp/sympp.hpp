#ifndef SYMPP
#define SYMPP

#include <string>
#include <memory>

namespace sympp {

enum expression_type {
    EXPRESSION_SYMBOL,
    EXPRESSION_NUMBER,
    EXPRESSION_OPERATION,
    EXPRESSION_FUNCTION,
};

template <typename T>
class expression {
    public:
        virtual ~expression() = default;
        
        virtual expression_type Type() = 0;
        virtual std::string String() = 0;
        virtual T Eval() = 0;
        virtual std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x) = 0;
        virtual std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e) = 0;
        virtual std::shared_ptr<expression<T>> Copy() = 0;
};

template <typename T>
class symbol : public expression <T> {
    private:
        std::string name;

    public:
        symbol(std::string name);
        ~symbol() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
class number : public expression <T> {
    private:
        T value;

    public:
        number(T value);
        ~number() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
class add : public expression <T> {
    private:
        std::shared_ptr<expression<T>> left;
        std::shared_ptr<expression<T>> right;

    public:
        add(std::shared_ptr<expression<T>> left, std::shared_ptr<expression<T>> right);
        ~add() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
class sub : public expression <T> {
    private:
        std::shared_ptr<expression<T>> left;
        std::shared_ptr<expression<T>> right;

    public:
        sub(std::shared_ptr<expression<T>> left, std::shared_ptr<expression<T>> right);
        ~sub() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
class mul : public expression <T> {
    private:
        std::shared_ptr<expression<T>> left;
        std::shared_ptr<expression<T>> right;

    public:
        mul(std::shared_ptr<expression<T>> left, std::shared_ptr<expression<T>> right);
        ~mul() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
class div : public expression <T> {
    private:
        std::shared_ptr<expression<T>> left;
        std::shared_ptr<expression<T>> right;

    public:
        div(std::shared_ptr<expression<T>> left, std::shared_ptr<expression<T>> right);
        ~div() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
class pow : public expression <T> {
    private:
        std::shared_ptr<expression<T>> left;
        std::shared_ptr<expression<T>> right;

    public:
        pow(std::shared_ptr<expression<T>> left, std::shared_ptr<expression<T>> right);
        ~pow() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
class ln : public expression <T> {
    private:
        std::shared_ptr<expression<T>> arg;

    public:
        ln(std::shared_ptr<expression<T>> arg);
        ~ln() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
class exp : public expression <T> {
    private:
        std::shared_ptr<expression<T>> arg;

    public:
        exp(std::shared_ptr<expression<T>> arg);
        ~exp() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
class sin : public expression <T> {
    private:
        std::shared_ptr<expression<T>> arg;

    public:
        sin(std::shared_ptr<expression<T>> arg);
        ~sin() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
class cos : public expression <T> {
    private:
        std::shared_ptr<expression<T>> arg;

    public:
        cos(std::shared_ptr<expression<T>> arg);
        ~cos() = default;

        expression_type Type();
        std::string String();
        T Eval();
        std::shared_ptr<expression<T>> Diff(std::shared_ptr<expression<T>> x);
        std::shared_ptr<expression<T>> Subs(std::shared_ptr<expression<T>> s, std::shared_ptr<expression<T>> e);
        std::shared_ptr<expression<T>> Copy();
};

template <typename T>
std::shared_ptr<expression<T>> Symbol(std::string name);

template <typename T>
std::shared_ptr<expression<T>> Number(T value);

template <typename T>
std::shared_ptr<expression<T>> operator+(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs);
template <typename T>
std::shared_ptr<expression<T>> operator+(std::shared_ptr<expression<T>> lhs, T rhs);
template <typename T>
std::shared_ptr<expression<T>> operator+(T lhs, std::shared_ptr<expression<T>> rhs);

template <typename T>
std::shared_ptr<expression<T>> operator-(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs);
template <typename T>
std::shared_ptr<expression<T>> operator-(std::shared_ptr<expression<T>> lhs, T rhs);
template <typename T>
std::shared_ptr<expression<T>> operator-(T lhs, std::shared_ptr<expression<T>> rhs);

template <typename T>
std::shared_ptr<expression<T>> operator*(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs);
template <typename T>
std::shared_ptr<expression<T>> operator*(std::shared_ptr<expression<T>> lhs, T rhs);
template <typename T>
std::shared_ptr<expression<T>> operator*(T lhs, std::shared_ptr<expression<T>> rhs);

template <typename T>
std::shared_ptr<expression<T>> operator/(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs);
template <typename T>
std::shared_ptr<expression<T>> operator/(std::shared_ptr<expression<T>> lhs, T rhs);
template <typename T>
std::shared_ptr<expression<T>> operator/(T lhs, std::shared_ptr<expression<T>> rhs);

template <typename T>
std::shared_ptr<expression<T>> operator^(std::shared_ptr<expression<T>> lhs, std::shared_ptr<expression<T>> rhs);
template <typename T>
std::shared_ptr<expression<T>> operator^(std::shared_ptr<expression<T>> lhs, T rhs);
template <typename T>
std::shared_ptr<expression<T>> operator^(T lhs, std::shared_ptr<expression<T>> rhs);

template <typename T>
std::shared_ptr<expression<T>> Ln(std::shared_ptr<expression<T>> arg);

template <typename T>
std::shared_ptr<expression<T>> Exp(std::shared_ptr<expression<T>> arg);

template <typename T>
std::shared_ptr<expression<T>> Sin(std::shared_ptr<expression<T>> arg);

template <typename T>
std::shared_ptr<expression<T>> Cos(std::shared_ptr<expression<T>> arg);

std::shared_ptr<expression<long double>> Parse(std::string expr);

}

#endif