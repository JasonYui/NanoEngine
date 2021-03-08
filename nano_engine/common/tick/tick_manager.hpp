#pragma once
#include <chrono>

#include "common/fwd.hpp"

namespace Nano
{
    enum class TickMode
    {
        _Fixed,
        _Dynamic
    };

    class TickManager
    {
    public:
        bool Init(TickMode mode, uint32_t frameRate = 30) 
        { 
            return ResetTickMode(mode, frameRate);
        }

        void Close() {}

        bool ResetTickMode(TickMode mode, uint32_t frameRate = 30)
        {
            if (frameRate == 0)
            {
                LOG_ERROR("frame rate must over 0");
                return false;
            }
            m_InitTime = std::chrono::high_resolution_clock::now();
            m_TickMode = mode;
            m_FixedFrameRate = frameRate;
            m_FrameInterval = 1.0f / frameRate;
            m_AccumulatedTime = 0.0;
            return true;
        }

        bool TryGetDeltaTime(OUT float& deltaTime)
        {
            double seconds = GetSecondsCount();
            double delta = seconds - m_LastSecondsCount;
            m_LastSecondsCount = seconds;
            if (m_TickMode == TickMode::_Dynamic)
            {
                deltaTime = static_cast<float>(delta);
                return true;
            }
            else
            {
                m_AccumulatedTime += delta;
                if (m_AccumulatedTime > m_FrameInterval)
                {
                    deltaTime = static_cast<float>(m_FrameInterval);
                    m_AccumulatedTime -= m_FrameInterval;
                    return true;
                }
            }

            return false;
        }

        double GetSecondsCount() const
        {
            TimePoint current_time = std::chrono::high_resolution_clock::now();
            auto micro_seconds = std::chrono::duration_cast<std::chrono::microseconds>(current_time - m_InitTime);
            return static_cast<double>(micro_seconds.count()) / 1000000.0;
        }

    private:
        using TimePoint = std::chrono::high_resolution_clock::time_point;
        TimePoint m_InitTime;

        TickMode m_TickMode{ TickMode::_Fixed };
        uint32_t m_FixedFrameRate{ 30 };
        double m_FrameInterval{ 0.0 };
        double m_LastSecondsCount{ 0.0 };
        double m_AccumulatedTime{ 0.0 };

    };
}