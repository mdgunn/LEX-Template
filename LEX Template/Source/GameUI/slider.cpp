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

		LoadScheme();
	}

	Slider::~Slider()
	{
	}

	void Slider::LoadScheme()
	{
		if (FileSystem::GetFileType(FILE_RESOURCE_MENUSCHEME) == 0)
			return;

		pugi::xml_document xmlPanelRes;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		//<slider>
		xmlPanelRes.load_file(FILE_RESOURCE_MENUSCHEME);
		xml_node rootmenunode = xmlPanelRes.child("slider");

		// -<text>
		xml_node textnode = rootmenunode.child(NODE_BASEPANEL_TEXT);
		std::string textlabelfontval = textnode.attribute("font").value();
		std::string textlabelfontsizeval = textnode.attribute("size").value();
		int textlabelsizeint = atoi(textlabelfontsizeval.c_str());
		SetFont(textlabelfontval, textlabelsizeint);

		// -<colors>
		xml_node colorsnode = rootmenunode.child(NODE_BASEPANEL_COLORS);


		// --<color>
		xml_node basecolornode = colorsnode.child(NODE_BASEPANEL_BTN_COLOR);
		const char* basecolor_R_vals = basecolornode.attribute("r").value();
		const char* basecolor_G_vals = basecolornode.attribute("g").value();
		const char* basecolor_B_vals = basecolornode.attribute("b").value();
		SetSliderColor(atof(basecolor_R_vals),
			atof(basecolor_G_vals),
			atof(basecolor_B_vals));

		// --<text>
		xml_node txtcolornode = colorsnode.child(NODE_BASEPANEL_TEXT);
		const char* txtcolor_R_vals = txtcolornode.attribute("r").value();
		const char* txtcolor_G_vals = txtcolornode.attribute("g").value();
		const char* txtcolor_B_vals = txtcolornode.attribute("b").value();
		SetTextColor(atof(txtcolor_R_vals),
			atof(txtcolor_G_vals),
			atof(txtcolor_B_vals));

		// --<track>
		xml_node trackcolornode = colorsnode.child("track");
		const char* trackcolor_R_vals = trackcolornode.attribute("r").value();
		const char* trackcolor_G_vals = trackcolornode.attribute("g").value();
		const char* trackcolor_B_vals = trackcolornode.attribute("b").value();
		SetTrackColor(atof(trackcolor_R_vals),
			atof(trackcolor_G_vals),
			atof(trackcolor_B_vals));
	}

	void Slider::Update()
	{
		Leadwerks::Context *context = Context::GetCurrent();
		Leadwerks::Window *window = context->GetWindow();
		Vec4 oldr = context->GetColor();
		Leadwerks::Font* oldfont = context->GetFont();
		context->SetFont(titlefont);

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

		context->SetColor(oldr);
		context->SetFont(oldfont);
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
		LoadScheme();
	}

	SliderBox::~SliderBox()
	{
	}

	void SliderBox::LoadScheme()
	{
		if (FileSystem::GetFileType(FILE_RESOURCE_MENUSCHEME) == 0)
			return;

		pugi::xml_document xmlPanelRes;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		//<slider>
		xmlPanelRes.load_file(FILE_RESOURCE_MENUSCHEME);
		xml_node rootmenunode = xmlPanelRes.child("slider");

		// -<colors>
		xml_node colorsnode = rootmenunode.child(NODE_BASEPANEL_COLORS);

		// --<pressed>
		xml_node pressedcolornode = colorsnode.child(NODE_BASEPANEL_BTN_PRESSED);
		const char* pressedcolor_R_vals = pressedcolornode.attribute("r").value();
		const char* pressedcolor_G_vals = pressedcolornode.attribute("g").value();
		const char* pressedcolor_B_vals = pressedcolornode.attribute("b").value();
		SetPressedColor(atof(pressedcolor_R_vals),
			atof(pressedcolor_G_vals),
			atof(pressedcolor_B_vals));

		// --<rollover>
		xml_node rollovercolornode = colorsnode.child(NODE_BASEPANEL_BTN_ROLLOVER);
		const char* rollovercolor_R_vals = rollovercolornode.attribute("r").value();
		const char* rollovercolor_G_vals = rollovercolornode.attribute("g").value();
		const char* rollovercolor_B_vals = rollovercolornode.attribute("b").value();
		SetRolloverColor(atof(rollovercolor_R_vals),
			atof(rollovercolor_G_vals),
			atof(rollovercolor_B_vals));

		// --<border>
		xml_node bordercolornode = colorsnode.child(NODE_BASEPANEL_BTN_BORDER);
		const char* bordercolor_R_vals = bordercolornode.attribute("r").value();
		const char* bordercolor_G_vals = bordercolornode.attribute("g").value();
		const char* bordercolor_B_vals = bordercolornode.attribute("b").value();
		SetBorderColor(atof(bordercolor_R_vals),
			atof(bordercolor_G_vals),
			atof(bordercolor_B_vals));

		// --<highlight>
		xml_node highlightcolornode = colorsnode.child(NODE_BASEPANEL_BTN_HIGHLIGHT);
		const char* highlightcolor_R_vals = highlightcolornode.attribute("r").value();
		const char* highlightcolor_G_vals = highlightcolornode.attribute("g").value();
		const char* highlightcolor_B_vals = highlightcolornode.attribute("b").value();
		SetRolloverBorderColor(atof(highlightcolor_R_vals),
			atof(highlightcolor_G_vals),
			atof(highlightcolor_B_vals));

	}

	void SliderBox::Render()
	{
		Leadwerks::Context *context = Context::GetCurrent();
		Leadwerks::Window *window = context->GetWindow();
		Vec4 oldr = context->GetColor();
		Vec3 mousePos = window->GetMousePosition();

		if (mouseEvent == kEventMouseOver)
		{
			context->SetColor(GetRolloverColor().x, GetRolloverColor().y, GetRolloverColor().z);
		}
		else if (mouseEvent == kEventMouseLeftDown)
		{
			context->SetColor(GetPressedColor().x, GetPressedColor().y, GetPressedColor().z);
			short sliderpos = mousePos.x - GetWidth() / 2;
			if (sliderpos >= m_shortSliderMin && sliderpos <= m_shortSliderMin + m_shortSliderMax - GetWidth())
			{
				SetSliderPosition(sliderpos);
			}
		}
		else
		{
			context->SetColor(GetColor().x, GetColor().y, GetColor().z);
		}

		context->DrawRect(posX, posY, width, height);

		DrawBorder();
		context->SetColor(oldr);
	}
}
