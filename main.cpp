
/**
 * @brief - A toy project to generate mazes and explore them.
 */

# include <core_utils/StdLogger.hh>
# include <core_utils/PrefixedLogger.hh>
# include <core_utils/LoggerLocator.hh>
# include <core_utils/CoreException.hh>
# include "AppDesc.hh"
# include "TopViewFrame.hh"
# include "App.hh"

int
main(int /*argc*/, char** /*argv*/) {
  // Create the logger.
  utils::StdLogger raw;
  raw.setLevel(utils::Level::Debug);
  utils::PrefixedLogger logger("pge", "main");
  utils::LoggerLocator::provide(&raw);

  /// TODO: Restore old code.
  /*
  application::sdl::SdlApplication app("Agents watcher", "65px-Stop_hand.svg[1].BMP", argc, argv);

  environment::Environment env;
  environment::drawable::EnvironmentDrawer drawable(env, utils::sdl::Area(0.0, 0.0, 13.47, 10.0), utils::sdl::Area(10.0, 10.0, 620, 460.0));
  environment::launcher::EnvironmentLauncher launcher(10.0, 1.0 / 1.0, environment::time::Unit::Second);
  environment::EnvironmentInitializer init(0u, 2u, utils::sdl::Area(0.0, 0.0, 10.0, 0.0));

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
  */

  try {
    logger.logMessage(utils::Level::Notice, "Starting application");

    pge::Viewport tViewport = pge::Viewport(olc::vf2d(-5.0f, -5.0f), olc::vf2d(59.0f, 59.0f));
    pge::Viewport pViewport = pge::Viewport(olc::vf2d(0.0f, 0.0f), olc::vf2d(768.0f, 768.0f));

    pge::CoordinateFrameShPtr cf = std::make_shared<pge::TopViewFrame>(
      tViewport,
      pViewport,
      olc::vi2d(64, 64)
    );
    pge::AppDesc ad = pge::newDesc(olc::vi2d(768, 768), cf, "maze");
    pge::App demo(ad);

    demo.Start();
  }
  catch (const utils::CoreException& e) {
    logger.logError(utils::Level::Critical, "Caught internal exception while setting up application", e.what());
  }
  catch (const std::exception& e) {
    logger.logError(utils::Level::Critical, "Caught internal exception while setting up application", e.what());
  }
  catch (...) {
    logger.logMessage(utils::Level::Critical, "Unexpected error while setting up application");
  }

  return EXIT_SUCCESS;
}
