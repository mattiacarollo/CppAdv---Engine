#include "Forces.h"

namespace Pns
{
	Vector3 Forces::SphereInertia(float mass, float radius)
	{
		//inertia moment of full sphere (I = 2/5 * (m*r^2))
		float inertia = 2 * mass*radius*radius / 5;
		return Vector3(inertia, inertia, inertia);
	}

	Vector3 Forces::CubeInertia(float mass, float width, float height, float depth)
	{
		float x = mass*(height*height + depth*depth) / 12;
		float y = mass*(width*width + depth*depth) / 12;
		float z = mass*(height*height + width*width) / 12;

		return Vector3(x, y, z);
	}
}