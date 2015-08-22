/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#include "chooser.h"

namespace LEX
{
	Chooser::Chooser(short pWorldPosX, short pWorldPosY, short pWidth, short pHeight)
	{
		width = pWidth;
		height = pHeight;

		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = 1;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		chooserfont = context->GetFont();
		SetLabel("");
		SetIncreaseRate(1);

		Leadwerks::Texture* backicon = Leadwerks::Texture::Load(FILE_ARROWLEFT);
		backbutton = new ImageButton(backicon, 0, 0);

		Leadwerks::Texture* forwardicon = Leadwerks::Texture::Load(FILE_ARROWRIGHT);
		nextbutton = new ImageButton(forwardicon, 0, 0);

		SetMinOptionValue(0);
		SetMaxOptionValue(2);
		SetChooseOption(GetMinOptionValue());

		SetColor(37, 37, 37);
		SetBorderColor(64, 64, 64);
		SetTextColor(241, 241, 241);
		SetAlpha(255);
	}

	Chooser::~Chooser()
	{
		delete backbutton;
		delete nextbutton;

		chooserfont->Release();
	}

	void Chooser::Update()
	{
		if (m_bVisible)
		{
			Render();
			Logic();
		}
	}


	void Chooser::Logic()
	{
		if (backbutton->GetMouseEvent() == kEventMouseLeftUp)
		{
			//DEVMSG("PRESS-");
			if (m_intoption != GetMinOptionValue())
			{
				m_intoption = m_intoption - m_intincreaserate;
			}
			else
			{
				m_intoption = GetMaxOptionValue();
			}

		}

		if (nextbutton->GetMouseEvent() == kEventMouseLeftUp)
		{
			//DEVMSG("PRESS+");
			if (m_intoption != GetMaxOptionValue())
			{
				m_intoption = m_intoption + m_intincreaserate;
			}
			else
			{
				m_intoption = GetMinOptionValue();
			}
		}

		/*
		if (m_intoption == GetMaxOptionValue())
		{
			SetLabel("High");
		}
		else if (m_intoption == GetMinOptionValue())
		{
			SetLabel("Low");
		}
		else
		{
			SetLabel("Medium");
		}
		*/
	}

	void Chooser::Render()
	{
		Context *context = Context::GetCurrent();
		context->SetColor(GetColor().x, GetColor().y, GetColor().z, GetAlpha());
		context->DrawRect(posX, posY, width, height);

		if (m_btnmsg != S_NULL)
		{
			context->SetColor(GetTextColor().x, GetTextColor().y, GetTextColor().z, GetAlpha());
			float x = posX + GetWidth() / 2;
			float y = posY + GetHeight() / 2;

			context->SetFont(chooserfont);
			x = x - chooserfont->GetTextWidth(m_btnmsg) / 2;
			y = y - chooserfont->GetHeight() / 2;
			context->DrawText(m_btnmsg, x, y);
		}

		context->SetColor(1, 1, 1);

		float by = posY + GetHeight() / 2;
		by = by - backbutton->GetHeight() / 2;
		backbutton->SetPosition(posX, by);
		backbutton->Update();

		float ny = posY + GetHeight() / 2;
		ny = ny - nextbutton->GetHeight() / 2;
		nextbutton->SetPosition(posX + GetWidth() - nextbutton->GetWidth(), ny);
		nextbutton->Update();
		DrawBorder();
	}

	void Chooser::DrawBorder()
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		context->SetColor(GetBorderColor().x, GetBorderColor().y, GetBorderColor().z, GetAlpha());

		if (borderLineWidth <= 0)
			return;

		if (borderLineWidth > 1)
		{
			context->DrawRect(worldPosX, worldPosY, width, height - (height - borderLineWidth));
			context->DrawRect(worldPosX, (worldPosY + height - borderLineWidth), width, borderLineWidth);
			context->DrawRect(worldPosX, worldPosY + borderLineWidth, borderLineWidth, (height - borderLineWidth * 2));
			context->DrawRect(worldPosX + (width - borderLineWidth), worldPosY + borderLineWidth, borderLineWidth, (height - borderLineWidth * 2));
		}
		else if (borderLineWidth == 1)
		{
			//Draw A line
			context->DrawLine(worldPosX, worldPosY, worldPosX + width, worldPosY);
			context->DrawLine(worldPosX, (worldPosY + height), worldPosX + width, (worldPosY + height));
			context->DrawLine(worldPosX, worldPosY, worldPosX, worldPosY + height);
			context->DrawLine(worldPosX + width, worldPosY, worldPosX + width, worldPosY + height);
		}

		context->SetColor(1, 1, 1, 1);

	}

	Chooser3::Chooser3(short pWorldPosX, short pWorldPosY, short pWidth, short pHeight)
	{
		width = pWidth;
		height = pHeight;

		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = 1;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		chooserfont = context->GetFont();
		SetLabel("");
		SetIncreaseRate(1);

		Leadwerks::Texture* backicon = Leadwerks::Texture::Load(FILE_ARROWLEFT);
		backbutton = new ImageButton(backicon, 0, 0);

		Leadwerks::Texture* forwardicon = Leadwerks::Texture::Load(FILE_ARROWRIGHT);
		nextbutton = new ImageButton(forwardicon, 0, 0);


		SetMinOptionValue(0);
		SetMaxOptionValue(2);
		SetChooseOption(GetMinOptionValue());

		SetColor(37, 37, 37);
		SetBorderColor(64, 64, 64);
		SetTextColor(241, 241, 241);
		SetAlpha(255);
	}

	Chooser3::~Chooser3()
	{
	}

	void Chooser3::Logic()
	{
		Chooser::Logic();

		if (m_intoption == GetMaxOptionValue())
		{
			SetLabel("High");
		}
		else if (m_intoption == GetMinOptionValue())
		{
			SetLabel("Low");
		}
		else
		{
			SetLabel("Medium");
		}
	}

	ChooserMSAA::ChooserMSAA(short pWorldPosX, short pWorldPosY, short pWidth, short pHeight)
	{
		width = pWidth;
		height = pHeight;

		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = 1;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		chooserfont = context->GetFont();
		SetIncreaseRate(1);

		Leadwerks::Texture* backicon = Leadwerks::Texture::Load(FILE_ARROWLEFT);
		backbutton = new ImageButton(backicon, 0, 0);

		Leadwerks::Texture* forwardicon = Leadwerks::Texture::Load(FILE_ARROWRIGHT);
		nextbutton = new ImageButton(forwardicon, 0, 0);

		SetMinOptionValue(1);
		SetMaxOptionValue(5);
		//SetChooseOption(GetMSAAOptionValue());

		SetColor(37, 37, 37);
		SetBorderColor(64, 64, 64);
		SetTextColor(241, 241, 241);
		SetAlpha(255);
	}

	ChooserMSAA::~ChooserMSAA()
	{
	}

	void ChooserMSAA::Logic()
	{
		Chooser::Logic();

		if (m_intoption == GetMinOptionValue())
		{
			SetLabel("None");
			SetMSAAOptionValue(1);
		}
		else if (m_intoption == 2)
		{
			SetLabel("2x");
			SetMSAAOptionValue(2);
		}
		else if (m_intoption == 3)
		{
			SetLabel("4x");
			SetMSAAOptionValue(4);
		}
		else if (m_intoption == 4)
		{
			SetLabel("8x");
			SetMSAAOptionValue(8);
		}
		else if (m_intoption == 5)
		{
			SetLabel("16x");
			SetMSAAOptionValue(16);
		}
		else
		{
			m_intoption = GetMinOptionValue();
			System::Print(m_intoption);
		}
	}
}
