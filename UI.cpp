#include "UI.h"

void MenuBlock::AddMenuItem(const int& id, const std::string& menuItem)
{
	items[id] = MenuItem(id, menuItem);
	items[id].GetTotalString();
	items[id].daddyBlock = this;
	items[id].loc = loc;
	items[id].color[0] = 1.0f; items[id].color[1] = 1.0f; items[id].color[2] = 1.0f; items[id].color[3] = 1.0f;
	firstItemLoc = loc;
	firstItemLoc.x += CHARSIZES::CALIBRI24; firstItemLoc.y += menuPadding;
}
void MenuBlock::SetBlockSize(const bool& _displayValidItems)
{
	firstItemLoc = loc;
	firstItemLoc.x += CHARSIZES::CALIBRI28; firstItemLoc.y += menuPadding;
	titlePos = loc; titlePos.x += CHARSIZES::CALIBRI28; titlePos.y += menuPadding * 1.5;

	if (!isDraw)
	{
		width = title.size() * CHARSIZES::CALIBRI28 + CHARSIZES::CALIBRI28 * 2;
		height = 3 * menuPadding;
		return;
	}

	displayValidItems = _displayValidItems;
	if (!displayValidItems)
	{
		height = items.size() * menuPadding + 3 * menuPadding;
	}
	else
	{
		int validCoutner = 0;
		for (auto& i : items)
		{
			if (!i.second.value.empty())
			{
				validCoutner++;
			}
		}
		height = validCoutner * menuPadding + 3 * menuPadding;
	}

	int longestItem = 0;
	for (auto& i : items)
	{
		if (i.second.GetSize() > longestItem)
			longestItem = i.second.GetSize();
	}
	if (title.size() > longestItem)
		longestItem = title.size();

	width = longestItem * CHARSIZES::CALIBRI24 + CHARSIZES::CALIBRI24 * 5;
	if (!isDraw)
		height = 3 * menuPadding;

	GetMenuItemLocation();
}
void MenuBlock::GetMenuItemLocation()
{
	if (!displayValidItems)
		for (int i = 0; i < items.size(); i++)
		{
			Vertex2 pos;
			pos = firstItemLoc; pos.y += i * menuPadding + 2 * menuPadding;
			items[i].loc = pos;
		}
	else
	{
		int validCoutner = 0;
		for (int i = 0; i < items.size(); i++)
		{
			if (items[i].value.empty())
				continue;
			validCoutner++;
			Vertex2 pos;
			pos = firstItemLoc; pos.y += validCoutner * menuPadding + 1 * menuPadding;
			items[i].loc = pos;
		}
	}

}
bool MenuBlock::IsHovered(const Vec2&mouseCrd)
{
	return (mouseCrd.x > loc.x && mouseCrd.x < loc.x + width && mouseCrd.y > loc.y && mouseCrd.y < loc.y + height);
}