#include "utils.h"

int main(void)
{
    utils::print_ip(char(-1));
    utils::print_ip(short(0));
    utils::print_ip(int(2130706433));
    utils::print_ip(long(8875824491850138409));
    utils::print_ip(std::string("192.168.0.1"));
    utils::print_ip(std::vector<int>{1, 2, 3, 4});
    utils::print_ip(std::list<int>{5, 6, 7, 8});
    return 0;
}
