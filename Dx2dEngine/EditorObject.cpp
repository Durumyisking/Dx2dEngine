#include "EditorObject.h"
namespace dru
{
	CEditorObject::CEditorObject()
		:CGameObj()
	{
	}

	CEditorObject::~CEditorObject()
	{
	}

	void CEditorObject::Initialize()
	{
		CGameObj::Initialize();
	}

	void CEditorObject::update()
	{
		CGameObj::update();
	}

	void CEditorObject::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CEditorObject::render()
	{
		CGameObj::render();
	}

}