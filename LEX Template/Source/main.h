/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( MAIN_H )
#define MAIN_H
#pragma once

#include "Leadwerks.h"
using namespace Leadwerks;

#include "pugixml.hpp"
using namespace pugi;

#ifdef _RETAIL
#define IsRetail() true
#else
#define IsRetail() false
#endif

#ifdef _DEBUG
#define IsRelease() false
#define IsDebug() true
#else
#define IsRelease() true
#define IsDebug() false
#endif

#ifdef _DEMO
#define IsDemo() true
#else
#define IsDemo() false
#endif

#ifdef _WIN32
	#define IsWindows() true
	#define IsLinux() false
	#define IsAndroid() false
	#define IsOSX() false
#else
	#define IsWindows() false
	// linux
	#ifdef __linux__
		#define IsLinux() true
		#define IsOSX() false
		// Just in-case LE goes back to mobile.
		#ifdef __ANDROID__ 
		#define IsAndroid() true
		#else
		#define IsAndroid() false 
		#endif
	#else
		#define IsLinux() false
	#endif

	// OSX
	#ifdef __APPLE__
		#define IsOSX() true
	#else
		#define IsOSX() false
	#endif
#endif

#define _RVGUI
#define S_NULL ""
#define ON "1"
#define OFF "0"
#define STRING_ERROR "ERROR :("
#define LEX_DEVINFO "Leadwerks Extended Executable 100"

#define LUA_APP_CLASS "App"

// Context
#define CONTEXT_OPEN Blend::Alpha
#define CONTEXT_CLOSE Blend::Solid

#define CONTEXT_TEXT_OK "OK"
#define CONTEXT_TEXT_CANCEL "Cancel"
#define CONTEXT_TEXT_APPLY "Apply"
#define CONTEXT_TEXT_YES "Yes"
#define CONTEXT_TEXT_NO "No"
#define CONTEXT_TEXT_BACK "Back"
#define CONTEXT_TEXT_ADVOPTIONS "Advanced Options"

// Lua scripts.
#define GAMESCRIPT_MAIN "Scripts/Main.lua"
#define GAMESCRIPT_GAMERULES "Scripts/GameRules.lua"

// Fonts
#define FONT_DEFAULT "Fonts/consola.ttf"
#define FONT_ARIAL "Fonts/arial.ttf"

// Files
#define FILE_SETTINGS "Settings.xml"						
#define FILE_PRECACHELIST "Scripts/PrecacheGlobal.lua"			
#define FILE_RESOURCE_MENUSCHEME "ClientScheme.xml" 
#define FILE_SAVE "SaveData.dat"

// File UI
#define FILE_LOADSCREEN "Materials/UI/LoadingScreen/loadingscreen_default.tex"
#define FILE_BACKGROUND FILE_LOADSCREEN // <--- If you just want a image background instead of a map, replace this value.
#define FILE_LOADICON "Materials/UI/LoadingScreen/loadingicon.tex"
#define FILE_ARROWLEFT "Materials/UI/Icons/arrowleft.tex"
#define FILE_ARROWRIGHT "Materials/UI/Icons/arrowright.tex"
#define FILE_CLOSEICON "Materials/UI/Icons/close.tex"

// Properties
#define PROPERTY_SCREENWIDTH "screenwidth"				// Screenwidth
#define PROPERTY_SCREENHEIGHT "screenheight"			// Screenheight
#define PROPERTY_FULLSCREEN "fullscreen"				// Fullscreen
#define PROPERTY_VR "vr"								// Virtual Reality 
#define PROPERTY_LIGHTINGQUALITY "lightquality"			// Light Quality
#define PROPERTY_MULTISAMPLE "multisample"				// Multisampling (MSAA)
#define PROPERTY_TERRAIN "terrainquality"				// Terrain Resoultion
#define PROPERTY_TESSELLATION "tessellation"			// Tessellation. Not yet utilized in 3.6, but support is here.
#define PROPERTY_MOUSESENSITIVITY "mousesensitivity"	// The value we use to control the mouse sensitivity/drag 
#define PROPERTY_FOV "fov"								// Feild of View.
#define PROPERTY_DRAWSTATS "drawstats"					// Draw framerate and other information on the screen.
#define PROPERTY_DEVELOPER "dev"						// Developer mode shows more of what's going on in the application. You can use this value to also toggle things in your scripts.													
#define PROPERTY_VSYNC "vsync"							// Vertical sync.
#define PROPERTY_VOLUME "volume"						// Volume. If you uncomment most of the code relating to this, you'll have a working slider that changes this value. I could not figure out how to get it to properly work; so right now, it's disabled. 
#define PROPERTY_NOVGUI "novgui"						// Tell the application not to create or call the vgui. Great for quick tests.
#define PROPERTY_MAP "map"								// Property used to load maps.
#define PROPERTY_SANDBOX "sandbox"						// Sandbox mode. Alows the game to run in a lua sandbox. 
#define PROPERTY_GAME "game"							// Used by the game launcher to load multiple games with one application. 

// XML NODES
#define NODE_SETTINGS_ROOT "settings"
#define NODE_SETTINGS_DISPLAY "display"
#define NODE_SETTINGS_GRAPHICS "graphics"
#define NODE_SETTINGS_CONTROLS "camera"
#define NODE_SETTINGS_MISC "misc"

#define NODE_MENUSCHEME_ROOT "menuscheme"
#define NODE_MENUSCHEME_BACKGROUND "background"
#define NODE_MENUSCHEME_BACKGROUND_MUSIC "music"
#define NODE_MENUSCHEME_TITLE "title"
#define NODE_MENUSCHEME_TITLE_POSITION "position"
#define NODE_MENUSCHEME_TITLE_TEXT "text"
#define NODE_MENUSCHEME_TITLE_COLOR "color"
#define NODE_MENUSCHEME_TITLE_IMAGE "image"

#define NODE_MENUSCHEME_BUTTONS "buttons"
#define NODE_MENUSCHEME_BUTTONS_TEXT "text"
#define NODE_MENUSCHEME_BUTTONS_COLORS "colors"
#define NODE_MENUSCHEME_BUTTONS_COLOR "color"
#define NODE_MENUSCHEME_BUTTONS_ROLLOVERCOLOR "rollover"
#define NODE_MENUSCHEME_BUTTONS_PRESSEDCOLOR "pressed"
#define NODE_MENUSCHEME_BUTTONS_SOUNDS "sounds"

#define NODE_MENUSCHEME_BUTTONS_CONTINUE "continue"
#define NODE_MENUSCHEME_BUTTONS_RESUME "resume"
#define NODE_MENUSCHEME_BUTTONS_NEWGAME "newgame"
#define NODE_MENUSCHEME_BUTTONS_OPTIONS "options"
#define NODE_MENUSCHEME_BUTTONS_QUIT "quit"

#define NODE_BASEPANEL_ROOT "basepanel"
#define NODE_BASEPANEL_TEXT "text"
#define NODE_BASEPANEL_LABEL "label"
#define NODE_BASEPANEL_MESSAGE "message"
#define NODE_BASEPANEL_BORDER "border"
#define NODE_BASEPANEL_COLORS "colors"

// Keys
#define KEY_SAFTEY Key::End
#define KEY_SCREENSHOT Key::F5 
#define KEY_PAUSE Key::Escape
#define KEY_DEV_DISCONNECT Key::Home
#define KEY_DEV_LOADMAP Key::L

// MACROS
#define MSG(x) System::Print(x);
#define DEVMSG(x) if (System::GetProperty(PROPERTY_DEVELOPER, "0") == "1") {System::Print(x);}

#define SAFE_DELETE( p )       { if( p ) { delete ( p );     ( p ) = NULL; } }
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete[] ( p );   ( p ) = NULL; } }
#define SAFE_RELEASE( p )      { if( p ) { ( p )->Release(); ( p ) = NULL; } }
#define SAFE_RETURN( p )       { if( p ) { return ( p ); } } 

#endif // MAIN_H