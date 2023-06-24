#include <iostream>
#include <vector>

template<typename T>
inline std::ostream& operator<<(std::ostream& out_, const std::vector<T>& v_)
{
    out_ << "[";
    if (!v_.empty())
    {
        for (const auto& i : v_)
        {
            out_ << i << ",";

        }
        out_ << "\b"; // use one ANSI backspace characters '\b' to overwrite final ","
    }
    out_ << "]";
    return out_;
}