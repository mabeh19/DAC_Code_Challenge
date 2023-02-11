#include <iostream>
#include <fstream>
#include <string>

#ifdef _TEST
#include "gtest/gtest.h"
#endif /* TEST */

#include "parser/parser.hpp"
#include "jobsolver/jobsolver.hpp"
#include "job/job.hpp"
#include "exceptions/circularexception.hpp"
#include "exceptions/badfileexception.hpp"

const char* USAGE_MESSAGE = R"(
        solve_dependencies requires an input file to solve!
        Perhaps you should checkout the test_files folder, and use
        one of the files available, or get inspired by them to make
        your own :)
)";

int main(int argc, char* argv[])
{
#ifdef _TEST
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();

#else
const char* file;
        
        if (argc > 1) {
                file = argv[1];
        } else {
                std::cout << USAGE_MESSAGE << std::endl;
                return EXIT_FAILURE;
        }

        std::vector<DAC::Job> jobs = DAC::Job::ParseFile(file);
        DAC::JobSolver solver(jobs);

        try {
                auto solution = solver.Solve();

                for (auto group : solution) {
                        std::cout << group;
                }

        } catch (DAC::CircularDependencyException e) {
                std::cout << e.what() << std::endl;
        } catch (DAC::BadFileException e) {
                std::cout << e.what() << std::endl;
        }
        
        return EXIT_SUCCESS;
#endif /* TEST */
}
