#pragma once
#include "Component.h"

namespace dru
{
	using namespace math;
	class CCamera : public CComponent
	{
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


	private:
		void sortGameObjects();
		void renderOpaque();
		void renderCutout();
		void renderTransparent();

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


	};


}