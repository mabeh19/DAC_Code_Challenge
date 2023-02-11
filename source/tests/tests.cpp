#include "gtest/gtest.h"
#include "../exceptions/badfileexception.hpp"
#include "../exceptions/circularexception.hpp"
#include "../jobsolver/jobsolver.hpp"

#ifdef _TEST
TEST(ParserTests, StringToIDTest) 
{
        int arr[] = {100, 200, 300, 400};
        std::vector<ID> trueIDs(std::begin(arr), std::end(arr));
        std::string idArray("[100,200,300,400]");

        std::vector<ID> ids = Parser::ParseArray<ID>(idArray);
        EXPECT_EQ(ids, trueIDs);
}

TEST(ParserTests, SplitLineTest)
{
        std::vector<std::string> arr = {"100", "build thing", "[200,300,400]"};
        std::string line = "100 build thing [200,300,400]";
        std::vector<std::string> correctVector(std::begin(arr), std::end(arr));

        std::vector<std::string> splitLine = Parser::SplitLine(line);

        EXPECT_EQ(splitLine, correctVector);
}

TEST(ParserTests, ParseLineTest)
{
        std::string line = "100 build [200,300,400]";
        int jobDeps[] = {200, 300, 400};
        auto correctDeps = std::vector<ID>(std::begin(jobDeps), std::end(jobDeps));
        DAC::Job correctJob(100, "build", correctDeps);

        DAC::Job job = Parser::Parse<DAC::Job>(line);

        EXPECT_EQ(job, correctJob);
}

TEST(ParserTests, ParseFileTest)
{
        const char* path = "../../test_files/test1.txt";
        int linkDeps[] = {100};
        auto correctBuildDeps = std::vector<ID>();
        auto correctLinkDeps = std::vector<ID>(std::begin(linkDeps), std::end(linkDeps));
        DAC::Job buildJob(100, "build", correctBuildDeps);
        DAC::Job linkJob(200, "link", correctLinkDeps);
        std::vector<DAC::Job> correctJobs;
        correctJobs.push_back(buildJob);
        correctJobs.push_back(linkJob);

        try {
                std::vector<DAC::Job> jobs = DAC::Job::FromFile(path);
                EXPECT_EQ(jobs, correctJobs);      
        } catch (DAC::BadFileException e) {
                std::cout << e.what() << std::endl;
                EXPECT_TRUE(false);
        }
}
#endif /* TEST */
