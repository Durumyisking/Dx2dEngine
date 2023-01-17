#include "Renderer.h"


namespace dru::renderer
{
	// vertex data
	Vertex				arrVertex[4] = {};

	// vertex buffer
	ID3D11Buffer*		triangleBuffer = nullptr;
	ID3DBlob*			errorBlob = nullptr; // dx ���ο��� ���� ������ �˷��ִ� ģ��
	
	// VS
	ID3DBlob*			triangleVSBlob = nullptr; // VS bytecode ����
	ID3D11VertexShader* triangleVS = nullptr;

	// PS
	ID3DBlob*			trianglePSBlob = nullptr; // PS bytecode ����
	ID3D11PixelShader*	trianglePS = nullptr;

	// Input Layout
	ID3D11InputLayout*	triangleLayout = nullptr; // ���� ���ۿ� �������� �������ִ¾�


	void SetUpState()
	{
		// input Layout (���� ���� ����)
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {}; // �츮�� vertex�� ����� pos, color ��������ϱ� 2���� ������

		arrLayout[0].AlignedByteOffset = 0; // �迭�� 0����Ʈ���� �����ϰڴ�.
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // pos�� 12����Ʈ ¥���ϱ�
		arrLayout[0].InputSlot = 0; // == D3D11_INPUT_PER_VERTEX_DATA 0�������� �̰���
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12; // ������ 12����Ʈ ��ŭ ������������ ���⼭���� �����Ұ���
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // color�� 16����Ʈ ¥���ϱ�
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		GetDevice()->CreateInputLayout(arrLayout, 2
			, triangleVSBlob->GetBufferPointer()
			, triangleVSBlob->GetBufferSize()
			, &triangleLayout);
	}

	void LoadBuffer()
	{
		// ����Ʈ ���� : Ÿ�� ���� �����ߴ�;
		// ���� �ϳ��� ������ ����
		D3D11_BUFFER_DESC triangleDesc = {}; // �ʱ�ȭ ���ϸ� �����Ⱚ ��! 0�ƴ�!
		triangleDesc.ByteWidth = sizeof(Vertex) * 4; // ������ ũ��
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // ����Ÿ������
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.CPUAccessFlags = D3D10_CPU_ACCESS_FLAG::D3D10_CPU_ACCESS_WRITE; // cpu���� ���� : �츮�� �翬�� �����ϱ� write

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = arrVertex;

		GetDevice()->CreateBuffer(&triangleDesc, &triangleData, &triangleBuffer);
	}

	void LoadShader()
	{
		GetDevice()->CreateShader();
	}

	void init()
	{
		// �߾��� 0, 0, 0�̰� ���̰� 1�� ���ﰢ��

		arrVertex[0].pos = Vector3(0.0f, 0.5f, 0.5f);
//		arrVertex[0].color = Vector4(1.f, 0.f, 0.f, 1.f); // RGB ������ǥ��

		arrVertex[1].pos = Vector3(0.5f, 0.f, 0.5f);
//		arrVertex[1].color = Vector4(0.f, 1.f, 0.f, 1.f);




		LoadShader();
		SetUpState();
		LoadBuffer();

	}

	void release()
	{

	}
}