#include<allegro5\allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
using namespace std;

//GLOBALS and constants
const int WIDTH = 720;
const int HEIGHT = 720;
bool keys[] = { false, false, false, false, false, false, false, false };
enum KEYS { UP, DOWN, LEFT, RIGHT, W, S, A, D };


int main(void)
{
	//game variables
	bool done = false;
	bool render = false;

	//allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *square = NULL;
	ALLEGRO_BITMAP *square2 = NULL;

	//player vaiables
	float square_x = 50;
	float square_y = 50;
	float dx = 0;
	float dy = 0;

	float square2_x = 100;
	float square2_y = 50;
	float dx2 = 0;
	float dy2 = 0;
	// to keep track if the player can jump again so he doesn't perform another jump midair
	bool mayJumpAgain = false;
	bool mayJumpAgain2 = false;

	// is true if the player is on the ground
	bool isOnSolidGround = false;
	bool isOnSolidGround2 = false;



	//program setup
	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	//set up player
	square = al_create_bitmap(32, 32);
	al_set_target_bitmap(square);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	square2 = al_create_bitmap(32, 32);
	al_set_target_bitmap(square2);
	al_clear_to_color(al_map_rgb(255, 255, 255));


	//set up game stuff: display, event queue, timer, etc.
	display = al_create_display(WIDTH, HEIGHT);

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_set_target_bitmap(al_get_backbuffer(display));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	//GAME LOOP
	while (!done)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		//Keyboard Section////////////////////////////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)

		{
			cout << "key pressed";
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;

			case ALLEGRO_KEY_W:
				keys[W] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = true;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;

			case ALLEGRO_KEY_W:
				keys[W] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = false;
				break;


			}
		}
		//TIMER SECTION/////////////////////////////////////////////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			cout << "may jump is " << mayJumpAgain << ", solid ground is " << isOnSolidGround << endl;
			//player movement


			//stop falling when you hit the bottom.
			//ADD CODE: if player goes below the bottom of the screen, 
			//reset his position so he's standing on the bottom of the screen, 
			//set isOnSolidGround true
			//and set y velocity to 0
			//otherwise, isOnsolidGround is false.
			if (square_y+32 > HEIGHT) {
				square_y = HEIGHT-32;
				isOnSolidGround = true;
				dy = 0;

			}
			else
				isOnSolidGround = false;

			if (square2_y + 32 > HEIGHT) {
				square2_y = HEIGHT - 32;
				isOnSolidGround2 = true;
				dy2 = 0;

			}
			else
				isOnSolidGround2 = false;
			//here's my check to stop my square from walking off the window (left, right, and top sides)
			if (square_x > WIDTH - 30)
				square_x = WIDTH - 30;
			if (square_x < 0)
				square_x = 0;
			if (square_y < 0)
				square_y = 0;

			if (square2_x > WIDTH - 30)
				square2_x = WIDTH - 30;
			if (square2_x < 0)
				square2_x = 0;
			if (square2_y < 0)
				square2_y = 0;

			//JUMPING
			//if the up button is pressed

			//ADD CODE
			//if the up button has been pressed AND the mayJumpAgain is true AND the //player is on solid ground, set y velocity to some nonzero number and //mayJumpAgain to false.
			//otherwise, set mayJumpagain to true


			//left
			if (keys[UP] && mayJumpAgain == true && isOnSolidGround == true) {
				dy = -15;
				mayJumpAgain = false;
			}
			else 
				mayJumpAgain = true;
			if (keys[LEFT]) {
				square_x -= 4.0;
			}
			//right
			if (keys[RIGHT]) {
				square_x += 4.0;
			}
//////////////////////////////////////////////////////////////////////////////////////////
			if (keys[W] && mayJumpAgain2 == true && isOnSolidGround2 == true) {
				dy2 = -15;
				mayJumpAgain2 = false;
			}
			else
				mayJumpAgain2 = true;
			if (keys[A]) {
				square2_x -= 4.0;
			}
			//right
			if (keys[D]) {
				square2_x += 4.0;
			}


			//gravity
			//if we're not on solid ground, we should be falling (remember, positive y is "down")

			//ADD CODE: if you're not on solid ground, increase y velocity by 1.
			if (isOnSolidGround == false)
				dy++;
			if (isOnSolidGround2 == false)
				dy2++;
			//ADD CODE: if your y velocity goes higher than 8, reset it to 8.
			if (dy > 8)
				dy = 8;

			if (dy2 > 8)
				dy2 = 8;




			render = true;
		}

		//here's where your box's coordinates are acutally updated
		square_x += dx; //adding the component velocities to the actual positions
		square_y += dy;
		cout << "dy is " << dy << " , square_y is " << square_y << endl;

		square2_x += dx2; //adding the component velocities to the actual positions
		square2_y += dy2;
		cout << "dy is " << dy << " , square_y is " << square2_y << endl;
		//RENDER SECTION//////////////////////////////////////////////////////////////////////
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			al_draw_bitmap(square, square_x, square_y, 0);
			al_draw_bitmap(square2, square2_x, square2_y, 0);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}//end game loop

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}