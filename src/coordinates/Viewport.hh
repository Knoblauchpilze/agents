#ifndef    VIEWPORT_HH
# define   VIEWPORT_HH

# include <maths_utils/Point2.hh>
# include "olcEngine.hh"

namespace pge {

  /// @brief - Defines a viewport from its top left
  /// corner and the associated dimensions.
  class Viewport {
    public:

      /**
       * @brief - Create a new viewport with the specified
       *          position and dimensions.
       * @param tl - the top left corner of the viewport.
       * @param dims - the dimensions of the viewport.
       */
      Viewport(const olc::vf2d& tl,
               const olc::vf2d& dims) noexcept;

      /**
       * @brief - Return the top left corner of the viewport.
       * @return - the top left corner.
       */
      olc::vf2d&
      topLeft() noexcept;

      /**
       * @brief - Return the top left corner of the viewport.
       * @return - the top left corner.
       */
      const olc::vf2d&
      topLeft() const noexcept;

      /**
       * @brief - Return the dimensions of the viewport.
       * @return - the dimensions of the viewport.
       */
      olc::vf2d&
      dims() noexcept;

      /**
       * @brief - Return the dimensions of the viewport.
       * @return - the dimensions of the viewport.
       */
      const olc::vf2d&
      dims() const noexcept;

      /**
       * @brief - Whether or not a position with the specified
       *          radius is at least partially visible based on
       *          the viewport dimensions.
       * @param p - the position to check.
       * @param radius - the radius of the element.
       * @return - `true` if the element is at least partially
       *            visible.
       */
      bool
      visible(const utils::Point2i& p, float radius = 1.0f) const noexcept;

      /**
       * @brief - Similar method to the above but handles position
       *          as a floating point position and the radius as a
       *          rectangular-ish shape.
       * @param p - the position to check.
       * @param sz - the dimensions of the element.
       * @return - `true` if the element is at least partially
       *            visible.
       */
      bool
      visible(const olc::vf2d& p, const olc::vf2d& sz = olc::vf2d(1.0f, 1.0f)) const noexcept;

    private:

      /**
       * @brief - Defines the origin of the viewport: it
       *          represents the top left corner of the
       *          view window.
       */
      olc::vf2d m_tl;

      /**
       * @brief - Represents the dimensions of the view
       *          window along each axis.
       */
      olc::vf2d m_dims;

      /**
       * @brief - Whether the cached version of the min
       *          and max bounds for the viewport need
       *          to be recomputed.
       */
      mutable bool m_dirty;

      /**
       * @brief - Cached version of the maximum point of
       *          the viewport.
       */
      mutable olc::vf2d m_max;
  };

}

#endif    /* VIEWPORT_HH */
