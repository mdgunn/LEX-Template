/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#include "optionscontextbox.h"
#define CONTEXT_INDENT  20

namespace LEX
{
	OptionsContextBox::OptionsContextBox(short pWidth, short pHeight, short pWorldPosX, short pWorldPosY, bool pCenter, short pBorderWidth)
	{
		width = pWidth;
		height = pHeight;

		if (pCenter)
		{
			worldPosX = pWorldPosX - GetWidth() / 2;
			worldPosY = pWorldPosY - GetHeight() / 2;
		}
		else
		{
			worldPosX = pWorldPosX;
			worldPosY = pWorldPosY;
		}

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = pBorderWidth;

		CH_MSAA = new ChooserMSAA(0, 0, 120, 24);
		CH_MSAA->SetVisible(true);
		CH_MSAA->SetPosition(posX + GetWidth() - CH_MSAA->GetWidth() - CONTEXT_INDENT, posY + 58);

		CH_LightQuality = new Chooser3(0, 0, 120, 24);
		CH_LightQuality->SetVisible(true);
		CH_LightQuality->SetPosition(posX + GetWidth() - CH_LightQuality->GetWidth() - CONTEXT_INDENT, CH_MSAA->GetY() + CH_MSAA->GetHeight() + 8);

		CH_Terrain = new Chooser3(0, 0, 120, 24);
		CH_Terrain->SetVisible(true);
		CH_Terrain->SetPosition(posX + GetWidth() - CH_LightQuality->GetWidth() - CONTEXT_INDENT, CH_LightQuality->GetY() + CH_LightQuality->GetHeight() + 8);

		CH_Tessellation = new Chooser3(0, 0, 120, 24);
		CH_Tessellation->SetVisible(true);
		CH_Tessellation->SetPosition(posX + GetWidth() - CH_Terrain->GetWidth() - CONTEXT_INDENT, CH_Terrain->GetY() + CH_Terrain->GetHeight() + 8);

		CB_FullScreen = new BaseCheckBox();
		CB_FullScreen->SetPosition(posX + GetWidth() - CB_FullScreen->GetWidth() - CONTEXT_INDENT, CH_Tessellation->GetY() + CH_Tessellation->GetHeight() + 8);

		/* Camera */
		SL_CamSmoothing = new Slider(posX + CONTEXT_INDENT, CB_FullScreen->GetY() + CB_FullScreen->GetHeight() + 48);
		SL_CamSmoothing->SetLabel("Mouse Camera Drag");
		ND_CamSmoothing = new NumberDisplay();
		ND_CamSmoothing->SetPosition(posX + GetWidth() - ND_CamSmoothing->GetWidth() - CONTEXT_INDENT, SL_CamSmoothing->GetY() + SL_CamSmoothing->GetHeight() / 2);

		SL_FOV = new Slider(posX + CONTEXT_INDENT, SL_CamSmoothing->GetY() + SL_CamSmoothing->GetHeight() * 2);
		SL_FOV->SetLabel("Feild of View (FOV)");
		SL_FOV->SetMaxValue(90);
		ND_FOV = new NumberDisplay();
		ND_FOV->SetPosition(posX + GetWidth() - ND_FOV->GetWidth() - CONTEXT_INDENT, SL_FOV->GetY() + SL_FOV->GetHeight() / 2);

		/*
		SL_Volume = new Slider(posX + CONTEXT_INDENT, SL_FOV->GetY() + SL_FOV->GetHeight() * 2);
		SL_Volume->SetLabel("Volume");
		ND_Volume = new NumberDisplay();
		ND_Volume->SetPosition(posX + GetWidth() - ND_Volume->GetWidth() - CONTEXT_INDENT, SL_Volume->GetY() + SL_Volume->GetHeight() / 2);
		*/

		// Load XML File
		if (FileSystem::GetFileType(FILE_SETTINGS) == 1)
		{
			xmlSettings.load_file(FILE_SETTINGS);
		}

		//----------------------------------------------------------------------------
		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT);

		//----------------------------------------------------------------------------
		xml_node displaynode = rootnode.child(NODE_SETTINGS_DISPLAY);
		std::string fullscreen = displaynode.attribute(PROPERTY_FULLSCREEN).value();
		CB_FullScreen->SetTick(stoi(fullscreen));

		//----------------------------------------------------------------------------
		xml_node controlsnode = rootnode.child(NODE_SETTINGS_CONTROLS);
		const char* camsmooth = controlsnode.attribute(PROPERTY_MOUSESENSITIVITY).value();
		SL_CamSmoothing->SetSliderPosition(atoi(camsmooth));

		const char* fov = controlsnode.attribute(PROPERTY_FOV).value();
		SL_FOV->SetSliderPosition(atoi(fov));

		/*
		xml_node miscsnode = rootnode.child(NODE_SETTINGS_MISC);
		const char* vol = miscsnode.attribute(PROPERTY_VOLUME).value();
		SL_Volume->SetSliderPosition(atoi(vol));
		*/

		CreateCloseButton();
		CreateButtons();

		cancelbutton->SetButtonLabel(CONTEXT_TEXT_BACK);
		activatebutton->SetButtonLabel(CONTEXT_TEXT_APPLY);

		advancedoptionsbutton = new RectButton(0, 0, 83, 22);
		advancedoptionsbutton->SetButtonLabel(CONTEXT_TEXT_ADVOPTIONS);
		float x = worldPosX + GetWidth();
		float y = worldPosY + GetHeight();

		x = x - GetWidth() + 8;
		y = y - advancedoptionsbutton->GetHeight() - 8;

		advancedoptionsbutton->SetPosition(x, y);
	}

	OptionsContextBox::~OptionsContextBox()
	{
		SAFE_DELETE(cancelbutton);
		SAFE_DELETE(activatebutton);
		SAFE_DELETE(CloseButton);
		SAFE_DELETE(advancedoptionsbutton);

		SAFE_DELETE(CH_MSAA);
		SAFE_DELETE(CH_LightQuality);
		SAFE_DELETE(CH_Terrain);
		SAFE_DELETE(CB_FullScreen);
		//SAFE_DELETE(CB_DrawStats);

		SAFE_DELETE(SL_CamSmoothing);
		SAFE_DELETE(ND_CamSmoothing);

		SAFE_DELETE(SL_FOV);
		SAFE_DELETE(ND_FOV);

		//SAFE_DELETE(SL_Volume);
		//SAFE_DELETE(SL_Volume);
	}

	void OptionsContextBox::Open()
	{
		if (m_bDrawing) return;
		m_bDrawing = true;
		Reload();
	}

	void OptionsContextBox::Reload()
	{
		// Load XML File
		//----------------------------------------------------------------------------
		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT);

		int i = world->GetMultisample();
		CH_MSAA->SetMSAAOptionValue(i);
		CH_MSAA->SetChooseOption(CH_MSAA->GetRelativeOptionValue());
		CH_LightQuality->SetChooseOption(world->GetLightQuality());
		CH_Terrain->SetChooseOption(world->GetTerrainQuality());
		CH_Tessellation->SetChooseOption(world->GetTessellationQuality());

		//----------------------------------------------------------------------------
		xml_node displaynode = rootnode.child(NODE_SETTINGS_DISPLAY);
		std::string fullscreen = displaynode.attribute(PROPERTY_FULLSCREEN).value();
		CB_FullScreen->SetTick(stoi(fullscreen));

		//----------------------------------------------------------------------------
		xml_node controlsnode = rootnode.child(NODE_SETTINGS_CONTROLS);
		const char* camsmooth = controlsnode.attribute(PROPERTY_MOUSESENSITIVITY).value();
		SL_CamSmoothing->SetSliderPosition(atoi(camsmooth));

		const char* fov = controlsnode.attribute(PROPERTY_FOV).value();
		SL_FOV->SetSliderPosition(atoi(fov));

		/*
		xml_node miscsnode = rootnode.child(NODE_SETTINGS_MISC);
		const char* vol = miscsnode.attribute(PROPERTY_VOLUME).value();
		SL_Volume->SetSliderPosition(atoi(vol));
		*/
	}

	void OptionsContextBox::FixButtonPos()
	{
		if (m_bfixedpos) return;

		float x = worldPosX + GetWidth();
		float y = worldPosY + GetHeight();

		x = x - cancelbutton->GetWidth() - 8;
		y = y - cancelbutton->GetHeight() - 8;
		cancelbutton->SetPosition(x, y);

		activatebutton->SetPosition(x - activatebutton->GetWidth() - 4, y);
		m_bfixedpos = true;
	}

	void OptionsContextBox::Draw()
	{
		BasePanel::Draw();

		if (!m_bDrawing)
			return;

		FixButtonPos();

		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		context->SetColor(1, 1, 1, 1);

		context->SetFont(BasePanel::GetMessageFont());

		context->DrawText("Anti Aliasing",
			posX + CONTEXT_INDENT,
			CH_MSAA->GetY() + CH_MSAA->GetHeight() / 4);
		CH_MSAA->Update();

		context->DrawText("Light Quality",
			posX + CONTEXT_INDENT,
			CH_LightQuality->GetY() + CH_LightQuality->GetHeight() / 4);
		CH_LightQuality->Update();

		context->DrawText("Terrain Resoultion",
			posX + CONTEXT_INDENT,
			CH_Terrain->GetY() + CH_Terrain->GetHeight() / 4);
		CH_Terrain->Update();

		context->DrawText("Tessellation Quality",
			posX + CONTEXT_INDENT,
			CH_Tessellation->GetY() + CH_Tessellation->GetHeight() / 4);
		CH_Tessellation->Update();

		context->DrawText("Fullscreen*",
			posX + CONTEXT_INDENT,
			//CB_FullScreen->GetX() - messagefont->GetTextWidth("Fullscreen") - 128, 
			CB_FullScreen->GetY() + CB_FullScreen->GetHeight() / 4);
		CB_FullScreen->Update();

		context->SetColor(GetLabelColor().x, GetLabelColor().y, GetLabelColor().z);
		context->DrawText("GRAPHICS",
			posX + CONTEXT_INDENT,
			posY + CONTEXT_INDENT * 2);

		context->DrawText("CAMERA",
			posX + CONTEXT_INDENT,
			CB_FullScreen->GetY() + CB_FullScreen->GetHeight() + 24);

		/*
		context->DrawText("MISC",
			posX + CONTEXT_INDENT,
			SL_FOV->GetY() + SL_FOV->GetHeight() + 32);
			*/

		SL_CamSmoothing->Update();
		ND_CamSmoothing->Update();
		int csval = SL_CamSmoothing->GetValue();
		string camerasmoothString = static_cast<ostringstream*>(&(ostringstream() << csval))->str();
		ND_CamSmoothing->Display(camerasmoothString);


		SL_FOV->Update();
		ND_FOV->Update();
		int fovval = SL_FOV->GetValue();
		string fovString = static_cast<ostringstream*>(&(ostringstream() << fovval))->str();
		ND_FOV->Display(fovString);

		/*
		SL_Volume->Update();
		ND_Volume->Update();
		int volval = SL_Volume->GetValue();
		string volString = static_cast<ostringstream*>(&(ostringstream() << volval))->str();
		ND_Volume->Display(volString);
		*/

		context->DrawText("* Requires Restart",
			posX + CONTEXT_INDENT,
			posY + GetHeight() - 24 * 2);

		context->SetColor(GetMessageColor().x, GetMessageColor().y, GetMessageColor().z);

		CloseButton->Update();
		if (CloseButton->GetMouseEvent() == kEventMouseLeftUp)
		{
			Close();
		}

		cancelbutton->Update();
		if (cancelbutton->GetMouseEvent() == kEventMouseLeftUp)
		{
			Close();
		}

		activatebutton->Update();
		if (activatebutton->GetMouseEvent() == kEventMouseLeftUp)
		{
			ApplyMSAA();
			ApplyLightQuality();
			ApplyTerrain();
			ApplyTessellation();
			ApplyFullscreen();

			ApplyCamSmoothing();
			ApplyFOV();

			//ApplyVolume();

			xmlSettings.save_file(FILE_SETTINGS);

			//Close();
		}

		advancedoptionsbutton->Update();
		if (advancedoptionsbutton->GetMouseEvent() == kEventMouseLeftUp)
		{
		}
	}

	void OptionsContextBox::ApplyMSAA()
	{
		int i = CH_MSAA->GetMSAAOptionValue();
		std::string s = std::to_string(i);
		char const* msaa = s.c_str();

		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_GRAPHICS);
		xml_attribute attribue = rootnode.attribute(PROPERTY_MULTISAMPLE);
		attribue.set_value(msaa);
		world->SetMultisample(i);

		//xmlSettings.save_file(FILE_SETTINGS);

		//SaveSetting(PROPERTY_DRAWSTATS, drawstats);
	}

	void OptionsContextBox::ApplyLightQuality()
	{
		int i = CH_LightQuality->GetChooseOption();
		std::string s = std::to_string(i);
		char const* lightquality = s.c_str();

		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_GRAPHICS);
		xml_attribute attribue = rootnode.attribute(PROPERTY_LIGHTINGQUALITY);
		attribue.set_value(lightquality);

		// We can just set the quality in real time.
		//Leadwerks::World* world = World::GetCurrent();
		world->SetLightQuality(i);

		//xmlSettings.save_file(FILE_SETTINGS);

		//SaveSetting(PROPERTY_DRAWSTATS, drawstats);
	}

	void OptionsContextBox::ApplyTerrain()
	{
		int i = CH_Terrain->GetChooseOption();
		std::string s = std::to_string(i);
		char const* terrain = s.c_str();

		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_GRAPHICS);
		xml_attribute attribue = rootnode.attribute(PROPERTY_TERRAIN);
		attribue.set_value(terrain);

		// We can just set the quality in real time.
		//Leadwerks::World* world = World::GetCurrent();
		world->SetTerrainQuality(i);

		//xmlSettings.save_file(FILE_SETTINGS);

		//SaveSetting(PROPERTY_DRAWSTATS, drawstats);
	}

	void OptionsContextBox::ApplyTessellation()
	{
		int i = CH_Terrain->GetChooseOption();
		std::string s = std::to_string(i);
		char const* terrain = s.c_str();

		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_GRAPHICS);
		xml_attribute attribue = rootnode.attribute(PROPERTY_TESSELLATION);
		attribue.set_value(terrain);

		// We can just set the quality in real time.
		//Leadwerks::World* world = World::GetCurrent();
		world->SetTessellationQuality(i);

		//xmlSettings.save_file(FILE_SETTINGS);

		//SaveSetting(PROPERTY_DRAWSTATS, drawstats);
	}

	void OptionsContextBox::ApplyFullscreen()
	{
		//std::string fullscreen = rootnode.attribute(PROPERTY_FULLSCREEN).value();
		bool b = CB_FullScreen->IsTicked();
		const char* fullscreen;
		if (b)
		{
			fullscreen = "1";
		}
		else
		{
			fullscreen = "0";
		}

		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_DISPLAY);
		xml_attribute attribue = rootnode.attribute(PROPERTY_FULLSCREEN);
		attribue.set_value(fullscreen);
		//xmlSettings.save_file(FILE_SETTINGS);

		//SaveSetting(PROPERTY_FULLSCREEN, fullscreen);

	}

	void OptionsContextBox::ApplyCamSmoothing()
	{
		int i = SL_CamSmoothing->GetValue();
		std::string s = std::to_string(i);
		char const* camsmooth = s.c_str();

		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_CONTROLS);
		xml_attribute attribue = rootnode.attribute(PROPERTY_MOUSESENSITIVITY);
		attribue.set_value(camsmooth);

		// We can just set the quality in real time.
		System::SetProperty(PROPERTY_MOUSESENSITIVITY, camsmooth);

		//xmlSettings.save_file(FILE_SETTINGS);

		//SaveSetting(PROPERTY_DRAWSTATS, drawstats);
	}

	void OptionsContextBox::ApplyFOV()
	{
		int i = SL_FOV->GetValue();
		std::string s = std::to_string(i);
		char const* fov = s.c_str();

		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_CONTROLS);
		xml_attribute attribue = rootnode.attribute(PROPERTY_FOV);
		attribue.set_value(fov);

		// We can just set the quality in real time.
		System::SetProperty(PROPERTY_FOV, fov);

		//xmlSettings.save_file(FILE_SETTINGS);

		//SaveSetting(PROPERTY_DRAWSTATS, drawstats);
	}

	/*
	void OptionsContextBox::ApplyVolume()
	{
		int i = SL_Volume->GetValue();
		std::string s = std::to_string(i);
		char const* vol = s.c_str();

		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_MISC);
		xml_attribute attribue = rootnode.attribute(PROPERTY_VOLUME);
		attribue.set_value(vol);

		// We can just set the quality in real time.
		System::SetProperty(PROPERTY_VOLUME, vol);
	}
	*/

	AdvOptionsContextBox::AdvOptionsContextBox(short pWidth, short pHeight, short pWorldPosX, short pWorldPosY, bool pCenter, short pBorderWidth)
	{
		width = pWidth;
		height = pHeight;

		if (pCenter)
		{
			worldPosX = pWorldPosX - GetWidth() / 2;
			worldPosY = pWorldPosY - GetHeight() / 2;
		}
		else
		{
			worldPosX = pWorldPosX;
			worldPosY = pWorldPosY;
		}

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = pBorderWidth;

		CreateCloseButton();
		CreateButtons();

		cancelbutton->SetButtonLabel(CONTEXT_TEXT_BACK);
		activatebutton->SetButtonLabel(CONTEXT_TEXT_APPLY);

		CB_DrawStats = new BaseCheckBox();
		CB_DrawStats->SetPosition(posX + GetWidth() - CB_DrawStats->GetWidth() - CONTEXT_INDENT, posY + 58);

		CB_VSync = new BaseCheckBox();
		CB_VSync->SetPosition(posX + GetWidth() - CB_VSync->GetWidth() - CONTEXT_INDENT, CB_DrawStats->GetY() + CB_DrawStats->GetHeight() + 8);

		if (System::GetProperty(PROPERTY_DEVELOPER) == ON)
		{
			CB_DrawStats->Lock(true);
		}

		if (FileSystem::GetFileType(FILE_SETTINGS) == 1)
		{
			xmlSettings.load_file(FILE_SETTINGS);
		}

		//----------------------------------------------------------------------------
		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT);

		//----------------------------------------------------------------------------
		xml_node miscnode = rootnode.child(NODE_SETTINGS_MISC);
		std::string drawstats = miscnode.attribute(PROPERTY_DRAWSTATS).value();
		CB_DrawStats->SetTick(stoi(drawstats));

		std::string vsync = miscnode.attribute(PROPERTY_DRAWSTATS).value();
		CB_VSync->SetTick(stoi(vsync));
	}

	AdvOptionsContextBox::~AdvOptionsContextBox()
	{
		SAFE_DELETE(cancelbutton);
		SAFE_DELETE(activatebutton);
		SAFE_DELETE(CloseButton);

		SAFE_DELETE(CB_DrawStats);
		SAFE_DELETE(CB_VSync);
	}

	void AdvOptionsContextBox::FixButtonPos()
	{
		if (m_bfixedpos) return;

		float x = worldPosX + GetWidth();
		float y = worldPosY + GetHeight();

		x = x - cancelbutton->GetWidth() - 8;
		y = y - cancelbutton->GetHeight() - 8;
		cancelbutton->SetPosition(x, y);

		activatebutton->SetPosition(x - activatebutton->GetWidth() - 4, y);
		m_bfixedpos = true;
	}

	void AdvOptionsContextBox::Draw()
	{
		BasePanel::Draw();

		if (!m_bDrawing)
			return;

		FixButtonPos();

		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		context->SetColor(1, 1, 1, 1);

		context->SetFont(BasePanel::GetMessageFont());

		context->SetColor(GetLabelColor().x, GetLabelColor().y, GetLabelColor().z);
		context->DrawText("MISC",
			posX + CONTEXT_INDENT,
			posY + CONTEXT_INDENT * 2);

		
		// Gray out DrawStats if dev mode is on.
		if (CB_DrawStats->IsLocked())
		{
			context->SetColor(.25, .25, .25, 1);
		}
		else
		{
			context->SetColor(1, 1, 1, 1);
		}

		
		context->DrawText("Draw Stats",
			posX + CONTEXT_INDENT,
			CB_DrawStats->GetY() + CB_DrawStats->GetHeight() / 4);
		CB_DrawStats->Update();

		context->SetColor(1, 1, 1, 1);
		context->DrawText("VSync",
			posX + CONTEXT_INDENT,
			CB_VSync->GetY() + CB_VSync->GetHeight() / 4);
		CB_VSync->Update();

		CloseButton->Update();
		if (CloseButton->GetMouseEvent() == kEventMouseLeftUp)
		{
			Close();
		}

		cancelbutton->Update();
		if (cancelbutton->GetMouseEvent() == kEventMouseLeftUp)
		{
			Close();
		}

		activatebutton->Update();
		if (activatebutton->GetMouseEvent() == kEventMouseLeftUp)
		{
			ApplyDrawStats();
			ApplyVSync();
			xmlSettings.save_file(FILE_SETTINGS);
			//Close();
		}
	}
	void AdvOptionsContextBox::Open()
	{
		if (m_bDrawing) return;
		m_bDrawing = true;
		Reload();
	}

	void AdvOptionsContextBox::Reload()
	{
		//----------------------------------------------------------------------------
		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT);

		//----------------------------------------------------------------------------
		xml_node miscnode = rootnode.child(NODE_SETTINGS_MISC);
		std::string drawstats = miscnode.attribute(PROPERTY_DRAWSTATS).value();
		CB_DrawStats->SetTick(stoi(drawstats));

		std::string vs = miscnode.attribute(PROPERTY_VSYNC).value();
		CB_VSync->SetTick(world->VSync());
	}


	void AdvOptionsContextBox::ApplyDrawStats()
	{
		bool b = CB_DrawStats->IsTicked();
		const char* drawstats;
		if (b)
		{
			drawstats = "1";
		}
		else
		{
			drawstats = "0";
		}

		m_bdrawstats = b;

		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_MISC);
		xml_attribute attribue = rootnode.attribute(PROPERTY_DRAWSTATS);
		attribue.set_value(drawstats);
		//xmlSettings.save_file(FILE_SETTINGS);

		//SaveSetting(PROPERTY_DRAWSTATS, drawstats);
	}

	void AdvOptionsContextBox::ApplyVSync()
	{
		bool b = CB_VSync->IsTicked();
		const char* vs;
		if (b)
		{
			vs = "1";
		}
		else
		{
			vs = "0";
		}

		m_bvsync = b;
		world->SetVSync(m_bvsync);

		xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_MISC);
		xml_attribute attribue = rootnode.attribute(PROPERTY_VSYNC);
		attribue.set_value(vs);
		//xmlSettings.save_file(FILE_SETTINGS);

		//SaveSetting(PROPERTY_DRAWSTATS, drawstats);
	}
}
