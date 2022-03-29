#ifndef    TOPVIEW_FRAME_HH
# define   TOPVIEW_FRAME_HH

# include "CoordinateFrame.hh"

namespace pge {

  class TopViewFrame: public CoordinateFrame {
    public:

      /**
       * @brief - Defines a new top view frame with the specified
       *          viewport and tile size.
       * @param cvp - the cells viewport. Defines how many cells
       *              are visible.
       * @param pvp - the pixels viewport, allowing to compute the
       *              size of a tile on scree.
       * @param tileSize - the initial size of a tile.
       */
      TopViewFrame(const Viewport& cvp,
                   const Viewport& pvp,
                   const olc::vi2d& tileSize);

      ~TopViewFrame() = default;

      /**
       * @brief - Implementation of the interface method to get
       *          the viewport in cells for this isometric frame.
       * @return - the viewport of this coordinate frame in cells.
       */
      Viewport
      cellsViewport() const noexcept override;

      /**
       * @brief - Implementation of the interface method that
       *          define the conversion from tile coords to
       *          pixels. We apply an isometric projection to
       *          compute the corresponding pixels position.
       * @param x - the cell coordinate along the `x` axis.
       * @param y - the cell coordinate along the `y` axis.
       * @param loc - the relative position of the tile when
       *              compared to the provided location.
       * @param radius - the radius of the element for which the
       *                 pixels position is computed. Allows to
       *                 adapt the relative position to the size
       *                 of the element.
       * @return - the coordinates in pixels of the tile defined
       *           by the input coords.
       */
      olc::vf2d
      tileCoordsToPixels(float x,
                         float y,
                         const RelativePosition& loc = RelativePosition::BottomRight,
                         float radius = 1.0f) const noexcept override;

      /**
       * @brief - Implementation of the interface method to
       *          perform the reverse operation.
       * @param pixels - the pixels coordinates to convert into
       *                 tile coords.
       * @param intraTile - used to provide the intra tile coords
       *                    if a non `null` value is provided. The
       *                    coordinates are expressed in the range
       *                    `[0; 1]` (as in a percentage).
       * @return - the corresponding tile coordinates.
       */
      olc::vi2d
      pixelCoordsToTiles(const olc::vi2d& pixels,
                         olc::vf2d* intraTile = nullptr) const noexcept override;
  };

}

#endif    /* TOPVIEW_FRAME_HH */
