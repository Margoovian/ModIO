#pragma once

#include "Application.h"
#include "Maths.h"
#include <memory>

namespace ModIO::Interfaces {
	class AudioGeneratorInterface;
}

class ExampleApplication : public Application
{
private:
	//Any data that should persist for the duration of your program,
	//declare it here.


public:
	ExampleApplication();
	~ExampleApplication();
	void Initialise() override;

	void Update(float delta) override;

	void OnMouseScroll(bool positive) override;
	void  OnKeyPress(Key key) override;

private: 
	Vec2 mPoint = { 0,0 };
	int mWaveType = 0;

	std::weak_ptr<ModIO::Interfaces::AudioGeneratorInterface> mSaw;
	std::weak_ptr<ModIO::Interfaces::AudioGeneratorInterface> mSquare;
	std::weak_ptr<ModIO::Interfaces::AudioGeneratorInterface> mSine;
	std::weak_ptr<ModIO::Interfaces::AudioGeneratorInterface> mTriangle;

};