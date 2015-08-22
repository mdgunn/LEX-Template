/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( RVGUI_H )
#define RVGUI_H
#pragma once

#include "../main.h"
#include "../rworld.h"

#include "rtitleui.h"
#include "basepanel.h"
#include "optionscontextbox.h"

namespace LEX
{
	class RVGUI
	{
	public:
		RVGUI(RWorld* pWorld);
		virtual ~RVGUI();

		void LoadMenuScheme();
		void Update();
		void DrawDebugScreen();
		void DrawStats(bool b);
		void DrawEngineInfo();
		void DrawBlackOverlay();
		void DrawMenu();
		void DrawContextBoxes();
		void DrawVersion();

		bool HasNewGameOpened();
		bool HasOptionsOpened();
		bool HasQuitOpened();
		bool HasWindowOpen();

		Leadwerks::Font* GetDefaultFont()
		{
			return mainfont;
		}

		bool CloseApp()
		{
			return m_bKillApp;
		}

	private:
		RWorld* world;

#ifdef DEBUG
		Leadwerks::Texture* debugscreen;
#endif

		Leadwerks::Font* mainfont;

		LEX::TitleUI* titleui;
		LEX::TextButton* BTN_ContinueGame;
		LEX::TextButton* BTN_ResumeGame;
		LEX::TextButton* BTN_NewGame;
		LEX::TextButton* BTN_Options;
		LEX::TextButton* BTN_Quit;

		LEX::BaseContextBox* NewGamePanel;
		LEX::OptionsContextBox* OptionsDialogPanel;
		LEX::AdvOptionsContextBox* AdvOptionsDialogPanel;
		LEX::BaseContextBox* QuitDialogPanel;

		bool m_bKillApp = false;
		bool m_bloadedsave = false;

		Leadwerks::Texture* background;
		std::string m_stringBGTexture = FILE_BACKGROUND;
		Leadwerks::Sound* BGMusic = NULL;
		Leadwerks::Source* BGSource = NULL;
	};
}

#endif //RVGUI_H

