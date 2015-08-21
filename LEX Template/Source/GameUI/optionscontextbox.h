/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( OPTIONSCONTEXTBOX_H )
#define OPTIONSCONTEXTBOX_H
#pragma once

#include "../main.h"
#include "../rworld.h"
#include "basepanel.h"
#include "contextbuttons.h"
#include "chooser.h"
#include "slider.h"
#include "numberdisplay.h"

namespace LEX
{
	class OptionsContextBox : public BaseContextBox
	{
	public:
		OptionsContextBox(short pWidth = 800, short pHeight = 600, short pWorldPosX = 0, short pWorldPosY = 0, bool pCenter = true, short pBorderWidth = 1);
		virtual ~OptionsContextBox();
		virtual void FixButtonPos();
		virtual void Draw();
		//virtual void SaveSetting(const char *pSetting, const char *pNewVal);

		virtual void Reload();
		virtual void Open();
		virtual void ApplyMSAA();
		virtual void ApplyLightQuality();
		virtual void ApplyTerrain();
		virtual void ApplyTessellation();
		virtual void ApplyFullscreen();
		virtual void ApplyCamSmoothing();
		virtual void ApplyFOV();
		//virtual void ApplyVolume();

		void SetWorld(RWorld* pWorld)
		{
			world = pWorld;
		}

		RectButton* GetAdvOptionsBtn()
		{
			return  advancedoptionsbutton;
		}

	private:
		RWorld* world;

		RectButton* advancedoptionsbutton;

		ChooserMSAA* CH_MSAA;
		Chooser3* CH_LightQuality;
		Chooser3* CH_Terrain;
		Chooser3* CH_Tessellation;

		BaseCheckBox* CB_FullScreen;

		Slider* SL_CamSmoothing;
		NumberDisplay* ND_CamSmoothing;

		Slider* SL_FOV;
		NumberDisplay* ND_FOV;

		/*
		Slider* SL_Volume;
		NumberDisplay* ND_Volume;
		*/

		pugi::xml_document xmlSettings;

	};

	class AdvOptionsContextBox : public BaseContextBox
	{
	public:
		AdvOptionsContextBox(short pWidth = 800, short pHeight = 600, short pWorldPosX = 0, short pWorldPosY = 0, bool pCenter = true, short pBorderWidth = 1);
		virtual ~AdvOptionsContextBox();
		virtual void FixButtonPos();
		virtual void Draw();
		virtual void Reload();
		virtual void Open();
		virtual void ApplyDrawStats();
		void SetWorld(RWorld* pWorld)
		{
			world = pWorld;
		}

		bool Drawstats()
		{
			return  m_bdrawstats;
		}

		virtual void ApplyVSync();
		bool VSync()
		{
			return  m_bvsync;
		}

	private:
		bool m_bdrawstats;
		RWorld* world;
		BaseCheckBox* CB_DrawStats;

		bool m_bvsync;
		BaseCheckBox* CB_VSync;

		pugi::xml_document xmlSettings;
	};
}

#endif // OPTIONSCONTEXTBOX_H