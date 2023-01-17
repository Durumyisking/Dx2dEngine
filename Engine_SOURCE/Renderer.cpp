#include "Renderer.h"


namespace dru::renderer
{
	// vertex data
	Vertex				arrVertex[4] = {};

	// vertex buffer
	ID3D11Buffer*		triangleBuffer = nullptr;
	ID3DBlob*			errorBlob = nullptr; // dx 내부에서 생긴 에러를 알려주는 친구
	
	// VS
	ID3DBlob*			triangleVSBlob = nullptr; // VS bytecode 저장
	ID3D11VertexShader* triangleVS = nullptr;

	// PS
	ID3DBlob*			trianglePSBlob = nullptr; // PS bytecode 저장
	ID3D11PixelShader*	trianglePS = nullptr;

	// Input Layout
	ID3D11InputLayout*	triangleLayout = nullptr; // 정점 버퍼에 정점정보 세팅해주는애


	void SetUpState()
	{
		// input Layout (정점 구조 정보)
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {}; // 우리가 vertex의 멤버로 pos, color 들고있으니까 2개만 만들자

		arrLayout[0].AlignedByteOffset = 0; // 배열의 0바이트부터 삽입하겠다.
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // pos가 12바이트 짜리니까
		arrLayout[0].InputSlot = 0; // == D3D11_INPUT_PER_VERTEX_DATA 0번슬롯은 이거임
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12; // 위에서 12바이트 만큼 삽입해줬으니 여기서부터 삽입할거임
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // color가 16바이트 짜리니까
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
		// 디폴트 버퍼 : 타입 지정 해조야대;
		// 이중 하나만 빠져도 망함
		D3D11_BUFFER_DESC triangleDesc = {}; // 초기화 안하면 쓰레기값 들어감! 0아님!
		triangleDesc.ByteWidth = sizeof(Vertex) * 4; // 데이터 크기
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // 버퍼타입지정
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.CPUAccessFlags = D3D10_CPU_ACCESS_FLAG::D3D10_CPU_ACCESS_WRITE; // cpu접근 여부 : 우리는 당연히 쓸꺼니까 write

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
		// 중앙이 0, 0, 0이고 높이가 1인 정삼각형

		arrVertex[0].pos = Vector3(0.0f, 0.5f, 0.5f);
//		arrVertex[0].color = Vector4(1.f, 0.f, 0.f, 1.f); // RGB 비율좌표임

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