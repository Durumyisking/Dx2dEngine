#include "Renderer.h"
#include "Resources.h"

namespace dru::renderer
{
	// vertex data
	Vertex	arrVertex[4] = {};
	CMesh* Mesh = nullptr;
	CConstantBuffer* constantBuffers[static_cast<UINT>(eCBType::End)] = {};
	CShader* Shader = nullptr;

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

		Shader->CreateInputLayout(arrLayout, 2);

	}

	void LoadBuffer()
	{
		Mesh = new CMesh();
		CResources::Insert<CMesh>(L"RectMesh", Mesh);

		Mesh->CreateVertexBuffer(arrVertex, 4);

		std::vector<UINT> vecIdx = {};

		vecIdx.push_back(0);
		vecIdx.push_back(1);
		vecIdx.push_back(2);
		vecIdx.push_back(0);
		vecIdx.push_back(2);
		vecIdx.push_back(3);

		Mesh->CreateIndexBuffer(vecIdx.data(), vecIdx.size());

		Vector4 pos;
		pos = { 0.2f, 0.2f, 0.f, 0.0f };
		// Const Buffer
		UINT i = (UINT)eCBType::Transform;

		constantBuffers[static_cast<UINT>(eCBType::Transform)] = new CConstantBuffer();
		constantBuffers[static_cast<UINT>(eCBType::Transform)]->Create(sizeof(Vector4));
		constantBuffers[static_cast<UINT>(eCBType::Transform)]->Bind(&pos);
	}

	void LoadShader()
	{
		Shader = new CShader();
		Shader->Create(graphics::eShaderStage::VS, L"VSTriangle.hlsl", "VS");
		Shader->Create(graphics::eShaderStage::PS, L"PSTriangle.hlsl", "PS");
	}

	void Initialize()
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
		delete Mesh;
		delete Shader;
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;

		}
	}
}