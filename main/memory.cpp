#include <string>
#include <ostream>
#include <ctor_wrapper.hpp>
#include <unique_ptr.hpp>
#include <shared_ptr.hpp>
#include <weak_ptr.hpp>

#include <memory>

struct A
{
    A(): A(0, "default") {}
    A(double r_, const std::string& s_) : _r(r_), _s(s_) {}

    friend std::ostream& operator<<(std::ostream& os, const A& a);

private:
    double _r;
    std::string _s;
};

std::ostream& operator<<(std::ostream& os, const A& a)
{
    os << "A " << a._s << ' ' << a._r;
    return os;
}

using CtorWA = CtorWrapper<A>;

int main()
{
    std::cout << "std::unique_ptr\n";
    {
        std::unique_ptr<CtorWA> upA = std::make_unique<CtorWA>(A(1, "one"));
        std::cout << "upA  " << &upA << ' ' << *upA << ' ' << upA.get() << '\n';

        std::unique_ptr<CtorWA> upB = std::make_unique<CtorWA>(A(2, "two"));
        std::cout << "upB  " << &upB << ' ' << *upB << ' ' << upB.get() << '\n';
        // upA = upB; // does not compile
        upA = std::move(upB); // upB / A(1, "one") is destroyed
        std::cout << "upA  " << &upA << ' ' << *upA << ' ' << upA.get() << '\n';
    }

    std::cout << "\nunique_ptr\n";
    {
        unique_ptr<CtorWA> upA = new CtorWA(A(1, "one"));
        std::cout << "upA  " << &upA << ' ' << *upA << ' ' << upA.get() << '\n';

        unique_ptr<CtorWA> upB = new CtorWA(A(2, "two"));
        std::cout << "upB  " << &upB << ' ' << *upB << ' ' << upB.get() << '\n';
        // upA = upB; // does not compile
        upA = std::move(upB); // upB / A(1, "one") is destroyed
        std::cout << "upA  " << &upA << ' ' << *upA << ' ' << upA.get() << '\n';
    }


    std::cout << "\nstd::shared_ptr\n";
    {
        std::shared_ptr<CtorWA> spA0 = std::make_shared<CtorWA>(A(3, "three"));
        std::shared_ptr<CtorWA> spA1 = spA0;
        std::cout << "spA0 " << &spA0 << ' ' << *spA0 << ' ' << spA0.get() << ' ' << spA0.use_count() << '\n';
        std::cout << "spA1 " << &spA1 << ' ' << *spA1 << ' ' << spA1.get() << ' ' << spA1.use_count() << '\n';

        std::unique_ptr<CtorWA> upA = std::make_unique<CtorWA>(A(4, "four"));
        std::shared_ptr<CtorWA> spB {std::move(upA)}; // upA is destroyed
        std::cout << "spB  " << &spB << ' ' << *spB << ' ' << spB.get() << ' ' << spB.use_count() << '\n';

        std::unique_ptr<CtorWA> upB = std::make_unique<CtorWA>(A(5, "five"));
        spA0 = std::move(upB); // upB / spA0 count--
        std::cout << "spA0 " << &spA0 << ' ' << *spA0 << ' ' << spA0.get() << ' ' << spA0.use_count() << '\n';
        std::cout << "spA1 " << &spA1 << ' ' << *spA1 << ' ' << spA1.get() << ' ' << spA1.use_count() << '\n';
    }

    std::cout << "\nshared_ptr\n";
    {
        shared_ptr<CtorWA> spA0 = new CtorWA(A(3, "three"));
        shared_ptr<CtorWA> spA1 = spA0;
        std::cout << "spA0 " << &spA0 << ' ' << *spA0 << ' ' << spA0.get() << ' ' << spA0.use_count() << '\n';
        std::cout << "spA1 " << &spA1 << ' ' << *spA1 << ' ' << spA1.get() << ' ' << spA1.use_count() << '\n';

        unique_ptr<CtorWA> upA = new CtorWA(A(4, "four"));
        shared_ptr<CtorWA> spB {std::move(upA)}; // upA is destroyed
        std::cout << "spB  " << &spB << ' ' << *spB << ' ' << spB.get() << ' ' << spB.use_count() << '\n';

        unique_ptr<CtorWA> upB = new CtorWA(A(5, "five"));
        spA0 = std::move(upB); // upB / spA0 count--
        std::cout << "spA0 " << &spA0 << ' ' << *spA0 << ' ' << spA0.get() << ' ' << spA0.use_count() << '\n';
        std::cout << "spA1 " << &spA1 << ' ' << *spA1 << ' ' << spA1.get() << ' ' << spA1.use_count() << '\n';
    }

    std::cout << "\nstd::weak_ptr\n";
    {
        //shared_ptr<CtorWA> spA0 = new CtorWA(A(6, "six"));
        std::shared_ptr<CtorWA> spC = std::make_shared<CtorWA>(A(6, "six"));
        std::cout << "spC  " << &spC << ' ' << *spC << ' ' << spC.get() << ' ' << spC.use_count() << '\n';

        std::weak_ptr<CtorWA> wpA = spC;
        std::cout << "wpA  " << &wpA << ' ' << wpA.use_count() << '\n';

        spC = std::make_shared<CtorWA>(A(7, "seven")); // A(6, "six") is destroyed
        std::cout << "spC  " << &spC << ' ' << *spC << ' ' << spC.get() << ' ' << spC.use_count() << '\n';

        std::weak_ptr<CtorWA> wpB = spC;
        std::cout << "wpB  " << &wpB << ' ' << wpB.use_count() << '\n';
        std::cout << "wpA  " << &wpA << ' ' << wpA.use_count() << '\n';

        if (auto spwA = wpA.lock())
        {
            std::cout << "here\n";
            std::cout << "spC  " << &spC << ' ' << *spC << ' ' << spC.get() << ' ' << spC.use_count() << '\n';
            std::cout << "spwA  " << &spwA << ' ' << *spwA << ' ' << spwA.get() << ' ' << spwA.use_count() << '\n';
        }
        std::cout << "wpA  " << &wpA << ' ' << wpA.use_count() << '\n';

        if (auto spwB = wpB.lock())
        {
            std::cout << "spC  " << &spC << ' ' << *spC << ' ' << spC.get() << ' ' << spC.use_count() << '\n';
            std::cout << "spwB  " << &spwB << ' ' << *spwB << ' ' << spwB.get() << ' ' << spwB.use_count() << '\n';
        }
        std::cout << "wpB  " << &wpB << ' ' << wpB.use_count() << '\n';
    }

    std::cout << "\nweak_ptr\n";
    {
        shared_ptr<CtorWA> spC = new CtorWA(A(6, "six"));
        std::cout << "spC  " << &spC << ' ' << *spC << ' ' << spC.get() << ' ' << spC.use_count() << '\n';

        weak_ptr<CtorWA> wpA = spC;
        std::cout << "wpA  " << &wpA << ' ' << wpA.use_count() << '\n';

        spC = new CtorWA(A(7, "seven")); // A(6, "six") is destroyed
        std::cout << "spC  " << &spC << ' ' << *spC << ' ' << spC.get() << ' ' << spC.use_count() << '\n';

        weak_ptr<CtorWA> wpB = spC;
        std::cout << "wpB  " << &wpB << ' ' << wpB.use_count() << '\n';
        std::cout << "wpA  " << &wpA << ' ' << wpA.use_count() << '\n';

        if (auto spwA = wpA.lock())
        {
            std::cout << "here\n";
            std::cout << "spC  " << &spC << ' ' << *spC << ' ' << spC.get() << ' ' << spC.use_count() << '\n';
            std::cout << "spwA  " << &spwA << ' ' << *spwA << ' ' << spwA.get() << ' ' << spwA.use_count() << '\n';
        }
        std::cout << "wpA  " << &wpA << ' ' << wpA.use_count() << '\n';

        if (auto spwB = wpB.lock())
        {
            std::cout << "spC  " << &spC << ' ' << *spC << ' ' << spC.get() << ' ' << spC.use_count() << '\n';
            std::cout << "spwB  " << &spwB << ' ' << *spwB << ' ' << spwB.get() << ' ' << spwB.use_count() << '\n';
        }
        std::cout << "wpB  " << &wpB << ' ' << wpB.use_count() << '\n';
    }
    return 0;
}