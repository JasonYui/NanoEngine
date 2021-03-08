#pragma once
#include "common/runtime_module.hpp"
#include "common/type/type_def.hpp"
#include "client/application/window_defination.hpp"

namespace Nano
{

    _interface_ IApplication : IRuntimeModule
    {
    public:
        virtual ~IApplication() = default;
        virtual bool Init() = 0;
        virtual void Update(float dt) = 0;
        virtual void Close() {};

        virtual void CreateDisplayWindow(const WindowDefination& define) = 0;
        virtual bool IsQuit() const = 0;
        virtual void GetWindowSize(OUT uint32_t& width, OUT uint32_t& height) const = 0;
    };
}