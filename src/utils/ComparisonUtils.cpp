
#include <limits>
#include <cmath>
#include "ComparisonUtils.h"

namespace utils
{

	namespace comparison
	{

		bool doubleEqual(const double& value1, const double& value2)
		{
			double epsilon(5.0 * std::numeric_limits<double>::epsilon());
			return (std::fabs(value1 - value2) < epsilon);
		}

		bool nullVector(const utils::Vector3d& vector)
		{
			return (doubleEqual(vector.x(), 0.0) && doubleEqual(vector.y(), 0.0) && doubleEqual(vector.z(), 0.0));
		}

		bool nullVector(const utils::Vector2d& vector)
		{
			return (doubleEqual(vector.x(), 0.0) && doubleEqual(vector.y(), 0.0));
		}

	}
}
