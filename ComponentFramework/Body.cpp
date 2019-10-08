#include "Body.h"

using namespace MATH;

Body::Body(float mass_, float rotInertia_)
{
	mass = mass_;
	rotInertia = rotInertia_;
	pos = Vec3();
	vel = Vec3();
	accel = Vec3();
	angle = 0.0f;
	angVel = 0.0f;
	angAccel = 0.0f;
}

Body::~Body() {
	if (shape.size() > 0) {
		shape.clear();
		shape.shrink_to_fit();
	}
}

Vec3 Body::getPos() const {
	return pos;
}

Vec3 Body::getVel() const {
	return vel;
}

Vec3 Body::getAccel() const {
	return accel;
}

float Body::getAngVel() const {
	return angVel;
}

float Body::getAngAccel() const {
	return angAccel;
}

void Body::addPoints(Vec3 v) {
	vertices.push_back(v);
}

std::vector<Vec3> Body::getBodies() const {
	return vertices;
}

void Body::SetPos(Vec3 pos_) {
	pos = pos_;
}
void Body::SetVel(Vec3 vel_) {
	vel = vel_;
}
void Body::SetAngVel(float angularVelocity_) {
	angVel = angularVelocity_;
}
void Body::SetShape(std::vector<Vec3> shape_) {
	vertices = shape_;
}



void Body::Update(const float deltaTime) {

	pos += vel * deltaTime + 0.5f * gravity * deltaTime * deltaTime;
	vel += gravity * deltaTime;
}