#ifndef    UTILS_HH
# define   UTILS_HH

# include <string>
# include "olcEngine.hh"

template <typename CoordinateType>
std::string
toString(const olc::v2d_generic<CoordinateType>& vec) noexcept;

template <typename CoordinateType>
std::ostream&
operator<<(std::ostream& out, const olc::v2d_generic<CoordinateType>& vec) noexcept;

template <typename CoordinateType>
std::ostream&
operator<<(const olc::v2d_generic<CoordinateType>& vec, std::ostream& out) noexcept;

# include "utils.hxx"

#endif    /* UTILS_HH */
