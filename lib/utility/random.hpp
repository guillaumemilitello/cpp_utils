#include <random>
#include <vector>
#include <limits>

template<typename T>
T getRand(const T& min_, const T& max_)
{
    std::default_random_engine re;
    if constexpr (std::is_floating_point_v<T>)
    {
        std::uniform_real_distribution<T> uniform_dist(min_, max_);
        return uniform_dist(re);
    }
    if constexpr (std::is_integral_v<T>)
    {
        std::uniform_int_distribution<T> uniform_dist(min_, max_);
        return uniform_dist(re);
    }
}

template<typename T>
std::vector<T> getRandVect(size_t size_, const T min_=std::numeric_limits<T>::min(), const T max_=std::numeric_limits<T>::max())
{
    std::vector<T> res(size_);
    for(size_t i=0; i<size_; ++i)
    {
        res[i] = static_cast<T>(getRand(min_, max_));
    }
    return res;
}

