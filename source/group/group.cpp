#include <iostream>
#include "group.hpp"

Group::Group() : number{0}
{

}

Group::Group(size_t n) : number{n}
{

}

Group::Group(size_t n, std::vector<std::string> m) : number{n}, members{m}
{

}

Group::~Group()
{

}

void Group::AddMember(std::string member)
{
        members.push_back(member);
}

size_t Group::Members()
{
        return members.size();
}

std::ostream& operator<<(std::ostream& os, Group& g)
{
        os << "[Group " << g.number << "]" << std::endl;
        for (auto s : g.members) {
                os << s << std::endl;
        }

        return os;
}
