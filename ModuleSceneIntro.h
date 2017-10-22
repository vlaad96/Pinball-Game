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

	PhysBody* left_paddle_body;
	PhysBody* right_paddle_body;

	// Sensors 
	PhysBody* tunnel_beginning;
	PhysBody* tunnel_finish;
	PhysBody* right_tunnel2;
	PhysBody* left_tunnel2;
	PhysBody* midpoint;
	PhysBody* up_hole;
	PhysBody* launcher;
	PhysBody* cannon;
	PhysBody* chip_loop;
	PhysBody* ball_saver_right;
	PhysBody* ball_saver_left;
	PhysBody* monster_hit;
	PhysBody* right_hole = nullptr;
	PhysBody* deadline;

	// Textures
	SDL_Texture* circle;
	SDL_Texture* background;
	SDL_Texture* tunnels;
	SDL_Texture* tunnels_top;
	SDL_Texture* sprites;

	// Animations
	Animation canon;
	Animation boss;
	Animation hit_boss;
	Animation paddle_left;
	Animation paddle_right;
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
	bool on_hole;
	bool boss_hited;
	bool on_top;
	bool want_to_delete = false;
	bool mid_hitted = false;
	bool gameover = false;
	bool winning = false;
	bool played = false;

	//FX & sounds
	uint paddle_fx;
	uint contact_fx;
	uint kickers_fx;
	uint lose;
	uint saver_hit;
	uint canon_sound;
	uint explosion;
	uint chip_sound;
	uint win_fx;

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
