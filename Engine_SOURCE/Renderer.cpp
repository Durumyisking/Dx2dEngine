#include "Renderer.h"
#include "GraphicDevice.h"

namespace dru::renderer
{
	// vertex data
	Vertex				arrVertex[3] = {};

	// vertex buffer
	ID3D11Buffer*		triangleBuffer = nullptr;
	ID3DBlob*			errorBlob = nullptr; // dx ���ο��� ���� ������ �˷��ִ� ģ��
	
	// VS
	ID3DBlob*			triangleVSBlob = nullptr;
	ID3D11VertexShader* triangleVS = nullptr;

	// PS
	ID3DBlob*			trianglePSBlob = nullptr;
	ID3D11PixelShader*	trianglePS = nullptr;

	// Input Layout
	ID3D11InputLayout*	triangleLayout = nullptr; // ���� ���ۿ� �������� �������ִ¾�


	void SetUpState()
	{
		//// ����Ʈ ���� : Ÿ�� ���� �����ߴ�;
		//// ���� �ϳ��� ������ ����
		//D3D11_BUFFER_DESC triangleDesc = {}; // �ʱ�ȭ ���ϸ� �����Ⱚ ��! 0�ƴ�!
		//triangleDesc.ByteWidth = sizeof(Vertex) * 3; // ������ ũ��
		//triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // ����Ÿ������
		//triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		//triangleDesc.CPUAccessFlags = D3D10_CPU_ACCESS_FLAG::D3D10_CPU_ACCESS_WRITE; // cpu���� ���� : �츮�� �翬�� �����ϱ� write

		//D3D11_SUBRESOURCE_DATA triangleData = {};
		//triangleData.pSysMem = arrVertex;

		//graphics::GetDevice()->CreateBuffer(&triangleDesc, &triangleData, &triangleBuffer);

	}

	void LoadBuffer()
	{
		// ����Ʈ ���� : Ÿ�� ���� �����ߴ�;
		// ���� �ϳ��� ������ ����
		D3D11_BUFFER_DESC triangleDesc = {}; // �ʱ�ȭ ���ϸ� �����Ⱚ ��! 0�ƴ�!
		triangleDesc.ByteWidth = sizeof(Vertex) * 3; // ������ ũ��
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // ����Ÿ������
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.CPUAccessFlags = D3D10_CPU_ACCESS_FLAG::D3D10_CPU_ACCESS_WRITE; // cpu���� ���� : �츮�� �翬�� �����ϱ� write

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = arrVertex;

		graphics::GetDevice()->CreateBuffer(&triangleDesc, &triangleData, &triangleBuffer);
	}

	void LoadShader()
	{

	}

	void init()
	{
		// �߾��� 0, 0, 0�̰� ���̰� 1�� ���ﰢ��
		arrVertex[0].pos = Vector3(0.0f, 0.5f, 1.f);
		arrVertex[0].color = Vector4(1.f, 0.f, 0.f, 1.f); // RGB ������ǥ��
		
		arrVertex[1].pos = Vector3(-0.5f, -0.5f, 1.f);
		arrVertex[1].color = Vector4(0.f, 1.f, 0.f, 1.f);
		
		arrVertex[2].pos = Vector3(0.5f, -0.5f, 1.f);
		arrVertex[2].color = Vector4(0.f, 0.f, 1.f, 1.f);

		SetUpState();
		LoadBuffer();
		LoadShader();

	}

	void release()
	{

	}
}