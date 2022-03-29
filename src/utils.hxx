#ifndef    UTILS_HXX
# define   UTILS_HXX

# include "utils.hh"

template <typename CoordinateType>
inline
std::string
toString(const olc::v2d_generic<CoordinateType>& vec) noexcept {
  return std::string("[x: ") + std::to_string(vec.x) + ", y: " + std::to_string(vec.y) + "]";
}

template <typename CoordinateType>
inline
std::ostream&
operator<<(std::ostream& out, const olc::v2d_generic<CoordinateType>& vec) noexcept {
  out << toString(vec);
  return out;
}

template <typename CoordinateType>
inline
std::ostream&
operator<<(const olc::v2d_generic<CoordinateType>& vec, std::ostream& out) noexcept {
  return operator<<(out, vec);
}

#endif    /* UTILS_HXX */
