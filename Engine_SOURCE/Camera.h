#pragma once
#include "Component.h"

namespace dru
{
	using namespace math;
	class CCamera : public CComponent
	{
		enum class eProjectionType
		{
			Perspective,
			Orthographic,
			End,
		};

	public:
		__forceinline static Matrix& GetViewMatrix() { return mView; }
		__forceinline static Matrix& GetProjectionMatrix() { return mProjection; }

		CCamera();
		virtual ~CCamera();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedupdate() override;
		virtual void render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();


	private:
		static Matrix mView;
		static Matrix mProjection; // ��� obj���� �ش� ����� ������


		eProjectionType mType;
		float mAspectRatio; // ��Ⱦ��

		float mNear;
		float mFar;
		float mScale;
	};


}