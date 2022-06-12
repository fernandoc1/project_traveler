#include "modes/battle/battle.h"

#include "engine/audio/audio.h"
#include "engine/input.h"
#include "engine/mode_manager.h"
#include "engine/video/video.h"
#include "engine/system.h"

#include "common/global/global.h"
#include "common/gui/gui.h"
#include "common/app_settings.h"
#include "common/app_name.h"

#include "modes/boot/boot.h"
#include "modes/battle/battle.h"
#include "main_options.h"

#include <SDL2/SDL_image.h>


using namespace vt_utils;
using namespace vt_common;
using namespace vt_audio;
using namespace vt_video;
using namespace vt_gui;
using namespace vt_mode_manager;
using namespace vt_input;
using namespace vt_system;
using namespace vt_global;
using namespace vt_script;
using namespace vt_boot;
using namespace vt_map;


/** \brief Initializes all engine components and makes other preparations for the game to start
*** \return True if the game engine was initialized successfully, false if an unrecoverable error occurred
*** \throw exception if initialization failed.
**/
static void InitializeEngine()
{
    setenv("SDL_VIDEO_FULLSCREEN_DISPLAY", "0", 0);


    // Initialize SDL. The video, audio, and joystick subsystems are initialized elsewhere.
    if(SDL_Init(SDL_INIT_TIMER) != 0) {
        throw Exception("MAIN ERROR: Unable to initialize SDL: ",
                        __FILE__, __LINE__, __FUNCTION__);
    }

    // Create and initialize singleton class managers
    AudioManager = AudioEngine::SingletonCreate();
    InputManager = InputEngine::SingletonCreate();
    ScriptManager = ScriptEngine::SingletonCreate();
    VideoManager = VideoEngine::SingletonCreate();
    SystemManager = SystemEngine::SingletonCreate();
    ModeManager = ModeEngine::SingletonCreate();
    GUIManager = GUISystem::SingletonCreate();
    GlobalManager = GameGlobal::SingletonCreate();

    if(!VideoManager->SingletonInitialize()) {
        throw Exception("ERROR: unable to initialize VideoManager",
                        __FILE__, __LINE__, __FUNCTION__);
    }

    if(!AudioManager->SingletonInitialize()) {
        throw Exception("ERROR: unable to initialize AudioManager",
                        __FILE__, __LINE__, __FUNCTION__);
    }

    if(!ScriptManager->SingletonInitialize()) {
        throw Exception("ERROR: unable to initialize ScriptManager",
                        __FILE__, __LINE__, __FUNCTION__);
    }

    if(!SystemManager->SingletonInitialize()) {
        throw Exception("ERROR: unable to initialize SystemManager",
                        __FILE__, __LINE__, __FUNCTION__);
    }
    if(!InputManager->SingletonInitialize()) {
        throw Exception("ERROR: unable to initialize InputManager",
                        __FILE__, __LINE__, __FUNCTION__);
    }
    if(!ModeManager->SingletonInitialize()) {
        throw Exception("ERROR: unable to initialize ModeManager",
                        __FILE__, __LINE__, __FUNCTION__);
    }

    // Apply engine configuration settings with delayed initialization calls to the managers
    InputManager->InitializeJoysticks();

    if(!VideoManager->FinalizeInitialization())
        throw Exception("ERROR: Unable to apply video settings",
                        __FILE__, __LINE__, __FUNCTION__);

    // NOTE: This function call should have its argument set to false for release builds
    GUIManager->DEBUG_EnableGUIOutlines(false);

    // Loads needed game text styles (fonts + colors + shadows)
    if (!TextManager->LoadFonts(SystemManager->GetLanguageLocale()))
        exit(EXIT_FAILURE);

    // Loads potential emotes
    GlobalManager->GetEmoteHandler().LoadEmotes("data/entities/emotes.lua");

    // Hide the mouse cursor since we don't use or acknowledge mouse input from the user
    SDL_ShowCursor(SDL_DISABLE);

    // Ignore the events that we don't care about so they never appear in the event queue
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
    SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
    SDL_EventState(SDL_USEREVENT, SDL_IGNORE);

    if(!GUIManager->SingletonInitialize()) {
        throw Exception("ERROR: unable to initialize GUIManager",
                        __FILE__, __LINE__, __FUNCTION__);
    }

    // This loads the game global script, once everything is ready,
    // and will permit to load skills, items and other translatable strings
    // using the correct settings language.
    if(!GlobalManager->SingletonInitialize())
        throw Exception("ERROR: unable to initialize GlobalManager",
                        __FILE__, __LINE__, __FUNCTION__);

    SystemManager->InitializeTimers();
}

void DeinitializeEngine()
{
    // NOTE: Even if the singleton objects do not exist when this function is called, invoking the
    // static Destroy() singleton function will do no harm (it checks that the object exists before deleting it).

    // Delete the mode manager first so that all game modes free their resources
    ModeEngine::SingletonDestroy();

    // Delete the global manager second
    // to remove all object references corresponding to other engine subsystems
    GameGlobal::SingletonDestroy();

    // Delete all of the reamining independent engine components
    GUISystem::SingletonDestroy();
    AudioEngine::SingletonDestroy();
    InputEngine::SingletonDestroy();
    SystemEngine::SingletonDestroy();
    VideoEngine::SingletonDestroy();
    // Do it last since all luabind objects must be freed
    // before closing the lua state.
    ScriptEngine::SingletonDestroy();
}

//! \brief Render the game frame.
void RenderFrame()
{
    // Clear the primary render target.
    VideoManager->Clear();

    // Render the game.
    ModeManager->Draw();
    ModeManager->DrawEffects();
    ModeManager->DrawPostEffects();
    VideoManager->DrawFadeEffect();
    VideoManager->DrawDebugInfo();
}

//! \brief Update the engine logic with the provided new absolute tick time.
void UpdateEngine(uint32_t update_tick)
{
    //uint32_t update_begin_tick = update_tick;

    // Update timers for correct time-based movement operation
    SystemManager->UpdateTimers(update_tick);

    //std::cout << "Update timers delay: " << SDL_GetTicks() - update_tick << "ms" << std::endl;
    //update_tick = SDL_GetTicks();

    // Process all new events
    InputManager->EventHandler();

    //std::cout << "Update events delay: " << SDL_GetTicks() - update_tick << "ms" << std::endl;
    //update_tick = SDL_GetTicks();

    // Update video
    VideoManager->Update();

    //std::cout << "Update video delay: " << SDL_GetTicks() - update_tick << "ms" << std::endl;
    //update_tick = SDL_GetTicks();

    // Update any streaming audio sources
    AudioManager->Update();

    //std::cout << "Update audio delay: " << SDL_GetTicks() - update_tick << "ms" << std::endl;
    //update_tick = SDL_GetTicks();

    // Update the game status
    ModeManager->Update();

    //std::cout << "Update events delay: " << SDL_GetTicks() - update_tick << "ms" << std::endl;
    //std::cout << "Update total delay: " << SDL_GetTicks() - update_begin_tick << "ms" << std::endl;
}

// Every great game begins with a single function :)
// N.B.: The main signature must be:
// int main(int argc, char *argv[]) to permit compilation
// with Visual Studio and SDL2.
// See: https://stackoverflow.com/questions/6847360/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
int main(int argc, char* argv[])
{
    // When the program exits, call 'SDL_Quit'.
    atexit(SDL_Quit);

    if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        PRINT_ERROR << "SDL video initialization failed" << std::endl;
        return EXIT_FAILURE;
    }

    // Create a default window
    SDL_Window* sdl_window = SDL_CreateWindow(APPFULLNAME,
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         vt_video::VIDEO_VIEWPORT_WIDTH,
                         vt_video::VIDEO_VIEWPORT_HEIGHT,
                         SDL_WINDOW_OPENGL);
    if (!sdl_window) {
        PRINT_ERROR << "SDL window creation failed: "
                    << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    // Set the window icon
    SDL_Surface* icon = IMG_Load("data/icons/program_icon.png");
    if (icon) {
        SDL_SetWindowIcon(sdl_window, icon);
        // ...and the surface containing the icon pixel data is no longer required.
        SDL_FreeSurface(icon);
    }

    // Create an OpenGL context associated with the window.
    SDL_GLContext glcontext = SDL_GL_CreateContext(sdl_window);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 2);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_GL_SetSwapInterval(1);

    try {
        // Initialize the random number generator (note: 'unsigned int' is a required usage in this case)
        srand(static_cast<unsigned int>(time(nullptr)));

        // This variable will be set by the ParseProgramOptions function
        int32_t return_code = EXIT_FAILURE;

        // Parse command lines and exit out of the game if needed
        if(!vt_main::ParseProgramOptions(return_code,
                                         static_cast<int32_t>(argc), argv)) {
            return static_cast<int>(return_code);
        }

        // Function call below throws exceptions if any errors occur
        InitializeEngine();

    } catch(const Exception &e) {
        PRINT_ERROR << e.ToString() << std::endl;
        return EXIT_FAILURE;
    }

    // Set the window handle, apply actual screen resolution
    VideoManager->SetWindowHandle(sdl_window);
    VideoManager->ApplySettings();

    // Now the settings are loaded, let's set the windows translated title.
    // tr: The window title only supports UTF-8 characters in SDL2.
    std::string app_fullname = "Battle test";
    SDL_SetWindowTitle(sdl_window, app_fullname.c_str());
    SDL_ShowWindow(sdl_window);

    ModeManager->Push(new vt_battle::BattleMode(), false, true);

    // Used for a variable game speed,
    // sleeping when on sufficiently fast hardware, and max FPS.
    const uint32_t UPDATES_PER_SECOND = 60 + 10; // 10 is a smoothness safety margin (gives a max of 70 FPS)
    const uint32_t SKIP_RENDER_TICKS = 1000 / UPDATES_PER_SECOND;
    uint32_t render_tick = SDL_GetTicks();
    uint32_t next_render_tick = 0;

    try {
        // This is the main loop for the game.
        // The loop iterates once for every frame drawn to the screen.
        while (SystemManager->NotDone()) {

            // Render part
            render_tick = SDL_GetTicks();

            // We want to be nice with the CPU % used..
            // And set fixed rendering updates
            if (render_tick < next_render_tick) {
                SDL_Delay(next_render_tick - render_tick);
                continue;
            }

            UpdateEngine(render_tick);

            RenderFrame();

            // Swap the buffers once the draw operations are done.
            SDL_GL_SwapWindow(sdl_window);

            next_render_tick = SDL_GetTicks() + SKIP_RENDER_TICKS;

        } // while (SystemManager->NotDone())
    } catch(const Exception& e) {
        std::cerr << e.ToString() << std::endl;
        return EXIT_FAILURE;
    }

    DeinitializeEngine();

    // Once finished with OpenGL functions, the SDL_GLContext can be deleted.
    SDL_GL_DeleteContext(glcontext);

    // Close and destroy the window.
    SDL_DestroyWindow(sdl_window);

    return EXIT_SUCCESS;
}
