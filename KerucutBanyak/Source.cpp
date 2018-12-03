#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

typedef struct {
	float x;
	float y;
} Point2D_t;
typedef struct {
	int x;
	int y;
} Point2D_i;
typedef struct {
	int x, y, z;
} Point3D_t;
typedef struct {
	float v[3];
} Vector3D_t;
typedef struct {
	float m[3][3];
} matrix3D_t;
typedef struct {
	int m[3][3];
} matrix3D_i;
typedef struct {
	float r;
	float g;
	float b;
} color_t;
typedef struct {
	int numofVertices;
	long int pnt[32];
} face_t;
typedef struct {
	int numofVertices;
	Point3D_t pnt[100];
	int numofFaces;
	face_t fc[32];
	color_t col;
} object3D_t;

double sudutRotasi = (float)(0);
object3D_t Kubus, ShapeKerucut, ShapeKerucut1, ShapeKerucut2, ShapeKerucut3, ShapeKerucut4, ShapeKerucut5;
void createOFF();

matrix3D_t create_identity() {
	matrix3D_t rotate;
	rotate.m[0][0] = 0.0;
	rotate.m[0][1] = 0.0;
	rotate.m[0][2] = 0.0;

	rotate.m[1][0] = 0.0;
	rotate.m[1][1] = 0.0;
	rotate.m[1][2] = 0.0;

	rotate.m[2][0] = 0.0;
	rotate.m[2][1] = 0.0;
	rotate.m[2][1] = 0.0;
	return rotate;
}

matrix3D_t rotasi_x(float teta) {
	matrix3D_t rotate = create_identity();
	rotate.m[0][0] = 1.0;
	rotate.m[0][1] = 0.0;
	rotate.m[0][2] = 0.0;

	rotate.m[1][0] = 0.0;
	rotate.m[1][1] = cos(teta / 57.3);
	rotate.m[1][2] = -sin(teta / 57.3);

	rotate.m[2][0] = 0.0;
	rotate.m[2][1] = sin(teta / 57.3);
	rotate.m[2][2] = cos(teta / 57.3);

	return rotate;
}

matrix3D_t rotasi_y(float teta) {
	matrix3D_t rotate = create_identity();
	rotate.m[0][0] = cos(teta / 57.3);
	rotate.m[0][1] = 0.0;
	rotate.m[0][2] = sin(teta / 57.3);

	rotate.m[1][0] = 0.0;
	rotate.m[1][1] = 1.0;
	rotate.m[1][2] = 0.0;

	rotate.m[2][0] = -sin(teta / 57.3);
	rotate.m[2][1] = 0.0;
	rotate.m[2][2] = cos(teta / 57.3);

	return rotate;
}

matrix3D_t rotasi_z(float teta) {
	matrix3D_t rotate = create_identity();
	rotate.m[0][0] = cos(teta / 57.3);
	rotate.m[0][1] = -sin(teta / 57.3);
	rotate.m[0][2] = 0.0;

	rotate.m[1][0] = sin(teta / 57.3);
	rotate.m[1][1] = cos(teta / 57.3);
	rotate.m[1][2] = 0.0;

	rotate.m[2][0] = 0.0;
	rotate.m[2][1] = 0.0;
	rotate.m[2][2] = 1.0;

	return rotate;
}

Vector3D_t operator +(Vector3D_t a, Vector3D_t b) {
	Vector3D_t c;
	for (int i = 0; i < 3; i++) {
		c.v[i] = a.v[i] + b.v[i];
	} return c;
}

Vector3D_t operator -(Vector3D_t a, Vector3D_t b) {
	Vector3D_t c;
	for (int i = 0; i < 3; i++) {
		c.v[i] = a.v[i] - b.v[i];
	} return c;
}

Vector3D_t operator *(matrix3D_t a, Vector3D_t b) {
	Vector3D_t c; for (int i = 0; i < 3; i++) {
		c.v[i] = 0; for (int j = 0; j < 3; j++) {
			c.v[i] += a.m[i][j] * b.v[j];
		}
	} return c;
}

Vector3D_t operator ^(Vector3D_t a, Vector3D_t b) { 
	Vector3D_t c;  
	c.v[0] = a.v[1] * b.v[2] - a.v[2] * b.v[1];  
	c.v[1] = a.v[2] * b.v[0] - a.v[0] * b.v[2];  
	c.v[2] = a.v[0] * b.v[1] - a.v[1] * b.v[0];        
	return c; 
}

void create3DObject(object3D_t object) {
	glColor3f(1.0,0.0,1.0);	
	for (int i = 0; i < object.numofFaces; i++) {
		glBegin(GL_LINE_STRIP);		
		for (int j = 0; j < object.fc[i].numofVertices; j++) {
			int p = object.fc[i].pnt[j];
			float x = object.pnt[p].x;
			float y = object.pnt[p].y;
			glVertex3f(x, y, 0.0);
		}
		glEnd();
	}	
}

void create_kerucut() {
	glClear(GL_COLOR_BUFFER_BIT);
	ShapeKerucut.col.r = 0.3;
	ShapeKerucut.col.g = 1.0;
	ShapeKerucut.col.b = 0.5;
	ShapeKerucut.numofVertices = 14;
	ShapeKerucut.numofFaces = 24;
	int sudut = 0, r = 100;
	ShapeKerucut.pnt[0].x = 0;
	ShapeKerucut.pnt[0].y = -100;
	ShapeKerucut.pnt[0].z = 0;

	ShapeKerucut.pnt[13].x = 0;
	ShapeKerucut.pnt[13].y = -300;
	ShapeKerucut.pnt[13].z = 0;
	for (int i = 1; i <= 12; i++) {
		float teta = (double)(sudut / 57.3);
		ShapeKerucut.pnt[i].x = (float)(r*cos(teta));
		ShapeKerucut.pnt[i].y = -100;
		ShapeKerucut.pnt[i].z = (float)(r*sin(teta));
		sudut += 30;
	}
	for (int i = 0; i <= 23; i++) {
		ShapeKerucut.fc[i].numofVertices = 3;
		if (i < 12) {
			if (i != 11) {
				ShapeKerucut.fc[i].pnt[0] = 0;
				ShapeKerucut.fc[i].pnt[1] = i + 1;
				ShapeKerucut.fc[i].pnt[2] = i + 2;
			}
			else {
				ShapeKerucut.fc[i].pnt[0] = 0;
				ShapeKerucut.fc[i].pnt[1] = i + 1;
				ShapeKerucut.fc[i].pnt[2] = 1;
			}
		}
		else {
			if (i != 23) {
				ShapeKerucut.fc[i].pnt[0] = 13;
				ShapeKerucut.fc[i].pnt[1] = i - 11;
				ShapeKerucut.fc[i].pnt[2] = i - 10;
			}
			else {
				ShapeKerucut.fc[i].pnt[0] = 13;
				ShapeKerucut.fc[i].pnt[1] = i - 11;
				ShapeKerucut.fc[i].pnt[2] = 1;
			}
		}
	}
	matrix3D_t matrix_X = rotasi_x(20.0);
	matrix3D_t matrix_Y = rotasi_y(sudutRotasi);
	matrix3D_t matrix_Z = rotasi_z(0);
	for (int i = 0; i < ShapeKerucut.numofVertices; i++) {
		Vector3D_t p;
		p.v[0] = ShapeKerucut.pnt[i].x;
		p.v[1] = ShapeKerucut.pnt[i].y;
		p.v[2] = ShapeKerucut.pnt[i].z;
		p = (matrix_Y)*(p);
		p = (matrix_X)*(p);
		p = (matrix_Z)*(p);
		ShapeKerucut.pnt[i].x = p.v[0];
		ShapeKerucut.pnt[i].y = p.v[1];
		ShapeKerucut.pnt[i].z = p.v[2];
	}
	create3DObject(ShapeKerucut);

	ShapeKerucut1.col.r = 0.2;
	ShapeKerucut1.col.g = 0.5;
	ShapeKerucut1.col.b = 0.3;
	ShapeKerucut1.numofVertices = 14;
	ShapeKerucut1.numofFaces = 24;
	ShapeKerucut1.pnt[0].x = 0;
	ShapeKerucut1.pnt[0].y = 100;
	ShapeKerucut1.pnt[0].z = 0;

	ShapeKerucut1.pnt[13].x = 0;
	ShapeKerucut1.pnt[13].y = 300;
	ShapeKerucut1.pnt[13].z = 0;
	for (int i = 1; i <= 12; i++) {
		float teta = (double)(sudut / 57.3);
		ShapeKerucut1.pnt[i].x = (float)(r*cos(teta));
		ShapeKerucut1.pnt[i].y = 100;
		ShapeKerucut1.pnt[i].z = (float)(r*sin(teta));
		sudut += 30;
	}
	for (int i = 0; i <= 23; i++) {
		ShapeKerucut1.fc[i].numofVertices = 3;
		if (i < 12) {
			if (i != 11) {
				ShapeKerucut1.fc[i].pnt[0] = 0;
				ShapeKerucut1.fc[i].pnt[1] = i + 1;
				ShapeKerucut1.fc[i].pnt[2] = i + 2;
			}
			else {
				ShapeKerucut1.fc[i].pnt[0] = 0;
				ShapeKerucut1.fc[i].pnt[1] = i + 1;
				ShapeKerucut1.fc[i].pnt[2] = 1;
			}
		}
		else {
			if (i != 23) {
				ShapeKerucut1.fc[i].pnt[0] = 13;
				ShapeKerucut1.fc[i].pnt[1] = i - 11;
				ShapeKerucut1.fc[i].pnt[2] = i - 10;
			}
			else {
				ShapeKerucut1.fc[i].pnt[0] = 13;
				ShapeKerucut1.fc[i].pnt[1] = i - 11;
				ShapeKerucut1.fc[i].pnt[2] = 1;
			}
		}
	}
	for (int i = 0; i < ShapeKerucut1.numofVertices; i++) {
		Vector3D_t p1;
		p1.v[0] = ShapeKerucut1.pnt[i].x;
		p1.v[1] = ShapeKerucut1.pnt[i].y;
		p1.v[2] = ShapeKerucut1.pnt[i].z;
		p1 = (matrix_Y)*(p1);
		p1 = (matrix_X)*(p1);
		p1 = (matrix_Z)*(p1);
		ShapeKerucut1.pnt[i].x = p1.v[0];
		ShapeKerucut1.pnt[i].y = p1.v[1];
		ShapeKerucut1.pnt[i].z = p1.v[2];
	}
	create3DObject(ShapeKerucut1);

	ShapeKerucut2.col.r = 0.3;
	ShapeKerucut2.col.g = 0.7;
	ShapeKerucut2.col.b = 1.0;
	ShapeKerucut2.numofVertices = 14;
	ShapeKerucut2.numofFaces = 24;
	ShapeKerucut2.pnt[0].x = 100;
	ShapeKerucut2.pnt[0].y = 0;
	ShapeKerucut2.pnt[0].z = 0;

	ShapeKerucut2.pnt[13].x = 300;
	ShapeKerucut2.pnt[13].y = 0;
	ShapeKerucut2.pnt[13].z = 0;
	for (int i = 1; i <= 12; i++) {
		float teta = (double)(sudut / 57.3);
		ShapeKerucut2.pnt[i].x = 100;
		ShapeKerucut2.pnt[i].y = (float)(r*cos(teta));
		ShapeKerucut2.pnt[i].z = (float)(r*sin(teta));
		sudut += 30;
	}
	for (int i = 0; i <= 23; i++) {
		ShapeKerucut2.fc[i].numofVertices = 3;
		if (i < 12) {
			if (i != 11) {
				ShapeKerucut2.fc[i].pnt[0] = 0;
				ShapeKerucut2.fc[i].pnt[1] = i + 1;
				ShapeKerucut2.fc[i].pnt[2] = i + 2;
			}
			else {
				ShapeKerucut2.fc[i].pnt[0] = 0;
				ShapeKerucut2.fc[i].pnt[1] = i + 1;
				ShapeKerucut2.fc[i].pnt[2] = 1;
			}
		}
		else {
			if (i != 23) {
				ShapeKerucut2.fc[i].pnt[0] = 13;
				ShapeKerucut2.fc[i].pnt[1] = i - 11;
				ShapeKerucut2.fc[i].pnt[2] = i - 10;
			}
			else {
				ShapeKerucut2.fc[i].pnt[0] = 13;
				ShapeKerucut2.fc[i].pnt[1] = i - 11;
				ShapeKerucut2.fc[i].pnt[2] = 1;
			}
		}
	}
	for (int i = 0; i < ShapeKerucut2.numofVertices; i++) {
		Vector3D_t p1;
		p1.v[0] = ShapeKerucut2.pnt[i].x;
		p1.v[1] = ShapeKerucut2.pnt[i].y;
		p1.v[2] = ShapeKerucut2.pnt[i].z;
		p1 = (matrix_Y)*(p1);
		p1 = (matrix_X)*(p1);
		p1 = (matrix_Z)*(p1);
		ShapeKerucut2.pnt[i].x = p1.v[0];
		ShapeKerucut2.pnt[i].y = p1.v[1];
		ShapeKerucut2.pnt[i].z = p1.v[2];
	}
	create3DObject(ShapeKerucut2);

	ShapeKerucut3.col.r = 1.0;
	ShapeKerucut3.col.g = 1.0;
	ShapeKerucut3.col.b = 0.2;
	ShapeKerucut3.numofVertices = 14;
	ShapeKerucut3.numofFaces = 24;
	ShapeKerucut3.pnt[0].x = -100;
	ShapeKerucut3.pnt[0].y = 0;
	ShapeKerucut3.pnt[0].z = 0;

	ShapeKerucut3.pnt[13].x = -300;
	ShapeKerucut3.pnt[13].y = 0;
	ShapeKerucut3.pnt[13].z = 0;
	for (int i = 1; i <= 12; i++) {
		float teta = (double)(sudut / 57.3);
		ShapeKerucut3.pnt[i].x = -100;
		ShapeKerucut3.pnt[i].y = (float)(r*cos(teta));
		ShapeKerucut3.pnt[i].z = (float)(r*sin(teta));
		sudut += 30;
	}
	for (int i = 0; i <= 23; i++) {
		ShapeKerucut3.fc[i].numofVertices = 3;
		if (i < 12) {
			if (i != 11) {
				ShapeKerucut3.fc[i].pnt[0] = 0;
				ShapeKerucut3.fc[i].pnt[1] = i + 1;
				ShapeKerucut3.fc[i].pnt[2] = i + 2;
			}
			else {
				ShapeKerucut3.fc[i].pnt[0] = 0;
				ShapeKerucut3.fc[i].pnt[1] = i + 1;
				ShapeKerucut3.fc[i].pnt[2] = 1;
			}
		}
		else {
			if (i != 23) {
				ShapeKerucut3.fc[i].pnt[0] = 13;
				ShapeKerucut3.fc[i].pnt[1] = i - 11;
				ShapeKerucut3.fc[i].pnt[2] = i - 10;
			}
			else {
				ShapeKerucut3.fc[i].pnt[0] = 13;
				ShapeKerucut3.fc[i].pnt[1] = i - 11;
				ShapeKerucut3.fc[i].pnt[2] = 1;
			}
		}
	}
	for (int i = 0; i < ShapeKerucut3.numofVertices; i++) {
		Vector3D_t p1;
		p1.v[0] = ShapeKerucut3.pnt[i].x;
		p1.v[1] = ShapeKerucut3.pnt[i].y;
		p1.v[2] = ShapeKerucut3.pnt[i].z;
		p1 = (matrix_Y)*(p1);
		p1 = (matrix_X)*(p1);
		p1 = (matrix_Z)*(p1);
		ShapeKerucut3.pnt[i].x = p1.v[0];
		ShapeKerucut3.pnt[i].y = p1.v[1];
		ShapeKerucut3.pnt[i].z = p1.v[2];
	}
	create3DObject(ShapeKerucut3);

	ShapeKerucut4.col.r = 0.8;
	ShapeKerucut4.col.g = 1.0;
	ShapeKerucut4.col.b = 0.5;
	ShapeKerucut4.numofVertices = 14;
	ShapeKerucut4.numofFaces = 24;
	ShapeKerucut4.pnt[0].x = 0;
	ShapeKerucut4.pnt[0].y = 0;
	ShapeKerucut4.pnt[0].z = -100;

	ShapeKerucut4.pnt[13].x = 0;
	ShapeKerucut4.pnt[13].y = 0;
	ShapeKerucut4.pnt[13].z = -300;
	for (int i = 1; i <= 12; i++) {
		float teta = (double)(sudut / 57.3);
		ShapeKerucut4.pnt[i].x = (float)(r*sin(teta));
		ShapeKerucut4.pnt[i].y = (float)(r*cos(teta));
		ShapeKerucut4.pnt[i].z = -100;
		sudut += 30;
	}
	for (int i = 0; i <= 23; i++) {
		ShapeKerucut4.fc[i].numofVertices = 3;
		if (i < 12) {
			if (i != 11) {
				ShapeKerucut4.fc[i].pnt[0] = 0;
				ShapeKerucut4.fc[i].pnt[1] = i + 1;
				ShapeKerucut4.fc[i].pnt[2] = i + 2;
			}
			else {
				ShapeKerucut4.fc[i].pnt[0] = 0;
				ShapeKerucut4.fc[i].pnt[1] = i + 1;
				ShapeKerucut4.fc[i].pnt[2] = 1;
			}
		}
		else {
			if (i != 23) {
				ShapeKerucut4.fc[i].pnt[0] = 13;
				ShapeKerucut4.fc[i].pnt[1] = i - 11;
				ShapeKerucut4.fc[i].pnt[2] = i - 10;
			}
			else {
				ShapeKerucut4.fc[i].pnt[0] = 13;
				ShapeKerucut4.fc[i].pnt[1] = i - 11;
				ShapeKerucut4.fc[i].pnt[2] = 1;
			}
		}
	}
	for (int i = 0; i < ShapeKerucut4.numofVertices; i++) {
		Vector3D_t p1;
		p1.v[0] = ShapeKerucut4.pnt[i].x;
		p1.v[1] = ShapeKerucut4.pnt[i].y;
		p1.v[2] = ShapeKerucut4.pnt[i].z;
		p1 = (matrix_Y)*(p1);
		p1 = (matrix_X)*(p1);
		p1 = (matrix_Z)*(p1);
		ShapeKerucut4.pnt[i].x = p1.v[0];
		ShapeKerucut4.pnt[i].y = p1.v[1];
		ShapeKerucut4.pnt[i].z = p1.v[2];
	}
	create3DObject(ShapeKerucut4);

	ShapeKerucut5.col.r = 1.0;
	ShapeKerucut5.col.g = 0.4;
	ShapeKerucut5.col.b = 1.0;
	ShapeKerucut5.numofVertices = 14;
	ShapeKerucut5.numofFaces = 24;
	ShapeKerucut5.pnt[0].x = 0;
	ShapeKerucut5.pnt[0].y = 0;
	ShapeKerucut5.pnt[0].z = 100;

	ShapeKerucut5.pnt[13].x = 0;
	ShapeKerucut5.pnt[13].y = 0;
	ShapeKerucut5.pnt[13].z = 300;
	for (int i = 1; i <= 12; i++) {
		float teta = (double)(sudut / 57.3);
		ShapeKerucut5.pnt[i].x = (float)(r*sin(teta));
		ShapeKerucut5.pnt[i].y = (float)(r*cos(teta));
		ShapeKerucut5.pnt[i].z = 100;
		sudut += 30;
	}
	for (int i = 0; i <= 23; i++) {
		ShapeKerucut5.fc[i].numofVertices = 3;
		if (i < 12) {
			if (i != 11) {
				ShapeKerucut5.fc[i].pnt[0] = 0;
				ShapeKerucut5.fc[i].pnt[1] = i + 1;
				ShapeKerucut5.fc[i].pnt[2] = i + 2;
			}
			else {
				ShapeKerucut5.fc[i].pnt[0] = 0;
				ShapeKerucut5.fc[i].pnt[1] = i + 1;
				ShapeKerucut5.fc[i].pnt[2] = 1;
			}
		}
		else {
			if (i != 23) {
				ShapeKerucut5.fc[i].pnt[0] = 13;
				ShapeKerucut5.fc[i].pnt[1] = i - 11;
				ShapeKerucut5.fc[i].pnt[2] = i - 10;
			}
			else {
				ShapeKerucut5.fc[i].pnt[0] = 13;
				ShapeKerucut5.fc[i].pnt[1] = i - 11;
				ShapeKerucut5.fc[i].pnt[2] = 1;
			}
		}
	}
	for (int i = 0; i < ShapeKerucut5.numofVertices; i++) {
		Vector3D_t p1;
		p1.v[0] = ShapeKerucut5.pnt[i].x;
		p1.v[1] = ShapeKerucut5.pnt[i].y;
		p1.v[2] = ShapeKerucut5.pnt[i].z;
		p1 = (matrix_Y)*(p1);
		p1 = (matrix_X)*(p1);
		p1 = (matrix_Z)*(p1);
		ShapeKerucut5.pnt[i].x = p1.v[0];
		ShapeKerucut5.pnt[i].y = p1.v[1];
		ShapeKerucut5.pnt[i].z = p1.v[2];
	}
	create3DObject(ShapeKerucut5);
	sudutRotasi++;

	if (sudutRotasi >= 360.0)
		sudutRotasi = 0.0;
	glFlush();	
	createOFF();
}

void createOFF() {
	ofstream file("C:/Users/Yosyafat/OneDrive/Grafika Komputer/Projects/KerucutBanyak/KerucutBanyak.off");	
	if (file.is_open())
	{
		file << "COFF" << endl;
		file << ShapeKerucut.numofVertices * 6 << " ";
		file << ShapeKerucut.numofFaces * 6 << " ";
		file << "0" << endl;
		for (int i = 0; i < 14; i++) {
			file << ShapeKerucut.pnt[i].x << " ";
			file << ShapeKerucut.pnt[i].y << " ";
			file << ShapeKerucut.pnt[i].z << " ";
			file << ShapeKerucut.col.r << " ";
			file << ShapeKerucut.col.g << " ";
			file << ShapeKerucut.col.b << endl;
		}

		for (int i = 0; i < 14; i++) {
			file << ShapeKerucut1.pnt[i].x << " ";
			file << ShapeKerucut1.pnt[i].y << " ";
			file << ShapeKerucut1.pnt[i].z << " ";
			file << ShapeKerucut1.col.r << " ";
			file << ShapeKerucut1.col.g << " ";
			file << ShapeKerucut1.col.b << endl;
		}

		for (int i = 0; i < 14; i++) {
			file << ShapeKerucut2.pnt[i].x << " ";
			file << ShapeKerucut2.pnt[i].y << " ";
			file << ShapeKerucut2.pnt[i].z << " ";
			file << ShapeKerucut2.col.r << " ";
			file << ShapeKerucut2.col.g << " ";
			file << ShapeKerucut2.col.b << endl;
		}

		for (int i = 0; i < 14; i++) {
			file << ShapeKerucut3.pnt[i].x << " ";
			file << ShapeKerucut3.pnt[i].y << " ";
			file << ShapeKerucut3.pnt[i].z << " ";
			file << ShapeKerucut3.col.r << " ";
			file << ShapeKerucut3.col.g << " ";
			file << ShapeKerucut3.col.b << endl;
		}

		for (int i = 0; i < 14; i++) {
			file << ShapeKerucut4.pnt[i].x << " ";
			file << ShapeKerucut4.pnt[i].y << " ";
			file << ShapeKerucut4.pnt[i].z << " ";
			file << ShapeKerucut4.col.r << " ";
			file << ShapeKerucut4.col.g << " ";
			file << ShapeKerucut4.col.b << endl;
		}

		for (int i = 0; i < 14; i++) {
			file << ShapeKerucut5.pnt[i].x << " ";
			file << ShapeKerucut5.pnt[i].y << " ";
			file << ShapeKerucut5.pnt[i].z << " ";
			file << ShapeKerucut5.col.r << " ";
			file << ShapeKerucut5.col.g << " ";
			file << ShapeKerucut5.col.b << endl;
		}

		for (int i = 0; i < 24; i++) {
			file << "3 ";
			file << ShapeKerucut.fc[i].pnt[0] << " ";
			file << ShapeKerucut.fc[i].pnt[1] << " ";
			file << ShapeKerucut.fc[i].pnt[2] << " " << endl;
		}

		for (int i = 0; i < 24; i++) {
			file << "3 ";
			file << ShapeKerucut1.fc[i].pnt[0] + 14 << " ";
			file << ShapeKerucut1.fc[i].pnt[1] + 14 << " ";
			file << ShapeKerucut1.fc[i].pnt[2] + 14 << " " << endl;
		}

		for (int i = 0; i < 24; i++) {
			file << "3 ";
			file << ShapeKerucut2.fc[i].pnt[0] + 14 * 2 << " ";
			file << ShapeKerucut2.fc[i].pnt[1] + 14 * 2 << " ";
			file << ShapeKerucut2.fc[i].pnt[2] + 14 * 2 << " " << endl;
		}

		for (int i = 0; i < 24; i++) {
			file << "3 ";
			file << ShapeKerucut3.fc[i].pnt[0] + 14 * 3 << " ";
			file << ShapeKerucut3.fc[i].pnt[1] + 14 * 3 << " ";
			file << ShapeKerucut3.fc[i].pnt[2] + 14 * 3 << " " << endl;
		}

		for (int i = 0; i < 24; i++) {
			file << "3 ";
			file << ShapeKerucut4.fc[i].pnt[0] + 14 * 4 << " ";
			file << ShapeKerucut4.fc[i].pnt[1] + 14 * 4 << " ";
			file << ShapeKerucut4.fc[i].pnt[2] + 14 * 4 << " " << endl;
		}

		for (int i = 0; i < 24; i++) {
			file << "3 ";
			file << ShapeKerucut5.fc[i].pnt[0] + 14 * 5 << " ";
			file << ShapeKerucut5.fc[i].pnt[1] + 14 * 5 << " ";
			file << ShapeKerucut5.fc[i].pnt[2] + 14 * 5 << " " << endl;
		}		
		file.close();
	}
	else cout << "Unable to open file";
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Dua Kerucut");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500, 500, -500, 500);
	glutDisplayFunc(create_kerucut);
	glutTimerFunc(50, timer, 0);
	glutMainLoop();
	return 0;
}
