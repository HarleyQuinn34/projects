#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include<iostream>
using namespace std;


const float FPS = 60;
const int SCREEN_W = 900;
const int SCREEN_H = 500;
const int BOUNCER_SIZE = 32;
int worldWidth = 4128;
int worldHeight = 3754;
int cameraX = 0;
int cameraY = 0;
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *map = NULL;
	//float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
	//float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;

	float bouncer_x = 2606 + SCREEN_W;
	float bouncer_y = 574 + SCREEN_W;

	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;
	bool onEdge = false;


	al_init();

	al_init_image_addon();

	al_install_keyboard();
	map = al_load_bitmap("ff1.png");

	timer = al_create_timer(1.0 / FPS);


	display = al_create_display(SCREEN_W, SCREEN_H);


	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);


	al_set_target_bitmap(bouncer);

	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			cameraX = bouncer_x - SCREEN_W / 2;
			cameraY = bouncer_y - SCREEN_H / 2;

			if (key[KEY_UP] && bouncer_y < worldHeight + 32) {
				bouncer_y -= 4.0;
			}

			if (key[KEY_DOWN] && bouncer_y < worldHeight - 32) {
				bouncer_y += 4.0;
			}

			if (key[KEY_LEFT] && bouncer_x < worldWidth - 32) {
				bouncer_x -= 4.0;
			}

			if (key[KEY_RIGHT] && bouncer_x < worldWidth - 32) {
				bouncer_x += 4.0;
			}

			redraw = true;
			cout << "onedge is " << onEdge << endl;
			//left
			if (cameraX < 0) {
				cameraX = 0;
				onEdge = true; 
			}
			else 
				onEdge = false;


			//top
			if (cameraY < 0) {
				cameraY = 0;
				onEdge = true;
			}
			else
				onEdge = false;


			//right
			if (cameraX > worldWidth - SCREEN_W) { 
				cameraX = worldWidth - SCREEN_W;
				onEdge = true;
			}
			else
				onEdge = false;

			//bottom
			if (cameraY > worldHeight - SCREEN_H) {
				cameraY = worldHeight - SCREEN_H;
				onEdge = true;
			}
			else
				onEdge = false;
			}

			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = true;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
				}
			}

			if (redraw && al_is_event_queue_empty(event_queue)) {
				redraw = false;

				al_clear_to_color(al_map_rgb(0, 0, 0));

				//this draws your map
				al_draw_bitmap(map, -cameraX, -cameraY, 0);

				//if you're not on the edge, draw the player in the middle!
			if (onEdge == false)
				al_draw_bitmap(bouncer, SCREEN_W / 2, SCREEN_H / 2, 0);
			else//otherwise let him move!
				al_draw_bitmap(bouncer, bouncer_x - cameraX, bouncer_y - cameraY, 0);


				al_flip_display();
			}
		}

		al_destroy_bitmap(bouncer);
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);

		return 0;
	}