#pragma once

#include	<vector>
#include	<wrl/client.h>
#include	"dx11helper.h"
#include	"renderer.h"

using Microsoft::WRL::ComPtr;

//-----------------------------------------------------------------------------
//IndexBuffer�N���X
//-----------------------------------------------------------------------------
class IndexBuffer {

	ComPtr<ID3D11Buffer> m_IndexBuffer;

public:
	void Create(const std::vector<unsigned int>& indices) {

		// �f�o�C�X�擾
		ID3D11Device* device = nullptr;

		device = Renderer::GetDevice();

		assert(device);

		// �C���f�b�N�X�o�b�t�@�쐬
		bool sts = CreateIndexBuffer(
			device,										// �f�o�C�X
			(unsigned int)(indices.size()),				// �C���f�b�N�X��
			(void*)indices.data(),						// �C���f�b�N�X�f�[�^�擪�A�h���X
			&m_IndexBuffer);							// �C���f�b�N�X�o�b�t�@

		assert(sts == true);
	}

	void SetGPU() {
		// �f�o�C�X�R���e�L�X�g�擾
		ID3D11DeviceContext* devicecontext = nullptr;
		devicecontext = Renderer::GetDeviceContext();

		// �C���f�b�N�X�o�b�t�@���Z�b�g
		devicecontext->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	}

	// �C���f�b�N�X�o�b�t�@�o�b�t�@��������
	template <typename T>
	void Modify(const std::vector<T>& indices)
	{
		//���_�f�[�^��������
		D3D11_MAPPED_SUBRESOURCE msr;
		HRESULT hr = Renderer::GetDeviceContext()->Map(
			m_IndexBuffer.Get(),
			0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		if (SUCCEEDED(hr)) {
			memcpy(msr.pData, indices.data(), indices.size() * sizeof(T));
			Renderer::GetDeviceContext()->Unmap(m_IndexBuffer.Get(), 0);
		}
	}
};
