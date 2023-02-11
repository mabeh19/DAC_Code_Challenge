#pragma once
#include <string>
#include <vector>
#include <array>

#include "../parser/parser.hpp"

typedef int32_t ID;

namespace DAC
{

class Job
{
private:
        ID id;
        std::string name;
        std::vector<ID> dependencies;
        bool solved;

public:
        Job() : id{0}, name{""}, solved{false} {}
        Job(ID _id, std::string _name);
        Job(ID _id, std::string _name, std::vector<ID> &deps);        
        template<size_t N>
        Job(ID _id, std::string _name, std::array<ID, N>& deps);

        static std::vector<Job> FromFile(const char* filePath);

        std::vector<ID>& Dependencies();
        const std::string& Name();
        const ID Id();
        std::string& NameAsMut();
        ID& IdAsMut();
        void AddDependency(ID dep);
        void RemoveDependency(ID dep);
        void SetSolved(bool solved);
        bool IsSolved();
        bool operator==(Job const& rhs) const;
        std::string ToString();
        std::string ToStringVerbose();


        static std::vector<Job> ParseFile(const char* filePath, std::string del = " ");

        friend std::istream& operator>>(std::istream& is, Job& j)
        {
                std::string line;

                while (!is.eof()) {
                        line.push_back(is.get());
                }

                std::vector<std::string> tokens = Parser::SplitLine(line);
                j.id = Parser::Parse<ID>(tokens[0]);
                j.name = tokens[1];
                j.dependencies = Parser::ParseArray<ID>(tokens[2]);

                return is;
        }

        friend std::stringstream& operator>>(std::stringstream& ss, Job& j)
        {
                std::string line = ss.str();

                std::vector<std::string> tokens = Parser::SplitLine(line);

                j.id = Parser::Parse<ID>(tokens[0]);
                j.name = tokens[1];
                j.dependencies = Parser::ParseArray<ID>(tokens[2]);

                return ss;
        }
};
}
