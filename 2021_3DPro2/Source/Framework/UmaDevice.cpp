#include"UmaDevice.h"
#include "UmaFramework.h"

bool Uma3DDevice::Create(const HWND& hWnd, int w, int h, bool isFullScreen, bool isDebug, std::string& resultErrMes)
{
	// �E�B���h�E�n���h���ۑ�
	m_hWnd = hWnd;

	// �g�p����DirectX�o�[�W����(�ォ�珇�Ɏg���Ă���)
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
	D3D_FEATURE_LEVEL futureLevel; // ���ۂɎg�p���ꂽ�o�[�W����

	// Debug���擾
	UINT creationFlags = 0;
	// �ڍׂȃf�o�b�O�����擾���邽�߂̃t���O
	if (isDebug)
	{
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}

	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�쐬
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
		resultErrMes = "Direct3D11�f�o�C�X�쐬���s";
		return false;
	}


	return true;

	// �X���b�v�`�F�C���쐬�p�t�@�N�g���쐬
	ComPtr<IDXGIFactory> factory = nullptr;
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(factory.GetAddressOf()))))
	{
		resultErrMes = "�t�@�N�g���[�쐬���s";
		return false;
	}

	// �X���b�v�`�F�[���̐ݒ�f�[�^
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

	// �X���b�v�`�F�C���쐬
	if (FAILED(factory->CreateSwapChain(m_pDevice.Get(), &DXGISwapChainDesc, m_pGISwapChain.ReleaseAndGetAddressOf())))
	{
		resultErrMes = "�X���b�v�`�F�C���쐬���s";

		return false;
	}

	// �X���b�v�`�F�C������o�b�N�o�b�t�@�擾
	ComPtr<ID3D11Texture2D> pBackBuffer;
	if (FAILED(m_pGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pBackBuffer.GetAddressOf())))
	{
		resultErrMes = "�o�b�N�o�b�t�@�擾���s";

		return false;
	}

}
