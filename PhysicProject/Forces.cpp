#include "Forces.h"

namespace Pns
{
	Vector3 Forces::SphereInertia(float mass, float radius)
	{
		//inertia moment of full sphere (I = 2/5 * (m*r^2))
		float inertia = 0.4f * mass*radius*radius;
		return Vector3(inertia, inertia, inertia);
	}

	Vector3 Forces::CubeInertia(float mass, float width, float height, float depth)
	//Vector3 Forces::CubeInertia(float mass, float width, float height)
	{
		float x = mass*(height*height + depth*depth) / 12.0f;
		float y = mass*(width*width + depth*depth) / 12.0f;
		float z = mass*(height*height + width*width) / 12.0f;

		//float x = (((4.0f*width*width) + (4.0f*height*height))*mass / 12.0f);
		//float y = (((4.0f*width*width) + (4.0f*height*height))*mass / 12.0f);
		//float z = (((4.0f*width*width) + (4.0f*height*height))*mass / 12.0f);

		return Vector3(x, y, z);
	}
}