/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Const/Header.h"
#include "Platformer/Define.h"

NS_DOROTHY_PLATFORMER_BEGIN

TargetAllow::TargetAllow():
_flag(0)
{ }

void TargetAllow::allow(Relation flag, bool allow)
{
	if (allow)
	{
		_flag |= s_cast<Uint32>(flag);
	}
	else
	{
		_flag &= ~s_cast<Uint32>(flag);
	}
}

bool TargetAllow::isAllow(Relation flag)
{
	return (_flag & s_cast<Uint32>(flag)) != 0;
}

void TargetAllow::setTerrainAllowed(bool var)
{
	if (var)
	{
		_flag |= (1<<3);
	}
	else
	{
		_flag &= ~(1<<3);
	}
}

bool TargetAllow::isTerrainAllowed() const
{
	return (_flag & (1<<3)) != 0;
}

NS_DOROTHY_PLATFORMER_END
