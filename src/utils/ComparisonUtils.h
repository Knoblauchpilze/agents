#ifndef COMPARISONUTILS_H
#define COMPARISONUTILS_H

#include "Vector3d.h"
#include "Vector2d.h"

namespace utils
{
	namespace comparison
	{

		bool doubleEqual(const double& value1, const double& value2);

		bool nullVector(const utils::Vector3d& vector);

		bool nullVector(const utils::Vector2d& vector);

	}
}

#endif // COMPARISONUTILS_H
