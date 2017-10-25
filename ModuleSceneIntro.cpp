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
	
	
	
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
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
