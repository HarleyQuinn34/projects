#include <stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include<iostream>
using namespace std;
const int PACSIZE = 20;
const float FPS = 60;
const int SCREEN_W = 570;
const int SCREEN_H = 615;
const int BOUNCER_SIZE = 60;
enum dir {
	UP, DOWN, LEFT, 
	RIGHT
};
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int wallCollide(int x, int y, int dir, int level[21][21]);

int main(int argc, char **argv) {
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *bouncer2 = NULL; 
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP*wall = NULL;
	//ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *sample2Instance = NULL;
	ALLEGRO_BITMAP*dots = NULL;


	cout << "FLEGIN" << endl;
	int bouncer_x = 305 - BOUNCER_SIZE / 2;
	int bouncer_y = 280 - BOUNCER_SIZE / 2;
	float bouncer_dx = -4.0, bouncer_dy = 4.0;

	float bouncer2_x = SCREEN_W / 4.0 - BOUNCER_SIZE / 2.0;
	float bouncer2_y = SCREEN_H / 4.0 - BOUNCER_SIZE / 2.0;
	float bouncer2_dx = -2.0, bouncer2_dy = 4.0;

	bool key[4] = { false, false, false, false };
	bool key2[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	
	timer = al_create_timer(1.0 / FPS);
	display = al_create_display(SCREEN_W, SCREEN_H);
	al_reserve_samples(2);
	sample2 = al_load_sample("pac.wav");
	//sample = al_load_sample("oof.wav");

	sample2Instance = al_create_sample_instance(sample2);
	al_set_sample_instance_playmode(sample2Instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(sample2Instance, al_get_default_mixer());
	al_play_sample_instance(sample2Instance);

	dots = al_create_bitmap(5, 5);
	al_set_target_bitmap(dots);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	//////////////////////
	wall = al_create_bitmap(30, 30);////////////////////wall size
	al_set_target_bitmap(wall);
	al_clear_to_color(al_map_rgb(128, 0, 0));
	/////////////////////////////////
	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	bouncer2 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);

	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(255, 255, 0));
	al_set_target_bitmap(bouncer2);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);
	int level[21][21] = {
		1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,
		1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,1,0,0,1,1,1,1,1,0,0,1,1,1,0,1,
		1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,
		1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
		1,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,
		1,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,1,1,1,0,1,
		1,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,1,
		1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,1,
		1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,0,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1, };
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++)
			cout << level[i][j];
		cout << endl;

	}


	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			if (key[KEY_UP] && bouncer_y >= 4.0) {
				bouncer_y -= 4.0;
			}

			if (key[KEY_DOWN] && bouncer_y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
				bouncer_y += 4.0;
			}

			//go right
			
			if (key[KEY_RIGHT] && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
				bouncer_x += 4.0;
			}

			if (key[KEY_LEFT] && bouncer_x > 4) {
				bouncer_x -= 4.0;
			}
			if (level[bouncer_x / 30][bouncer_y / 30] == 0) {
				level[bouncer_x / 30][bouncer_y / 30] = 2;
			}
			redraw = true;
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


			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;

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

				/*case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;*/
			}
		}




		//render section//////////////////////////////////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_filled_circle(bouncer_x, bouncer_y, 15, al_map_rgb(255, 255, 0));


			for (int i = 0; i < 21; i++)
				for (int j = 0; j < 21; j++) {
					if (level[i][j] == 1)
						al_draw_bitmap(wall, i * 30, j * 30, 0);
					if (level[i][j] == 0)
						al_draw_bitmap(dots, i * 30+10, j * 30+10, 0);

				}
			al_flip_display();
		}
	}


	al_destroy_bitmap(bouncer);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


	return 0;
}

bool pixelCollision(int x1, int y1, int x2, int y2) {

	if (pixelCollision(x1, y1, x2, y2) == true);
	/*if (key[3] && !wallCollide(bouncer_x, bouncer_y, RIGHT, wall)) {
		bouncer_x += 4.0;
	}*/
	return false;



}
int wallCollide(int x, int y, int dir, int level[21][21]) {
	int x1;
	int x2;
	int x3;
	int y1;
	int y2;
	int y3;
	if (dir == RIGHT) { 		// Moving Right
								// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		x1 = x + 5 + PACSIZE;
		x2 = x + 5 + PACSIZE;
		x3 = x + 5 + PACSIZE;
		// Check at three point along that edge
		y1 = y;
		y2 = y +PACSIZE / 2;
		y3 = y +PACSIZE;
		if ((level[x1 / 30][y1 / 30] == 1) || (level[x2 / 30][y2 / 30] == 1) || (level[x3 / 30][y3 / 30] == 1)) {
	}
		cout << "right collision" << endl;
		return 1;

	}
	else {
		return 0;

	}
	if (dir == LEFT) { 		// Moving Right
								// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		x1 = x - 3;
		x2 = x - 3;
		x3 = x - 3;
		y1 = y;
		y2 = y + PACSIZE / 2;
		y3 = y + PACSIZE;
	}
	if ((level[x1 / 30][y1 / 30] == 1) || (level[x2 / 30][y2 / 30] == 1) || (level[x3 / 30][y3 / 30] == 1)) {
	}
	else {
		return 0;
	}
	if (dir == UP) { 		// Moving Right
							// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		x1 = x;
		x2 = x + PACSIZE / 2;
		x3 = x + PACSIZE;
		y1 = y - 5;
		y2 = y - 5;
		y3 = y - 5;
	}
	if ((level[x1 / 30][y1 / 30] == 1) || (level[x2 / 30][y2 / 30] == 1) || (level[x3 / 30][y3 / 30] == 1)) {
	}
	else {
		return 0;
	}
	if (dir == DOWN) { 		// Moving Right
		x1 = x;
		x2 = x + PACSIZE / 2;
		x3 = x + PACSIZE;
		y1 = y + PACSIZE + 5;
		y2 = y + PACSIZE + 5;
		y3 = y + PACSIZE + 5;
	}
	if ((level[x1 / 30][y1 / 30] == 1) || (level[x2 / 30][y2 / 30] == 1) || (level[x3 / 30][y3 / 30] == 1)) {
	}
	else {
		return 0;
	}
}
 