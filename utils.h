#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <list>
#include <cassert>

namespace utils
{
    void print_ip(const std::string &ip, std::ostream &out = std::cout)
    {
        out << ip << std::endl;
    }

    template<typename T,
             typename Fake =
             typename std::enable_if<
                 std::is_integral<T>::value, void
                 >::type
             >
    void print_ip(const T &ip, std::ostream &out = std::cout)
    {
        int ip_copy = static_cast<int>(ip);
        out << ((ip_copy >> 24) & 0xFF) << "."
            << ((ip_copy >> 16) & 0xFF) << "."
            << ((ip_copy >>  8) & 0xFF) << "."
            << ((ip_copy >>  0) & 0xFF) << std::endl;
    }

    template<typename T>
    struct is_container {
            static const bool value = false;
    };

    template<typename U>
    struct is_container<std::vector<U>> {
            static const bool value = true;
    };

    template<typename U>
    struct is_container<std::list<U>> {
            static const bool value = true;
    };

    template<typename T,
             typename Fake =
             typename std::enable_if<
                 is_container<T>::value, void
                 >::type
             >
    void print_ip(T &&ip, std::ostream &out = std::cout)
    {
        assert(ip.size() == sizeof(int));
        auto i = 0u;
        for (auto it = ip.begin(); it != ip.end(); it++) {
            out << *it;
            if (i < sizeof(int) - 1) {
                out << '.';
            } else {
                out << std::endl;
            }
            i++;
        }
    }
}

#endif // UTILS_H
