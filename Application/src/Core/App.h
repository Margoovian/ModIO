#pragma once

#include <memory>
#include <SDL3/SDL.h>

// Application Context
struct AppContext {
	int Width, Height;
	const char* Title;
	uint32_t Flags;
};

// Application framework
class App {

public:

	App(const AppContext Context);

	void Start();

protected:
	void virtual Render() = 0;
	void virtual Process() = 0;
	void virtual Shutdown() = 0;
	void virtual SetupApp() = 0;

	const int GetWidth() const;
	const int GetHeight() const;


private:

	SDL_Window* GetWindow() const;
	SDL_Renderer* GetRenderer() const;

	void Initialize();
	void CreateWindow(const AppContext& Context);
	void SetupContexts();
	void FinalizeSetup();

private:
	void Exit();
	void RenderInternal();
	bool ProcessInternal();

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	
	bool m_Running = false;

};