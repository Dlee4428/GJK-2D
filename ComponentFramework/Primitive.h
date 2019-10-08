#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Model.h"
#include "Shader.h"
#include "ObjLoader.h"
#include "Simplex.h"
#include "Mesh.h"

namespace GAME {
	class Primitive : public Model{
	private:

		Shader *shader;
		GLuint vbo;
		GLuint vao;
		GLint verticiesID;
		GLint normalsID;
		GLint uvCoordsID;

		GLint projectionMatrixID;
		GLint modelViewMatrixID;
		GLint normalMatrixID;

	public:
		Primitive(const Primitive&) = delete;
		Primitive(Primitive&&) = delete;
		Primitive& operator = (const Primitive&) = delete;
		Primitive& operator = (Primitive&&) = delete;

		Primitive(GLenum drawMode_, std::vector<Vec3> &vertices_, 
			std::vector<Vec3> &normals, std::vector<Vec2> &uvs_);
		Primitive(std::string filepath_);

		virtual ~Primitive();
		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render(const Matrix4& projectionMatrix, const Matrix4& viewMatrix,
			const Matrix3& normalMatrix)const;
	};
}

#endif // !PRIMITIVE_H