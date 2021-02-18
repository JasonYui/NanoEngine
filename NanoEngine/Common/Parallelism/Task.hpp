#pragma once
#include <functional>
#include <future>
#include <atomic>

#include "TaskScheduler.hpp"
#include "Common/Fwd.hpp"
#include "Common/Type/ArrayWrapper.hpp"
#include "Common/Type/MemoryWrapper.hpp"

namespace Nano
{
    size_t AllocNextTaskId();

    enum class TaskStatus
    {
        _Invalid = 0,
        _Created,
        _WaitingToRun,
        _Runing,
        _WaitingForChild,
        _Completed,
        _Canceled,
        _Faulted
    };

    class ITask
    {
    public:
        ITask() : m_TaskId(AllocNextTaskId()), m_Status(TaskStatus::_Created) {}
        virtual ~ITask() = default;
        bool IsComplete() const { return m_Status == TaskStatus::_Completed; }
        virtual bool IsValid() const { return m_Status != TaskStatus::_Invalid; }

        virtual void Run() = 0;
    protected:
        virtual void MoveTask(ITask&& task)
        {
            m_TaskId = task.m_TaskId;
            m_ContinueTasks = std::move(task.m_ContinueTasks);
            m_Status = task.m_Status;
            task.m_TaskId = 0;
            task.m_Status = TaskStatus::_Invalid;
        }

        size_t m_TaskId{ 0 };
        Queue<SharedPtr<ITask>> m_ContinueTasks;
        TaskStatus m_Status{ TaskStatus::_Invalid };
    };

    template<typename TRet>
    class Task : public ITask
    {
        using Func = std::function<TRet()>;
    public:
        Task(Func func) : ITask(), m_Func(func) {};
        Task(const Task& func) = delete;
        Task(Task&& task) noexcept { MoveTask(std::forward<Task>(task)); }

        Task& operator= (Task&& task) noexcept
        {
            MoveTask(std::forward<Task>(task));
            return *this;
        }

        bool IsValid() const { return m_Status != TaskStatus::_Invalid && m_Future.valid(); }

        template<typename T>
        SharedPtr<Task<T>> Then(std::function<T()> func)
        {
            SharedPtr<Task<T>> subTask = std::make_shared<Task<T>>(func);
            m_ContinueTasks.push(subTask);
            return subTask;
        }

        TRet Result();

        void Wait() { if (m_Future.valid()) m_Future.wait(); }

        void Run() override
        {
            if (m_Status != TaskStatus::_Invalid)
            {
                m_Future = g_TaskScheduler->AddTask(std::bind(&Task::TaskWrapper, this));
                m_Status = TaskStatus::_WaitingToRun;
            }
        }

    protected:
        void MoveTask(Task&& task);

        TRet TaskWrapper()
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
                    SharedPtr<ITask> subTask = m_ContinueTasks.front();
                    m_ContinueTasks.pop();
                    subTask->Run();
                }
            }
            else
            {
                m_Status = TaskStatus::_Completed;
            }

            return ret;
        }
    private:
        std::future<TRet> m_Future;
        Func m_Func;
    };

    template<>
    class Task<void> : public ITask
    {
        using Func = std::function<void()>;
    public:
        Task(Func func) : ITask(), m_Func(func) {}
        Task(const Task& task) = delete;
        Task(Task&& task) noexcept { MoveTask(std::forward<Task>(task)); }

        Task& operator= (Task&& task) noexcept
        {
            MoveTask(std::forward<Task>(task));
            return *this;
        }

        template<typename T>
        SharedPtr<Task<T>> Then(std::function<T()> func)
        {
            SharedPtr<Task<T>> subTask = std::make_shared<Task<T>>(func);
            m_ContinueTasks.push(subTask);
            return subTask;
        }

        void Wait() { if (m_Future.valid()) m_Future.wait(); }

        void Run() override;

    protected:
        void MoveTask(Task&& task);

        void TaskWrapper();
    private:
        std::future<void> m_Future;
        Func m_Func;
    };
}