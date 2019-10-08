#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include "Body.h"
#include "Vector.h"
#include "VMath.h"
#include "MMath.h"
#include "Matrix2.h"

using namespace MATH;

class Simplex
{
private:
	std::vector<Vec3> vertices;
	/*static Vec3 Origin, contactA, contactB, closestA, closestB, scaledClosestA, scaledClosestB, contactNormal;*/
public:
	static bool GJKCollision(const Body& b1, const Body& b2);
	static void HandleCollision(Body& b1, Body& b2);
	static void contactNP(const Body& b1, const Body& b2);
};

#endif