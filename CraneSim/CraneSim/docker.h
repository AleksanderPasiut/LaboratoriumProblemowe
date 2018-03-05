#pragma once

#include "include.h"

class Docker
{
public:
	enum Position
	{
		Fill = 0x00,
		FillAR = 0x01,
		Vertical = 0x10,
		Horizontal = 0x20,
		Top = 0x11,
		Bottom = 0x12,
		InvTop = 0x13,
		InvBottom = 0x14,
		Left = 0x21,
		Right = 0x22,
		InvLeft = 0x23,
		InvRight = 0x24
	};
	enum Type
	{
		Fixed,
		Percent
	};
private:
	HWND& parent;
	HWND target;

	Position position;
	Type type;
	union
	{
		float percent;
		int fixed;
	};

public:
	Docker(HWND& parent, HWND target, Position position, float percent) : parent(parent), target(target), position(position), type(Percent), percent(percent) { SetParent(target, parent); }
	Docker(HWND& parent, HWND target, Position position, int fixed) : parent(parent), target(target), position(position), type(Fixed), fixed(fixed) { SetParent(target, parent); }

	void operator() ()
	{
		RECT rect;
		GetClientRect(parent, &rect);
		this->operator()(rect.right, rect.bottom);
	}
	void operator() (const LONG& width, const LONG& height)
	{
		switch (position)
		{
			case Fill:
			{
				SetWindowPos(target, 0, 0, 0, width, height, SWP_NOZORDER);
				break;
			}
			case FillAR:
			{
				if (width / percent <= height)
				{
					int h = static_cast<int>(static_cast<float>(width) / percent);
					SetWindowPos(target, 0, 0, (height - h) / 2, width, h, SWP_NOZORDER);
				}
				else
				{
					int w = static_cast<int>(static_cast<float>(height) * percent);
					SetWindowPos(target, 0, (width - w) / 2, 0, w, height, SWP_NOZORDER);
				}
				break;
			}
			default:
			{
				int factor;
				switch (type)
				{
					case Fixed: factor = fixed; break;
					case Percent: 
					{
						switch (position & 0xf0)
						{
							case Horizontal: factor = static_cast<int>(percent * static_cast<float>(width)); break;
							case Vertical: factor = static_cast<int>(percent * static_cast<float>(height)); break;
						}
						break;
					}
				}

				switch (position)
				{
					case Top: SetWindowPos(target, 0, 0, 0, width, factor, SWP_NOZORDER | SWP_NOMOVE); break;
					case InvTop: SetWindowPos(target, 0, 0, factor, width, height - factor, SWP_NOZORDER); break;
					case Bottom: SetWindowPos(target, 0, 0, height - factor, width, factor, SWP_NOZORDER); break;
					case InvBottom: SetWindowPos(target, 0, 0, 0, width, height - factor, SWP_NOZORDER | SWP_NOMOVE); break;
					case Left: SetWindowPos(target, 0, 0, 0, factor, height, SWP_NOZORDER | SWP_NOMOVE); break;
					case InvLeft: SetWindowPos(target, 0, factor, 0, width - factor, height, SWP_NOZORDER); break;
					case Right: SetWindowPos(target, 0, width - factor, 0, factor, height, SWP_NOZORDER); break;
					case InvRight: SetWindowPos(target, 0, 0, 0, width - factor, height, SWP_NOZORDER | SWP_NOMOVE); break;
				}
			}
		}
	}
	bool operator() (HWND cmp) const noexcept
	{
		return target == cmp;
	}
};