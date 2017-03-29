#include "stdafx.h"
#include "WinDialog.h"
#include "SFMLGameObject.h"
#include "SFMLSprite.h"

WinDialog * WinDialog::Instance(nullptr);

WinDialog::WinDialog()
: SFMLGameObject("winBack", 283, 134)
{
	GetSprite()->SetPerformCollisionDetection(false);
	GetSprite()->SetVisible(false);
	SetDepth(99);
}

WinDialog::~WinDialog()
{
	Instance = NULL;
}

WinDialog * WinDialog::GetWinDialog()
{
	if (Instance == nullptr)
	{
		Instance = new WinDialog();
	}

	return Instance;
}

void WinDialog::Display()
{
	GetSprite()->SetVisible(true);
}