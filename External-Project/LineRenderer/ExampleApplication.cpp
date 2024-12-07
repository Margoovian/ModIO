#include "ExampleApplication.h"
#include "LineRenderer.h"
#include "imgui.h"
#include "ModIO.h"
#include "Key.h"

std::unique_ptr<ModIO::AudioSession> gSession;

ExampleApplication::ExampleApplication()
{
	//Use the constructor to set up the application info, because the harness
	//needs this information early so it can set the name of the window when
	//it creates it.
	appInfo.appName = "ModIO Example Intergration";
	appInfo.grid.show = false;

	

}

ExampleApplication::~ExampleApplication()
{
	gSession->Stop();
}

void ExampleApplication::Initialise()
{
	//You should set up your application here. This function gets called
	//after the window is set up and the rendering context is created, so if
	//you're doing anything weird with rendering, OpenGL functions will be
	//available at this point.

	gSession = ModIO::CreateSession();

	using namespace ModIO;

	TD::MasterRef masterRef = gSession->GetMaster();

	TD::SharedMaster master = masterRef.lock();

	if (master) {

		TD::SharedMixer mixer = master->AddMixer();

		TD::SharedChain chain = mixer->AddChain();

		mSaw = chain->SetGenerator<Generators::SawtoothGenerator>();
		mSquare = mixer->AddChain()->SetGenerator<Generators::SquarewaveGenerator>();
		mSine = mixer->AddChain()->SetGenerator<Generators::SinewaveGenerator>();
		mTriangle = mixer->AddChain()->SetGenerator<Generators::TrianglewaveGenerator>();

	}

	gSession->Start();

}

void ExampleApplication::Update(float delta)
{
	//Everything that your program does every frame should go here.
	//This includes rendering done with the line renderer!

	if (
		leftMouseDown &&
		cursorPos.x < 10 && cursorPos.x > -10 &&
		cursorPos.y < 10 && cursorPos.y > -10
		) {
		mPoint = cursorPos;
	}

	float volume = Remap(mPoint.y, -10, 10, 0, 1.0f);;

	int sawOn = mWaveType == 0;
	int sineOn = mWaveType == 2;
	int squareOn = mWaveType == 1;
	int triangleOn = mWaveType == 3;

	ModIO::GetShared(mSaw)->mAmplitude = volume * sawOn;
	ModIO::GetShared(mSine)->mAmplitude = volume * sineOn;
	ModIO::GetShared(mSquare)->mAmplitude = volume * squareOn;
	ModIO::GetShared(mTriangle)->mAmplitude = volume * triangleOn;
	
	float freq = Remap(mPoint.x, -10, 10, 0, 523.25f);

	ModIO::GetShared(mSaw)->mFrequency = freq;
	ModIO::GetShared(mSine)->mFrequency = freq;
	ModIO::GetShared(mSquare)->mFrequency = freq;
	ModIO::GetShared(mTriangle)->mFrequency = freq;

	lines->DrawCircle(mPoint, 0.20f, Colour::ORANGE);
	lines->DrawCircle(mPoint, 0.175f, Colour::ORANGE);
	lines->DrawCircle(mPoint, 0.15f, Colour::ORANGE);
	lines->DrawCircle(mPoint, 0.125f, Colour::ORANGE);
	lines->DrawCircle(mPoint, 0.1f, Colour::ORANGE);
	lines->DrawCircle(mPoint, 0.075f, Colour::ORANGE);
	lines->DrawCircle(mPoint, 0.05f, Colour::ORANGE);
	lines->DrawCircle(mPoint, 0.025f, Colour::ORANGE);

	lines->DrawLineSegment({ -10,-10 }, { -10,10 });
	lines->DrawLineSegment({ 10,-10 }, { -10,-10 });

	lines->DrawText("Freq: " + std::to_string(freq), {-10,-13}, 1.0f);
	lines->DrawText("Volume: " + std::to_string((int)(volume * 100.0f)) + "%", {-10,-16}, 1.0f);
	
	if(sawOn) lines->DrawText("Generator: Sawtooth", {-10,-19}, 1.0f);
	else if(sineOn) lines->DrawText("Generator: Sine", {-10,-19}, 1.0f);
	else if(squareOn) lines->DrawText("Generator: Square", {-10,-19}, 1.0f);
	else if(triangleOn) lines->DrawText("Generator: Triangle", {-10,-19}, 1.0f);

}

void ExampleApplication::OnMouseScroll(bool positive)
{
	
}

void ExampleApplication::OnKeyPress(Key key)
{
	if (key == Key::X) {
		mWaveType++;
		if (mWaveType > 3) {
			mWaveType = 0;
		}
	}
	else if (key == Key::Z) {
		mWaveType--;
		if (mWaveType < 0) {
			mWaveType = 3;
		};
	}
}
