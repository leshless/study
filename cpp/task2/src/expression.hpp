#include <string>
#include <memory>

#define expression_ptr std::shared_ptr<expression>

namespace sympp {
    enum expression_type {
        EXPRESSION_SYMBOL,
        EXPRESSION_NUMBER,
        
        EXPRESSION_ADD,
        EXPRESSION_SUB,
        EXPRESSION_MUL,
        EXPRESSION_DIV,
        EXPRESSION_POW,

        EXPRESSION_EXP,
        EXPRESSION_LOG,
        EXPRESSION_SIN,
        EXPRESSION_COS,
    };

    class expression {
    public:
        virtual expression_type type() = 0;
        virtual long double eval() = 0;
        virtual expression_ptr diff(expression_ptr s) = 0;
        virtual expression_ptr subs(expression_ptr s, expression_ptr e) = 0;
    };

    class symbol : public expression {
        private:
            std::string name;

        public:
            expression_type type();
            long double eval();
            expression_ptr diff(expression_ptr s);
            expression_ptr subs(expression_ptr s, expression_ptr e);
    };

    class number : public expression {
        private:
            long double value;

        public:
            expression_type type();
            long double eval();
            expression_ptr diff(expression_ptr s);
            expression_ptr subs(expression_ptr s, expression_ptr e);
    };

}