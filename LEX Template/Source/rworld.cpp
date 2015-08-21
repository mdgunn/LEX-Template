/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#include "rworld.h"

/* Hook Related */
vector<Entity*> entities;
vector<Object*> objects;
std::string nextmap;

Leadwerks::Texture* loadingscreen;
Leadwerks::Texture* loadingicon;

void LoadingScreen()
{
	Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
	Leadwerks::Window* window = Leadwerks::Window::GetCurrent();

	context->SetBlendMode(CONTEXT_OPEN);
	context->SetColor(1, 1, 1, 1);

	std::string bgscreen = FILE_LOADSCREEN;

	// If a tex file under Materials/UI/LoadingScreen/ has a name that matches a map,
	// have that be the loadingscreen for that map.
	std::string file = Leadwerks::FileSystem::StripDir(nextmap);
	std::string filename = Leadwerks::FileSystem::StripExt(file);
	if (FileSystem::GetFileType("Materials/UI/LoadingScreen/" + filename + ".tex") == 1)
	{
		bgscreen = "Materials/UI/LoadingScreen/" + filename + ".tex";
	}

	// Display the loading screen.
	if (FileSystem::GetFileType(FILE_LOADSCREEN) == 1)
	{
		if (loadingscreen = Texture::Load(bgscreen))
		{
			context->DrawImage(loadingscreen, 0, 0, context->GetWidth(), context->GetHeight());
		}
	}
	else
	{
		context->SetColor(1, 0, 1, 1);
		context->DrawRect(0, 0, window->GetWidth(), window->GetHeight());
		context->SetColor(1, 1, 1, 1);
	}
	
	if (loadingicon = Texture::Load(FILE_LOADICON))
	{
		float x = context->GetWidth() - loadingicon->GetWidth();
		float y = context->GetHeight() - loadingicon->GetHeight();
		context->DrawImage(loadingicon, x, y, loadingicon->GetWidth(), loadingicon->GetHeight());
	}

	context->Sync(false);
	context->SetColor(1, 1, 1, 1);
	context->SetBlendMode(CONTEXT_CLOSE);
}

// Handles loading.
void MapHook(Entity* entity, Object* extra)
{
	LoadingScreen();
	objects.push_back(extra);
	entities.push_back(entity);
}
namespace LEX
{
	RWorld::RWorld(int LightQuality)
	{
		SetLightQuality(LightQuality);
	}

	RWorld::~RWorld()
	{
		//savefile->Release();
	}

	void RWorld::Verify()
	{
		DEVMSG("Hello RWorld!");
	}

	// Precache System.
	void RWorld::Precache()
	{
		// Run the script. This script calls the app class.
		if (FileSystem::GetFileType(FILE_PRECACHELIST) == 1)
		{
			//Execute script file
			Interpreter::ExecuteFile(FILE_PRECACHELIST);
		}
		else
		{
			MSG("Missing precache list!");
		}
	}

	// Update the world!
	void RWorld::Update()
	{
		// Never update the world if we are paused.
		if (!IsPaused())
		{
			// The vanila update.
			World::Update();
		}

		// Always update the Time.
		Leadwerks::Time::Update();

		if (m_stringchangelevel != S_NULL)
		{
			nextmap = m_stringchangelevel;
		
			// Announce the loading.
			DEVMSG("Changing Map To: " + m_stringchangelevel);

			// Call the loading screen.
			LoadingScreen();

			// Clear World, and Pause Time.
			Clear();

			Leadwerks::Time::Pause();
			m_bPaused = true;

			if (Map::Load(m_stringchangelevel, &MapHook) == false)
			{
				Debug::Error("Failed to load: " + m_stringchangelevel);
				m_stringchangelevel = S_NULL;
				nextmap = S_NULL;
				Disconnect();
				return;

			}
			else
			{
				//Precache(m_stringchangelevel);
				Precache();
				if (m_stringchangelevel == GetBackgroundMap())
				{
					m_bInBackgroundMap = true;
				}
				else
				{
					m_bInBackgroundMap = false;
				}

				// We are connected.
				if (!m_bInBackgroundMap)
				{
					m_bConnected = true;
				}
			}

			// Get out of pause pausing.
			Leadwerks::Time::Resume();
			m_bPaused = false;
			nextmap = S_NULL;

			// Set the current map to a string.
			SetCurrentLevel(m_stringchangelevel);
		}
	}

	void RWorld::LoadMap(std::string mapname)
	{
		if (mapname != S_NULL)
		{
			m_stringchangelevel = mapname;
		}
		else
		{
			MSG("Failed to load map: " + mapname)
		}
	}

	void RWorld::SetCurrentLevel(std::string mapname)
	{
		// Save the changelevel string to a diffrent one, and clear it
		m_stringcurrentlevel = m_stringchangelevel;
		m_stringchangelevel = S_NULL;
		DEVMSG("Current map: " + m_stringcurrentlevel);
		SAFE_RELEASE(loadingicon);
		SAFE_RELEASE(loadingscreen);

		// Clear any clicks or key presses.
		Leadwerks::Window* window = Leadwerks::Window::GetCurrent();
		window->FlushMouse();
		window->FlushKeys();
		//SaveFile();
	}

	bool RWorld::Pause()//lua
	{
		// Never Pause if we are not connected.
		if (IsConnected() == false) return false;

		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		Leadwerks::Window* window = Leadwerks::Window::GetCurrent();

		window->SetMousePosition(context->GetWidth() / 2, context->GetHeight() / 2);
		if (GetWorldState() != RWorld_Paused)
		{
			Leadwerks::Time::Pause();
			m_bPaused = true;
		}
		else
		{
			Leadwerks::Time::Resume();
			m_bPaused = false;
		}

		// Clear any clicks or key presses.
		window->FlushMouse();
		window->FlushKeys();

		return m_bPaused;
	};

	int RWorld::GetWorldState()
	{
		// If we are not connected (i.e, not in a map).
		if (!m_bConnected)
		{
			// This image acts like a curtain to hide the last frame of the disconnected scene.
			if (m_bInBackgroundMap)
			{
				return RWorld_Background;
			}

			return RWorld_NotConnected;

		}
		else if (m_bConnected)
		{
			// If we are connected, but we are paused.
			if (m_bPaused)
			{
				return RWorld_Paused;
			}

			// Connected and playing!
			return RWorld_InGame;
		}

		// Connected and playing!
		return RWorld_InGame;
	}

	void RWorld::LoadSaveFile()
	{
		savefile = FileSystem::ReadFile(FILE_SAVE);
		if (savefile == NULL)
			Debug::Error("'savefile' file does not exist!");
		savefile->Seek(0);

		m_stringchangelevel = savefile->ReadLine();
		savefile->Release();
	}

	void RWorld::SaveFile()//lua
	{
		if (InBackgroundMap())
		{
			MSG("Can't create save file with the background map");
			return;
		}

		savefile = FileSystem::WriteFile(FILE_SAVE);
		savefile->Seek(0);
		savefile->WriteLine(m_stringcurrentlevel);
		savefile->Release();

		MSG("Game Saved!");
	}

	void RWorld::Disconnect()//lua
	{
		if (m_stringcurrentlevel == S_NULL) return;

		DEVMSG("Disconnecting From: " + m_stringcurrentlevel);
		m_stringcurrentlevel = "";
		Clear();
		Leadwerks::Time::Pause();
		m_stringchangelevel = "";
		m_bConnected = false;
		m_bInBackgroundMap = false;

	}

	/*
	void RWorld::FindActiveCamera()
	{
		// for i=0,self.world:CountEntities()-1 do  --CountEntities is not a supported command
		int i;
		for (i = 0; CountEntities() -1;)
		{
			if (GetEntity(i)->GetClass() == Object::CameraClass)
			{
				Camera* camera = dynamic_cast<Camera*>(GetEntity(i));
				System::Print(camera->GetKeyValue("name"));
				//i++;

			}
		}
	}
	*/
}