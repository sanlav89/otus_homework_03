#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <list>
#include <cassert>

/**
    @brief Функции для вывода ip-адресов в разных форматах.
    1. Адрес может быть представлен в виде произвольного целочисленного типа. Представление
    не зависит от знака типа. Выводить побайтово, начиная со старшего байта, с символом `.`
    (символ точки) в качестве разделителя.
    2. Адрес может быть представлен в виде строки. Выводится как есть.
    3. Адрес может быть представлен в виде контейнеров `std::list`, `std::vector`. Выводится
    содержимое контейнера поэлементно и разделяется `.` (одним символом точка).
    4. Опционально адрес может быть представлен в виде `std::tuple` при условии, что все типы
    одинаковы. Выводится содержимое поэлементно и разделяется `.` (одним символом
    точка).
    @version 1.0
    @date 10/11/2021
*/
namespace utils
{
    /**
     * @brief print_ip - вывод ip-адреса в строковом формате
     * @param[in] ip - строка с ip-адресом
     * @param[in] out - поток вывода (по умолчанию std::cout)
     */
    void print_ip(const std::string &ip, std::ostream &out = std::cout)
    {
        out << ip << std::endl;
    }

    /**
     * @brief print_ip - вывод ip-адреса в целочисленном формате
     * @tparam T - произвольный целочисленный тип
     * @param[in] ip - ip-адрес, представленный целочисленной переменной
     * @param[in] out - поток вывода (по умолчанию std::cout)
     */
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

    /**
     * @cond
     */
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
    /**
     * @endcond
     */

    /**
     * @brief print_ip - вывод ip-адреса в формате контейнеров std::vector, std::list
     * @tparam T - контейнер типа std::vector или std::list
     * @param[in] ip - ip-адрес, представленный контейнером
     * @param[in] out - поток вывода (по умолчанию std::cout)
     */
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
