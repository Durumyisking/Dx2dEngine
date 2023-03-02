#include "Editor.h"
#include "Mesh.h"
#include "Material.h"
#include "Resources.h"
#include "Transform.h"
#include "MeshRenderer.h"

namespace dru
{
	void CEditor::Initialize()
	{
		mDebugObjects.resize(static_cast<UINT>(eColliderType::End));

		std::shared_ptr<CMesh> rectMesh =  CResources::Find<CMesh>(L"Rectmesh");
		std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new CDebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<CTransform>(eComponentType::Transform);
		CMeshRenderer* RectMeshrenderer = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<CMeshRenderer>(eComponentType::MeshRenderer);

		RectMeshrenderer->SetMaterial(material);
		RectMeshrenderer->SetMesh(rectMesh);


		std::shared_ptr<CMesh> CircleMesh = CResources::Find<CMesh>(L"Circlemesh");
		
		mDebugObjects[(UINT)eColliderType::Circle] = new CDebugObject();
		mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<CTransform>(eComponentType::Transform);
		CMeshRenderer* CicleMeshrenderer = mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<CMeshRenderer>(eComponentType::MeshRenderer);

		CicleMeshrenderer->SetMaterial(material);
		CicleMeshrenderer->SetMesh(CircleMesh);

	}

	void CEditor::Run()
	{
		update();
		fixedUpdate();
		render();
	}

	void CEditor::update()
	{
	}

	void CEditor::fixedUpdate()
	{
	}

	void CEditor::render()
	{
	}

	void CEditor::destroy()
	{
	}

	void CEditor::debugRender(graphics::DebugMesh& mesh)
	{
			

	}
}