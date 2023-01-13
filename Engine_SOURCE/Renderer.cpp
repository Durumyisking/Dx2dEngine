#include "Renderer.h"
#include "GraphicDevice.h"

namespace dru::renderer
{
	// vertex data
	Vertex				arrVertex[3] = {};

	// vertex buffer
	ID3D11Buffer*		triangleBuffer = nullptr;
	ID3DBlob*			errorBlob = nullptr; // dx 내부에서 생긴 에러를 알려주는 친구
	
	// VS
	ID3DBlob*			triangleVSBlob = nullptr;
	ID3D11VertexShader* triangleVS = nullptr;

	// PS
	ID3DBlob*			trianglePSBlob = nullptr;
	ID3D11PixelShader*	trianglePS = nullptr;

	// Input Layout
	ID3D11InputLayout*	triangleLayout = nullptr; // 정점 버퍼에 정점정보 세팅해주는애


	void SetUpState()
	{
		//// 디폴트 버퍼 : 타입 지정 해조야대;
		//// 이중 하나만 빠져도 망함
		//D3D11_BUFFER_DESC triangleDesc = {}; // 초기화 안하면 쓰레기값 들어감! 0아님!
		//triangleDesc.ByteWidth = sizeof(Vertex) * 3; // 데이터 크기
		//triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // 버퍼타입지정
		//triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		//triangleDesc.CPUAccessFlags = D3D10_CPU_ACCESS_FLAG::D3D10_CPU_ACCESS_WRITE; // cpu접근 여부 : 우리는 당연히 쓸꺼니까 write

		//D3D11_SUBRESOURCE_DATA triangleData = {};
		//triangleData.pSysMem = arrVertex;

		//graphics::GetDevice()->CreateBuffer(&triangleDesc, &triangleData, &triangleBuffer);

	}

	void LoadBuffer()
	{
		// 디폴트 버퍼 : 타입 지정 해조야대;
		// 이중 하나만 빠져도 망함
		D3D11_BUFFER_DESC triangleDesc = {}; // 초기화 안하면 쓰레기값 들어감! 0아님!
		triangleDesc.ByteWidth = sizeof(Vertex) * 3; // 데이터 크기
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // 버퍼타입지정
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.CPUAccessFlags = D3D10_CPU_ACCESS_FLAG::D3D10_CPU_ACCESS_WRITE; // cpu접근 여부 : 우리는 당연히 쓸꺼니까 write

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = arrVertex;

		graphics::GetDevice()->CreateBuffer(&triangleDesc, &triangleData, &triangleBuffer);
	}

	void LoadShader()
	{

	}

	void init()
	{
		// 중앙이 0, 0, 0이고 높이가 1인 정삼각형
		arrVertex[0].pos = Vector3(0.0f, 0.5f, 1.f);
		arrVertex[0].color = Vector4(1.f, 0.f, 0.f, 1.f); // RGB 비율좌표임
		
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