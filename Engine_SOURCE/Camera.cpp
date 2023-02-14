#include "Camera.h"
#include "Transform.h"
#include "GameObj.h"
#include "Application.h"

extern dru::CApplication application;

namespace dru
{
	Matrix CCamera::mView = Matrix::Identity;
	Matrix CCamera::mProjection = Matrix::Identity;

	CCamera::CCamera()
		: CComponent(eComponentType::Camera)
		, mType(eProjectionType::Orthographic)
		, mAspectRatio(1.f)
		, mNear(1.f)
		, mFar(1000.f)
		, mScale(1.f)
	{
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
	}

	void CCamera::render()
	{

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

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
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

}