#include "jobsolver.hpp"
#include "circularexception.hpp"

namespace DAC
{

JobSolver::JobSolver()
{

}

JobSolver::JobSolver(std::vector<Job> _jobs) : jobs{_jobs}
{

}


JobSolver::JobSolver(char *filePath)
{

}

JobSolver::~JobSolver()
{

}

void JobSolver::AddJob(Job const& job)
{
        this->jobs.push_back(job);
}

Solution JobSolver::Solve()
{
        return SolveDependencies();
}

Solution JobSolver::SolveDependenciesRecursive(Solution& solution, size_t groupNr)
{
        Group group = DetermineGroup(groupNr);
        
        if (IsSolved() == false && group.Members() == 0)
                throw DAC::CircularDependencyException(jobs);

        solution.push_back(group);
        groupNr++;
 
        if (IsSolved() == false)
                SolveDependenciesRecursive(solution, groupNr);

        return solution;
}

Solution JobSolver::SolveRecursive()
{
        Solution solution;
        size_t groupNr = 1;
        return SolveDependenciesRecursive(solution, groupNr);
}

Solution JobSolver::SolveDependencies()
{
        Solution solution;
        size_t groupNr = 1;

        do {
                Group group = DetermineGroup(groupNr);
                
                if (IsSolved() == false && group.Members() == 0) {
                        throw DAC::CircularDependencyException(jobs);
                }
                else
                        solution.push_back(group);
                
                groupNr++;
        } while (IsSolved() == false);

        return solution;
}

Group JobSolver::DetermineGroup(size_t groupNr)
{
        Group group(groupNr);
        std::vector<Job> freeJobs = FindJobsWithNoDependecies();

        for (auto& job : freeJobs) {
                group.AddMember(job.ToString());
                RemoveDependencyFromOtherJobs(job.Id());
        }

        return group;
}

std::vector<Job> JobSolver::FindJobsWithNoDependecies()
{
        std::vector<Job> freeJobs;

        for (auto& job : jobs) {
                if (job.Dependencies().empty() && job.IsSolved() == false) {
                        freeJobs.push_back(job);
                        job.SetSolved(true);
                }
        }

        return freeJobs;       
}


void JobSolver::RemoveDependencyFromOtherJobs(ID id)
{
        for (auto& job : jobs) {
                job.RemoveDependency(id);
        }
}


bool JobSolver::IsSolved()
{
        bool solved = true;

        for (auto& job : jobs) {
                if (job.Dependencies().empty() == false || job.IsSolved() == false) {
                        solved = false;
                }
        }

        return solved;
}


}
