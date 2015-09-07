/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#include "App.h"

pugi::xml_document xmlSettings;

App::App(std::string wintitle, std::string mapname) : window(NULL), context(NULL), world(NULL)
{
	SetWindowTitle(wintitle);
	SetBackgroundMap(mapname);

    // Start the App!
	if (Start())
	{
	//	while (Loop()) {}
	}
}

App::~App()
{
	SAFE_DELETE(world);
	SAFE_DELETE(window);

	if (System::GetProperty(PROPERTY_NOVGUI, OFF) == OFF)
	{
#ifdef _RVGUI
		SAFE_DELETE(vgui);
#endif
	}

}

/* Start Function */
bool App::Start()
{
	// Load all of our xml scripts.
	if (FileSystem::GetFileType(FILE_SETTINGS) == 0)
	{
		Debug::Error("Failed to find settings file.");
		return false;
	}
	else
	{
		// load settings.xml
		xmlSettings.load_file(FILE_SETTINGS);
	}
	//SAFE_DELETE(settingsfile);

    // Load our settings.
	xml_node rootnode = xmlSettings.child(NODE_SETTINGS_ROOT);
	xml_node resnode = rootnode.child(NODE_SETTINGS_DISPLAY);
	std::string x = resnode.attribute(PROPERTY_SCREENWIDTH).value();
	DEVMSG(PROPERTY_SCREENWIDTH + x);
	std::string y = resnode.attribute(PROPERTY_SCREENHEIGHT).value();
	DEVMSG(PROPERTY_SCREENHEIGHT  + y);
	std::string fullscreen = resnode.attribute(PROPERTY_FULLSCREEN).value();
	DEVMSG(PROPERTY_FULLSCREEN + fullscreen);

	xml_node graphicsnode = rootnode.child(NODE_SETTINGS_GRAPHICS);
	std::string lightquality = graphicsnode.attribute(PROPERTY_LIGHTINGQUALITY).value();
	DEVMSG(PROPERTY_LIGHTINGQUALITY + lightquality);
	std::string msaa = graphicsnode.attribute(PROPERTY_MULTISAMPLE).value();
	DEVMSG(PROPERTY_MULTISAMPLE + msaa);
	std::string terrain = graphicsnode.attribute(PROPERTY_TERRAIN).value();
	DEVMSG(PROPERTY_TERRAIN + terrain);
	std::string tessellation = graphicsnode.attribute(PROPERTY_TESSELLATION).value();
	DEVMSG(PROPERTY_TESSELLATION + terrain);

	xml_node controlsnode = rootnode.child(NODE_SETTINGS_CONTROLS);
	std::string mousesensitivity = controlsnode.attribute(PROPERTY_MOUSESENSITIVITY).value();
	std::string fov = controlsnode.attribute(PROPERTY_FOV).value();
	DEVMSG(PROPERTY_MOUSESENSITIVITY + mousesensitivity);

	xml_node miscsnode = rootnode.child(NODE_SETTINGS_MISC);
	std::string drawstats = miscsnode.attribute(PROPERTY_DRAWSTATS).value();
	DEVMSG(PROPERTY_DRAWSTATS + drawstats);

	/*
	std::string volume = miscsnode.attribute(PROPERTY_VOLUME).value();
	DEVMSG(PROPERTY_VOLUME + volume);
	System::SetProperty(PROPERTY_VOLUME, volume);
	*/

	m_bDrawStats = stoi(drawstats);

	std::string vsync = miscsnode.attribute(PROPERTY_VSYNC).value();
	DEVMSG(PROPERTY_VSYNC + vsync);

    // Toggle fullscreen.
	unsigned int intStyle = Leadwerks::Window::Titlebar;
	
	// Get the screen res from the settings file.
	unsigned int resx = atoi(System::GetProperty(PROPERTY_SCREENWIDTH, x).c_str());;
	unsigned int resy = atoi(System::GetProperty(PROPERTY_SCREENHEIGHT, y).c_str());;
	if (System::GetProperty(PROPERTY_FULLSCREEN, fullscreen) == ON && System::GetProperty(PROPERTY_FORCERES, OFF) == OFF) //<- Have it possible to force read the settings file
    {
        intStyle = Leadwerks::Window::FullScreen;

		/* 8-25-15: In fullscreen, always use the current monitor dimentions.*/ 
		resx = System::GetGraphicsMode(System::CountGraphicsModes() - 1).x;
		resy = System::GetGraphicsMode(System::CountGraphicsModes() - 1).y;
    }
	else if (System::GetProperty(PROPERTY_VR, OFF) == ON)
    {
		// I'm gonna be honest, I have no idea if VR works or not.
		intStyle = Leadwerks::Window::VRDisplay;
    }

	if (IsDebug())
	{
		// Debug mode auto shoots the game into devmode.
		m_bdevmode = true;
	}
	else
	{ 
		// If not debug, we only launch dev mode if we are told to by a param.
		if (System::GetProperty(PROPERTY_DEVELOPER, OFF) == ON)
		{
			//DrawStats(true);
			m_bdevmode = true;
		}
	}

	
	// Title of window.
	/*
	std::string werkfile;
	Leadwerks::Directory* dir = Leadwerks::FileSystem::LoadDir(".");
	if (dir)
	{
		for (size_t i = 0; i<dir->files.size(); i++)
		{
			std::string file = dir->files[i];
			std::string ext = Leadwerks::String::Lower(Leadwerks::FileSystem::ExtractExt(file));
			if (ext == "werk")
			{
				werkfile = Leadwerks::FileSystem::StripExt(file);
			}
		}
		SAFE_DELETE(dir);
	}
	*/

	//Create a window.
	window = Leadwerks::Window::Create(GetWindowTitle(), 0, 0, resx, resy, intStyle);

	//Create a context.
	context = Context::Create(window);

	// Set Mouse Sensitivity
	System::SetProperty(PROPERTY_MOUSESENSITIVITY, mousesensitivity);

	// Set FOV value.
	System::SetProperty(PROPERTY_FOV, fov);

	// Move the mouse to the center of the screen.
	window->SetMousePosition(context->GetWidth() / 2, context->GetHeight() / 2);

	// Create a world.
	int lq = atoi(System::GetProperty(PROPERTY_LIGHTINGQUALITY, lightquality).c_str());
	world = new LEX::RWorld(lq);
	world->SetBackgroundMap(m_stringbackgroundmap);
	world->LoadMap(System::GetProperty(PROPERTY_MAP, world->GetBackgroundMap()));

	// Set Terrian
	int terrainvalue = atoi(System::GetProperty(PROPERTY_TERRAIN, terrain).c_str());
	world->SetTerrainQuality(terrainvalue);

	// Set Tessellation: Come back to this once this is re-enabled.
	float tessellationvalue = atof(System::GetProperty(PROPERTY_TESSELLATION, tessellation).c_str());
	world->SetTessellationQuality(tessellationvalue);

	// Set MSAA
	int msaavalue = atoi(System::GetProperty(PROPERTY_MULTISAMPLE, msaa).c_str());
	world->SetMultisample(msaavalue);

	// UI
	if (System::GetProperty(PROPERTY_NOVGUI, OFF) == OFF)
	{
#ifdef _RVGUI
		vgui = new LEX::RVGUI(world);
#endif
	}

	return true;
}

/* The Loop Function */
bool App::CheckDrawStats()
{
	// Completely ignore this if devmode is on!
	if (m_bdevmode) return true;

	if (System::GetProperty(PROPERTY_NOVGUI, OFF) == OFF)
	{
#ifdef _RVGUI
		// Only keep loading the xml file if the options panel is opened.
		if (vgui->HasOptionsOpened())
		{
			// I dunno why, but we have to load this file again.
			xmlSettings.load_file(FILE_SETTINGS);
			xml_node miscnode = xmlSettings.child(NODE_SETTINGS_ROOT).child(NODE_SETTINGS_MISC);
			std::string DrawStats = miscnode.attribute(PROPERTY_DRAWSTATS).value();

			if (DrawStats == ON)
			{
				m_bDrawStats = true;
			}
			else
			{
				m_bDrawStats = false;
			}
		}
#endif
	}

	if (System::GetProperty(PROPERTY_DRAWSTATS) == ON)
		return true;

	if (m_bDrawStats)
		return true;

	return false;
}

/* The Loop Function */
bool App::Loop()//lua
{
    // If we got told to "Quit", stop looping.
    if (m_bQuit) return false;

	if (System::GetProperty(PROPERTY_NOVGUI, OFF) == OFF)
	{
#ifdef _RVGUI
		if (vgui->CloseApp()) return false;
#endif
	}

	// If the window is closed.
	if (window->Closed()) return false;

    // Abort!
#ifndef _RETAIL
	if (window->KeyHit(KEY_SAFTEY)) return false;
#endif

    // Easy screenshot!
	if (window->KeyHit(KEY_SCREENSHOT))
	{
        context->Screenshot();
	}

	// ESC pauses the game.
	if (window->KeyHit(KEY_PAUSE))
	{
		world->Pause();
	}

	if (m_bdevmode && window->KeyHit(KEY_DEV_DISCONNECT))
	{
		world->Disconnect();
	}

	//---------------------------------------------------------\\
	// This will be fixed engine side in a future version of LE.
	// For now, we are gonna apply this patch. 
	if (window->Active())
	{ 
		// Update the world.
		world->Update();
	}

	if (window->Minimized() == false)
	{
		world->Render();
	}
	//---------------------------------------------------------\\

	// Test if we should make the mouse visible.
    if (ShouldDrawMouse())
    {
        window->ShowMouse();
    }
    else
    {
        window->HideMouse();
    }

    // Open up the context.
	OpenContext();

	if (System::GetProperty(PROPERTY_NOVGUI, OFF) == OFF)
	{
#ifdef _RVGUI
		vgui->Update();
		vgui->DrawStats(CheckDrawStats());
#endif
	}

    CloseContext();
    context->Sync(world->VSync());

	return true;
}

/* Input: Set Background Map */
bool App::SetBackgroundMap(std::string mapname)//lua
{
	m_stringbackgroundmap = mapname;
	return true;
}


/* Input: Set Start Map */
bool App::SetStartMap(std::string mapname)//lua
{
	world->SetStartMap(mapname);
	return true;
}

/* Input: Load Map */
bool App::LoadMap(std::string mapname)//lua
{
	world->LoadMap(mapname);
    return true;
}

/* Input: Load Save File */
bool App::LoadSaveFile()//lua
{
	world->LoadSaveFile();
	return true;
}

/* Input: Save File */
bool App::SaveFile()//lua
{
	world->SaveFile();
	return true;
}

/* Input: Pause the game */
bool App::Pause()//lua
{
	world->Pause();
	return true;
};

/* Test to see if we should draw the mouse. */
bool App::ShouldDrawMouse()
{
    // If we are paused, draw it.
	if (world->IsPaused())
    {
        return true;
    }

    // If we are NOT in a map, draw it.
    if (world->IsConnected() == false)
    {
        return true;
    }

    return false;
}

/* Input: This bool toggles the engine's stats. */
bool App::DrawStats(bool value)//lua
{
    m_bDrawStats = value;
    return m_bDrawStats;
}

/* Input: Open Context. */
bool App::OpenContext()//lua
{
	// Open up the context.
	context->SetBlendMode(CONTEXT_OPEN);
	context->SetColor(1, 1, 1, 1);

	return true;
}

/* Input: Open Context. */
bool App::CloseContext()//lua
{
	// Reset the font.
	if (System::GetProperty(PROPERTY_NOVGUI, OFF) == OFF)
	{
#ifdef _RVGUI
		context->SetFont(vgui->GetDefaultFont());
#endif
	}

	// Reset the color.
	context->SetColor(1, 1, 1, 1);

	// Close up the context.
	context->SetBlendMode(CONTEXT_CLOSE);

	return true;
}

/* Input: Check to see if we are connected. */
bool App::Connected() //lua
{
	return world->IsConnected();
}

/* Input: Disconnect from map. */
bool App::Disconnect()//lua
{
	world->Disconnect();
    return true;
}

/* Input: Close application*/
bool App::Quit()//lua
{
    m_bQuit = true;
    return true;
}