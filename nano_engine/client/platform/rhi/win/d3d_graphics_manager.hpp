#pragma once
#include "wrl/client.h"
#include <dxgi1_6.h>
#include <d3d12.h>
#include "client/gfx/graphics_manager.hpp"

namespace Nano
{
    class D3dGraphicsManager : public GraphicsManager
    {
        template<typename T>
        using ComPtr = Microsoft::WRL::ComPtr<T>;
    public:
        ~D3dGraphicsManager() final = default;

        bool Init() final;
        void Close() final;
        void Update(float dt) final;

    private:
        void LogAdapters();
        void GetHardwareAdapter(IDXGIFactory* factory, IDXGIAdapter** adapter);
        bool CreateDevice();
        //bool CreateFence();
        bool CheckMSAA();
        bool CreateCommandQueue();
        bool CreateSwapChain();

    private:
        ComPtr<IDXGIFactory> m_Factory{ nullptr };
        ComPtr<ID3D12Device> m_Device{ nullptr };
        ComPtr<ID3D12CommandQueue> m_CommandQueue{ nullptr };
        ComPtr<ID3D12CommandAllocator> m_CommandAllocator{ nullptr };
        ComPtr<ID3D12GraphicsCommandList> m_CommandList{ nullptr };
        ComPtr<IDXGISwapChain> m_SwapChain{ nullptr };

        uint32_t m_4xMSAAQuality{ 0 };
        bool m_Enable4xMSAA{ true };
        const uint32_t k_BufferCount = 2;
        DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
        DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    };
}