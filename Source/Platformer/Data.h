/* Copyright (c) 2018 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#pragma once

NS_DOROTHY_BEGIN
class World;
NS_DOROTHY_END

NS_DOROTHY_PLATFORMER_BEGIN

class Unit;

class Data
{
public:
	void apply(World* world);
	void setRelation(int groupA, int groupB, Relation relation);
	Relation getRelation(int groupA, int groupB) const;
	Relation getRelation(Unit* unitA, Unit* unitB) const;
	PROPERTY_READONLY(int, GroupHide);
	PROPERTY_READONLY(int, GroupDetectPlayer);
	PROPERTY_READONLY(int, GroupTerrain);
	PROPERTY_READONLY(int, GroupDetect);
	void setDamageFactor(uint16 damageType, uint16 defenceType, float bounus);
	float getDamageFactor(uint16 damageType, uint16 defenceType) const;
	bool isPlayer(Body* body);
	bool isTerrain(Body* body);
	SINGLETON_REF(Data, Director);
private:
	unordered_map<int, Relation> _relationMap;
	unordered_map<uint32, float> _damageBounusMap;
};

#define SharedData \
	Dorothy::Singleton<Dorothy::Platformer::Data>::shared()

NS_DOROTHY_PLATFORMER_END
