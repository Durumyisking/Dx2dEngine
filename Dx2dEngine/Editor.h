#pragma once
#include "DebugObject.h"
#include "EditorObject.h"
#include "Widget.h"
#include "Graphics.h"

namespace dru
{
	class CEditor
	{
	public:
		void Initialize();
		void Run();

		void update();
		void fixedUpdate();
		void render();
		void destroy();
		void debugRender(graphics::DebugMesh& mesh);

		std::shared_ptr<CMesh> GetLineMesh() const { mDebugObjects[(UINT)eColliderType::Line]->GetComponent<CMesh>(); }

	private:
		std::vector<CWidget*> mWidgets;
		std::vector<CEditorObject*> mEditorObjects;
		std::vector<CDebugObject*> mDebugObjects;
	};

}