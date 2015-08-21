/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( APP_H )
#define APP_H
#pragma once

#include "main.h"
#include "gameui/rvgui.h"
#include "rworld.h"

#undef GetFileType

class App
{
public:
	Leadwerks::Window* window;
	Context* context;
	LEX::RWorld* world;

#ifdef _RVGUI
	LEX::RVGUI* vgui;
#endif
	
	App(std::string wintitle = "Leadwerks", std::string mapname="");
	virtual ~App();

    // Main functions.
    bool Start();
    bool Loop();//lua

	void SetWindowTitle(std::string wintitle)
	{
		m_stringwintitle = wintitle;
	}

	std::string GetWindowTitle()
	{
		return m_stringwintitle;
	}

    // Map Related.
	bool SetBackgroundMap(std::string mapname);//lua
	bool SetStartMap(std::string mapname);//lua
    bool LoadMap(std::string mapname);//lua

	bool LoadSaveFile();
	bool SaveFile();

    // Pausing
    bool Pause();//lua

	bool OpenContext();//lua
	bool CloseContext();//lua

    bool ShouldDrawMouse();
    bool DrawStats(bool value=false);

    // Disconnect + Quit
	bool Connected();//lua
    bool Disconnect();//lua
    bool Quit();//lua

	bool IsDevMode()
	{
		return m_bdevmode;
	};

	bool CheckDrawStats();


private:

	Leadwerks::ChoiceBox* test;

	std::string m_stringwintitle;
	std::string m_stringbackgroundmap;

    bool m_bDrawStats = false;

     // Disconnect + Quit
    bool m_bQuit = false;

    // Settings
    int m_intsettingmsaa = 0;
	bool m_bdevmode = false;

};
#endif
