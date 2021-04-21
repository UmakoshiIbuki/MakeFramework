#pragma once

class Uma3DDevice
{
public:

	// �f�o�C�X�̍쐬��X���b�v�`�F�C���̍쐬
	bool Create(
		const HWND& hWnd, int w, int h,
		bool isFullScreen, bool isDebug,
		std::string& resultErrMes);

private:

	ComPtr<ID3D11Device>			m_pDevice = nullptr;            // �쐬�֌W
	ComPtr<ID3D11DeviceContext>		m_pDeviceContext = nullptr;     // �`��֌W

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