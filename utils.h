#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <tuple>

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

    /**
     * @brief print_ip - вывод ip-адреса в формате std::tuple
     * @tparam Args... - типы std::tuple
     * @param[in] ip - ip-адрес, представленный std::tuple
     * @param[in] out - поток вывода (по умолчанию std::cout)
     */
    template <typename... Args>
    void print_ip(const std::tuple<Args...>& ip, std::ostream &out = std::cout)
    {
        static_assert(sizeof...(Args) == 4, "Incorrect tuple size");
        using T0 = typename std::tuple_element<0, std::tuple<Args...> >::type;
        using T1 = typename std::tuple_element<1, std::tuple<Args...> >::type;
        using T2 = typename std::tuple_element<2, std::tuple<Args...> >::type;
        using T3 = typename std::tuple_element<3, std::tuple<Args...> >::type;
        static_assert(std::is_same<T0, T1>::value, "");
        static_assert(std::is_same<T0, T2>::value, "");
        static_assert(std::is_same<T0, T3>::value, "");
        out << std::get<0>(ip) << ".";
        out << std::get<1>(ip) << ".";
        out << std::get<2>(ip) << ".";
        out << std::get<3>(ip) << std::endl;
    }

}

#endif // UTILS_H
