#include"UmaDevice.h"
#include "UmaFramework.h"

bool Uma3DDevice::Create(const HWND& hWnd, int w, int h, bool isFullScreen, bool isDebug, std::string& resultErrMes)
{
	// ウィンドウハンドル保存
	m_hWnd = hWnd;

	// 使用するDirectXバージョン(上から順に使っていく)
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,	// Direct3D 11.1  ShaderModel 5
		D3D_FEATURE_LEVEL_11_0,	// Direct3D 11    ShaderModel 5
		D3D_FEATURE_LEVEL_10_1,	// Direct3D 10.1  ShaderModel 4
		D3D_FEATURE_LEVEL_10_0,	// Direct3D 10.0  ShaderModel 4
		D3D_FEATURE_LEVEL_9_3,	// Direct3D 9.3   ShaderModel 3
		D3D_FEATURE_LEVEL_9_2,	// Direct3D 9.2   ShaderModel 3
		D3D_FEATURE_LEVEL_9_1,	// Direct3D 9.1   ShaderModel 3
	};
	D3D_FEATURE_LEVEL futureLevel; // 実際に使用されたバージョン

	// Debug情報取得
	UINT creationFlags = 0;
	// 詳細なデバッグ情報を取得するためのフラグ
	if (isDebug)
	{
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}

	// デバイスとデバイスコンテキスト作成
	if (FAILED(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&m_pDevice,
		&futureLevel,
		&m_pDeviceContext)))
	{
		resultErrMes = "Direct3D11デバイス作成失敗";
		return false;
	}


	return true;

	// スワップチェイン作成用ファクトリ作成
	ComPtr<IDXGIFactory> factory = nullptr;
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(factory.GetAddressOf()))))
	{
		resultErrMes = "ファクトリー作成失敗";
		return false;
	}

	// スワップチェーンの設定データ
	DXGI_SWAP_CHAIN_DESC DXGISwapChainDesc = {};
	DXGISwapChainDesc.BufferDesc.Width = w;
	DXGISwapChainDesc.BufferDesc.Height = h;
	DXGISwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	DXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	DXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	DXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGISwapChainDesc.SampleDesc.Count = 1;
	DXGISwapChainDesc.SampleDesc.Quality = 0;

	DXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	DXGISwapChainDesc.BufferCount = 2;
	DXGISwapChainDesc.OutputWindow = hWnd;
	DXGISwapChainDesc.Windowed = TRUE;
	DXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	DXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// スワップチェイン作成
	if (FAILED(factory->CreateSwapChain(m_pDevice.Get(), &DXGISwapChainDesc, m_pGISwapChain.ReleaseAndGetAddressOf())))
	{
		resultErrMes = "スワップチェイン作成失敗";

		return false;
	}

	// スワップチェインからバックバッファ取得
	ComPtr<ID3D11Texture2D> pBackBuffer;
	if (FAILED(m_pGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pBackBuffer.GetAddressOf())))
	{
		resultErrMes = "バックバッファ取得失敗";

		return false;
	}

}
