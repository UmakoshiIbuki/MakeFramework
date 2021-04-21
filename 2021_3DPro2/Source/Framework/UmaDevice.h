#pragma once

class Uma3DDevice
{
public:

	// デバイスの作成やスワップチェインの作成
	bool Create(
		const HWND& hWnd, int w, int h,
		bool isFullScreen, bool isDebug,
		std::string& resultErrMes);

private:

	ComPtr<ID3D11Device>			m_pDevice = nullptr;            // 作成関係
	ComPtr<ID3D11DeviceContext>		m_pDeviceContext = nullptr;     // 描画関係

	ComPtr <IDXGISwapChain>			m_pGISwapChain = nullptr;
	HWND							m_hWnd;

public:
	static Uma3DDevice& GetInstance()
	{
		static Uma3DDevice instance;
		return instance;
	}

private:
	Uma3DDevice() {};
	~Uma3DDevice() {};
};

#define D3D Uma3DDevice::GetInstance()