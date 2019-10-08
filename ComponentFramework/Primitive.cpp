#include "Primitive.h"

using namespace GAME;

Primitive::Primitive(GLenum drawMode_, std::vector<Vec3> &vertices_,
	std::vector<Vec3> &normals, std::vector<Vec2> &uvs_){

	meshes.push_back(new Mesh(drawMode_, vertices_, normals, uvs_));
	OnCreate();
}

Primitive::Primitive(std::string filepath_) {
	ObjLoader obj(filepath_.c_str());
	//GL LOOP
	meshes.push_back(new Mesh(GL_LINE_LOOP, obj.vertices, obj.normals, obj.uvCoords));
	OnCreate();
}


Primitive::~Primitive(){
	OnDestroy();
}

bool Primitive::OnCreate() {
	shader = new Shader("baseVert.glsl", "baseFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");

	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");

	bodies = new Body(1.0f, 0.0f);
	for (size_t i = 0; i < meshes.size(); i++) {
		for (size_t j = 0; j < meshes[i]->vertices.size(); j++) {
			bodies->addPoints(meshes[i]->vertices[j]);
		}
	}
	return true;
}

void Primitive::OnDestroy() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	if (shader) {
		delete shader;
	}
	shader = nullptr;
	for (Mesh* m : meshes) {
		if (m) {
			delete m;
		}
		m = nullptr;
	}
}

void Primitive::Update(const float deltaTime) {
	Model::Update(deltaTime);
	modelMatrix = MMath::translate(bodies->getPos().x, bodies->getPos().y, bodies->getPos().z);
	//modelMatrix = MMath::scale(0.1f, 0.1f, 0.1f);
}

void Primitive::Render(const Matrix4& projectionMatrix, const Matrix4& viewMatrix, const Matrix3& normalMatrix)const {
	glUseProgram(shader->getProgram()); //Tell OpenGL to use currentShader program
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, viewMatrix *  modelMatrix);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	for (Mesh* mesh : meshes) {
		mesh->Render();
	}
	glEnableVertexAttribArray(0); // Disable the VAO
}