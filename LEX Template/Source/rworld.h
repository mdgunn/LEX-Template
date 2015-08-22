/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( RWORLD_H )
#define RWORLD_H
#pragma once

#include "main.h"

enum
{
	RWorld_NotConnected,
	RWorld_Background,
	RWorld_Paused,
	RWorld_InGame,
};

namespace LEX
{
	class RWorld : public World
	{
	public:
		RWorld(int LightQuality = 1);
		virtual ~RWorld();

		void Verify();
		void Precache();
		virtual void Update();

		void SetBackgroundMap(std::string mapname)
		{
			m_stringbackgroundmap = mapname;
		}
		std::string GetBackgroundMap()
		{
			return m_stringbackgroundmap;
		}
		void SetStartMap(std::string mapname)
		{
			m_stringstartmap = mapname;
		}
		std::string GetStartMap()
		{
			return m_stringstartmap;
		}
		void LoadMap(std::string mapname);
		void SetCurrentLevel(std::string mapname);
		std::string GetCurrentLevel()
		{
			return m_stringcurrentlevel;
		}

		bool IsConnected()
		{
			return m_bConnected;
		}

		bool InBackgroundMap()
		{
			return m_bInBackgroundMap;
		}

		void SetMultisample(int value)
		{
			string MSAAtring = static_cast<ostringstream*>(&(ostringstream() << value))->str();
			System::SetProperty(PROPERTY_MULTISAMPLE, MSAAtring);
			m_intsettingmsaa = value;
		};

		int GetMultisample()
		{
			return m_intsettingmsaa;
		};

		int GetTerrainQuality()
		{
			return terrainquality;
		};

		// Pausing
		bool Pause();//lua
		bool IsPaused() // lua
		{
			return m_bPaused;
		};

		void SoildPause()
		{
			if (m_bPaused)
				return;

			if (IsConnected() == false)
				return;

			Leadwerks::Time::Pause();
			m_bPaused = true;
		}

		void SoildUnPause()
		{
			if (!m_bPaused)
				return;

			if (IsConnected() == false)
				return;

			Leadwerks::Time::Resume();
			m_bPaused = false;
		}

		bool HasSaveFile()
		{
			savefile = FileSystem::ReadFile(FILE_SAVE);
			if (savefile != NULL)
				return true;

			return false;
		}

		void LoadSaveFile();
		void SaveFile();

		bool LoadStartMap()
		{
			if (m_stringstartmap != S_NULL)
			{
				LoadMap(m_stringstartmap);
				return true;
			}

			return false;
		}

		int GetWorldState();
		void Disconnect();

		bool VSync()
		{
			return m_bvsync;
		}

		void SetVSync(bool b)
		{
			m_bvsync = b;
		}

		//void FindActiveCamera

	private:
		// Map Related.
		std::string m_stringbackgroundmap;
		std::string m_stringstartmap;

		bool m_bConnected = false;
		bool m_bInBackgroundMap = false;
		std::string m_stringchangelevel;
		std::string m_stringcurrentlevel;

		Stream* savefile;

		// Pausing
		bool m_bPaused = false;
		bool m_bvsync = true;

		int m_intsettingmsaa;
	};
}

#endif