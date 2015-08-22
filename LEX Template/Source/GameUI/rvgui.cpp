/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#include "rvgui.h"

pugi::xml_document xmlTitleRes;

// This makes it so we can convert int to a string with gnu.
namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}
namespace LEX
{
	RVGUI::RVGUI(RWorld* pWorld)
	{
		MSG("Creating VGUI");

		world = pWorld;

		// Load the default font for our context.
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		mainfont = Leadwerks::Font::Load(FONT_DEFAULT, 10);
		context->SetFont(mainfont);

		DEVMSG("VGUI: Creating menu.");

		titleui = new LEX::TitleUI(FONT_ARIAL, 48, STRING_ERROR);
		float tx = context->GetWidth() / 12;
		float ty = context->GetHeight() / 2 - titleui->GetHeight() - 24;
		titleui->SetPosition(tx, ty);

		float x = context->GetWidth() / 2;
		float y = context->GetHeight() / 2;

		// Continue
		BTN_ContinueGame = new TextButton();
		BTN_ContinueGame->SetPosition(context->GetWidth() / 12, context->GetHeight() / 2 + 12);

		// If we don't have a save file, lock the button.
		m_bloadedsave = world->HasSaveFile();
		if (m_bloadedsave)
		{
			BTN_ContinueGame->Lock(false);
		}
		else
		{
			BTN_ContinueGame->Lock(true);
		}

		// Resume
		BTN_ResumeGame = new TextButton();
		BTN_ResumeGame->SetPosition(context->GetWidth() / 12, context->GetHeight() / 2 + 12);

		// New Game, Options, Quit
		BTN_NewGame = new TextButton();
		BTN_Options = new TextButton();
		BTN_Quit = new TextButton();

		/* Panels! */
		MSG("Creating Panels");
		NewGamePanel = new BaseContextBox(420, 141, x, y);
		NewGamePanel->SetLabel("NEW GAME");
		NewGamePanel->SetMessage("Starting a new game will override the existing game.");

		OptionsDialogPanel = new OptionsContextBox(380, 500, x, y);
		OptionsDialogPanel->SetLabel("OPTIONS");
		OptionsDialogPanel->SetWorld(world);

		AdvOptionsDialogPanel = new AdvOptionsContextBox(366, 141, x, y);
		AdvOptionsDialogPanel->SetLabel("ADVANCED OPTIONS");
		AdvOptionsDialogPanel->SetWorld(world);

		QuitDialogPanel = new BaseContextBox(366, 141, x, y);
		QuitDialogPanel->SetLabel("QUIT GAME");
		QuitDialogPanel->SetMessage("Are you sure you want to quit the game?");
		QuitDialogPanel->cancelbutton->SetButtonLabel(CONTEXT_TEXT_NO);
		QuitDialogPanel->activatebutton->SetButtonLabel(CONTEXT_TEXT_YES);

		BGSource = Source::Create();

		LoadMenuScheme();
#ifdef DEBUG
		//debugscreen = Leadwerks::Texture::Load("materials/debug/debug_screenposition.tex");
#endif
	}

	RVGUI::~RVGUI()
	{
		SAFE_DELETE(titleui);
		SAFE_DELETE(BTN_ContinueGame);
		SAFE_DELETE(BTN_ResumeGame);
		SAFE_DELETE(BTN_NewGame);
		SAFE_DELETE(BTN_Options);
		SAFE_DELETE(BTN_Quit);

		SAFE_RELEASE(BGSource);

		SAFE_DELETE(NewGamePanel);
		SAFE_DELETE(OptionsDialogPanel);
		SAFE_DELETE(AdvOptionsDialogPanel);
		SAFE_DELETE(QuitDialogPanel);
	}


	void RVGUI::LoadMenuScheme()
	{
		if (FileSystem::GetFileType(FILE_RESOURCE_MENUSCHEME) == 0)
		{
			DEVMSG("VGUI: Failed to find menu scheme file.");
			return;
		}

		DEVMSG("VGUI: Reading menu scheme res.");
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		xmlTitleRes.load_file(FILE_RESOURCE_MENUSCHEME);
		xml_node rootmenunode = xmlTitleRes.child(NODE_MENUSCHEME_ROOT); // menuscheme

		DEVMSG("VGUI: Setting up Background.");

		// -<background>
		xml_node bgnode = rootmenunode.child(NODE_MENUSCHEME_BACKGROUND);
		xml_node bg_imagennode = bgnode.child(NODE_MENUSCHEME_TITLE_IMAGE);
		m_stringBGTexture = bg_imagennode.attribute("image").value();

		if (m_stringBGTexture != S_NULL)
		{
			background = Texture::Load(m_stringBGTexture);
		}
		else
		{
			background = Texture::Load(FILE_BACKGROUND);
		}
		
		xml_node bg_musicnnode = bgnode.child(NODE_MENUSCHEME_BACKGROUND_MUSIC);
		std::string music = bg_musicnnode.attribute("file").value();
		float musicvol = atof(bg_musicnnode.attribute("volume").value());
		if (FileSystem::GetFileType(music) == 1)
		{
			DEVMSG("VGUI: Setting Up Music: " + music);
			BGMusic = Sound::Load(music);
			BGSource->SetSound(BGMusic);
			BGSource->SetVolume(musicvol/100);
			SAFE_RELEASE(BGMusic);
			BGSource->Stop();
		}


		DEVMSG("VGUI: Setting up title.");

		// -<title>
		xml_node titlenode = rootmenunode.child(NODE_MENUSCHEME_TITLE);

		// --<image>
		xml_node title_imagennode = titlenode.child(NODE_MENUSCHEME_TITLE_IMAGE);
		std::string titleimageval = title_imagennode.attribute("image").value();
		std::string titleimageenableval = title_imagennode.attribute("enable").value();
		if (stoi(titleimageenableval))
		{
			titleui->SetImage(titleimageval);
			titleui->UseImage(true);
		}
		else
		{
			// Make sure it's false.
			titleui->UseImage(false);
		}

		// --<position>
		xml_node title_positionnode = titlenode.child(NODE_MENUSCHEME_TITLE_POSITION);

		const char* xvals = title_positionnode.attribute("x").value();
		const char* yvals = title_positionnode.attribute("y").value();
		float addedx = titleui->GetX() + atof(xvals);
		float addedy = titleui->GetY() + atof(yvals);
		titleui->SetPosition(addedx, addedy);

		// --<text>
		xml_node title_textnode = titlenode.child(NODE_MENUSCHEME_TITLE_TEXT);
		std::string titleval = title_textnode.attribute("title").value();
		std::string titlefontval = title_textnode.attribute("font").value();
		std::string titlesizevals = title_textnode.attribute("size").value();
		int titlesizeval = atoi(titlesizevals.c_str());
		titleui->SetTitle(titleval);
		titleui->SetFontFile(titlefontval, titlesizeval);


		// --<color>
		xml_node title_colornode = titlenode.child(NODE_MENUSCHEME_TITLE_COLOR);
		const char* title_color_R_vals = title_colornode.attribute("r").value();
		const char* title_color_G_vals = title_colornode.attribute("g").value();
		const char* title_color_B_vals = title_colornode.attribute("b").value();
		const char* title_color_A_vals = title_colornode.attribute("a").value();

		titleui->SetColor(atof(title_color_R_vals),
			atof(title_color_G_vals),
			atof(title_color_B_vals),
			atof(title_color_A_vals));

		DEVMSG("VGUI: Completed setting up title.");

		// ==================================END OF <title>============================================

		DEVMSG("VGUI: Setting up buttons.");

		// -<buttons>
		xml_node buttons_node = rootmenunode.child(NODE_MENUSCHEME_BUTTONS);

		// --<text>
		xml_node buttons_textsnode = buttons_node.child(NODE_MENUSCHEME_BUTTONS_TEXT);
		std::string btnfontval = buttons_textsnode.attribute("font").value();
		std::string btnsizevals = buttons_textsnode.attribute("size").value();
		Leadwerks::Font* menufont = Leadwerks::Font::Load(btnfontval, atoi(btnsizevals.c_str()));
		BTN_ContinueGame->SetContextFont(menufont);
		BTN_ResumeGame->SetContextFont(menufont);
		BTN_NewGame->SetContextFont(menufont);
		BTN_Options->SetContextFont(menufont);
		BTN_Quit->SetContextFont(menufont);


		// --<colors>
		xml_node buttons_maincolorsnode = buttons_node.child(NODE_MENUSCHEME_BUTTONS_COLORS);

		// ---<color>
		xml_node buttons_colornode = buttons_maincolorsnode.child(NODE_MENUSCHEME_BUTTONS_COLOR);
		const char* color_R_vals = buttons_colornode.attribute("r").value();
		const char* color_G_vals = buttons_colornode.attribute("g").value();
		const char* color_B_vals = buttons_colornode.attribute("b").value();

		BTN_ContinueGame->SetColor(atof(color_R_vals), atof(color_G_vals), atof(color_B_vals));
		BTN_ResumeGame->SetColor(atof(color_R_vals), atof(color_G_vals), atof(color_B_vals));
		BTN_NewGame->SetColor(atof(color_R_vals), atof(color_G_vals), atof(color_B_vals));
		BTN_Options->SetColor(atof(color_R_vals), atof(color_G_vals), atof(color_B_vals));
		BTN_Quit->SetColor(atof(color_R_vals), atof(color_G_vals), atof(color_B_vals));


		// ---<rollover>
		xml_node buttons_rollovercolornode = buttons_maincolorsnode.child(NODE_MENUSCHEME_BUTTONS_ROLLOVERCOLOR);
		const char* colorr_R_vals = buttons_rollovercolornode.attribute("r").value();
		const char* colorr_G_vals = buttons_rollovercolornode.attribute("g").value();
		const char* colorr_B_vals = buttons_rollovercolornode.attribute("b").value();

		BTN_ContinueGame->SetRolloverColor(atof(colorr_R_vals), atof(colorr_G_vals), atof(colorr_B_vals));
		BTN_ResumeGame->SetRolloverColor(atof(colorr_R_vals), atof(colorr_G_vals), atof(colorr_B_vals));
		BTN_NewGame->SetRolloverColor(atof(colorr_R_vals), atof(colorr_G_vals), atof(colorr_B_vals));
		BTN_Options->SetRolloverColor(atof(colorr_R_vals), atof(colorr_G_vals), atof(colorr_B_vals));
		BTN_Quit->SetRolloverColor(atof(colorr_R_vals), atof(colorr_G_vals), atof(colorr_B_vals));

		// ---<press>
		xml_node buttonpressedcolornode = buttons_maincolorsnode.child(NODE_MENUSCHEME_BUTTONS_PRESSEDCOLOR);
		const char* colorp_R_vals = buttonpressedcolornode.attribute("r").value();
		const char* colorp_G_vals = buttonpressedcolornode.attribute("g").value();
		const char* colorp_B_vals = buttonpressedcolornode.attribute("b").value();

		BTN_ContinueGame->SetPressedColor(atof(colorp_R_vals), atof(colorp_G_vals), atof(colorp_B_vals));
		BTN_ResumeGame->SetPressedColor(atof(colorp_R_vals), atof(colorp_G_vals), atof(colorp_B_vals));
		BTN_NewGame->SetPressedColor(atof(colorp_R_vals), atof(colorp_G_vals), atof(colorp_B_vals));
		BTN_Options->SetPressedColor(atof(colorp_R_vals), atof(colorp_G_vals), atof(colorp_B_vals));
		BTN_Quit->SetPressedColor(atof(colorp_R_vals), atof(colorp_G_vals), atof(colorp_B_vals));


		// --<sounds>
		xml_node buttons_soundssnode = buttons_node.child(NODE_MENUSCHEME_BUTTONS_SOUNDS);
		std::string rolloversoundval = buttons_soundssnode.attribute("onrollover").value();
		std::string pressedsoundval = buttons_soundssnode.attribute("onpressed").value();

		BTN_ContinueGame->SetRollOverSoundFile(rolloversoundval);
		BTN_ContinueGame->SetPressSoundFile(pressedsoundval);
		BTN_ResumeGame->SetRollOverSoundFile(rolloversoundval);
		BTN_ResumeGame->SetPressSoundFile(pressedsoundval);
		BTN_NewGame->SetRollOverSoundFile(rolloversoundval);
		BTN_NewGame->SetPressSoundFile(pressedsoundval);
		BTN_Options->SetRollOverSoundFile(rolloversoundval);
		BTN_Options->SetPressSoundFile(pressedsoundval);
		BTN_Quit->SetRollOverSoundFile(rolloversoundval);
		BTN_Quit->SetPressSoundFile(pressedsoundval);


		// --<continue>
		xml_node buttons_continuesnode = buttons_node.child(NODE_MENUSCHEME_BUTTONS_CONTINUE);
		std::string clabelval = buttons_continuesnode.attribute("label").value();
		BTN_ContinueGame->SetText(clabelval);

		// --<resume>
		xml_node buttons_resumesnode = buttons_node.child(NODE_MENUSCHEME_BUTTONS_RESUME);
		std::string rlabelval = buttons_resumesnode.attribute("label").value();
		BTN_ResumeGame->SetText(rlabelval);

		// --<newgame>
		xml_node buttons_newgamesnode = buttons_node.child(NODE_MENUSCHEME_BUTTONS_NEWGAME);
		std::string nlabelval = buttons_newgamesnode.attribute("label").value();
		BTN_NewGame->SetText(nlabelval);

		// --<options>
		xml_node buttons_optionssnode = buttons_node.child(NODE_MENUSCHEME_BUTTONS_OPTIONS);
		std::string olabelval = buttons_optionssnode.attribute("label").value();
		BTN_Options->SetText(olabelval);

		// --<quit>
		xml_node buttons_quitnode = buttons_node.child(NODE_MENUSCHEME_BUTTONS_QUIT);
		std::string qlabelval = buttons_quitnode.attribute("label").value();
		BTN_Quit->SetText(qlabelval);

		DEVMSG("VGUI: Completed setting up buttons.");
		/**/
		DEVMSG("VGUI: Completed setting up menu.");
	}

	void RVGUI::Update()
	{
		switch (world->GetWorldState())
		{
		case RWorld_NotConnected:
		{
			if (BGSource->GetState() != Source::Playing)
			{
				BGSource->Play();
			}

			DrawMenu();
			break;
		}
		case RWorld_Background:
		{
			// If we have a context window open, draw the overlay
			// to make the window stand out more.
			if (HasWindowOpen())
			{
				DrawBlackOverlay();
			}

			if (BGSource->GetState() != Source::Playing)
			{
				BGSource->Play();
			}

			DrawMenu();
			break;
		}
		case RWorld_Paused:
		{
			DrawBlackOverlay();
			DrawEngineInfo();
			DrawMenu();
			break;
		}
		case RWorld_InGame:
		{
			// If we have a window opened and we jump back in game, 
			// Close all windows.
			if (HasWindowOpen())
			{
				OptionsDialogPanel->Close();
				AdvOptionsDialogPanel->Close();
				QuitDialogPanel->Close();
			}

			BGSource->Stop();

			break;
		}
		}
	}

	void RVGUI::DrawVersion()
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		context->SetFont(mainfont);
		std::string demo = LEX_DEVINFO;
		context->DrawText(demo, context->GetWidth() - mainfont->GetTextWidth(demo) - 4, context->GetHeight() - mainfont->GetHeight() - 4);
	}

	void RVGUI::DrawDebugScreen()
	{
#ifdef DEBUG
		//Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		//Leadwerks::Window* window = Leadwerks::Window::GetCurrent();
		//context->SetColor(1, 1, 1, 1);
		//context->DrawImage(debugscreen, 0, 0, window->GetWidth(), window->GetHeight());
#endif
	}

	void RVGUI::DrawStats(bool b)
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		if (b)
		{
			// Only draw on vaild map.
			if (world->IsConnected() || world->InBackgroundMap())
			{
				context->SetFont(mainfont);
				context->DrawStats(2, 2);

				// Only draw this bit in dev/debug.
				if (System::GetProperty(PROPERTY_DEVELOPER, OFF) == ON || IsDebug() == true)
				{
					int LQ = world->GetLightQuality();
					string LQString = static_cast<ostringstream*>(&(ostringstream() << LQ))->str();
					context->DrawText("Light Quality: " + LQString, 2, 110);
					int msaavalue = atoi(System::GetProperty(PROPERTY_MULTISAMPLE).c_str());
					//int msaavalue = world->GetMultisample();
					string MSAAString = static_cast<ostringstream*>(&(ostringstream() << msaavalue))->str();
					context->DrawText("MultiSampling: " + MSAAString, 2, 128);
					int TQ = world->GetTerrainQuality();
					string TQString = static_cast<ostringstream*>(&(ostringstream() << TQ))->str();
					context->DrawText("Terrain Quality: " + TQString, 2, 146);
				}
			}
		}
	}

	void RVGUI::DrawEngineInfo()
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		// Only draw in dev or debug mode.
		if (System::GetProperty(PROPERTY_DEVELOPER, OFF) == ON || IsDebug() == true)
		{
			Context *context = Context::GetCurrent();
			int t = System::GetVersion();
			context->SetFont(mainfont);
			std::string devinfo = "Leadwerks Game Engine " + patch::to_string(t);
			context->DrawText(devinfo, context->GetWidth() - mainfont->GetTextWidth(devinfo) - 4, 2);
			std::string mapinfo = "Map: '" + world->GetCurrentLevel() + "'";
			context->DrawText(mapinfo, context->GetWidth() - mainfont->GetTextWidth(mapinfo) - 4, mainfont->GetHeight() + 6);
			DrawVersion();
		}
	}

	//----
	// Actual UI Stuff!
	//----

	void RVGUI::DrawBlackOverlay()
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		Leadwerks::Window* window = Leadwerks::Window::GetCurrent();
		context->SetColor(0, 0, 0, 0.5);
		context->DrawRect(0, 0, window->GetWidth(), window->GetHeight());
		context->SetColor(1, 1, 1, 1);

	}

	void RVGUI::DrawMenu()
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		if (world->GetWorldState() == RWorld_NotConnected)
		{
			Leadwerks::Window* window = Leadwerks::Window::GetCurrent();
			context->SetColor(1, 1, 1, 1);

			if (background)
			{
				context->DrawImage(background, 0, 0, context->GetWidth(), context->GetHeight());
			}
			else
			{
				context->DrawRect(0, 0, context->GetWidth(), context->GetHeight());
			}

			context->SetColor(1, 1, 1, 1);
		}

		if (HasWindowOpen() == false)
		{
			titleui->Draw();
			BTN_NewGame->Update();
			BTN_Options->Update();
			BTN_Quit->Update();
		}

		if (world->GetWorldState() == RWorld_Background || world->GetWorldState() == RWorld_NotConnected)
		{
			if (HasWindowOpen() == false)
			{
				BTN_ContinueGame->Update();
			}

			if (BTN_ContinueGame->GetMouseEvent() == kEventMouseLeftUp)
			{
				BGSource->Stop();
				world->LoadSaveFile();
			}

			BTN_NewGame->SetPosition(BTN_ContinueGame->GetX(), BTN_ContinueGame->GetY() + BTN_ContinueGame->GetHeight() + 16);

		}
		else if (world->GetWorldState() == RWorld_Paused)
		{
			if (HasWindowOpen() == false)
			{
				BTN_ResumeGame->Update();
			}

			if (BTN_ResumeGame->GetMouseEvent() == kEventMouseLeftUp)
			{
				world->Pause();
			}

			BTN_NewGame->SetPosition(BTN_ResumeGame->GetX(), BTN_ResumeGame->GetY() + BTN_ResumeGame->GetHeight() + 16);
		}

		if (BTN_NewGame->GetMouseEvent() == kEventMouseLeftUp)
		{
			//if (world->HasSaveFile() == true || m_bloadedsave)
			if (m_bloadedsave)
			{
				NewGamePanel->Open();
			}
			else
			{
				BGSource->Stop();
				world->LoadStartMap();
			}
		}

		BTN_Options->SetPosition(BTN_NewGame->GetX(), BTN_NewGame->GetY() + BTN_NewGame->GetHeight() + 16);
		if (BTN_Options->GetMouseEvent() == kEventMouseLeftUp)
		{
			OptionsDialogPanel->Open();
		}

		if (OptionsDialogPanel->GetAdvOptionsBtn()->GetMouseEvent() == kEventMouseLeftUp)
		{
			AdvOptionsDialogPanel->Open();
		}


		BTN_Quit->SetPosition(BTN_Options->GetX(), BTN_Options->GetY() + BTN_Options->GetHeight() + 16);
		if (BTN_Quit->GetMouseEvent() == kEventMouseLeftUp)
		{
			QuitDialogPanel->Open();
		}

		DrawContextBoxes();
	}

	void RVGUI::DrawContextBoxes()
	{
		if (world->GetWorldState() == RWorld_Background || RWorld_Paused)
		{
			NewGamePanel->Draw();
			if (NewGamePanel->Drawing())
			{
				if (NewGamePanel->activatebutton->GetMouseEvent() == kEventMouseLeftUp)
				{
					if (world->LoadStartMap())
					{
						BGSource->Stop();
						NewGamePanel->Close();
					}
					else
					{
						NewGamePanel->activatebutton->mouseEvent = kEventMouseNone;
						NewGamePanel->Close();
					}
				}
			}

		}

		AdvOptionsDialogPanel->Draw();
		if (AdvOptionsDialogPanel->Drawing() == false)
		{
			OptionsDialogPanel->Draw();
		}

		QuitDialogPanel->Draw();
		if (QuitDialogPanel->activatebutton->GetMouseEvent() == kEventMouseLeftUp)
		{
			m_bKillApp = true;
		}
	}

	bool RVGUI::HasNewGameOpened()
	{
		return NewGamePanel->Drawing();
	}

	bool RVGUI::HasOptionsOpened()
	{
		return OptionsDialogPanel->Drawing();
	}

	bool RVGUI::HasQuitOpened()
	{
		return QuitDialogPanel->Drawing();
	}

	bool RVGUI::HasWindowOpen()
	{
		if (HasNewGameOpened())
			return true;

		if (HasOptionsOpened())
			return true;

		if (HasQuitOpened())
			return true;

		return false;
	}
}