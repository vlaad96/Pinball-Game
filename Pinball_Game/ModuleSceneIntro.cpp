#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ball = NULL;
	ray_on = false;
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//Textures of the game

	background = App->textures->Load("/spritesheet/Background.png");
	tunnel1 = App->textures->Load("/spritesheet/T1.png");
	tunnel2 = App->textures->Load("/spritesheet/T2.png");
	spritesheet= App->textures->Load("/spritesheet/sprites.png");


	//Audio

	fx_flopper = App->audio->LoadFx("FX/Paddle_sound.ogg");
	fx_collision = App->audio->LoadFx("FX/Contact_sound.ogg");
	fx_kickers = App->audio->LoadFx("FX/Kickers_sound.ogg");
	fx_gameover = App->audio->LoadFx("FX/fx_gameover.ogg");
	fx_saverhit = App->audio->LoadFx("FX/Hit_Saver.ogg");
	fx_cannon = App->audio->LoadFx("FX/canon_shot.ogg");
	fx_explosion = App->audio->LoadFx("FX/hiting_monster.ogg");
	fx_chiploop = App->audio->LoadFx("FX/chip_loop.ogg");
	fx_victory = App->audio->LoadFx("FX/won.wav");


	//Sensors on tunnels

	tunnel_beginning = App->physics->CreateRectangleSensor(135, 261, 20, 1);
	tunnel_finish = App->physics->CreateRectangleSensor(90, 640, 20, 1);
	left_tunnel2 = App->physics->CreateRectangleSensor(42, 400, 10, 1);
	right_tunnel2 = App->physics->CreateRectangleSensor(460, 400, 10, 1);
	right_hole = App->physics->CreateRectangleSensor(480, 450, 2, 2);


	//Playability sensors

	midpoint = App->physics->CreateRectangleSensor(239, 440, 5, 1);
	up_hole = App->physics->CreateRectangleSensor(308, 247, 5, 1);
	cannon_sensor = App->physics->CreateRectangleSensor(490, 600, 5, 1);
	launcher = App->physics->CreateRectangleSensor(490, 800, 5, 1);
	chip_loop = App->physics->CreateRectangleSensor(202, 102, 5, 1);
	deadline = App->physics->CreateRectangleSensor(240, 900, 120, 1);
	ball_saver_right = App->physics->CreateRectangleSensor(435, 772, 5, 1);
	ball_saver_left = App->physics->CreateRectangleSensor(45, 772, 5, 1);
	monster_hit = App->physics->CreateRectangleSensor(405, 161, 5, 1);


	//variable initializing

	Create_Limits();
	Create_Kickers();

	//Cannon animation

	cannon.PushBack({ 3, 151, 56, 60 });
	cannon.PushBack({ 65, 151, 56, 60 });
	cannon.PushBack({ 129, 151, 56, 60 });
	cannon.PushBack({ 3, 151, 56, 60 });
	cannon.PushBack({ 3, 151, 56, 60 });
	cannon.PushBack({ 3, 151, 56, 60 });
	cannon.PushBack({ 3, 151, 56, 60 });
	cannon.speed = 0.2f;
	cannon.loop = false;

	//Raptor animation

	raptor.PushBack({ 3, 23, 106, 114 });
	raptor.PushBack({ 119, 23, 100, 114 });
	raptor.PushBack({ 229, 29, 84, 108 });
	raptor.PushBack({ 323, 35, 100, 102 });

	raptor.speed = 0.03f;
	raptor.loop = true;


	//Floppers animation

	left_floppers.PushBack({ 477, 237, 42, 80 });
	left_floppers.PushBack({ 529, 237, 42, 80 });
	left_floppers.speed = 0.08f;
	left_floppers.loop = true;

	right_floppers.PushBack({ 581, 237, 42, 80 });
	right_floppers.PushBack({ 633, 237, 42, 80 });
	right_floppers.speed = 0.08f;
	right_floppers.loop = true;

	//Game over

	game_over.PushBack({ 524, 1291, 516, 5 });
	game_over.PushBack({ 524, 1291, 516, 10 });
	game_over.PushBack({ 524, 1291, 516, 15 });
	game_over.PushBack({ 524, 1291, 516, 20 });
	game_over.PushBack({ 524, 1291, 516, 25 });
	game_over.PushBack({ 524, 1291, 516, 30 });
	game_over.PushBack({ 524, 1291, 516, 35 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 40 });
	game_over.PushBack({ 524, 1291, 516, 35 });
	game_over.PushBack({ 524, 1291, 516, 30 });
	game_over.PushBack({ 524, 1291, 516, 25 });
	game_over.PushBack({ 524, 1291, 516, 20 });
	game_over.PushBack({ 524, 1291, 516, 15 });
	game_over.PushBack({ 524, 1291, 516, 10 });
	game_over.PushBack({ 524, 1291, 516, 5 });
	game_over.speed = 0.1f;
	game_over.loop = false;

	//won

	win.PushBack({ 524, 1201, 516, 5 });
	win.PushBack({ 524, 1201, 516, 10 });
	win.PushBack({ 524, 1201, 516, 15 });
	win.PushBack({ 524, 1201, 516, 20 });
	win.PushBack({ 524, 1201, 516, 25 });
	win.PushBack({ 524, 1201, 516, 30 });
	win.PushBack({ 524, 1201, 516, 35 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 40 });
	win.PushBack({ 524, 1201, 516, 35 });
	win.PushBack({ 524, 1201, 516, 30 });
	win.PushBack({ 524, 1201, 516, 25 });
	win.PushBack({ 524, 1201, 516, 20 });
	win.PushBack({ 524, 1201, 516, 15 });
	win.PushBack({ 524, 1201, 516, 10 });
	win.PushBack({ 524, 1201, 516, 5 });
	win.speed = 0.1f;
	win.loop = false;

	left_flopper_body->body->GetFixtureList()->SetRestitution(1.25f);
	right_flopper_body->body->GetFixtureList()->SetRestitution(1.25f);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
	//Background blit

	App->renderer->Blit(background, 0, 0);

	Check_Area();
	
	//Input

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && (lost || won))
	{
		played = false;
		App->player->number_balls = 5;
		App->player->score = 0;
		lost = false;
		won = false;
		game_over.Reset();
		win.Reset();
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && App->player->number_balls > 0)
	{
		if (ball == NULL)
		{
			played = false;
			App->player->number_balls--;
			ball = App->physics->CreateCircle(490, 800, 15, "static", 0x0004,0x000);
		}
		ball->listener = this;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		rev_joint_left->SetMotorSpeed(30);
		rev_joint_left2->SetMotorSpeed(30);
	}
	else
	{
		rev_joint_left->SetMotorSpeed(-30);
		rev_joint_left2->SetMotorSpeed(-30);
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && ball != nullptr && on_launcher)
	{
		ball->body->SetType(b2_dynamicBody);
		ball->body->SetLinearVelocity(b2Vec2(0, -10));
		on_launcher = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		rev_joint_right->SetMotorSpeed(-30);
		rev_joint_right2->SetMotorSpeed(-30);
	}
	else
	{
		rev_joint_right->SetMotorSpeed(30);
		rev_joint_right2->SetMotorSpeed(30);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) App->audio->PlayFx(fx_kickers);

	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// Draw paddles -----------------------------------------------------------------

	App->renderer->Blit(spritesheet, 112, 620, &left_floppers.GetCurrentFrame());
	App->renderer->Blit(spritesheet, 330, 620, &right_floppers.GetCurrentFrame());

	//Draw middle hole lights
	Draw_Lights();

	//Draw ball saver
	
	saver.x = 113;
	saver.y = 383;
	saver.w = 32;
	saver.h = 42;

	App->renderer->Blit(spritesheet, 30, 772, &saver);
	App->renderer->Blit(spritesheet, 422, 772, &saver);

	// Draw white mid --------------------------------------------------------------------
	if (white_mid.Finished())
	{
		mid_hit = false;
		white_mid.Reset();
	}
	else if (mid_hit)
		App->renderer->Blit(spritesheet, 125, 270, &white_mid.GetCurrentFrame());

	if (middle_hole_hit < 5)
	{
		right_hole->body->SetActive(false);

		section.x = 757;
		section.y = 220;
		section.w = 41;
		section.h = 41;

		App->renderer->Blit(spritesheet, 470, 420, &section);
	}
	else
	{
		right_hole->body->SetActive(true);
	}

	// Draw kickers -----------------------------------------------------------------
	Draw_Kickers();

	// Draw ball & tunnel ----------------------------------------------------------------

	if (on_tunnel) App->renderer->Blit(tunnel1, 0, -1);
	if (on_top) App->renderer->Blit(tunnel2, 0, -1);

	int x, y;
	if (ball != NULL)
	{
		ball->GetPosition(x, y);
		ball->body->SetTransform(b2Vec2(ball->body->GetPosition().x, ball->body->GetPosition().y), 90);

		section.x = 0;
		section.y = 555;
		section.h = 31;
		section.w = 31;

		App->renderer->Blit(spritesheet, x - 2, y, &section, 1.0f, ball->GetRotation());
	}

	if (!on_tunnel) App->renderer->Blit(tunnel1, 0, -1);
	if (!on_top) App->renderer->Blit(tunnel2, 0, -1);

	// Ray --------------------------------------------------------------------

	if (ray_on == true)
	{
		fVector destination(mouse.x - ray.x, mouse.y - ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if (normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	// Drawong canon ---------------------------------------------------------

	if (!on_canon)
	{
		App->renderer->Blit(spritesheet, 455, 565, &cannon.frames[0]);
		cannon.Reset();
	}
	else
		App->renderer->Blit(spritesheet, 455, 565, &cannon.GetCurrentFrame());


	//Drawong boss + explossion
	App->renderer->Blit(spritesheet, 365, 95, &raptor.GetCurrentFrame());

	if (boss_hit)
	{
		
		last_frame.x = 617;
		last_frame.y = 85;
		last_frame.w = 58;
		last_frame.h = 52;

		App->renderer->Blit(spritesheet, 378, 132, &raptor_hit.GetCurrentFrame());
		if (raptor_hit.Finished())
		{
			boss_hit = false;
			raptor_hit.Reset();
		}
	}

	// Deleting ball if want_to_delete == true -------------------------------

	if (want_to_delete == true)
	{
		App->physics->DeleteBody(ball->body);
		ball = nullptr;
		want_to_delete = false;
	}

	// Draw yellow static kicker ------------------------------------------
	
	section5.x = 680;
	section5.y = 188;
	section5.h = 23;
	section5.w = 65;

	App->renderer->Blit(spritesheet, 340, 48, &section5, 1.0f, 0, 50, 15);

	// Draw Arrow ------------------------------------------------------
	if (middle_hole_hit < 3) App->renderer->Blit(spritesheet, 227, 338, &arrow.GetCurrentFrame());
	else App->renderer->Blit(spritesheet, 475, 400, &arrow.GetCurrentFrame());

	// won, game over, playing -----------------------------------------
	if (lost)
	{
		color_circles = 0;
		App->renderer->Blit(spritesheet, 0, 0, &game_over.GetCurrentFrame());
	}
	if (color_circles == 4)
	{
		won = true;
		App->renderer->Blit(spritesheet, 0, 0, &win.GetCurrentFrame());
		if (!played)
		{
			App->audio->PlayFx(fx_victory);
			played = true;
		}
	}


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == tunnel_beginning || bodyB == tunnel_finish)
	{
		on_tunnel = !on_tunnel;
		if (on_canon)
			on_canon = false;
	}

	else if (bodyB == left_tunnel2 || bodyB == right_tunnel2)
		on_top = !on_top;

	else if (bodyB == monster_hit)
	{
		boss_hit = true;
		if (!won)App->player->score += 1000;
		App->audio->PlayFx(fx_explosion);
	}

	else if (bodyB == right_hole)
	{
		color_circles++;
		if (!won) App->player->score += 3000;
		middle_hole_hit = 0;
	}

	else if (bodyB == deadline)
	{
		if (!won)
		{
			if (App->player->number_balls == 0)
			{
				lost = true;
				App->audio->PlayFx(fx_gameover);
			}
			want_to_delete = true;
			on_launcher = true;
			chip_lights_on = 0;
			middle_hole_hit = 0;
		}
		else
		{
			color_circles = 0;
			App->player->number_balls = 0;
			want_to_delete = true;
			on_launcher = true;
			chip_lights_on = 0;
			middle_hole_hit = 0;
		}
	}

	else if (bodyB == up_hole && up_hole_hit < 3) {
		up_hole_hit++;
		if (!won)App->player->score += 250;

		if (up_hole_hit == 3) {
			if (!won)App->player->score += 1000;
		}
	}

	else if (bodyB == left_flopper_body)
	{
		App->audio->PlayFx(fx_flopper);
	}

	else if (bodyB == right_flopper_body)
	{
		App->audio->PlayFx(fx_flopper);
	}

	else if (bodyB == chip_loop && chip_lights_on < 4)
	{
		chip_lights_on++;
		if (!won)App->player->score += 500;

		App->audio->PlayFx(fx_chiploop);

		if (chip_lights_on == 4) {
			if (!won) App->player->score += 2000;
		}
	}

	else if (bodyB == midpoint && middle_hole_hit < 3 && color_circles < 4)
	{
		mid_hit = true;
		middle_hole_hit++;
		if (!won) App->player->score += 250;
	}

	else if (bodyB == ball_saver_left || bodyB == ball_saver_right)
	{
		bodyA->body->SetLinearVelocity(b2Vec2(0, -10));
		App->audio->PlayFx(fx_saverhit);
	}


	else if ((bodyB == left_flopper || bodyB == right_flopper2) && chip_lights_on == 4) {
		chip_lights_on = 0;
	}
	else if ((bodyB == left_flopper || bodyB == right_flopper2) && up_hole_hit == 3) {
		up_hole_hit = 0;
	}

	else if (bodyB == cannon_sensor)
	{
		ball->body->SetLinearVelocity(b2Vec2(-13, -15));
		App->audio->PlayFx(fx_cannon);
		on_canon = true;
		on_launcher = false;
	}
}

void ModuleSceneIntro::Create_Limits()
{
	int piece_1_tunnel_3[102] = {
		66, 412,
		50, 375,
		34, 294,
		27, 250,
		24, 204,
		25, 161,
		34, 132,
		45, 108,
		63, 84,
		82, 68,
		110, 56,
		146, 46,
		186, 40,
		251, 39,
		308, 45,
		350, 51,
		375, 58,
		394, 62,
		418, 72,
		439, 90,
		458, 117,
		467, 141,
		474, 167,
		473, 206,
		470, 273,
		458, 332,
		441, 398,
		428, 413,
		426, 402,
		438, 393,
		448, 355,
		457, 316,
		466, 263,
		470, 209,
		470, 163,
		452, 115,
		426, 83,
		392, 66,
		325, 51,
		241, 43,
		165, 47,
		87, 69,
		50, 111,
		34, 145,
		27, 187,
		28, 238,
		36, 290,
		47, 347,
		61, 392,
		68, 400,
		71, 410
	};

	tunnel_2_1 = App->physics->CreateChain(0, 0, piece_1_tunnel_3, 102, "static", 0x0001, 0x0004);

	int piece_2_tunnel_3[134] = {
		22, 411,
		29, 410,
		25, 396,
		16, 376,
		8, 346,
		-2, 310,
		-10, 269,
		-13, 247,
		-15, 214,
		-14, 190,
		-14, 175,
		-10, 153,
		-7, 137,
		0, 118,
		11, 95,
		29, 70,
		40, 59,
		77, 35,
		120, 20,
		161, 8,
		207, 2,
		233, -1,
		269, -1,
		320, 3,
		354, 9,
		403, 25,
		435, 38,
		463, 58,
		484, 80,
		498, 105,
		507, 132,
		510, 252,
		507, 283,
		503, 312,
		494, 350,
		481, 395,
		468, 420,
		470, 427,
		476, 424,
		483, 418,
		482, 407,
		496, 369,
		508, 317,
		518, 250,
		515, 136,
		509, 110,
		498, 89,
		477, 62,
		453, 41,
		421, 24,
		392, 12,
		350, 1,
		313, -5,
		285, -7,
		260, -9,
		231, -8,
		187, -4,
		144, 4,
		89, 21,
		44, 44,
		12, 80,
		-9, 120,
		-20, 163,
		-21, 222,
		-12, 286,
		0, 343,
		18, 400
	};

	tunnel_2_2 = App->physics->CreateChain(0, 0, piece_2_tunnel_3, 134, "static", 0x0001, 0x0004);

	// Creating tunnels limits -------------------------

	int Tunnel[288] = {
		158, 262,
		108, 211,
		100, 197,
		96, 180,
		96, 154,
		98, 122,
		106, 102,
		124, 81,
		146, 70,
		188, 65,
		226, 74,
		246, 85,
		260, 98,
		268, 117,
		270, 141,
		269, 177,
		263, 205,
		254, 231,
		242, 248,
		220, 268,
		195, 284,
		35, 365,
		0, 399,
		0, 556,
		8, 565,
		30, 577,
		57, 592,
		68, 599,
		72, 611,
		72, 623,
		71, 634,
		72, 647,
		80, 654,
		96, 656,
		109, 646,
		109, 632,
		107, 620,
		105, 595,
		101, 581,
		87, 566,
		64, 555,
		49, 546,
		38, 538,
		38, 413,
		60, 395,
		227, 310,
		275, 265,
		301, 206,
		308, 173,
		300, 103,
		291, 83,
		284, 69,
		279, 58,
		266, 52,
		249, 44,
		240, 41,
		219, 36,
		199, 34,
		179, 34,
		153, 36,
		133, 42,
		109, 51,
		93, 62,
		82, 75,
		72, 92,
		63, 114,
		57, 139,
		56, 159,
		60, 184,
		71, 214,
		87, 237,
		105, 256,
		117, 268,
		126, 279,
		133, 289,
		74, 227,
		58, 193,
		50, 147,
		61, 103,
		81, 66,
		101, 50,
		120, 40,
		142, 33,
		166, 30,
		183, 29,
		209, 30,
		225, 32,
		245, 38,
		261, 46,
		276, 51,
		284, 56,
		291, 63,
		294, 70,
		297, 80,
		302, 91,
		306, 100,
		308, 118,
		309, 141,
		314, 172,
		309, 204,
		296, 237,
		278, 270,
		230, 313,
		63, 398,
		41, 415,
		42, 536,
		90, 562,
		104, 578,
		110, 596,
		111, 623,
		117, 634,
		116, 640,
		113, 649,
		104, 656,
		93, 660,
		79, 659,
		69, 649,
		64, 635,
		69, 624,
		66, 605,
		54, 593,
		18, 576,
		-5, 557,
		-4, 393,
		32, 360,
		205, 273,
		240, 247,
		263, 199,
		267, 151,
		263, 108,
		241, 85,
		208, 70,
		173, 69,
		140, 75,
		121, 87,
		110, 104,
		102, 125,
		100, 145,
		99, 181,
		108, 206,
		126, 225,
		145, 246,
		155, 254,
		160, 260
	};

	tunnel = App->physics->CreateChain(0, 0, Tunnel, 288, "static", 0x0001, 0x0004);

	// Creating background limits -----------------------------------

	int Background[180] = {
		413, 832,
		422, 843,
		449, 844,
		460, 837,
		460, 663,
		454, 606,
		448, 587,
		437, 575,
		459, 512,
		451, 504,
		504, 446,
		505, 433,
		498, 423,
		484, 421,
		463, 440,
		459, 436,
		498, 372,
		454, 360,
		444, 393,
		435, 409,
		418, 411,
		426, 384,
		440, 383,
		466, 286,
		464, 265,
		486, 230,
		497, 190,
		500, 144,
		492, 99,
		465, 73,
		425, 57,
		395, 55,
		371, 61,
		346, 77,
		326, 96,
		312, 123,
		310, 152,
		310, 191,
		326, 224,
		337, 242,
		343, 256,
		333, 259,
		329, 248,
		319, 237,
		304, 236,
		291, 243,
		280, 239,
		285, 221,
		287, 199,
		285, 180,
		279, 150,
		270, 130,
		241, 95,
		219, 85,
		192, 80,
		144, 79,
		105, 85,
		65, 108,
		40, 138,
		22, 173,
		24, 239,
		39, 298,
		57, 333,
		68, 357,
		61, 370,
		78, 419,
		71, 423,
		56, 367,
		46, 340,
		8, 370,
		52, 460,
		54, 473,
		45, 472,
		39, 483,
		36, 497,
		36, 524,
		37, 566,
		50, 575,
		32, 598,
		25, 656,
		23, 834,
		33, 844,
		48, 843,
		67, 837,
		67, 775,
		185, 833,
		183, 905,
		295, 907,
		297, 834,
		417, 775
	};

	limits_background.add(App->physics->CreateChain(0, 0, Background, 180, "static", 0x0001, 0x0004));

	// Creating launcher -------------------------

	int launcher[24] = {
		476, 635,
		476, 817,
		481, 820,
		487, 822,
		495, 822,
		502, 820,
		507, 817,
		507, 634,
		512, 634,
		511, 825,
		470, 825,
		470, 634
	};

	limits_background.add(App->physics->CreateChain(0, 0, launcher, 24, "static", 0x0001, 0x0004));

	// Creating map -------------------------

	int left_up_curve[30] = {
		143, 127,
		122, 130,
		108, 138,
		91, 151,
		79, 166,
		74, 181,
		72, 194,
		64, 194,
		64, 182,
		70, 168,
		81, 149,
		92, 137,
		111, 127,
		130, 118,
		142, 117
	};

	limits_background.add(App->physics->CreateChain(0, 0, left_up_curve, 30, "static", 0x0001, 0x0004));

	int right_up_curve[34] = {
		178, 118,
		178, 127,
		194, 127,
		209, 131,
		221, 140,
		230, 146,
		235, 156,
		242, 172,
		243, 189,
		248, 191,
		253, 187,
		249, 171,
		244, 156,
		235, 141,
		223, 131,
		207, 121,
		189, 119
	};

	limits_background.add(App->physics->CreateChain(0, 0, right_up_curve, 34, "static", 0x0001, 0x0004));

	int left_bottom_piece[18] = {
		170, 773,
		76, 728,
		66, 717,
		65, 645,
		73, 634,
		73, 696,
		80, 710,
		94, 722,
		169, 756
	};

	limits_background.add(App->physics->CreateChain(0, 0, left_bottom_piece, 18, "static", 0x0001, 0x0004));

	int right_bottom_piece[26] = {
		310, 757,
		315, 776,
		342, 763,
		391, 739,
		419, 722,
		417, 704,
		418, 644,
		410, 636,
		410, 693,
		404, 709,
		386, 725,
		356, 737,
		323, 753
	};

	limits_background.add(App->physics->CreateChain(0, 0, right_bottom_piece, 26, "static", 0x0001, 0x0004));

	int mill[46] = {
		375, 188,
		365, 168,
		364, 141,
		372, 127,
		383, 116,
		398, 109,
		420, 111,
		437, 115,
		447, 127,
		454, 141,
		457, 157,
		453, 169,
		444, 185,
		431, 196,
		426, 201,
		423, 184,
		424, 171,
		418, 157,
		407, 151,
		395, 152,
		388, 158,
		382, 170,
		380, 176
	};

	limits_background.add(App->physics->CreateChain(0, 0, mill, 46, "static", 0x0001, 0x0004));

	int iron_piece[34] = {
		108, 292,
		103, 298,
		105, 303,
		111, 305,
		117, 299,
		133, 286,
		112, 264,
		130, 232,
		177, 274,
		184, 263,
		160, 238,
		142, 227,
		127, 228,
		117, 238,
		111, 247,
		110, 262,
		110, 282
	};

	limits_background.add(App->physics->CreateChain(0, 0, iron_piece, 34, "static", 0x0001, 0x0004));

	int Paddle_Left[20] = {
		111, 676,
		111, 624,
		116, 620,
		119, 624,
		124, 634,
		153, 695,
		150, 701,
		133, 694,
		116, 686,
		111, 683
	};

	limits_background.add(App->physics->CreateChain(0, 0, Paddle_Left, 20, "static", 0x0001, 0x0004));
	left_flopper_body = limits_background.getLast()->data;

	int Paddle_Right[18] = {
		366, 622,
		330, 698,
		332, 702,
		337, 702,
		347, 697,
		371, 685,
		373, 682,
		373, 626,
		370, 622
	};

	limits_background.add(App->physics->CreateChain(0, 0, Paddle_Right, 18, "static", 0x0001, 0x0004));
	right_flopper_body = limits_background.getLast()->data;

	int bridge1[18] = {
		192, 210,
		190, 212,
		178, 212,
		174, 210,
		172, 179,
		175, 173,
		189, 170,
		191, 176,
		191, 203
	};

	int bridge2[18] = {
		252, 210,
		251, 212,
		235, 212,
		233, 210,
		233, 179,
		236, 173,
		250, 170,
		252, 176,
		252, 203
	};

	limits_background.add(App->physics->CreateChain(0, 0, bridge1, 18, "static", 0x0001, 0x0004));
	limits_background.add(App->physics->CreateChain(0, 0, bridge2, 18, "static", 0x0001, 0x0004));
}

void CreatePolygon(int x, int y, int* points, int size, float density, uint16 category, uint16 mask);

void ModuleSceneIntro::Create_Kickers()
{
	int left_flopper_vertices[8] = {
		0, 7,
		0, -7,
		48, -2,
		48, 2
	};

	int right_flopper2_vertices[8] = {
		0, 7,
		0, -7,
		-48, -2,
		-48, 2
	};

	int left_flopper_vertices2[8] = {
		0, 7,
		0, -7,
		48, -2,
		48, 2
	};

	int right_flopper2_vertices2[8] = {
		0, 7,
		0, -7,
		-48, -2,
		-48, 2
	};

	left_flopper = App->physics->CreatePolygon(180, 768, left_flopper_vertices, 8, 1.0f, 0x0001, 0x0004);
	PhysBody* B = App->physics->CreateCircle(180, 768, 7, "static", 0x0001, 0x0004);
	rev_joint_left = App->physics->CreateRevoluteJoint(left_flopper, B, 0, 0, -5, -15, 15);

	right_flopper2 = App->physics->CreatePolygon(305, 768, right_flopper2_vertices, 8, 1.0f, 0x0001, 0x0004);
	PhysBody* B2 = App->physics->CreateCircle(305, 768, 7, "static", 0x0001, 0x0004);
	rev_joint_right = App->physics->CreateRevoluteJoint(right_flopper2, B2, 0, 0, -180, 165, 200);

	left_flopper2 = App->physics->CreatePolygon(69, 367, left_flopper_vertices2, 8, 1.0f, 0x0001, 0x0004);
	PhysBody* B3 = App->physics->CreateCircle(69, 367, 7, "static", 0x0001, 0x0004);
	rev_joint_left2 = App->physics->CreateRevoluteJoint(left_flopper2, B3, 0, 0, -10, -55, -25);

	right_flopper2 = App->physics->CreatePolygon(450, 510, right_flopper2_vertices2, 8, 1.0f, 0x0001, 0x0004);
	PhysBody* B4 = App->physics->CreateCircle(450, 510, 7, "static", 0x0001, 0x0004);
	rev_joint_right2 = App->physics->CreateRevoluteJoint(right_flopper2, B4, 0, 0, -180, 225, 255);
}

void ModuleSceneIntro::Draw_Kickers()
{
	SDL_Rect section1;
	section1.x = 68;
	section1.y = 450;
	section1.h = 21;
	section1.w = 62;

	App->renderer->Blit(spritesheet, 255, 760, &section1, 1.0f, (-rev_joint_right->GetJointAngle() * RADTODEG) + 180, 50, 15);

	SDL_Rect section2;
	section2.x = 95;
	section2.y = 855;
	section2.h = 21;
	section2.w = 62;

	App->renderer->Blit(spritesheet, 168, 760, &section2, 1.0f, (-rev_joint_left->GetJointAngle() * RADTODEG), 10, 15);

	SDL_Rect section3;
	section3.x = 68;
	section3.y = 450;
	section3.h = 21;
	section3.w = 62;

	App->renderer->Blit(spritesheet, 400, 505, &section3, 1.0f, (-rev_joint_right2->GetJointAngle() * RADTODEG) + 185, 50, 10);

	SDL_Rect section4;
	section4.x = 95;
	section4.y = 855;
	section4.h = 21;
	section4.w = 62;

	App->renderer->Blit(spritesheet, 55, 362, &section4, 1.0f, (-rev_joint_left2->GetJointAngle() * RADTODEG) + 5, 10, 10);
}

void ModuleSceneIntro::Check_Area()
{
	if (!on_tunnel)
		tunnel_finish->body->SetActive(false);
	else
		tunnel_finish->body->SetActive(true);

	if (on_tunnel)
	{
		p2List_item<PhysBody*>* items = limits_background.getFirst();
		left_tunnel2->body->SetActive(false);
		tunnel->body->SetActive(true);
		tunnel_2_1->body->SetActive(false);
		tunnel_2_2->body->SetActive(false);
		rev_joint_left2->GetBodyA()->SetActive(false);
		rev_joint_left2->GetBodyB()->SetActive(false);

		while (items != nullptr)
		{
			items->data->body->SetActive(false);
			items = items->next;
		}
	}
	else if (on_top)
	{
		p2List_item<PhysBody*>* items = limits_background.getFirst();
		tunnel->body->SetActive(false);
		tunnel_2_1->body->SetActive(true);
		tunnel_2_2->body->SetActive(true);
		rev_joint_left2->GetBodyA()->SetActive(true);
		rev_joint_left2->GetBodyB()->SetActive(true);

		while (items != nullptr)
		{
			items->data->body->SetActive(false);
			items = items->next;
		}
	}
	else if (on_canon)
	{
		p2List_item<PhysBody*>* items = limits_background.getFirst();
		tunnel->body->SetActive(false);
		rev_joint_right2->GetBodyA()->SetActive(false);

		while (items != nullptr)
		{
			items->data->body->SetActive(false);
			items = items->next;
		}
	}
	else
	{
		p2List_item<PhysBody*>* items = limits_background.getFirst();
		left_tunnel2->body->SetActive(true);
		tunnel->body->SetActive(false);
		tunnel_2_1->body->SetActive(false);
		tunnel_2_2->body->SetActive(false);
		rev_joint_left2->GetBodyA()->SetActive(true);
		rev_joint_left2->GetBodyB()->SetActive(true);
		rev_joint_right2->GetBodyA()->SetActive(true);

		while (items != nullptr)
		{
			items->data->body->SetActive(true);
			items = items->next;
		}
	}
}

void ModuleSceneIntro::Draw_Lights()
{
	//up hole lights
	for (int i = 1; i < up_hole_hit + 1; i++) {
		switch (i)
		{
		case 1:
		{
			SDL_Rect r;

			r.x = 245;
			r.y = 665;
			r.w = 18;
			r.h = 18;

			App->renderer->Blit(spritesheet, 272, 281, &r);
			break;
		}
		case 2:
		{
			SDL_Rect r;

			r.x = 271;
			r.y = 671;
			r.w = 18;
			r.h = 18;

			App->renderer->Blit(spritesheet, 298, 288, &r);
			break;
		}

		case 3:
		{
			SDL_Rect r;

			r.x = 297;
			r.y = 665;
			r.w = 18;
			r.h = 18;

			App->renderer->Blit(spritesheet, 324, 281, &r);
			break;
		}
		}
	}

	//chip loop lights
	for (int i = 1; i <= chip_lights_on; i++) {
		switch (i)
		{
		case 1:
		{
			SDL_Rect r;

			r.x = 3;
			r.y = 595;
			r.w = 32;
			r.h = 32;

			App->renderer->Blit(spritesheet, 30, 211, &r);
			break;
		}
		case 2:
		{
			SDL_Rect r;

			r.x = 9;
			r.y = 631;
			r.w = 32;
			r.h = 32;

			App->renderer->Blit(spritesheet, 36, 247, &r);
			break;
		}

		case 3:
		{
			SDL_Rect r;

			r.x = 21;
			r.y = 665;
			r.w = 32;
			r.h = 32;

			App->renderer->Blit(spritesheet, 48, 281, &r);
			break;
		}

		case 4:
		{
			SDL_Rect r;

			r.x = 37;
			r.y = 699;
			r.w = 32;
			r.h = 32;

			App->renderer->Blit(spritesheet, 62, 313, &r);
			break;
		}
		}
	}

	//middle hole lights
	for (int i = 1; i <= middle_hole_hit; i++)
	{
		switch (i) {
		case 1:
		{
			SDL_Rect r;

			r.x = 629;
			r.y = 624;
			r.w = 37;
			r.h = 37;

			App->renderer->Blit(spritesheet, 189, 452, &r);
			break;
		}
		case 2:
		{
			SDL_Rect r;

			r.x = 664;
			r.y = 632;
			r.w = 37;
			r.h = 37;

			App->renderer->Blit(spritesheet, 225, 461, &r);
			break;
		}
		case 3:
		{
			SDL_Rect r;

			r.x = 697;
			r.y = 624;
			r.w = 37;
			r.h = 37;

			App->renderer->Blit(spritesheet, 258, 452, &r);
			break;
		}
		}
	}

	//color_circles lights
	for (int i = 0; i <= color_circles; i++)
	{
		switch (i) {
		case 0:
		{
			SDL_Rect r;

			r.x = 278;
			r.y = 286;
			r.w = 30;
			r.h = 30;

			App->renderer->Blit(spritesheet, 227, 683, &r);
			break;
		}
		case 1:
		{
			SDL_Rect r;

			r.x = 307;
			r.y = 275;
			r.w = 28;
			r.h = 30;

			App->renderer->Blit(spritesheet, 255, 672, &r);
			break;
		}
		case 2:
		{
			SDL_Rect r;

			r.x = 296;
			r.y = 244;
			r.w = 30;
			r.h = 30;

			App->renderer->Blit(spritesheet, 244, 641, &r);
			break;
		}
		case 3:
		{
			SDL_Rect r;

			r.x = 262;
			r.y = 244;
			r.w = 30;
			r.h = 30;

			App->renderer->Blit(spritesheet, 211, 642, &r);
			break;
		}
		case 4:
		{
			SDL_Rect r;

			r.x = 251;
			r.y = 275;
			r.w = 30;
			r.h = 30;

			App->renderer->Blit(spritesheet, 198, 672, &r);
			break;
		}
		}
	}


	//Drawong arrows permanently on
	App->renderer->Blit(spritesheet, 58, 429, &arrow_tunel2_left.GetCurrentFrame());
	App->renderer->Blit(spritesheet, 412, 429, &arrow_tunel2_right.GetCurrentFrame());
	App->renderer->Blit(spritesheet, 191, 228, &blue_arrow_top.GetCurrentFrame());
	App->renderer->Blit(spritesheet, 379, 211, &monster_arrow.GetCurrentFrame());
	App->renderer->Blit(spritesheet, 69, 480, &map_arrows.GetCurrentFrame());
	App->renderer->Blit(spritesheet, 377, 236, &yellow_arrows.GetCurrentFrame());

	//Drawong different down lights
	App->renderer->Blit(spritesheet, 40, 608, &down_lights.GetCurrentFrame());
	App->renderer->Blit(spritesheet, 88, 614, &down_lights.GetCurrentFrame());
	App->renderer->Blit(spritesheet, 375, 614, &down_lights.GetCurrentFrame());
	App->renderer->Blit(spritesheet, 423, 608, &down_lights.GetCurrentFrame());
}