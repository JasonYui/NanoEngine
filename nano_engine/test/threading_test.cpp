#include "gtest/gtest.h"
#include "common/parallelism/task.hpp"

using namespace Nano;

namespace Test
{
    TEST(TheadingTest, Test_Task)
    {
        Task<void> taskA([](){ LOG_INFO("I am taskA"); });
        Task<void> taskB = std::move(taskA);
        auto subTask = taskB.Then<bool>([]() { LOG_INFO("I am subA Task"); return true; });
        taskB.Run();
        taskB.Wait();
        subTask->Wait();

        Task<int>* taskC = new Task<int>([]() { LOG_INFO("I am taskC"); return 10; });
        auto subTaskC = taskC->Then<int>([taskC] { 
            LOG_INFO("I am taskC sub Task");
            return taskC->Result() + 1;
        });

        taskC->Run();
        LOG_INFO("taskC future is valid {0}", taskC->IsValid());
        LOG_INFO("result of taskC {0}", taskC->Result());
        LOG_INFO("result of subTaskC {0}", subTaskC->Result());

        delete taskC;
    }
}