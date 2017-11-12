
#include <iostream>
#include "StringUtilsTest.h"
#include "SdlApplication.h"
#include "Environment.h"
#include "EnvironmentDrawer.h"
#include "EnvironmentLauncher.h"
#include "EnvironmentInitializer.h"

int main(int argc, char* argv[])
{
    application::sdl::SdlApplication app("Agents watcher", "65px-Stop_hand.svg[1].BMP", argc, argv);

    freopen( "CON", "w", stdout );
    freopen( "con", "w", stderr );

    environment::Environment env;
    environment::drawable::EnvironmentDrawer drawable(env, utils::sdl::Area(0.0, 0.0, 13.47, 10.0), utils::sdl::Area(10.0, 10.0, 620, 460.0));
    environment::launcher::EnvironmentLauncher launcher(10.0, 1.0 / 1.0, environment::time::Unit::Second);
    environment::EnvironmentInitializer init(0u, 2u, utils::sdl::Area(0.0, 0.0, 10.0, 0.0));

    SDL_EnableKeyRepeat(1, 1);

    int errorCode(0);
    try
    {
        env.addListener(&drawable);
        app.addDrawable(&drawable);
        app.addListener(&drawable);
        app.addListener(&launcher);
        app.addListener(&env.getDrawablesUpdater());
        launcher.addRunnable(&env);
        env.create(init);
        launcher.start();

        app.run();

        launcher.stop();
    }
    catch (std::exception& e)
    {
        std::cerr << "[ERROR] Caught instance of exception (message: \"" << e.what() << "\"), aborting..." << std::endl;
        errorCode = 1;
    }
    catch (...)
    {
        std::cerr << "[ERROR] Caught unexpected error, aborting..." << std::endl;
        errorCode = 1;
    }
    return errorCode;
}
