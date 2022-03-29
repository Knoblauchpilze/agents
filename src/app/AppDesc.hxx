#ifndef    APP_DESC_HXX
# define   APP_DESC_HXX

# include "AppDesc.hh"

namespace pge {

  inline
  AppDesc
  newDesc(const olc::vi2d& dims,
          CoordinateFrameShPtr cf,
          const std::string& name) noexcept
  {
    AppDesc ad;

    ad.dims = dims;
    ad.pixRatio = olc::vi2d(1, 1);

    ad.name = name;

    ad.frame = cf;

    ad.fixedFrame = false;

    return ad;
  }

}

#endif    /* APP_DESC_HXX */
