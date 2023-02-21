#include "Camera.h"
#include "Transform.h"
#include "GameObj.h"
#include "Application.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Material.h"
#include "BaseRenderer.h"

extern dru::CApplication application;

namespace dru
{
	Matrix CCamera::View = Matrix::Identity;
	Matrix CCamera::Projection = Matrix::Identity;

	CCamera::CCamera()
		: CComponent(eComponentType::Camera)
		, mType(eProjectionType::Perspective)
		, mAspectRatio(1.f)
		, mNear(1.f)
		, mFar(1000.f)
		, mScale(1.f)
		, mView(Matrix::Identity)
		, mProjection(Matrix::Identity)
	{
		EnableLayerMasks();
	}

	CCamera::~CCamera()
	{
	}

	void CCamera::Initialize()
	{
	}

	void CCamera::update()
	{

	}

	void CCamera::fixedupdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();

		RegisterCameraInRenderer();
	}

	void CCamera::render()
	{
		View = mView;
		Projection = mProjection;

		sortGameObjects();

		renderOpaque();
		renderCutout();
		renderTransparent();
	}	

	void CCamera::CreateViewMatrix()
	{
		CTransform* transform = GetOwner()->GetComponent<CTransform>();
		
		// 이동정보
		Vector3 translation = transform->GetPosition();

		// create view translation matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-translation);
		
		// 회전정보
		Vector3 up = transform->Up();
		Vector3 right = transform->Right();
		Vector3 foward = transform->Forward();

		Matrix viewRotate;
		viewRotate._11 = right.x; 		viewRotate._12 = up.x;		 viewRotate._13 = foward.x;
		viewRotate._21 = right.y; 		viewRotate._22 = up.y;		 viewRotate._23 = foward.y;
		viewRotate._31 = right.z; 		viewRotate._32 = up.z;		 viewRotate._33 = foward.z;

		mView *= viewRotate;

	}

	void CCamera::CreateProjectionMatrix()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = (winRect.right - winRect.left) * mScale;
		float height = (winRect.bottom - winRect.top) * mScale;
		mAspectRatio = width / height;


		if (mType == eProjectionType::Perspective)
		{
			mProjection = Matrix::CreatePerspectiveFieldOfView(XM_2PI / 6.f, mAspectRatio, mNear, mFar);
		}
		else // (mType == eProjectionType::Orthographic)
		{
			mProjection = Matrix::CreateOrthographic(width / 100.f, height / 100.f, mNear, mFar);
		}

	}

	void CCamera::RegisterCameraInRenderer()
	{
		renderer::Cameras.push_back(this);
	}

	void CCamera::TurnLayerMask(eLayerType _layer, bool _enable)
	{
		mLayerMask.set((UINT)_layer, _enable);
	}


	void CCamera::sortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutoutGameObjects.clear();
		mTransparentGameObjects.clear();

		CScene* scene = CSceneMgr::mActiveScene;
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMask[i])
			{
				CLayer& layer = scene->GetLayer((eLayerType)i);

				GameObjects gameObjects = layer.GetGameObjects();

				if (0 == gameObjects.size())
					continue;

				for (CGameObj* obj : gameObjects)
				{
					pushGameObjectToRenderingModes(obj);
				}
			}
		}

	}

	void CCamera::renderOpaque()
	{
		for (CGameObj* obj : mOpaqueGameObjects)
		{
			if(nullptr == obj)
				continue;
			obj->render();

		}
	}

	void CCamera::renderCutout()
	{
		for (CGameObj* obj : mCutoutGameObjects)
		{
			if (nullptr == obj)
				continue;
			obj->render();

		}
	}

	void CCamera::renderTransparent()
	{
		for (CGameObj* obj : mTransparentGameObjects)
		{
			if (nullptr == obj)
				continue;
			obj->render();
		}
	}

	void CCamera::pushGameObjectToRenderingModes(CGameObj* obj)
	{
		CBaseRenderer* renderer = obj->GetComponent<CBaseRenderer>();

		if (nullptr == renderer)
			return;

		std::shared_ptr<CMaterial> material = renderer->GetMaterial();

		dru::graphics::eRenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case dru::graphics::eRenderingMode::Opaque:
			mOpaqueGameObjects.push_back(obj);
			break;
		case dru::graphics::eRenderingMode::Cutout:
			mCutoutGameObjects.push_back(obj);
			break;
		case dru::graphics::eRenderingMode::Transparent:
			mTransparentGameObjects.push_back(obj);
			break;
		default:
			break;
		}
	}

}