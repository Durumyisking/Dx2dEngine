#include "Editor.h"
#include "Mesh.h"
#include "Material.h"
#include "Resources.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Object.h"
#include "GridScript.h"

namespace dru
{
	void CEditor::Initialize()
	{
		mDebugObjects.resize(static_cast<UINT>(eColliderType::End));

		// rectmesh
		std::shared_ptr<CMesh> rectMesh =  CResources::Find<CMesh>(L"DebugRectmesh");
		std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new CDebugObject();
		CMeshRenderer* RectMeshrenderer = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<CMeshRenderer>(eComponentType::MeshRenderer);

		RectMeshrenderer->SetMaterial(material);
		RectMeshrenderer->SetMesh(rectMesh);

		// circlemesh
		std::shared_ptr<CMesh> CircleMesh = CResources::Find<CMesh>(L"Circlemesh");
		
		mDebugObjects[(UINT)eColliderType::Circle] = new CDebugObject();
		CMeshRenderer* CicleMeshrenderer = mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<CMeshRenderer>(eComponentType::MeshRenderer);

		CicleMeshrenderer->SetMaterial(material);
		CicleMeshrenderer->SetMesh(CircleMesh);


		{
			// gridobj
			CEditorObject* gridObj = new CEditorObject();
			gridObj->SetLayerType(eLayerType::Grid);
			CMeshRenderer* MeshRenderer = gridObj->AddComponent<CMeshRenderer>(eComponentType::MeshRenderer);
			MeshRenderer->SetMaterial(CResources::Find<CMaterial>(L"GridMaterial"));
			CGridScript* script = gridObj->AddComponent<CGridScript>(eComponentType::Script);
			script->SetCamera(renderer::mainCamera);
			//gridObj->DontDestroy();

			mEditorObjects.push_back(gridObj);
		}

	}

	void CEditor::Run()
	{
		update();
		fixedUpdate();
		render();
	}
	void CEditor::update()
	{
		for (CEditorObject* obj : mEditorObjects)
		{
			obj->update();
		}
	}

	void CEditor::fixedUpdate()
	{
		for (CEditorObject* obj : mEditorObjects)
		{
			obj->fixedUpdate();
		}
	}

	void CEditor::render()
	{
		for (CEditorObject* obj : mEditorObjects)
		{
			obj->render();
		}

		for (DebugMesh& mesh : renderer::debugMeshes)
		{
			debugRender(mesh);
		}

		renderer::debugMeshes.clear();
	}

	void CEditor::destroy()
	{
		for (auto* obj : mWidgets)
		{
			delete obj;
			obj = nullptr;
		}
		for (auto* obj : mEditorObjects)
		{
			delete obj;
			obj = nullptr;
		}

		delete mDebugObjects[(UINT)eColliderType::Rect];
		delete mDebugObjects[(UINT)eColliderType::Circle];
	}

	void CEditor::debugRender(graphics::DebugMesh& mesh)
	{
		CDebugObject* debugObj = mDebugObjects[(UINT)mesh.type];
		
		CTransform* tr = debugObj->GetComponent<CTransform>();
		tr->SetPosition(mesh.position);
		tr->SetRotation(mesh.rotation);

		switch (mesh.type)
		{
		case dru::enums::eColliderType::Rect:
			tr->SetScale(mesh.scale);
			break;
		case dru::enums::eColliderType::Circle:
			tr->SetScale(Vector3(mesh.radius));
			break;
		case dru::enums::eColliderType::Box:
			break;
		case dru::enums::eColliderType::Sphere:
			break;
		case dru::enums::eColliderType::End:
			break;
		default:
			break;
		}

		
		CBaseRenderer* renderer = debugObj->GetComponent<CBaseRenderer>();

		std::shared_ptr<CMaterial> material = renderer->GetMaterial();
		material->SetData(eGPUParam::Int_1, &mesh.state);
		tr->fixedUpdate(); // 행렬 다시만들어줌

		CCamera::SetGpuViewMatrix(renderer::mainCamera->GetViewMatrix());
		CCamera::SetGpuProjectionMatrix(renderer::mainCamera->GetProjectionMatrix());

		debugObj->render();
	}
}