#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "job.hpp"
#include "../exceptions/badfileexception.hpp"
using namespace DAC;


Job::Job(ID _id, std::string _name) : id{_id}, name{_name}, solved{false}
{

}

Job::Job(ID _id, std::string _name, std::vector<ID> &deps) : id{_id}, name{_name}, dependencies{deps}, solved{false}
{

}

template<size_t N>
Job::Job(ID _id, std::string _name, std::array<ID, N>& deps) : id{_id}, name{_name}, solved{false}
{
        for (ID id = std::begin(deps); id != std::end(deps); id++) {
                dependencies.push_back(id);
        }
}

std::vector<Job> Job::FromFile(const char* filePath)
{
        return Job::ParseFile(filePath);       
}

std::vector<ID>& Job::Dependencies()
{
        return this->dependencies;       
}

const std::string& Job::Name()
{
        return this->name;
}

const ID Job::Id()
{
        return this->id;
}

std::string& Job::NameAsMut()
{
        return name;
}

ID& Job::IdAsMut()
{
        return id;
}

void Job::SetSolved(bool solved)
{
        this->solved = solved;
}

bool Job::IsSolved()
{
        return solved;
}

void Job::AddDependency(ID dep)
{
        dependencies.push_back(dep);
}


void Job::RemoveDependency(ID dep)
{
        auto _dep = std::find(dependencies.begin(), dependencies.end(), dep);
        if (_dep != dependencies.end()) {
                dependencies.erase(_dep);
        }
}

bool Job::operator==(const Job& rhs) const
{
        return ((this->id == rhs.id) &&
                (this->name == rhs.name) &&
                (this->dependencies == rhs.dependencies));
}


std::string Job::ToString()
{
const size_t JOB_STRING_MAX_LENGTH = 1024;
        char s[JOB_STRING_MAX_LENGTH];

        std::sprintf(s, "%d - %s", id, name.data());
        
        return std::string(s);
}


std::string Job::ToStringVerbose()
{
const size_t JOB_STRING_MAX_LENGTH = 1024;
        char s[JOB_STRING_MAX_LENGTH];

        std::sprintf(s, "%d - %s: [", id, name.data());

        for (ID id : dependencies) {
                std::sprintf(s, "%s%d,", s, id);
        }

        std::sprintf(s, "%s]", s);
        
        return std::string(s);
}

std::vector<Job> Job::ParseFile(const char* filePath, std::string del)
{
std::vector<Job> jobs;
std::string line;
std::ifstream file;
ssize_t bytesRead;

        file.open(filePath);

        if (!file.is_open() || file.bad()) {
                // If we couldn't find the file, return early
                throw DAC::BadFileException(filePath);
                return jobs;
        }

        while (getline(file, line)) {
                if (line.length() > 0) {
                        Job j = Parser::Parse<Job>(line);
                        jobs.push_back(j);
                }
        }

        return jobs;
}

