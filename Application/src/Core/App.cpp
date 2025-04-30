#include "App.h"

#include <stdio.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

App::App(const AppContext Context)
{

	Initialize();

    CreateWindow(Context);

    SetupContexts();

    FinalizeSetup();

    m_AppContext = Context;

}

const int App::GetWidth() const
{
    return ImGui::GetWindowWidth();
}

const int App::GetHeight() const
{
    return ImGui::GetWindowHeight();
}

const ImVec2 App::GetSize() const
{
    return ImGui::GetWindowSize();
}

const ImVec2 App::GetWindowPosition() const
{
    return ImGui::GetWindowPos();
}

SDL_Window* App::GetWindow() const
{
    return m_Window;
}

SDL_Renderer* App::GetRenderer() const
{
    return m_Renderer;
}

void App::Initialize()
{

    // Setup SDL
    // [If using SDL_MAIN_USE_CALLBACKS: all code below until the main loop starts would likely be your SDL_AppInit() function]
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return;
    }

}

void App::CreateWindow(const AppContext& Context)
{

    // Create window with SDL_Renderer graphics context
    m_Window = SDL_CreateWindow(Context.Title, Context.Width, Context.Height, Context.Flags);
    if (m_Window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return;
    }
    m_Renderer = SDL_CreateRenderer(GetWindow(), nullptr);
    SDL_SetRenderVSync(GetRenderer(), 1);
    if (m_Renderer == nullptr)
    {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return;
    }
    SDL_SetWindowPosition(GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(GetWindow());

}

void App::SetupContexts()
{

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(GetWindow(), GetRenderer());
    ImGui_ImplSDLRenderer3_Init(GetRenderer());

}

void App::FinalizeSetup()
{
}

void App::Start()
{

    SetupApp();

    m_Running = true;

    while (m_Running)
    {
        
        if (ProcessInternal())
        {
            continue;
        }

        RenderInternal();
    }

    Exit();

}

void App::Exit()
{
    // Call virtual shutdown function for app implementation
    Shutdown();

    // Cleanup
    // [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppQuit() function]
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(GetRenderer());
    SDL_DestroyWindow(GetWindow());
    SDL_Quit();


}

void App::RenderInternal()
{
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // Call virtual render function for app implementation
    Render();

    // Rendering
    ImGui::Render();

    ImGuiIO& io = ImGui::GetIO();

    SDL_SetRenderScale(GetRenderer(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColorFloat(GetRenderer(),
        m_AppContext.BackgroundColour.r,
        m_AppContext.BackgroundColour.g,
        m_AppContext.BackgroundColour.b,
        m_AppContext.BackgroundColour.a
    );
    SDL_RenderClear(GetRenderer());
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), GetRenderer());
    SDL_RenderPresent(GetRenderer());
}

bool App::ProcessInternal()
{

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
            m_Running = false;
        if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(GetWindow()))
            m_Running = false;
    }

    // Call virtual process function for app implementation
    Process();

    // [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppIterate() function]
    //if (SDL_GetWindowFlags(GetWindow()) & SDL_WINDOW_MINIMIZED)
    //{
    //    SDL_Delay(10);
    //    return true; // Should skip
    //}

    return false; // Should continue

}
