#include <iostream>
#include "set.hpp"
#include "iterator.hpp"

int main() {
    try {
        Set<int> a;
        a.insert(1);
        a.insert(2);
        a.insert(3);
        a.insert(3);

        std::cout << "a (size=" << a.getLength() << "): ";
        for (std::size_t i = 0; i < a.getLength(); ++i)
            std::cout << a[i] << " ";
        std::cout << "\n";

        Set<int> b = {2,3,4,5};
        std::cout << "b (size=" << b.getLength() << "): ";
        for (std::size_t i = 0; i < b.getLength(); ++i)
            std::cout << b[i] << " ";
        std::cout << "\n";

        auto c = a + b;
        std::cout << "c = a + b: ";
        for (std::size_t i = 0; i < c.getLength(); ++i)
            std::cout << c[i] << " ";
        std::cout << "\n";

        auto d = a * b;
        std::cout << "d = a * b: ";
        for (std::size_t i = 0; i < d.getLength(); ++i)
            std::cout << d[i] << " ";
        std::cout << "\n";

        auto e = b - a;
        std::cout << "e = b - a: ";
        for (std::size_t i = 0; i < e.getLength(); ++i)
            std::cout << e[i] << " ";
        std::cout << "\n";

        Iterator<int> it1(a);
        std::cout << "iterate a via next/value: ";
        while (!it1.is_end()) {
            std::cout << it1.value() << " ";
            it1.next();
        }
        std::cout << "\n";

        Iterator<int> it2(b);
        std::cout << "iterate b via * and ++: ";
        for (; !it2.is_end(); it2++)
            std::cout << *it2 << " ";
        std::cout << "\n";

        std::cout << "a.at(1) = " << a.at(1) << "\n";

    } catch (const std::out_of_range& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }
    return 0;
}
