
# include "Game.hh"
# include <cxxabi.h>
# include "Menu.hh"
# include "Initializer.hh"

/// @brief - The height of the status menu in pixels.
# define STATUS_MENU_HEIGHT 50

/// @brief - The maximum speed for the simulation.
# define MAX_SIMULATION_SPEED 8.0f

namespace {

  pge::MenuShPtr
  generateMenu(const olc::vi2d& pos,
               const olc::vi2d& size,
               const std::string& text,
               const std::string& name,
               bool clickable = false,
               bool selectable = false)
  {
    pge::menu::MenuContentDesc fd = pge::menu::newMenuContent(text, "", size);
    fd.color = olc::WHITE;
    fd.hColor = olc::GREY;
    fd.align = pge::menu::Alignment::Center;

    return std::make_shared<pge::Menu>(
      pos,
      size,
      name,
      pge::menu::newColoredBackground(olc::VERY_DARK_BLUE),
      fd,
      pge::menu::Layout::Horizontal,
      clickable,
      selectable
    );
  }

}

namespace pge {

  Game::Game():
    utils::CoreObject("game"),

    m_state(
      State{
        true,  // paused
        true,  // disabled
        false, // terminated
        1.0f,  // speed
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
  Game::generateMenus(float width,
                      float /*height*/)
  {
    // Generate the status menu.
    MenuShPtr status = generateMenu(olc::vi2d(), olc::vi2d(width, STATUS_MENU_HEIGHT), "", "status");

    olc::vi2d pos;
    olc::vi2d dims(50, STATUS_MENU_HEIGHT);
    m_menus.count = generateMenu(pos, dims, "N/A agent(s)", "count");
    m_menus.speed = generateMenu(pos, dims, "Speed: x1", "speed", true);

    // Register menus in the parent.
    status->addMenu(m_menus.count);
    status->addMenu(m_menus.speed);
    m_menus.speed->setSimpleAction(
      [this](Game& g) {
        g.speedUpSimulation();
      }
    );

    // Package menus for output.
    std::vector<MenuShPtr> menus;

    menus.push_back(status);

    return menus;
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
  Game::speedUpSimulation() noexcept {
    // Only available when the game is not paused.
    if (m_state.paused) {
      return;
    }

    float s = m_state.speed;

    m_state.speed *= 2.0f;
    if (m_state.speed > MAX_SIMULATION_SPEED) {
      m_state.speed = 1.0f;
    }

    // Update the desired FPS for the simulation.
    m_launcher.setDesiredFramerate(m_state.speed);

    log(
      "Simulation speed updated from " + std::to_string(s) +
      " to " + std::to_string(m_state.speed),
      utils::Level::Info
    );
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
    // Update the speed of the simulation.
    int sp = static_cast<int>(std::round(m_state.speed));
    m_menus.speed->setText("Speed: x" + std::to_string(sp));

    /// TODO: Handle agents count.
    unsigned c = 0u;
    std::string str = std::to_string(c) + " agent";
    if (c != 1u) {
      str += "s";
    }
    m_menus.count->setText(str);
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
