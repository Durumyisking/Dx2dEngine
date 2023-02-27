#pragma once
#include "Component.h"

namespace dru
{
	using namespace math;
	class CCamera : public CComponent
	{
		friend class CCameraScript;
	public:
		enum class eProjectionType
		{
			Perspective,
			Orthographic,
			End,
		};

		__forceinline static Matrix& GetViewMatrix() { return View; }
		__forceinline static Matrix& GetProjectionMatrix() { return Projection; }

		CCamera();
		virtual ~CCamera();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedupdate() override;
		virtual void render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();
		
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType _layer, bool _enable = true);
		void EnableLayerMasks() { mLayerMask.set(); } // 전부다 true로 }
		void DisableLayerMasks() { mLayerMask.reset(); }

		void SetProjectionType(eProjectionType _Type) { mType = _Type; }

		float GetScale() const { return mScale; }

		void SetTarget(CGameObj* _Target);
		CGameObj* GetTarget() const { return mTargetObj; }


	private:
		void sortGameObjects();
		void renderOpaque();
		void renderCutout();
		void renderTransparent();
		void pushGameObjectToRenderingModes(CGameObj* obj);
	private:
		static Matrix View;
		static Matrix Projection; // 모든 obj들의 해당 행렬은 동일함

		Matrix mView;
		Matrix mProjection;


		eProjectionType mType;
		float mAspectRatio; // 종횡비

		float mNear;
		float mFar;
		float mScale;

		std::bitset<(UINT)eLayerType::End> mLayerMask;
		std::vector<CGameObj*> mOpaqueGameObjects;
		std::vector<CGameObj*> mCutoutGameObjects;
		std::vector<CGameObj*> mTransparentGameObjects;


		CGameObj*	mTargetObj;
		Vector3		mLookAt;
		Vector3		mPrevLookAt;
		Vector3		mCamDir;
		float		mCamSpeed;
		float		mTime;
		float		mAccTime;
	};


}