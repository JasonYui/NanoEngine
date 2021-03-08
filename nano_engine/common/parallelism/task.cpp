#include "common/parallelism/task.hpp"

namespace Nano
{
    size_t AllocNextTaskId()
    {
        static std::atomic<size_t> s_NextTaskId = 1;
        size_t id = s_NextTaskId;
        s_NextTaskId++;
        return id;
    }

    template<typename TRet>
    void Task<TRet>::MoveTask(Task&& task)
    {
        ITask::MoveTask(std::forward<ITask>(task));
        m_Future = std::move(task.m_Future);
        m_Func = std::move(task.m_Func);
        task.m_Func = nullptr;
    }

    /*template<typename TRet>
    TRet Task<TRet>::TaskWrapper()
    {
        m_Status = TaskStatus::_Runing;
        TRet ret;
        try
        {
            ret = m_Func();
        }
        catch (...)
        {
            m_Status = TaskStatus::_Faulted;
            LOG_ERROR("run task {0:d} meet error", m_TaskId);
            return ret;
        }
        if (!m_ContinueTasks.empty())
        {
            m_Status = TaskStatus::_WaitingForChild;
            while (m_ContinueTasks.size() > 0)
            {
                UniquePtr<ITask> subTask = std::move(m_ContinueTasks.front());
                m_ContinueTasks.pop();
                subTask->Run();
            }
        }
        else
        {
            m_Status = TaskStatus::_Completed;
        }

        return ret;
    }*/

    void Task<void>::Run()
    {
        if (IsValid())
        {
            m_Future = g_TaskScheduler->AddTask(std::bind(&Task::TaskWrapper, this));
            m_Status = TaskStatus::_WaitingToRun;
        }
    }

    void Task<void>::MoveTask(Task&& task)
    {
        ITask::MoveTask(std::forward<ITask>(task));
        m_Future = std::move(task.m_Future);
        m_Func = std::move(task.m_Func);
        task.m_Func = nullptr;
    }

    void Task<void>::TaskWrapper()
    {
        m_Status = TaskStatus::_Runing;
        try
        {
            m_Func();
        }
        catch (...)
        {
            m_Status = TaskStatus::_Faulted;
            LOG_ERROR("run task {0:d} meet error", m_TaskId);
            return;
        }
        if (!m_ContinueTasks.empty())
        {
            m_Status = TaskStatus::_WaitingForChild;
            while (m_ContinueTasks.size() > 0)
            {
                SharedPtr<ITask> subTask = m_ContinueTasks.front();
                m_ContinueTasks.pop();
                subTask->Run();
            }
        }
        else
        {
            m_Status = TaskStatus::_Completed;
        }
    }
}