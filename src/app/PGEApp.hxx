#ifndef    PGE_APP_HXX
# define   PGE_APP_HXX

# include "PGEApp.hh"

namespace pge {

  inline
  bool
  PGEApp::RenderDesc::visible(const utils::Point2i& p, float r) const noexcept {
    return cf.cellsViewport().visible(p, r);
  }

  inline
  bool
  PGEApp::RenderDesc::visible(const olc::vf2d& p, const olc::vf2d sz) const noexcept {
    return cf.cellsViewport().visible(p, sz);
  }

  inline
  bool
  PGEApp::OnUserDestroy() {
    cleanResources();
    cleanMenuResources();

    return true;
  }

  inline
  bool
  PGEApp::isFirstFrame() const noexcept {
    return m_first;
  }

  inline
  bool
  PGEApp::hasDebug() const noexcept {
    return m_debugOn;
  }

  inline
  bool
  PGEApp::hasUI() const noexcept {
    return m_uiOn;
  }

  inline
  void
  PGEApp::setLayerTint(const Layer& layer, const olc::Pixel& tint) {
    switch (layer) {
      case Layer::Draw:
        SetLayerTint(m_mLayer, tint);
        break;
      case Layer::DrawDecal:
        SetLayerTint(m_mDecalLayer, tint);
        break;
      case Layer::UI:
        SetLayerTint(m_uiLayer, tint);
        break;
      case Layer::Debug:
      default:
        SetLayerTint(m_dLayer, tint);
        break;
    }
  }

  inline
  void
  PGEApp::clearLayer() {
    // Clear the canvas with a neutral fully transparent color.
    SetPixelMode(olc::Pixel::ALPHA);
    Clear(olc::Pixel(255, 255, 255, alpha::Transparent));
    SetPixelMode(olc::Pixel::NORMAL);
  }

  inline
  void
  PGEApp::initialize(const olc::vi2d& dims, const olc::vi2d& pixRatio) {
    // Construct the window. Note that we use a pixel size
    // to screen size ratio of `1` (meaning that each pixel
    // of the viewport will be represented by a pixel on
    // the screen).
    olc::rcode c = Construct(dims.x, dims.y, pixRatio.x, pixRatio.y);

    if (c != olc::OK) {
      throw utils::CoreException(
        std::string("Could not build new frontiers application"),
        std::string("Initialization failed")
      );
    }
  }

}

#endif    /* PGE_APP_HXX */
