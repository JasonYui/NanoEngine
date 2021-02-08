#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib") 

#include "D3DGraphicsManager.hpp"
#include "Client/ClientGlobalContext.hpp"
#include "Client/Application/Application.hpp"
#include "Client/Platform/Application/Win/WinApplication.hpp"
#include <comdef.h>


namespace Nano
{
    bool D3dGraphicsManager::Init()
    {
        if (!CreateDevice() || !CheckMSAA() || !CreateCommandQueue() || !CreateSwapChain())
            return false;
        return true;
    }

    void D3dGraphicsManager::Close()
    {
    }

    void D3dGraphicsManager::Update(float dt)
    {
    }

    void D3dGraphicsManager::LogAdapters()
    {
        uint32_t i = 0;
        ComPtr<IDXGIFactory4> factory;
        ComPtr<IDXGIAdapter> adapter;

        if (FAILED(CreateDXGIFactory(IID_PPV_ARGS(factory.GetAddressOf()))))
        {
            return;
        }

        while (factory->EnumAdapters(i, adapter.GetAddressOf()) != DXGI_ERROR_NOT_FOUND)
        {
            i++;
            DXGI_ADAPTER_DESC desc;
            adapter->GetDesc(&desc);
            std::wstring name = desc.Description;
            LOG_INFO("find adapter: {0}", (char*)name.c_str());
        }

    }

    void D3dGraphicsManager::GetHardwareAdapter(IDXGIFactory* factory, IDXGIAdapter** adapter)
    {
        *adapter = nullptr;
        uint32_t i = 0;
        while (factory->EnumAdapters(i, adapter) != DXGI_ERROR_NOT_FOUND)
        {
            i++;
            if (SUCCEEDED(D3D12CreateDevice(*adapter, D3D_FEATURE_LEVEL_12_0, _uuidof(ID3D12Device), nullptr)))
                return;
        }

        if (*adapter == nullptr)
            (*adapter)->Release();
    }

    bool D3dGraphicsManager::CreateDevice()
    {
#if  defined(DEBUG) || defined(_DEBUG)
        ComPtr<ID3D12Debug> debugController;
        if (FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()))))
        {
            LOG_ERROR("call D3D12GetDebugInterface failed");
                return false;
        }
        debugController->EnableDebugLayer();
#endif

        if (FAILED(CreateDXGIFactory(IID_PPV_ARGS(m_Factory.GetAddressOf()))))
        {
            LOG_ERROR("call CreateDXGIFactory failed");
            return false;
        }

        ComPtr<IDXGIAdapter> adapter;
        GetHardwareAdapter(m_Factory.Get(), adapter.GetAddressOf());

        if (FAILED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(m_Device.GetAddressOf()))))
        {
            LOG_ERROR("call D3D12CreateDevice failed");
            return false;
        }
        return true;
    }
    bool D3dGraphicsManager::CheckMSAA()
    {
        D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS qualityLevel;
        qualityLevel.Format = m_BackBufferFormat;
        qualityLevel.SampleCount = 4;
        qualityLevel.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
        qualityLevel.NumQualityLevels = 0;
        m_Device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &qualityLevel, sizeof(qualityLevel));
        ASSERT(qualityLevel.NumQualityLevels > 0);
        m_4xMSAAQuality = qualityLevel.NumQualityLevels;
        return true;
    }
    bool D3dGraphicsManager::CreateCommandQueue()
    {
        D3D12_COMMAND_QUEUE_DESC queueDesc = {};
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        if (FAILED(m_Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_CommandQueue.GetAddressOf()))))
        {
            LOG_ERROR("call CreateCommandQueue failed");
            return false;
        }

        if (FAILED(m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_CommandAllocator.GetAddressOf()))))
        {
            LOG_ERROR("call CreateCommandAllocator failed");
            return false;
        }

        if (FAILED(m_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_CommandAllocator.Get(), nullptr, IID_PPV_ARGS(m_CommandList.GetAddressOf()))))
        {
            LOG_ERROR("call CreateCommandList failed");
            return false;
        }

        m_CommandList->Close();
        return true;
    }
    bool D3dGraphicsManager::CreateSwapChain()
    {
        const WinApplication* app = static_cast<const WinApplication*>(g_ClientGlobalContext.GetApplication());

        if (app == nullptr)
        {
            LOG_ERROR("can not cast to WinApplication for D3dGraphicsManager");
            return false;
        }

        m_SwapChain.Reset();

        DXGI_SWAP_CHAIN_DESC desc = {};
        uint32_t width, height = 0;
        app->GetWindowSize(width, height);
        desc.BufferDesc.Width = width;
        desc.BufferDesc.Height = height;
        desc.BufferDesc.Format = m_BackBufferFormat;
        desc.BufferDesc.RefreshRate.Numerator = 60;
        desc.BufferDesc.RefreshRate.Denominator = 1;
        desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

        /*https://github.com/Microsoft/DirectXTK12/wiki/Simple-rendering
        Direct3D 12 don't support creating MSAA swap chains--attempts to create a swap chain with SampleDesc.Count > 1 will fail. 
        Instead, you create your own MSAA render target and explicitly resolve to the DXGI back-buffer for presentation as shown here.*/
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;

        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = k_BufferCount;
        desc.OutputWindow = app->GetHWND();
        desc.Windowed = true;
        desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        if (FAILED(m_Factory->CreateSwapChain(m_CommandQueue.Get(), &desc, m_SwapChain.GetAddressOf())))
        {
            LOG_ERROR("call CreateSwapChain failed");
            return false;
        }

        return true;
    }
}
