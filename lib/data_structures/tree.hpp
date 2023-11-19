#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <string>

template<typename T>
class Tree
{
protected:
    struct Elem
    {
        virtual const T& data() const = 0;
        virtual Elem* const left() const = 0;
        virtual Elem* const right() const = 0;
        virtual ~Elem() {}
    };

    Elem* _root = nullptr;

public:
    virtual ~Tree()
    {
        clear(_root);
    }

    virtual void push(const T& data_) = 0;

    bool contains(const T& data_) const
    {
        return contains(data_, _root);
    }

    std::string to_string() const
    {
        return to_string(_root);
    }

    std::string to_tree_string() const
    {
        std::string res;
        const std::vector<std::string> res_v {to_tree_string(_root, 0)};
        for (const auto& s : res_v)
        {
            res += s + "\n";
        }
        return res;
    }

    std::string to_string_inorder() const
    {
        return to_string_inorder(_root);
    }

    std::string to_string_preorder() const
    {
        return to_string_preorder(_root);
    }

    std::string to_string_postorder() const
    {
        return to_string_postorder(_root);
    }

    std::string to_string_levelorder() const
    {
        std::string res;
        const std::vector<std::string> res_v {to_string_levelorder(_root)};
        for (const auto& s : res_v)
        {
            res += s + " ";
        }
        return res;
    }

    template<typename T_>
    friend std::ostream& operator<<(std::ostream& os_, const Tree<T_>& s_);

private:
    bool contains(const T& data_, Elem* const & root_) const
    {
        if (root_ == nullptr)
        {
            return false;
        }
        else
        {
            if (data_ == root_->data())
            {
                return true;
            }
            else if (data_ < root_->data())
            {
                return contains(data_, root_->left());
            }
            else
            {
                return contains(data_, root_->right());
            }
        }
    }

    void clear(Elem* root_)
    {
        if (root_ == nullptr)
        {
            return;
        }
        else
        {
            clear(root_->left());
            clear(root_->right());
            delete root_;
        }
    }

    static std::string get_space(size_t len_, char char_=' ')
    {
        std::string res;
        while (len_-- > 0)
        {
            res += char_;
        }
        return res;
    }

    static std::string get_string_with_padding(std::string s)
    {
        constexpr unsigned PADDING_SIZE {1};
        for (unsigned i=0; i < PADDING_SIZE; ++i)
        {
            s.insert(0, " ");
            s.append(" ");
        }
        return s;
    }

    static std::string to_string_with_padding(const T& v_)
    {
        return get_string_with_padding(std::to_string(v_));
    }

    static std::vector<std::string> to_tree_string(const Elem* const root_, size_t depth_)
    {
        if (root_ == nullptr)
        {
            return std::vector<std::string>{get_string_with_padding("-")};
        }

        const std::string str_data {to_string_with_padding(root_->data())};

        if (root_->left() == nullptr && root_->right() == nullptr)
        {
            return std::vector<std::string> {str_data};
        }

        std::vector<std::string> l_str_v {to_tree_string(root_->left(),  depth_ + 1)};
        std::vector<std::string> r_str_v {to_tree_string(root_->right(), depth_ + 1)};

        std::vector<std::string> res_v(std::max(l_str_v.size(), r_str_v.size()) + 1);

        if (l_str_v.size())
        {
            res_v[0] = get_space(l_str_v[0].length());

            size_t str_l {l_str_v[0].find_last_not_of(' ')};
            ++str_l;
            ++str_l;
            for(;str_l < l_str_v[0].length(); ++str_l)
            {
                l_str_v[0][str_l] = '-';
            }
        }
        res_v[0] += str_data;
        if (r_str_v.size())
        {
            res_v[0] += get_space(r_str_v[0].length());

            int str_f {static_cast<int>(r_str_v[0].find_first_not_of(' '))};
            --str_f;
            --str_f;
            for(;str_f >= 0; --str_f)
            {
                r_str_v[0][str_f] = '-';
            }
        }

        for(unsigned li = 0; li<l_str_v.size(); ++li)
        {
            res_v[li+1] += std::move(l_str_v[li]);
        }

        if (l_str_v.size())
        {
            for(unsigned li = l_str_v.size() + 1; li<res_v.size(); ++li)
            {
                res_v[li] += get_space(l_str_v[0].length());
            }
        }

        res_v[1] += get_space(str_data.length(), '-');

        for(unsigned i=2; i<res_v.size(); ++i)
        {
            res_v[i] += get_space(str_data.length());
        }

        for(unsigned ri = 0; ri<r_str_v.size(); ++ri)
        {
            res_v[ri+1] += std::move(r_str_v[ri]);
        }

        if (r_str_v.size())
        {
            for(unsigned li = r_str_v.size() + 1; li<res_v.size(); ++li)
            {
                res_v[li] += get_space(r_str_v[0].length());
            }
        }

        return res_v;
    }

    static std::string to_string(Elem* const root_)
    {
        if (root_ == nullptr)
        {
            return std::string{};
        }

        return std::to_string(root_->data()) + " " +
               to_string(root_->left()) +
               to_string(root_->right());
    }

    static std::string to_string_inorder(Elem* const root_)
    {
        if (root_ == nullptr)
        {
            return std::string{};
        }

        return to_string_inorder(root_->left()) +
               std::to_string(root_->data()) + " " +
               to_string_inorder(root_->right());
    }

    static std::string to_string_preorder(Elem* const root_)
    {
        if (root_ == nullptr)
        {
            return std::string{};
        }

        return std::to_string(root_->data()) + " " +
               to_string_inorder(root_->left()) +
               to_string_inorder(root_->right());
    }

    static std::string to_string_postorder(Elem* const root_)
    {
        if (root_ == nullptr)
        {
            return std::string{};
        }

        return to_string_inorder(root_->left()) +
               to_string_inorder(root_->right()) +
               std::to_string(root_->data()) + " ";
    }

    static std::vector<std::string> to_string_levelorder(Elem* const root_)
    {
        if (root_ == nullptr)
        {
            return std::vector<std::string>{};
        }

        std::queue<Elem*> q;
	    q.emplace(root_);

        std::vector<std::string> res_v;

        while (!q.empty())
        {
            Elem* const root = q.front();
            q.pop();
            res_v.emplace_back(std::to_string(root->data()));

            if (root->left() != nullptr)
            {
                q.emplace(root->left());
            }

            if (root->right() != nullptr)
            {
                q.emplace(root->right());
            }
        }

        return res_v;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os_, const Tree<T>& s_)
{
    os_ << "[ " << s_.to_string() << "]";
    return os_;
}
