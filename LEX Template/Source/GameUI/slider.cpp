/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#include "slider.h"

namespace LEX
{
	Slider::Slider(short pWorldPosX, short pWorldPosY)
	{
		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		slider = new SliderBox(0, 0);
		slider->SetPosition(posX, posY + slider->GetHeight() / 2);
		slider->SetMinDistance(posX);
		width = posX + m_intmaxvalue + slider->GetWidth();
		slider->SetMaxDistance(width - posX);

		SetTextColor(241, 241, 241);
		SetTrackColor(32, 32, 32);
		//SetSliderColor(45, 45, 45);
		SetSliderColor(104, 104, 104);
		SetSliderBorderColor(64, 64, 64);

		Leadwerks::Context *context = Context::GetCurrent();
		titlefont = context->GetFont();
		m_title = "SLIDER";
	}

	Slider::~Slider()
	{
	}

	void Slider::Update()
	{
		Leadwerks::Context *context = Context::GetCurrent();
		Leadwerks::Window *window = context->GetWindow();
		context->SetColor(GetTrackColor().x, GetTrackColor().y, GetTrackColor().z, 1);

		short lineY = slider->GetY() + slider->GetHeight() / 2;
		context->DrawLine(posX, lineY, width, lineY);

		context->DrawLine(posX, lineY + slider->GetHeight() / 2, posX, lineY - slider->GetHeight() / 2);
		context->DrawLine(GetWidth(), lineY + slider->GetHeight() / 2, GetWidth(), lineY - slider->GetHeight() / 2);

		// TODO: Add more lines.
		short halfline = posX + m_intmaxvalue / 2 + slider->GetWidth() / 2;
		context->DrawLine(halfline, lineY + slider->GetHeight() / 4, halfline, lineY - slider->GetHeight() / 4);

		short lft_qline = posX + m_intmaxvalue / 4 + slider->GetWidth() / 2;
		context->DrawLine(lft_qline, lineY + slider->GetHeight() / 6, lft_qline, lineY - slider->GetHeight() / 6); // 25

		short rt_qline = posX + m_intmaxvalue + slider->GetWidth() / 2 - m_intmaxvalue / 4;
		context->DrawLine(rt_qline, lineY + slider->GetHeight() / 6, rt_qline, lineY - slider->GetHeight() / 6); // 75

		context->SetColor(GetTextColor().x, GetTextColor().y, GetTextColor().z, 1);
		context->DrawText(m_title, posX, posY - slider->GetHeight() / titlefont->GetHeight());

		slider->Update();

		//if (m_intvalue != m_intvalue)
		//{
		m_intvalue = slider->GetSliderPosition() - posX;
		//System::Print(m_intvalue);
	//}


	}

	SliderBox::SliderBox(short pWorldPosX, short pWorldPosY, short pWidth, short pHeight)
	{
		width = pWidth;
		height = pHeight;

		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = 1;

		SetColor(45, 45, 45);
		//SetPressedColor(255, 0, 0);
		SetAlpha(255);
		SetBorderColor(64, 64, 64);

		//m_shortSliderMin = GetX();
		//m_shortSliderMax = GetX() + m_intSliderMaxValue;

		RectButton::Init();
	}

	SliderBox::~SliderBox()
	{
	}

	void SliderBox::Render()
	{
		Leadwerks::Context *context = Context::GetCurrent();
		Leadwerks::Window *window = context->GetWindow();

		Vec3 mousePos = window->GetMousePosition();
		context->SetColor(GetPressedColor().x, GetPressedColor().y, GetPressedColor().z, GetAlpha());

		if (mouseEvent == kEventMouseLeftDown)
		{
			short sliderpos = mousePos.x - GetWidth() / 2;
			context->SetColor(GetPressedColor().x, GetPressedColor().y, GetPressedColor().z, GetAlpha());

			if (sliderpos >= m_shortSliderMin && sliderpos <= m_shortSliderMin + m_shortSliderMax - GetWidth())
			{
				SetSliderPosition(sliderpos);
			}
		}
		else if (mouseEvent == kEventMouseLeftUp)
		{
		}

		context->SetColor(GetColor().x, GetColor().y, GetColor().z, GetAlpha());
		context->DrawRect(posX, posY, width, height);

		context->SetColor(1, 1, 1);
		DrawBorder();

		/*
		Vec3 mousePos = window->GetMousePosition();
		context->SetColor(GetPressedColor().x, GetPressedColor().y, GetPressedColor().z, GetAlpha());
		short lineXlength = m_shortSliderMin + m_shortSliderMax;
		short lineY = posY + GetHeight() / 2;
		context->DrawLine(m_shortSliderMin, lineY, lineXlength, lineY);

		if (mouseEvent == kEventMouseLeftDown)
		{
			short sliderpos = mousePos.x - GetWidth() / 2;
			context->SetColor(GetPressedColor().x, GetPressedColor().y, GetPressedColor().z, GetAlpha());

			if (sliderpos >= m_shortSliderMin && sliderpos <= m_shortSliderMin + m_shortSliderMax - GetWidth())
			{
				SetSliderPosition(sliderpos);
			}
		}
		else if (mouseEvent == kEventMouseLeftUp)
		{
			m_intvalue = GetSliderPosition() / 10;
			System::Print(m_intvalue);
		}

		context->SetColor(GetColor().x, GetColor().y, GetColor().z, GetAlpha());
		context->DrawRect(posX, posY, width, height);

		context->SetColor(1, 1, 1);
		DrawBorder();
		*/
	}
}