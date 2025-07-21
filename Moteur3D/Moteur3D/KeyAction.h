#ifndef  KEYACTION_H
#define KEYACTION_H

#pragma once
struct KeyAction
{
public :
	inline explicit KeyAction(int nKey, int nMods, int nAction) {
		key = nKey; mods = nMods; action = nAction;
	}

	int key;
	int mods;
	int action;

	bool operator==(const KeyAction& ka2) const
	{
		return key == ka2.key && mods == ka2.mods && action == ka2.action; 
	}

	auto operator<=>(const KeyAction& ka2) const
	{
		return key <=> ka2.key;
	}

};

#endif