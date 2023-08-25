#include <iostream>
#include <string>
#include <vector>
#include <memory>

template <typename T>
void draw(const T& x, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << x << '\n';
}

class object_t
{
public:
    template <typename T>
    object_t(T x) : self_(std::make_shared<model<T>>(std::move(x)))
    {
    }

    friend void draw(const object_t& x, std::ostream& out, size_t position)
    {
        x.self_->draw_(out, position);
    }

private:
    struct concept_t
    {
        virtual ~concept_t() = default;
        virtual void draw_(std::ostream&, size_t) const = 0;
    };
    template <typename T>
    struct model final : concept_t
    {
        model(T x) : data_(std::move(x)) {}
        void draw_(std::ostream& out, size_t position) const override
        {
            draw(data_, out, position);
        }

        T data_;
    };

    std::shared_ptr<const concept_t> self_;
};

using document_t = std::vector<object_t>;

void draw(const document_t& x, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << "<document>\n";
    for (const auto& e : x)
        draw(e, out, position + 2);
    out << std::string(position, ' ') << "</document>\n";
}

using history_t = std::vector<document_t>;

void commit(history_t& x)
{
    x.push_back(x.back());
}
void undo(history_t& x)
{
    x.pop_back();
}
document_t& current(history_t& x)
{
    return x.back();
}
