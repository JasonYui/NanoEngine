#include "TaskManager.hpp"
#include <functional>
#include <type_traits>
#include "NanoEngine/Common/Type/CommonMarco.hpp"

using namespace Nano;

Nano::TaskManager::TaskManager()
{
    
}

Nano::TaskManager::~TaskManager()
{
}

bool Nano::TaskManager::Init()
{
    return Init(std::thread::hardware_concurrency());
}

bool Nano::TaskManager::Init(uint16_t threadSize)
{
    m_ThreadSize = threadSize;

    m_ThreadPinnedTaskArray = std::make_unique<PriorityTaskArray[]>(threadSize);

    for (uint16_t i = 1; i < m_ThreadSize; ++i)
    {
        m_Workers.emplace_back(&TaskManager::ProcessTask, this, i);
    }
    return true;
}

void Nano::TaskManager::Close()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_IsClosed = true;
    m_Condition.notify_all();
    for(auto& worker: m_Workers)
    {
        worker.join();
    }

    m_ThreadSize = 1;
}

void Nano::TaskManager::Update(float dt)
{

}

bool Nano::TaskManager::HasUnprocessTask(uint32_t threadId) const
{
    ASSERT(threadId < m_ThreadSize)

    for (int i = 0; i < (int)TaskPriority::_SIZE; ++i)
    {
        if (!m_TaskQueueArray[i].empty())
        {
            return true;
        }

        if (!m_ThreadPinnedTaskArray[threadId][i].empty())
        {
            return true;
        }
    }

    return false;
}

void Nano::TaskManager::ProcessTask(uint32_t threadId)
{
    for(;;)
    {
        std::function<void()> task;
        std::unique_lock<std::mutex> lock(m_Mutex);
        m_Condition.wait(lock, [this, threadId]{
            return m_IsClosed || HasUnprocessTask(threadId);
        });

        for (int i = 0; i < (int)TaskPriority::_SIZE; ++i)
        {
            if (!m_ThreadPinnedTaskArray[threadId][i].empty())
            {
                task = m_ThreadPinnedTaskArray[threadId][i].front();
                m_ThreadPinnedTaskArray[threadId][i].pop();
                break;
            }

            if (!m_TaskQueueArray[i].empty())
            {
                task = std::move(m_TaskQueueArray[i].front());
                m_TaskQueueArray[i].pop();
                break;
            }
        }

        task();
    }
}