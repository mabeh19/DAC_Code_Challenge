#pragma once
#include <cstddef>
#include <string>
#include <vector>

class Group
{
private:
        size_t number;
        std::vector<std::string> members;

public:
        Group();
        Group(size_t n);
        Group(size_t n, std::vector<std::string> m);

        ~Group();

        void AddMember(std::string member);
        size_t Members();

        friend std::ostream& operator<<(std::ostream& os, Group& g);
};
