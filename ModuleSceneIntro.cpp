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

	background = App->textures->Load("/Sprites/Background.png");
	tunnel1 = App->textures->Load("/Sprites/T1.png");
	tunnel2 = App->textures->Load("/Sprites/T2.png");
	spritesheet = App->textures->Load("/Sprites/sprites.png");


	//Audio

	fx_flopper = App->audio->LoadFx("FX/Paddle_sound.ogg");
	fx_collision = App->audio->LoadFx("FX/Contact_sound.ogg");
	fx_kickers = App->audio->LoadFx("FX/Kickers_sound.ogg");
	fx_gameover = App->audio->LoadFx("FX/Lose.ogg");
	fx_saverhit = App->audio->LoadFx("FX/Hit_Saver.ogg");
	fx_cannon = App->audio->LoadFx("FX/canon_shot.ogg");
	fx_explosion = App->audio->LoadFx("FX/hiting_monster.ogg");
	fx_chiploop = App->audio->LoadFx("FX/chip_loop.ogg");
	fx_victory = App->audio->LoadFx("FX/Win.wav");


	//Sensors on tunnels

	tunnel_beginning = App->physics->CreateRectangleSensor(135, 261, 20, 1);
	tunnel_finish = App->physics->CreateRectangleSensor(90, 640, 20, 1);
	left_tunnel2 = App->physics->CreateRectangleSensor(42, 400, 10, 1);
	right_tunnel2 = App->physics->CreateRectangleSensor(460, 400, 10, 1);
	right_hole = App->physics->CreateRectangleSensor(480, 450, 2, 2);


	//Playability sensors

	midpoint = App->physics->CreateRectangleSensor(239, 440, 5, 1);
	up_hole = App->physics->CreateRectangleSensor(308, 247, 5, 1);
	cannon_senson = App->physics->CreateRectangleSensor(490, 600, 5, 1);
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

	left_flopper.PushBack({ 477, 237, 42, 80 });
	left_flopper.PushBack({ 529, 237, 42, 80 });
	left_flopper.speed = 0.08f;
	left_flopper.loop = true;

	right_flopper.PushBack({ 581, 237, 42, 80 });
	right_flopper.PushBack({ 633, 237, 42, 80 });
	right_flopper.speed = 0.08f;
	right_flopper.loop = true;

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

	//Win

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
			ball = App->physics->CreateCircle(490, 800, 15, "static", 0x0004);
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

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) App->audio->PlayFx(kickers_fx);

	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// Draw paddles -----------------------------------------------------------------

	App->renderer->Blit(sprites, 112, 620, &paddle_left.GetCurrentFrame());
	App->renderer->Blit(sprites, 330, 620, &paddle_right.GetCurrentFrame());

	//Draw middle hole lights
	Draw_Lights();

	//Draw ball saver
	SDL_Rect saver;
	saver.x = 113;
	saver.y = 383;
	saver.w = 32;
	saver.h = 42;

	App->renderer->Blit(sprites, 30, 772, &saver);
	App->renderer->Blit(sprites, 422, 772, &saver);

	// Draw white mid --------------------------------------------------------------------
	if (white_mid.Finished())
	{
		mid_hitted = false;
		white_mid.Reset();
	}
	else if (mid_hitted)
		App->renderer->Blit(sprites, 125, 270, &white_mid.GetCurrentFrame());

	if (middle_hole_hit < 3)
	{
		right_hole->body->SetActive(false);

		SDL_Rect section;
		section.x = 757;
		section.y = 220;
		section.w = 41;
		section.h = 41;

		App->renderer->Blit(sprites, 470, 420, &section);
	}
	else
	{
		right_hole->body->SetActive(true);
	}

	// Draw kickers -----------------------------------------------------------------
	Draw_Kickers();

	// Draw ball & tunnel ----------------------------------------------------------------

	if (on_tunnel) App->renderer->Blit(tunnels, 0, -1);
	if (on_top) App->renderer->Blit(tunnels_top, 0, -1);

	int x, y;
	if (ball != NULL)
	{
		ball->GetPosition(x, y);
		ball->body->SetTransform(b2Vec2(ball->body->GetPosition().x, ball->body->GetPosition().y), 90);

		SDL_Rect section;
		section.x = 0;
		section.y = 555;
		section.h = 31;
		section.w = 31;

		App->renderer->Blit(sprites, x - 2, y, &section, 1.0f, ball->GetRotation());
	}

	if (!on_tunnel) App->renderer->Blit(tunnels, 0, -1);
	if (!on_top) App->renderer->Blit(tunnels_top, 0, -1);

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

	// Drawing canon ---------------------------------------------------------

	if (!on_canon)
	{
		App->renderer->Blit(sprites, 455, 565, &canon.frames[0]);
		canon.Reset();
	}
	else
		App->renderer->Blit(sprites, 455, 565, &canon.GetCurrentFrame());


	//Drawing boss + explossion
	App->renderer->Blit(sprites, 365, 95, &boss.GetCurrentFrame());

	if (boss_hited)
	{
		SDL_Rect last_frame;
		last_frame.x = 617;
		last_frame.y = 85;
		last_frame.w = 58;
		last_frame.h = 52;

		App->renderer->Blit(sprites, 378, 132, &hit_boss.GetCurrentFrame());
		if (hit_boss.Finished())
		{
			boss_hited = false;
			hit_boss.Reset();
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
	SDL_Rect section5;
	section5.x = 680;
	section5.y = 188;
	section5.h = 23;
	section5.w = 65;

	App->renderer->Blit(sprites, 340, 48, &section5, 1.0f, 0, 50, 15);

	// Draw Arrow ------------------------------------------------------
	if (middle_hole_hit < 3) App->renderer->Blit(sprites, 227, 338, &arrow.GetCurrentFrame());
	else App->renderer->Blit(sprites, 475, 400, &arrow.GetCurrentFrame());

	// Win, game over, playing -----------------------------------------
	if (gameover)
	{
		color_circles = 0;
		App->renderer->Blit(sprites, 0, 0, &game_over.GetCurrentFrame());
	}
	if (color_circles == 4)
	{
		winning = true;
		App->renderer->Blit(sprites, 0, 0, &win.GetCurrentFrame());
		if (!played)
		{
			App->audio->PlayFx(win_fx);
			played = true;
		}
	}


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
