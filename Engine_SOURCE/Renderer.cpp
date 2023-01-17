#include "Renderer.h"


namespace dru::renderer
{
	// vertex data
	Vertex				arrVertex[4] = {};

	// vertex buffer
	ID3D11Buffer*		triangleBuffer = nullptr;
	ID3DBlob*			errorBlob = nullptr; // dx ���ο��� ���� ������ �˷��ִ� ģ��

	// idx buffer
	ID3D11Buffer* triangleIndexBuffer = nullptr;

	// idx buffer
	ID3D11Buffer* triangleConstantBuffer = nullptr;
	
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
		// Vertex Buffer
		// ����Ʈ ���� : Ÿ�� ���� �����ߴ�;
		// ���� �ϳ��� ������ ����
		D3D11_BUFFER_DESC triangleDesc = {}; // �ʱ�ȭ ���ϸ� �����Ⱚ ��! 0�ƴ�!
		triangleDesc.ByteWidth = sizeof(Vertex) * 4; // ������ ũ��
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // ����Ÿ������
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // cpu���� ���� : �츮�� �翬�� �����ϱ� write

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = arrVertex;

		GetDevice()->CreateBuffer(&triangleDesc, &triangleData, &triangleBuffer);


		// Idx Buffer
		std::vector<UINT> vecIndex;
		vecIndex.push_back(0);
		vecIndex.push_back(1);
		vecIndex.push_back(2);

		vecIndex.push_back(0);
		vecIndex.push_back(2);
		vecIndex.push_back(3);

		D3D11_BUFFER_DESC idxDesc = {}; 
		idxDesc.ByteWidth = vecIndex.size() * sizeof(UINT);
		idxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER; 
		idxDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT; // ���� �Ŀ� �ٲ� ���� ����
		idxDesc.CPUAccessFlags = 0; // cpu���� ������ ���� ����

		D3D11_SUBRESOURCE_DATA idxData = {};
		idxData.pSysMem = vecIndex.data();

		GetDevice()->CreateBuffer(&idxDesc, &idxData, &triangleIndexBuffer);


		// Const Buffer
		D3D11_BUFFER_DESC constDesc = {};
		constDesc.ByteWidth = sizeof(Vector4); // ������� ������ ũ�⸸ŭ (�ϴ��� ��ġ ������)
		constDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		constDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		constDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		GetDevice()->CreateBuffer(&constDesc, nullptr, &triangleConstantBuffer);

		Vector4 pos(0.2f, 0.2f, 0.f, 0.f);
		GetDevice()->BindConstantBuffer(triangleConstantBuffer, &pos, sizeof(Vector4));
	}

	void LoadShader()
	{
		GetDevice()->CreateShader();
	}

	void init()
	{
		// �߾��� 0, 0, 0�̰� ���̰� 1�� ���ﰢ��

		arrVertex[0].pos = Vector3(-0.5f, 0.5f, 0.5f);
		arrVertex[0].color = Vector4(1.f, 0.f, 0.f, 1.f); // RGB ������ǥ��

		arrVertex[1].pos = Vector3(0.5f, 0.5f, 0.5f);
		arrVertex[1].color = Vector4(0.f, 1.f, 0.f, 1.f);

		arrVertex[2].pos = Vector3(0.5f, -0.5f, 0.5f);
		arrVertex[2].color = Vector4(0.f, 0.f, 1.f, 1.f);

		arrVertex[3].pos = Vector3(-0.5f, -0.5f, 0.5f);
		arrVertex[3].color = Vector4(0.f, 0.f, 0.f, 1.f);


		LoadShader();
		SetUpState();
		LoadBuffer();

	}

	void release()
	{
		triangleBuffer->Release();

		triangleIndexBuffer->Release();
		triangleConstantBuffer->Release();

		triangleVSBlob->Release();
		triangleVS->Release();

		trianglePSBlob->Release();
		trianglePS->Release();

		triangleLayout->Release();
	}
}