#include "GridScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "ConstantBuffer.h"
#include "Renderer.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Application.h"

extern dru::CApplication application;

namespace dru
{
	CGridScript::CGridScript()
		: CScript()
		, mCamera(nullptr)
	{
		
	}

	CGridScript::~CGridScript()
	{
	}

	void CGridScript::Initialize()
	{
		UINT type = (UINT)CSceneMgr::mActiveScene->GetType();
		mCamera = renderer::Cameras[type][0];
	}

	void CGridScript::update()
	{
		if (nullptr == mCamera)
			return;

		CGameObj* gameobj = mCamera->GetOwner();
		CTransform* tr = gameobj->GetComponent<CTransform>();

		Vector3 campos = tr->GetPosition();
		Vector4 pos = Vector4(campos.x, campos.y, campos.z, 1.f);

		float scale = mCamera->GetScale();;

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float w = static_cast<float>(winRect.right - winRect.left);
		float h = static_cast<float>(winRect.top - winRect.bottom);
		Vector2 resolution(w, h);


		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Grid];
		renderer::GridCB data;

		data.cameraPosition = pos;
		data.cameraScale = Vector2(scale, scale);
		data.resolution = resolution;

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void CGridScript::fixedUpdate()
	{
	}

	void CGridScript::render()
	{
	}

}