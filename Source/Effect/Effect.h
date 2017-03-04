/* Copyright (c) 2017 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#pragma once

NS_DOROTHY_BEGIN

class Shader;

class Effect : public Object
{
public:
	PROPERTY_READONLY(bgfx::ProgramHandle, Program);
	virtual ~Effect();
	virtual bool init() override;
	CREATE_FUNC(Effect);
protected:
	Effect(Shader* vertShader, Shader* fragShader);
private:
	Ref<Shader> _fragShader;
	Ref<Shader> _vertShader;
	bgfx::ProgramHandle _program;
	DORA_TYPE_OVERRIDE(Effect);
};

class SpriteEffect : public Effect
{
public:
	virtual ~SpriteEffect();
	bgfx::UniformHandle getSampler() const;
	CREATE_FUNC(SpriteEffect);
protected:
	SpriteEffect(Shader* vertShader, Shader* fragShader);
private:
	bgfx::UniformHandle _sampler;
	DORA_TYPE_OVERRIDE(SpriteEffect);
};

NS_DOROTHY_END