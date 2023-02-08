#pragma once
#include <string>
#include <vector>
using namespace std;

#include "group.hpp"
#include "job.hpp"

typedef std::vector<Group> Solution;

namespace DAC
{
class JobSolver
{
private:
        std::vector<Job> jobs;
        std::vector<Job> FindJobsWithNoDependecies();
        Group DetermineGroup(size_t groupNr);
        Solution SolveDependencies();
        Solution SolveDependenciesRecursive(Solution& solution, size_t groupNr);
        
        bool IsSolved();
        void RemoveDependencyFromOtherJobs(ID id);

public:
        JobSolver();
        JobSolver(std::vector<Job> _jobs);
        JobSolver(char *filePath);
        ~JobSolver();

        void AddJob(Job const& job);
        Solution Solve();
        Solution SolveRecursive();
};
}
