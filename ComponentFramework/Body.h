#ifndef BODY_H
#define BODY_H

#include "Vector.h"
#include <iostream>
#include <vector>
#include "VMath.h"

namespace MATH {
	class Body
	{
	private:
		std::vector<Vec3>shape;
		Vec3 pos, vel, accel, gravity;
		float mass, rotInertia;
		float angle, angVel, angAccel;
	public:
		std::vector<Vec3>vertices;
	public:
		Body(float mass_, float rotInertia_);
		~Body();
		Body() : gravity(0.0f, -9.8f, 0.0f) { };

		Vec3 getPos() const;
		Vec3 getVel() const;
		Vec3 getAccel() const;
		Vec3 getWorldForce() const;

		float getAngVel() const;
		float getAngAccel() const;

		void SetPos(Vec3 pos_);
		void SetVel(Vec3 vel_);
		void SetAngVel(float angularVelocity_);
		void SetShape(std::vector<Vec3> vertices_);

		std::vector<Vec3> getBodies() const;
		void addPoints(Vec3 v);
		void Update(const float deltaTime);
	};
}
#endif