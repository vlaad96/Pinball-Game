#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"
#include "Box2D/Box2D/Box2D.h"

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
	PhysBody* right_flopper2;
	PhysBody* left_flopper2;

	PhysBody* left_flopper_body;
	PhysBody* right_flopper_body;

	// Sensors 

	PhysBody* tunnel_beginning;
	PhysBody* tunnel_finish;
	PhysBody* right_tunnel2;
	PhysBody* left_tunnel2;
	PhysBody* midpoint;
	PhysBody* up_hole;
	PhysBody* launcher;
	PhysBody* cannon_sensor;
	PhysBody* chip_loop;
	PhysBody* ball_saver_right;
	PhysBody* ball_saver_left;
	PhysBody* monster_hit;
	PhysBody* right_hole = nullptr;
	PhysBody* deadline;

	// Textures
	
	SDL_Rect section;
	SDL_Rect saver;
	SDL_Rect last_frame;
	SDL_Rect section5;

	SDL_Texture* background;
	SDL_Texture* tunnel1;
	SDL_Texture* tunnel2;
	SDL_Texture* spritesheet;

	// Animations

	Animation cannon;
	Animation raptor;
	Animation raptor_hit;
	Animation left_floppers;
	Animation right_floppers;
	Animation arrow_tunel2_left;
	Animation arrow_tunel2_right;
	Animation white_mid;
	Animation arrow;
	Animation blue_arrow_top;
	Animation monster_arrow;
	Animation down_lights;
	Animation map_arrows;
	Animation yellow_arrows;
	Animation game_over;
	Animation win;

	// Limits
	p2List<PhysBody*> limits_background;

	PhysBody* tunnel;
	PhysBody* tunnel_2_1;
	PhysBody* tunnel_2_2;

	bool on_tunnel;
	bool on_canon;
	bool on_launcher;
	bool boss_hit;
	bool on_top;
	bool want_to_delete = false;
	bool mid_hit = false;
	bool lost = false;
	bool won = false;
	bool played = false;

	//FX & sounds
	uint fx_flopper;
	uint fx_collision;
	uint fx_kickers;
	uint fx_gameover;
	uint fx_saverhit;
	uint fx_cannon;
	uint fx_explosion;
	uint fx_chiploop;
	uint fx_victory;

	uint main_theme;


	// Joints
	b2RevoluteJoint* rev_joint_right = nullptr;
	b2RevoluteJoint* rev_joint_left = nullptr;
	b2RevoluteJoint* rev_joint_right2 = nullptr;
	b2RevoluteJoint* rev_joint_left2 = nullptr;

	// Variables for playing
	int color_circles;
	int number_arrow_lights;
	int middle_hole_hit;
	int up_hole_hit;
	int chip_lights_on;		 //How many lights of the chip loop are on
};
