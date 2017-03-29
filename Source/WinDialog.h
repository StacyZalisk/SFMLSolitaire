#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <SFML/Graphics.hpp>
#include "SFMLGameObject.h"

class WinDialog;

class WinDialog : public SFMLGameObject
{
public:
	~WinDialog();

	static WinDialog * WinDialog::GetWinDialog();

	void Display();

private:
	WinDialog();

	static WinDialog * Instance;
};

#endif