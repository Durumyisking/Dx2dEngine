#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"


namespace dru
{
	using namespace graphics;
	class CMeshRenderer : public CComponent
	{
	public:
		CMeshRenderer();
		virtual ~CMeshRenderer();

		virtual void Initialize() override ;
		virtual void update() override;
		virtual void fixedupdate() override;
		virtual void render() override;

		void SetMesh(CMesh* _Mesh) { mMesh = _Mesh; }
		void SetShader(CShader* _Shader) { mShader = _Shader; }

	private:
		CMesh* mMesh;
		CShader* mShader;
	};
}