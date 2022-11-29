#include "../job.h"
#include <gtest/gtest.h>

TEST(calculateSumFromFiles, sixFilesFromDir)
{
    vector<path> work_files = filterFiles("D:\\qt\\let3\\testODIN");
    double sum = calculateInThreads(3, work_files);

    ASSERT_EQ(sum, 2506.84);
}

TEST(checkFilteredFiles, sixFilesFromDir)
{
    vector<path> work_files = filterFiles("D:\\qt\\let3\\testODIN");

    ASSERT_EQ(work_files.size(), 6);
}

TEST(dataWriting, checkData)
{
    double sum = 10.5;
    writeSumToFile(sum, "D:\\qt\\let3\\testODIN");

    double sumFromFile = readSumFromFile("D:\\qt\\let3\\testODIN\\out.dat");

    ASSERT_EQ(sum, sumFromFile);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
