// SFMLTemplate.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <SFML/Graphics.hpp>

#include "SFMLGame.h"
#include "MainMenuRoom.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SFMLGame::GetInstance()->Run( new MainMenuRoom() );
    return 0;
}

