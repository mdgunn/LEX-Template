/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/
#ifndef OS_IOS

#include "main.h"
#include "lua-gluecode.h"


#ifdef _RETAIL
	#ifdef _WIN32
	// This will remove the cmd window from showing up with our context.
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

// This makes it so we can convert int to a string.
namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

void DebugErrorHook(char* c)
{
	int n=0;//<--------------------------- Add a breakpoint here to catch errors
}

    #ifdef __APPLE__
int main_(int argc,const char *argv[])
{
	#else
int main(int argc,const char *argv[])
{
	#endif

#if 0
	//Load saved settings
	std::string settingsfile = std::string(argv[0]);
	settingsfile = FileSystem::StripAll(settingsfile);
	if (String::Right(settingsfile, 6) == ".debug") settingsfile = String::Left(settingsfile, settingsfile.length() - 6);
	System::AppName = settingsfile;
	std::string settingsdir = FileSystem::GetAppDataPath();

	if (IsLinux() && !IsAndroid())
	{
		settingsdir = settingsdir + "/." + String::Lower(settingsfile);
	}
	else
	{
		settingsdir = settingsdir + "/" + settingsfile;
	}

	if (FileSystem::GetFileType(settingsdir) == 0) FileSystem::CreateDir(settingsdir);
	settingsfile = settingsdir + "/" + settingsfile + ".cfg";
	System::LoadSettings(settingsfile);
#endif

	//Set program path
	System::AppPath = FileSystem::ExtractDir(argv[0]);

	//Load command-line parameters
	System::ParseCommandLine(argc, argv);

	//Enable Lua sandboxing
	if (String::Int(System::GetProperty(PROPERTY_SANDBOX)) != 0) Interpreter::sandboxmode = true;

	//Switch directory (This is really for the exe of the game launcher)
	std::string gamepack = System::GetProperty(PROPERTY_GAME);
	if (gamepack != S_NULL)
	{
		Package* package = Package::Load(gamepack);
		if (!package) return 1;
	}

	//Add debug hook for catching errors
	Leadwerks::System::AddHook(System::DebugErrorHook,(void*)DebugErrorHook);

    //Load any zip files in main directory
    Leadwerks::Directory* dir = Leadwerks::FileSystem::LoadDir(".");
    if (dir)
    {
		for (size_t i = 0; i<dir->files.size(); i++)
        {
            std::string file = dir->files[i];
			std::string ext = Leadwerks::String::Lower(Leadwerks::FileSystem::ExtractExt(file));
            if (ext=="zip" || ext=="pak")
            {
                Leadwerks::Package::Load(file);
            }
        }
        delete dir;
    }

	// Make sure we have a settings file.
	if (FileSystem::GetFileType(FILE_SETTINGS) == 0)
	{
		pugi::xml_document xmlSettings;
		xmlSettings.reset();

		xml_node rootnode = xmlSettings.append_child(NODE_SETTINGS_ROOT);
		xml_node resnode = rootnode.append_child(NODE_SETTINGS_DISPLAY);

		/*
		// The default screen res is the user's current res size from the graphics driver.
		unsigned int xo = System::GetGraphicsMode(System::CountGraphicsModes() - 1).x;
		std::string sx = patch::to_string(xo);
		char const *pchar_resX = sx.c_str();

		unsigned int yo = System::GetGraphicsMode(System::CountGraphicsModes() - 1).y;
		std::string sy = patch::to_string(yo);
		char const *pchar_resY = sy.c_str();

		resnode.append_attribute(PROPERTY_SCREENWIDTH) = pchar_resX;
		resnode.append_attribute(PROPERTY_SCREENHEIGHT) = pchar_resY;
		*/

		/* 8-25-15: The app class will get the monitor's dimention only if it's fullscreen.*/
		resnode.append_attribute(PROPERTY_SCREENWIDTH) = "1024";
		resnode.append_attribute(PROPERTY_SCREENHEIGHT) = "768";

		// We have fullscreen disabled by default. 
		//Some programs such as the Samsung SSD Wizard don't allow LE to go fullscreen if it's running.
		resnode.append_attribute(PROPERTY_FULLSCREEN) = "0"; // 0 or 1

		xml_node graphicsnode = rootnode.append_child(NODE_SETTINGS_GRAPHICS);
		graphicsnode.append_attribute(PROPERTY_LIGHTINGQUALITY) = "1"; // 0 - 2
		graphicsnode.append_attribute(PROPERTY_MULTISAMPLE) = "1"; // 0, 1, 2, 4, 8, or 16.
		graphicsnode.append_attribute(PROPERTY_TERRAIN) = "1"; // 0 - 2
		graphicsnode.append_attribute(PROPERTY_TESSELLATION) = "1"; // 0 - 2; Not yet utilized, but it's here. 

		xml_node controlsnode = rootnode.append_child(NODE_SETTINGS_CONTROLS);
		controlsnode.append_attribute(PROPERTY_MOUSESENSITIVITY) = "18"; //15 // 1 - 100
		controlsnode.append_attribute(PROPERTY_FOV) = "70"; // 1 - 100

		xml_node miscsnode = rootnode.append_child(NODE_SETTINGS_MISC);
		miscsnode.append_attribute(PROPERTY_DRAWSTATS) = "0"; // 0 or 1
		miscsnode.append_attribute(PROPERTY_VSYNC) = "1"; // 0 or 1
		//miscsnode.append_attribute(PROPERTY_VOLUME) = "100"; // 0 - 100

		xmlSettings.save_file(FILE_SETTINGS);
	}

	if (IsDebug())
	{
		std::string debuggerhostname = System::GetProperty("debuggerhostname");
		if (debuggerhostname != "")
		{
			//Connect to the debugger
			int debuggerport = String::Int(System::GetProperty("debuggerport"));
			if (!Interpreter::Connect(debuggerhostname, debuggerport))
			{
				Print("Error: Failed to connect to debugger with hostname \"" + debuggerhostname + "\" and port " + String(debuggerport) + ".");
				return false;
			}
			Print("Successfully connected to debugger.");
			std::string breakpointsfile = System::GetProperty("breakpointsfile");
			if (breakpointsfile != S_NULL)
			{
				if (!Interpreter::LoadBreakpoints(breakpointsfile))
				{
					Print("Error: Failed to load breakpoints file \"" + breakpointsfile + "\".");
				}
			}
		}
	}

	// Load LUA classes.
	if (Interpreter::L == NULL) Interpreter::Reset();
	tolua_luacom_open(Interpreter::L);

	// Run the main.lua script. This script calls the app class.
	if (FileSystem::GetFileType(GAMESCRIPT_MAIN) == 1)
	{
		//Execute main script file
		if (Interpreter::ExecuteFile(GAMESCRIPT_MAIN))
		{
			if (IsDebug())
			{
				Interpreter::Disconnect();
			}
			
			Steamworks::Shutdown();
			return 0;
		}
		else
		{
			if (IsDebug())
			{
				Interpreter::Disconnect();
			}

			Steamworks::Shutdown();
			return 1;
		}
	}
}

#endif // OS_IOS
