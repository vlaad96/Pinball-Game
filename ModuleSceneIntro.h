#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void Create_Limits();
	void Create_Kickers();
	void Draw_Kickers();
	void Draw_Lights();
	void Check_Area();

public:
	
	p2Point<int> ray;
	bool ray_on;

	PhysBody* ball;
	PhysBody* right_flopper;
	PhysBody* left_flopper;

};
