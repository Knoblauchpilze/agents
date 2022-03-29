#ifndef    TEXTURE_PACK_HH
# define   TEXTURE_PACK_HH

# include <memory>
# include <core_utils/CoreObject.hh>
# include "olcEngine.hh"

namespace pge {
  namespace sprites {

    /// @brief Convenience structure allowing to represent the sprites
    /// inside a file. In addition to the name of the file the layout
    /// of the sprites is also specified so as to be able to identify
    /// tiles in a correct way.
    struct Pack {
      // The `file` defines the path to the file defining the
      // textures. It should be a valid path.
      std::string file;

      // The `sSize` defines the size in pixels of a single
      // texture in the file. This allows to interpret the
      // sprites correctly.
      olc::vi2d sSize;

      // The `layout` defines the dimensions of the pack in
      // sprites. It allows to interpret coordinates so that
      // we can 'locate' a sprite in the pack.
      olc::vi2d layout;
    };

    /// @brief - Convenience structure regrouping needed props to draw
    /// a sprite.
    struct Sprite {
      // The `pack` defines the identifier of the pack from
      // which the sprite should be picked.
      unsigned pack;

      // The `sprite` defines an identifier for the sprite. The
      // position of the sprite in the resource pack will be
      // computed from this identifier.
      olc::vi2d sprite;

      // The `id` allows to select a variant for the sprite. By
      // default this value is `0` meaning the principal display
      // for the sprite.
      int id;

      // The `tint` defines a color to apply to tint the sprite
      // as a whole. Can also be used to provide some alpha.
      olc::Pixel tint;
    };

  }

  class TexturePack: public utils::CoreObject {
    public:

      /**
       * @brief - Generate a new texture pack with no resources
       *          registered yet.
       */
      TexturePack();

      /**
       * @brief - Detroys the texture pack and release the sprites
       *          and resources attached to it.
       */
      ~TexturePack();

      /**
       * @brief - Performs the registration of the input pack
       *          and return the corresponding pack identifier
       *          so that the caller can refer to this pack
       *          afterwards.
       * @param pack - the pack to load.
       * @return - an identifier allowing to reference this
       *           pack for later use.
       */
      unsigned
      registerPack(const sprites::Pack& pack);

      /**
       * @brief - Used to perform the drawing of the sprite as
       *          defined by the input argument using the engine.
       *          The sprite will be associated internally with
       *          the corresponding visual.
       * @param pge - the engine to use to perform the rendering.
       * @param s - the sprite to draw.
       * @param p - the position where the sprite will be drawn.
       * @param scale - defines a scaling factor to apply to the
       *                sprite.
       */
      void
      draw(olc::PixelGameEngine* pge,
           const sprites::Sprite& s,
           const olc::vf2d& p,
           const olc::vf2d& scale = olc::vf2d(1.0f, 1.0f)) const;

      /**
       * @brief - Variant of the above method to accept a scale
       *          expressed as a single float: the scale will be
       *          applied in both directions.
       * @param pge - the engine to use to perform the rendering.
       * @param s - the sprite to draw.
       * @param p - the position where the sprite will be drawn.
       * @param scale - defines a scaling factor to apply to the
       *                sprite. Both directions will be scaled
       *                uniformly.
       */
      void
      draw(olc::PixelGameEngine* pge,
           const sprites::Sprite& s,
           const olc::vf2d& p,
           float scale = 1.0f) const;

    private:

      /// @brief - Convenience structure referencing the needed
      /// information to describe a texture pack. Unlike the
      /// public interface this contains the values used internally
      /// to define the pack.
      struct Pack {
        // The `sSize` defines the size of an individual sprite
        // in the pack.
        olc::vi2d sSize;

        // The `layout` defines the repartition of the sprites
        // in the pack.
        olc::vi2d layout;

        // The `res` defines the raw data to the whole sprites
        // registered for this pack. Individual parts describe
        // each sprite.
        olc::Decal* res;
      };

      /**
       * @brief - Used to convert from sprite coordinates to the
       *          corresponding pixels coordinates. This method
       *          should mostly be used to locate a sprite in a
       *          resource pack. The internal layout allows to
       *          know in advance how sprites are laid out in
       *          the pack and thus find the correct location
       *          based on the coordinates of the sprite and
       *          its identifier.
       *          In order to find the correct sprite, both some
       *          coordinates and a variation id should be set
       *          to fix a single element in the sprites.
       * @param pack - the texture pack to which the coordinates
       *               correspond to.
       * @param coord - the coordinates of the sprite to convert
       *                to pixels in the resource pack.
       * @param id - the index of the variation of the sprite
       *             to use: default is `0`.
       * @return - a vector representing the pixels coordinates
       *           for the input sprite coords.
       */
      olc::vi2d
      spriteCoords(const Pack& pack,
                   const olc::vi2d& coord,
                   int id = 0) const;

    private:

      /**
       * @brief - The list of packs registered so far for
       *          this object. Note that the identifier of
       *          each pack corresponds to the position of
       *          the pack in this vector.
       */
      std::vector<Pack> m_packs;
  };

  using TexturePackShPtr = std::shared_ptr<TexturePack>;
}

# include "TexturePack.hxx"

#endif    /* TEXTURE_PACK_HH */
