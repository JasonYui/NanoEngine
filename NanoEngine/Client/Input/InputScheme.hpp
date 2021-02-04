#pragma once
#include "Common/Fwd.hpp"
#include "Common/Type/StringID.hpp"
#include "Common/Type/MapWrapper.hpp"

namespace Nano
{
    struct TempInputDef
    {
        StringID key;
        StringID modifyKey1;
        StringID modifyKey2;
    };

    class InputScheme
    {
    private:
        HashMap<uint32_t, StringID> m_InputMapping;
    };
}