#include "SoftwareRasteriser.h"
#include "RenderObject.h"
#include "Mesh.h"
#include "Texture.h"

int main() {
	SoftwareRasteriser r(800,600);
	Matrix4 viewMatrix;
	float aspect = 800.0f / 600.0f;

	Matrix4 translate = Matrix4::Translation(Vector3(0.65f, -0.7f, 0));
	Matrix4 rotate = Matrix4::Rotation(160.0f, Vector3(0, 0, 1));
	Matrix4 scale = Matrix4::Scale(Vector3(0.25, 0.25, 1));

	Matrix4 starRotate = Matrix4::Rotation(180.0f, Vector3(0, 0, 1));
	Matrix4 starTrans = Matrix4::Translation(Vector3(-0.65f, 0.65f, 0));
	Matrix4 starTrans2 = Matrix4::Translation(Vector3(-0.65f, 0.55f, 0));
	Matrix4 pitTrans = Matrix4::Translation(Vector3(0.635f, -0.635f, 0));
	Matrix4 starScale = Matrix4::Scale(Vector3(0.25f, 0.25f, 0));
	Matrix4 pitScale = Matrix4::Scale(Vector3(0.08f, 0.08f, 0));

	Mesh* testTri = Mesh::GenerateTriangle();
	Mesh* starTri = Mesh::GenerateStarTriangle();
	Mesh* cockpit = Mesh::GenerateBlueTriangle();
	Mesh* testStars = Mesh::GeneratePoints();
	Mesh* a1 = Mesh::GenerateLine(Vector3(0.0f,0.0f,0), Vector3(0.5f, 0.5f, 0));

	RenderObject* o1 = new RenderObject();
	o1->mesh = testTri;
	o1->texture = Texture::TextureFromTGA("../brick.tga");
	o1->modelMatrix = translate * rotate * scale;

	RenderObject* o2 = new RenderObject();
	o2->mesh = testStars;

	RenderObject* o3 = new RenderObject();
	o3->mesh = a1;

	RenderObject* o4 = new RenderObject();
	o4->mesh = starTri;
	o4->modelMatrix = starTrans2 * starRotate * starScale;

	RenderObject* o5 = new RenderObject();
	o5->mesh = starTri;
	o5->modelMatrix = starTrans * starScale;

	RenderObject* o6 = new RenderObject();
	o6->mesh = cockpit;
	o6->modelMatrix = pitTrans * rotate * pitScale;

	while(r.UpdateWindow()) {
		if (Keyboard::KeyDown(KEY_RIGHT)) {
			viewMatrix = viewMatrix * Matrix4::Translation(Vector3(-0.001f, 0.0, 0));
		}
		if (Keyboard::KeyDown(KEY_LEFT)) {
			viewMatrix = viewMatrix * Matrix4::Translation(Vector3(0.001f, 0.0, 0));
		}
		r.ClearBuffers();
		o2->modelMatrix = viewMatrix;
		r.SetViewMatrix(viewMatrix);
		r.DrawObject(o2);
		r.DrawObject(o1);
		r.DrawObject(o6);
		r.DrawObject(o3);
		r.DrawObject(o4);
		r.DrawObject(o5);
		r.SwapBuffers();

		if (Mouse::ButtonDown(MOUSE_LEFT)) {
			std::cout << "Mouse is at position: " << Mouse::GetAbsolutePosition().x << " , " << Mouse::GetAbsolutePosition().y << std::endl;
		}
	}

	//Memory Management
	delete o1->mesh;
	delete o2->mesh;
	delete o3->mesh;
	delete o1;
	delete o2;
	delete o3;
	return 0;
}