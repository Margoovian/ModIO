#include "Synode/Synode.h"

int main(int, char**)
{

    uint32_t Flags = 32 | 8; // 32 -> SDL_WINDOW_RESIZABLE | 8 -> SDL_WINDOW_HIDDEN

    Synode Synode({ 1280, 720, "Synode", Flags });
    Synode.Start();

    return 0;
}