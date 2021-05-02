#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class Trie
{
public:
    void insert(const std::string& s_)
    {
        insert(s_, 0, _root);
    }

    bool find(const std::string& s_) const
    {
        return find(s_, 0, _root);
    }

    std::vector<std::string> findAll(const std::string& s_) const
    {
        return findAll(s_, 0, _root);
    }

    bool erase(const std::string& s_)
    {
        return erase(s_, 0, _root);
    }

private:
    struct Elem
    {
        explicit Elem(char data_) : data(data_) {}

        const char data;
        std::unordered_map<char, std::unique_ptr<Elem>> children;

        static constexpr char ROOT_CHAR = '.';
        static constexpr char LEAF_CHAR = '*';
    };

    void insert(const std::string& s_, size_t si_, Elem& elem_)
    {
        auto& children {elem_.children};
        if (si_ < s_.length())
        {
            const char data {s_[si_]};
            auto itr {children.find(data)};
            if (itr == children.end())
            {
                auto res {children.emplace(std::make_pair(data, std::make_unique<Elem>(data)))};
                itr = std::get<0>(res);
            }

            insert(s_, ++si_, *itr->second);
        }
        else
        {
            const char data {Elem::LEAF_CHAR};
            auto itr {children.find(data)};
            if (itr == children.end())
            {
                children.emplace(std::make_pair(data, std::make_unique<Elem>(data)));
            }
        }
    }

    bool find(const std::string& s_, size_t si_, const Elem& elem_) const
    {
        auto& children {elem_.children};
        if (si_ < s_.length())
        {
            const char data {s_[si_]};
            auto itr {children.find(data)};
            if (itr == children.end())
            {
                return false;
            }

            return find(s_, ++si_, *itr->second);
        }

        const char data {Elem::LEAF_CHAR};
        return children.find(data) != children.end();
    }

    std::vector<std::string> findAll(const std::string& s_, size_t si_, const Elem& elem_) const
    {
        std::vector<std::string> foundVect;
        auto& children {elem_.children};
        if (si_ < s_.length())
        {
            const char data {s_[si_]};
            auto itr {children.find(data)};
            if (itr == children.end())
            {
                return foundVect;
            }

            return findAll(s_, ++si_, *itr->second);
        }

        const char data {Elem::LEAF_CHAR};
        auto itr {children.find(data)};
        if (itr != children.end())
        {
            std::vector<std::string> res {findEvery(s_, elem_)};
            std::move(res.begin(), res.end(), std::back_inserter(foundVect));
        }

        return foundVect;
    }

    std::vector<std::string> findEvery(const std::string& s_, const Elem& elem_) const
    {
        std::vector<std::string> foundVect;
        auto& children {elem_.children};

        const char data {Elem::LEAF_CHAR};
        if (children.find(data) != children.end())
        {
            foundVect.push_back(s_);
        }

        for (const auto& pair : children)
        {
            const char data {pair.first};
            if (data != Elem::LEAF_CHAR)
            {
                const std::string s{s_ + data};
                std::vector<std::string> res {findEvery(s, *pair.second)};
                std::move(res.begin(), res.end(), std::back_inserter(foundVect));
            }
        }

        return foundVect;
    }

    bool erase(const std::string& s_, size_t si_, Elem& elem_)
    {
        auto& children {elem_.children};
        if (si_ < s_.length())
        {
            const char data {s_[si_]};
            auto itr {children.find(data)};
            if (itr == children.end())
            {
                return false;
            }

            return erase(s_, ++si_, *itr->second);
        }

        const char data {Elem::LEAF_CHAR};
        auto itr {children.find(data)};
        if (itr != children.end())
        {
            children.erase(itr);
            return true;
        }

        return false;
    }

    Elem _root = Elem{Elem::ROOT_CHAR};
};
