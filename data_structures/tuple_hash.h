struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

namespace
{
    template <class T>
    inline void hash_combine(std::size_t& seed, const T& value)
    {
        // Code from boost
        // Reciprocal of the golden ratio helps spread entropy and handles duplicates.
        // See Mike Seymour in magic-numbers-in-boosthash-combine: http://stackoverflow.com/questions/4948780
        seed ^= std::hash<T>()(value) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    // Recursive template code derived from Matthieu M.
    template <class T, std::size_t I = std::tuple_size<T>::value-1>
    struct HashValueImpl
    {
        static void apply(std::size_t& seed, const T& tuple)
        {
            HashValueImpl<T, I-1>::apply(seed, tuple);
            hash_combine(seed, std::get<I>(tuple));
        }
    };

    template <class T>
    struct HashValueImpl<T,0>
    {
        static void apply(std::size_t& seed, const T& tuple)
        {
            hash_combine(seed, std::get<0>(tuple));
        }
    };
}

struct tuple_hash
{
    template<typename... Args>
    std::size_t operator() (const std::tuple<Args...>& tuple) const
    {
        size_t seed = 0;
        HashValueImpl<std::tuple<Args...>>::apply(seed, tuple);
        return seed;
    }
};
