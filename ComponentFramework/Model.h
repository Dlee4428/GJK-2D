#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "MMath.h"
#include "Mesh.h"
#include "Body.h"


using namespace MATH;

class Scene;

namespace GAME {

class Model {
protected:
	Sphere bounding;
	Matrix4 modelMatrix;
	Scene* parentScene;
	std::vector<Mesh*> meshes;
	Body* bodies;
public:
	inline void SetPos(const Vec3& pos_) {
		if (bodies) {
			bodies->SetPos(pos_);
		}
	}

	inline void SetVel(const Vec3& vel_) {
		if (bodies) {
			bodies->SetVel(vel_);
		}
	}

	inline Body* GetBody() {
		return bodies;
	}

	virtual ~Model() {
		if (bodies) {
			delete bodies;
		}
		bodies = nullptr;
	}

	Model(const Model&) = delete;
	Model(Model&&) = delete;
	Model& operator = (const Model&) = delete;
	Model& operator = (Model&&) = delete;

	Model() {};

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix)const = 0;

	virtual void Update(const float deltaTime){
		if (bodies) {
			bodies->Update(deltaTime);
		}
	}
};




} /// end of namespace

#endif