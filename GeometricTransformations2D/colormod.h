#ifndef COLORMOD_H_INCLUDED
#define COLORMOD_H_INCLUDED

#include <ostream>
namespace Color {
    enum Code {
        FG_RED      = 91,
        FG_GREEN    = 92,
        FG_BLUE     = 94,
        FG_DEFAULT  = 39,
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

#endif // COLORMOD_H_INCLUDED
