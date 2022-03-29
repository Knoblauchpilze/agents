#ifndef    APP_HH
# define   APP_HH

# include "PGEApp.hh"
# include "TexturePack.hh"
# include "Menu.hh"
# include "Game.hh"
# include "GameState.hh"

namespace pge {

  class App: public PGEApp {
    public:

      /**
       * @brief - Create a new default pixel game engine app.
       * @param desc - contains all the needed information to
       *               create the canvas needed by the app and
       *               set up base properties.
       */
      App(const AppDesc& desc);

      /**
       * @brief - Desctruction of the object.
       */
      ~App() = default;

    protected:

      void
      loadData() override;

      void
      loadResources() override;

      void
      loadMenuResources() override;

      void
      cleanResources() override;

      void
      cleanMenuResources() override;

      void
      drawDecal(const RenderDesc& res) override;

      void
      draw(const RenderDesc& res) override;

      void
      drawUI(const RenderDesc& res) override;

      void
      drawDebug(const RenderDesc& res) override;

      bool
      onFrame(float fElapsed) override;

      void
      onInputs(const controls::State& c,
               const CoordinateFrame& cf) override;

    private:

      /// @brief - Convenience structure regrouping needed props to
      /// draw a sprite.
      struct SpriteDesc {
        // The x coordinate of the sprite.
        float x;

        // The y coordinate of the sprite.
        float y;

        // The radius of the sprite: applied both along the x and y
        // coordinates.
        float radius;

        // The relative position of the sprite compared to its
        // position.
        RelativePosition loc;

        // A description of the sprite.
        sprites::Sprite sprite;
      };

      /// @brief - Describe a possible orientation for a graphic component
      /// (e.g. a healthbar, etc.).
      enum class Orientation {
        Horizontal,
        Vertical
      };

      /**
       * @brief - Used to draw the tile referenced by the input
       *          struct to the screen using the corresponding
       *          visual representation.
       * @param t - the description of the tile to draw.
       * @param cf - the coordinate frame to use to perform the
       *             conversion from tile position to pixels.
       */
      void
      drawSprite(const SpriteDesc& t, const CoordinateFrame& cf);

      /**
       * @brief - Used to draw a simple rect at the specified
       *          location. Note that we reuse the sprite desc
       *          but don't actually use the sprite.
       * @param t - the description of the tile to draw.
       * @param cf - the coordinate frame to use to perform the
       *             conversion from tile position to pixels.
       */
      void
      drawRect(const SpriteDesc& t,
               const CoordinateFrame& cf);

    private:

      /**
       * @brief - The game managed by this application.
       */
      GameShPtr m_game;

      /**
       * @brief - The management of the game state, which includes
       *          loading the saved games, handling game over and
       *          such things.
       */
      GameStateShPtr m_state;

      /**
       * @brief - Defines the list of menus available for
       *          this app.
       */
      std::vector<MenuShPtr> m_menus;

      /**
       * @brief - A description of the textures used to represent
       *          the elements of the game.
       */
      TexturePackShPtr m_packs;
  };

}

# include "App.hxx"

#endif    /* APP_HH */
