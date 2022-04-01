
# include "Game.hh"
# include <cxxabi.h>
# include "Menu.hh"
# include "Initializer.hh"

namespace pge {

  Game::Game():
    utils::CoreObject("game"),

    m_state(
      State{
        true,  // paused
        true,  // disabled
        false, // terminated
      }
    ),

    m_menus(),

    m_env(),
    m_launcher(&m_env, 1.0f, 1.0f, mas::time::Unit::Second)
  {
    setService("game");

    // Initialize the environment.
    mas::environment::Initializer init(utils::Boxf(0.0f, 0.0f, 10.0f, 5.0f));
    init(m_env);
  }

  Game::~Game() {}

  std::vector<MenuShPtr>
  Game::generateMenus(float /*width*/,
                      float /*height*/)
  {
    log("Generate UI menus here", utils::Level::Info);
    return std::vector<MenuShPtr>();
  }

  void
  Game::performAction(float /*x*/, float /*y*/) {
    // Only handle actions when the game is not disabled.
    if (m_state.disabled) {
      log("Ignoring action while menu is disabled");
      return;
    }
  }

  bool
  Game::step(float /*tDelta*/) {
    // When the game is paused it is not over yet.
    if (m_state.paused) {
      return true;
    }

    /// TODO: Handle step of game.

    updateUI();

    return true;
  }

  void
  Game::togglePause() {
    if (m_state.paused) {
      resume();
    }
    else {
      pause();
    }

    enable(!m_state.paused);
  }

  void
  Game::startSimulation() {
    m_launcher.start();
  }

  void
  Game::pauseSimulation() {
    m_launcher.pause();
  }

  void
  Game::resumeSimulation() {
    m_launcher.resume();
  }

  void
  Game::stopSimulation() {
    m_launcher.stop();
  }

  void
  Game::stepSimulation() {
    m_launcher.step();
  }

  void
  Game::enable(bool enable) {
    m_state.disabled = !enable;

    if (m_state.disabled) {
      log("Disabled game UI", utils::Level::Verbose);
    }
    else {
      log("Enabled game UI", utils::Level::Verbose);
    }
  }

  void
  Game::updateUI() {
    /// TODO: Handle update of UI.
  }

  bool
  Game::TimedMenu::update(bool active) noexcept {
    // In case the menu should be active.
    if (active) {
      if (!wasActive) {
        // Make it active if it's the first time that
        // we detect that it should be active.
        date = utils::now();
        wasActive = true;
        menu->setVisible(true);
      }
      else if (utils::now() > date + utils::toMilliseconds(duration)) {
        // Deactivate the menu in case it's been active
        // for too long.
        menu->setVisible(false);
      }
      else {
        // Update the alpha value in case it's active
        // for not long enough.
        olc::Pixel c = menu->getBackgroundColor();

        float d = utils::diffInMs(date, utils::now()) / duration;
        c.a = static_cast<uint8_t>(
          std::clamp((1.0f - d) * pge::alpha::Opaque, 0.0f, 255.0f)
        );
        menu->setBackground(pge::menu::newColoredBackground(c));
      }
    }
    // Or if the menu shouldn't be active anymore and
    // it's the first time we detect that.
    else if (wasActive) {
      // Deactivate the menu.
      menu->setVisible(false);
      wasActive = false;
    }

    return menu->visible();
  }

}
