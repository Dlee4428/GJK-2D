#include "Simplex.h"
#include <stdio.h>
#include <stdlib.h>

Vec3 FarthestPointInDirection(const std::vector<Vec3> &vertices, const Vec3& d) {

	int idx = 0;
	float maxP = VMath::dot(d, vertices[0]);
	size_t size = vertices.size();

	for (size_t i = 0; i < size; i++) {
		float p = VMath::dot(d, vertices[i]);
		if (p > maxP) {
			maxP = p;
			idx = i;
		}
	}
	return vertices[idx];
}

Vec3 centerPoint(const std::vector<Vec3> &vertices) {
	Vec3 center = { 0.0f, 0.0f, 0.0f };
	size_t size = vertices.size();
	for (size_t i = 0; i < size; i++) {
		center.x += vertices[i].x;
		center.y += vertices[i].y;
	}
	center.x /= size;
	center.y /= size;
	return center;
}

//This Function will use matrices to scale it down original shapes
Mat3 scaleTriangle(const std::vector<Vec3> &vertices) {
	Mat3 transCentre, transOrigin, scale, result;
	Vec3 pos{ 0.0f, 0.0f, 0.0f };
	pos = centerPoint(vertices);

	transCentre = MMath::Translate(pos.x, pos.y);
	transOrigin = MMath::Translate(-pos.x, -pos.y);
	scale = MMath::Scale(0.75f, 0.75f);

	result = transCentre * scale * transOrigin;

	return result;
}

Vec3 contactPointSupportA(const Body b1, const Body b2) {

	Vec3 shrinkA, shrinkB, shrinkC, shrinkD, shrinkE, shrinkF, posA, posB, d, r1, r2, r3, r4, r5, r6, largest, smallest;

	Mat3 resultantA = scaleTriangle(b1.vertices); //This doesn't scale as I wanted hmm...
	Mat3 resultantB = scaleTriangle(b2.vertices);

	shrinkA = resultantA * b1.vertices[0];
	shrinkB = resultantA * b1.vertices[1];
	shrinkC = resultantA * b1.vertices[2];

	shrinkD = resultantB * b2.vertices[0];
	shrinkE = resultantB * b2.vertices[1];
	shrinkF = resultantB * b2.vertices[2];

	posA = centerPoint(b1.vertices);
	posB = centerPoint(b2.vertices);

	d = posB - posA;

	r1 = VMath::dot(d, shrinkA);
	r2 = VMath::dot(d, shrinkB);
	r3 = VMath::dot(d, shrinkC);

	r4 = VMath::dot(d, shrinkD);
	r5 = VMath::dot(d, shrinkE);
	r6 = VMath::dot(d, shrinkF);

	//Loop for Largest
	if (r1 > r2 && r1 > r3) {
		largest = shrinkA;
	}
	else if (r2 > r1 && r2 > r3) {
		largest = shrinkB;
	}
	else if (r3 > r1 && r3 > r2) {
		largest = shrinkC;
	}

	//Loop for Smallest
	if (r4 < r5 && r4 < r6) {
		smallest = shrinkD;
	}
	else if (r5 < r4 && r5 < r6) {
		smallest = shrinkE;
	}
	else if (r6 < r4 && r6 < r5) {
		smallest = shrinkF;
	}

	return largest - smallest;
}

Vec3 contactPointSupportB(const Body b1, const Body b2) {

	Vec3 shrinkA, shrinkB, shrinkC, shrinkD, shrinkE, shrinkF, posA, posB, d, r1, r2, r3, r4, r5, r6, largest, smallest;

	Mat3 resultantA = scaleTriangle(b1.vertices); //This doesn't scale as I wanted hmm...
	Mat3 resultantB = scaleTriangle(b2.vertices);

	shrinkA = resultantA * b1.vertices[0];
	shrinkB = resultantA * b1.vertices[1];
	shrinkC = resultantA * b1.vertices[2];

	shrinkD = resultantB * b2.vertices[0];
	shrinkE = resultantB * b2.vertices[1];
	shrinkF = resultantB * b2.vertices[2];

	posA = centerPoint(b1.vertices);
	posB = centerPoint(b2.vertices);

	d = posB - posA;

	d = -d;

	r1 = VMath::dot(d, shrinkA);
	r2 = VMath::dot(d, shrinkB);
	r3 = VMath::dot(d, shrinkC);

	r4 = VMath::dot(d, shrinkD);
	r5 = VMath::dot(d, shrinkE);
	r6 = VMath::dot(d, shrinkF);

	//Loop for Largest
	if (r1 > r2 && r1 > r3) {
		largest = shrinkA;
	}
	else if (r2 > r1 && r2 > r3) {
		largest = shrinkB;
	}
	else if (r3 > r1 && r3 > r2){
		largest = shrinkC;
	}

	//Loop for Smallest
	if (r4 < r5 && r4 < r6) {
		smallest = shrinkD;
	}
	else if (r5 < r4 && r5 < r6) {
		smallest = shrinkE;
	}
	else if(r6 < r4 && r6 < r5) {
		smallest = shrinkF;
	}

	return largest - smallest;
}

Vec3 contactPointSupportC(const Body b1, const Body b2, const Vec3 &d) {

	Vec3 shrinkA, shrinkB, shrinkC, shrinkD, shrinkE, shrinkF, posA, posB, r1, r2, r3, r4, r5, r6, largest, smallest;

	Mat3 resultantA = scaleTriangle(b1.vertices); //This doesn't scale as I wanted hmm...
	Mat3 resultantB = scaleTriangle(b2.vertices);

	shrinkA = resultantA * b1.vertices[0];
	shrinkB = resultantA * b1.vertices[1];
	shrinkC = resultantA * b1.vertices[2];

	shrinkD = resultantB * b2.vertices[0];
	shrinkE = resultantB * b2.vertices[1];
	shrinkF = resultantB * b2.vertices[2];

	posA = centerPoint(b1.vertices);
	posB = centerPoint(b2.vertices);

	r1 = VMath::dot(d, shrinkA);
	r2 = VMath::dot(d, shrinkB);
	r3 = VMath::dot(d, shrinkC);

	r4 = VMath::dot(d, shrinkD);
	r5 = VMath::dot(d, shrinkE);
	r6 = VMath::dot(d, shrinkF);

	//Loop for Largest
	if (r1 > r2 && r1 > r3) {
		largest = shrinkA;
	}
	else if (r2 > r1 && r2 > r3) {
		largest = shrinkB;
	}
	else if (r3 > r1 && r3 > r2) {
		largest = shrinkC;
	}

	//Loop for Smallest
	if (r4 < r5 && r4 < r6) {
		smallest = shrinkD;
	}
	else if (r5 < r4 && r5 < r6) {
		smallest = shrinkE;
	}
	else if (r6 < r4 && r6 < r5) {
		smallest = shrinkF;
	}

	return largest - smallest;
}

//Triple product expansion to calculate perpendicular normal vectors
//This point forwards to the Origin in Minkowski space

Vec3 TripleProduct(Vec3 &a, Vec3 &b, Vec3 &c) {

	Vec3 result;

	float ac = a.x * c.x + a.y * c.y;
	float bc = b.x * c.x + b.y * c.y;

	result.x = b.x * ac - a.x * bc;
	result.y = b.y * ac - a.y * bc;

	return result;
}

//SupportFunction to build up Simplex
Vec3 SupportFunc(const Body b1, const Body b2, const Vec3 &d) {
	//d is a direction vector

	Vec3 farA = FarthestPointInDirection(b1.vertices, d);
	Vec3 farB = FarthestPointInDirection(b2.vertices, -d);

	return farA - farB;
}


//GJK Test
bool Simplex::GJKCollision(const Body& b1, const Body& b2){

	size_t index = 0;
	Vec3 a, b, c, d, AO, AB, AC, ABperp, ACperp, simplex[3];

	//Center Point for each shape
	Vec3 posA = centerPoint(b1.vertices); //Body vertices
	Vec3 posB = centerPoint(b2.vertices);

	//Initial direction from center of first point to second point
	d = posB - posA;

	//Set the support function to find first point of Simplex
	a = simplex[0] = SupportFunc(b1, b2, d);

	//Return false if this did not collide
	if (VMath::dot(a, d) <= 0) {
		return false;
	}
	
	d = -(a); //Search next direction by negating a since it's always towards the origin.

	while (true) {
		a = simplex[++index] = SupportFunc(b1, b2, d); //Add new point to Simplex since this haven't terminated yet

		//Return false if this did not collide
		if (VMath::dot(a, d) <= 0) {
			return false;
		}

		AO = -(a); //From point A to Origin is just negative A

	    //Since simplex has 2 points forming line, check if it's perpendicular to AB (not a triangle)
		if(index < 2){
			b = simplex[0];
			AB = b - a; // from point A to B
			d = TripleProduct(AB, AO, AB); //Normal to AB toward Origin
			if (VMath::lengthSquared(d) == 0) {
				d = VMath::Perpendicular(AB);
			}
			continue; //Skip to next iteration
		}
		b = simplex[1];
		c = simplex[0];
		AB = b - a; //from point A to B
		AC = c - a; //from point A to C

		ACperp = TripleProduct(AB, AC, AC);

		if (VMath::dot(ACperp, AO) >= 0) {
			d = ACperp; // new direction is normal to AC towards Origin
		} else {
			ABperp = TripleProduct(AC, AB, AB);

			if (VMath::dot(ABperp, AO) < 0) {
				return true; //collision happens
			}

			simplex[0] = simplex[1]; //Swap first element(PointC)
			d = ABperp; //New direction is normal to AB towards Origin
		}

		simplex[1] = simplex[2]; //Swap elements in the middle(point B)
		--index;
	}
	return false;
}



void Simplex::contactNP(const Body& b1, const Body& b2) {

	Vec3 o{ 0.0f, 0.0f, 0.0f }, AO, BO, AB, AC, BC, simplex[3], Q1, Q2, Q3, Q1mag, Q2mag, Q3mag, d3, d, L, closestA, closestB;
	Vec3 shrinkA, shrinkB, shrinkC, shrinkD, shrinkE, shrinkF, n, oriClosestA, oriClosestB;
	float aT, bT, cT, A1, A2;

	//Find Simplex point 1 & 2
	simplex[0] = contactPointSupportA(b1, b2); 
	simplex[1] = contactPointSupportB(b1, b2);

	//Find AB and AO
	AB = simplex[1] - simplex[0];
	AO = o - simplex[0];

	//Lerp from AO AB
	aT = VMath::dot(AO, AB) / VMath::dot(AB, AB);

	//Find Q1 for simplex line
	Q1 = simplex[0] + AB * aT;

	//Distance to origin Q1
	Q1mag = VMath::mag(Q1);

	//Find third direction vector
	d3 = o - Q1;

	//Find new Point using the line OQ1
	simplex[2] = contactPointSupportC(b1, b2, d3);

	//Finding the closest line
	AC = simplex[2] - simplex[0];
	BC = simplex[2] - simplex[1];
	BO = o - simplex[1];

	//Lerp from AO AC
	bT = VMath::dot(AO, AC) / VMath::dot(AC, AC);

	//Finding Q2
	Q2 = simplex[0] + AC * bT;

	//Distance to origin Q2
	Q2mag = VMath::mag(Q2);

	//Lerp from BO BC
	cT = VMath::dot(BO, BC) / VMath::dot(BC, BC);

	//Finding Q3 
	Q3 = simplex[1] + BC * cT;

	//Distance to origin Q3
	Q3mag = VMath::mag(Q3);

	//Simplex line
	L = simplex[1] - simplex[0];

	//Convex combination for Lambda values
	A1 = VMath::dot(simplex[1], L) / VMath::dot(L, L);
	A2 = 1 - A1;

	Mat3 resultantA = scaleTriangle(b1.vertices);
	Mat3 resultantB = scaleTriangle(b2.vertices);

	shrinkA = resultantA * b1.vertices[0];
	shrinkB = resultantA * b1.vertices[1];
	shrinkC = resultantA * b1.vertices[2];

	shrinkD = resultantB * b2.vertices[0];
	shrinkE = resultantB * b2.vertices[1];
	shrinkF = resultantB * b2.vertices[2];
	
	//A closest
	closestA = A1 * shrinkA + A2 * shrinkB;

	//B closest
	closestB = A1 * shrinkD + A2 * shrinkE;

	//Find contact normal
	n.x = closestB.x - closestA.x / VMath::mag(closestB - closestA);
	n.y = closestB.y - closestA.y / VMath::mag(closestB - closestA);


	//Original closest point
	oriClosestA = MMath::Inverse(resultantA) * closestA;
	oriClosestB = MMath::Inverse(resultantB) * closestB;

	std::cout << "Contact Normal is -> " << n.x << n.y << "     Closest point A is -> " << oriClosestA.x << oriClosestB.y << std::endl;
}

void Simplex::HandleCollision(Body &b1, Body &b2) {
	bool gjk = GJKCollision(b1, b2);

	if (gjk) {
		contactNP(b1, b2);
		printf("Collision Detected!\n");

	} else {
		printf("No Collision\n");
	}
}

