#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <stdio.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<iostream>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
//function declaration
bool PixelCollision(int x1, int y1, int w1, int hl, int x2, int y2, int w2, int h2);

using namespace std;

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int paddle1_SIZE = 32;
int score = 0;
enum MYKEYS2 {
	KEY_A, KEY_D
};

class brick {
private:
	int xpos;
	int ypos;
	bool isdead;
public:
	void initbrick(int x, int y);
	void drawbrick();
	bool brickcollision(int ballx, int bally, int ballw, int ballh);
	void kill();
	bool dead(); //added by mo
};

//
int main() {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_BITMAP *paddle2 = NULL;
	ALLEGRO_BITMAP *ball = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *sample2Instance = NULL;

	cout << "FLEGIN" << endl;
	brick b1;
	brick b2;
	brick b3;
	brick b4;
	brick b5;
	brick b6;
	brick b7;
	brick b8;
	brick b9;
	brick b10;
	brick b11;
	brick b12;
	brick b13;
	brick b14;
	brick b15;
	brick b16;
	brick b17;
	brick b18;
	brick b19;
	brick b20;

	b1.initbrick(500, 50);

	b2.initbrick(400, 50);

	b3.initbrick(300, 50);

	b4.initbrick(200, 50);

	b5.initbrick(100, 50);

	b6.initbrick(500, 100);

	b7.initbrick(400, 100);

	b8.initbrick(300, 100);

	b9.initbrick(200, 100);

	b10.initbrick(100, 100);

	b11.initbrick(500, 150);

	b12.initbrick(400, 150);

	b13.initbrick(300, 150);

	b14.initbrick(200, 150);

	b15.initbrick(100, 150);

	b16.initbrick(500, 200);

	b17.initbrick(400, 200);

	b18.initbrick(300, 200);

	b19.initbrick(200, 200);

	b20.initbrick(100, 200);


	//change these starting points
	float paddle2_x = SCREEN_W / 1.1 - paddle1_SIZE / 2.0;
	float paddle2_y = SCREEN_H / 1.1 - paddle1_SIZE / 2.0;

	float paddle2_dx = -4.0, paddle2_dy = 4.0;

	float ball_x = 200;
	float ball_y = 400;
	float ball_dx = -4.0, ball_dy = 4.0;

	//bool key[4] = { false, false, false, false };
	bool key2[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();
	timer = al_create_timer(1.0 / FPS);
	display = al_create_display(SCREEN_W, SCREEN_H);

	font = al_load_ttf_font("cubic.ttf", 20, 0);
	al_reserve_samples(2);
	sample2 = al_load_sample("8bit.wav");
	sample = al_load_sample("oof.wav");

	sample2Instance = al_create_sample_instance(sample2);
	al_set_sample_instance_playmode(sample2Instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(sample2Instance, al_get_default_mixer());
	al_play_sample_instance(sample2Instance);

	sample2Instance = al_create_sample_instance(sample);
	al_set_sample_instance_playmode(sample2Instance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(sample2Instance, al_get_default_mixer());



	paddle2 = al_create_bitmap(paddle1_SIZE, paddle1_SIZE);
	ball = al_create_bitmap(15, 15);



	al_set_target_bitmap(paddle2);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(ball);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);


	while (!doexit) {

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {//note from mo: this was in the wrong place... all physics should be *inside* the timer section
			if (ball_x < 0 || ball_x > 640 - 10) {
				ball_dx = -ball_dx;

			}


			if (ball_y < 0 || ball_y > 480 - 10) {
				ball_dy = -ball_dy;
			}
			//add the x velocity to the x position, 
			//and the y velocity to the y position
			ball_x += ball_dx;
			ball_y += ball_dy;



			//note from mo: timer section was here, moved up above

			if (key2[KEY_A]) {
				paddle2_x -= 4.0; //MO SAYS make this change the x coordinate, not the y
			}

			if (key2[KEY_D]) {
				paddle2_x += 4.0; //MO SAYS this too!
			}



			redraw = true;

			//collide ball with paddle
			if (PixelCollision(ball_x, ball_y, 15, 15, paddle2_x, paddle2_y, 100, 30)) {
				cout << "collision!";
				//sample = true;
				al_play_sample_instance(sample2Instance);
				ball_dx = -ball_dx;//reflection
				ball_dy = -ball_dy;
				// system("pause");
			}

			//do this for all yo bricks
			if (b1.dead() == false && b1.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b1.kill();

			}
			if (b2.dead() == false && b2.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b2.kill();

			}
			if (b3.dead() == false && b3.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b3.kill();

			}
			if (b4.dead() == false && b4.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b4.kill();

			}
			if (b5.dead() == false && b5.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b5.kill();

			}
			if (b6.dead() == false && b6.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b6.kill();

			}
			if (b7.dead() == false && b7.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b7.kill();
			}
			if (b8.dead() == false && b8.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b8.kill();
			}
			if (b9.dead() == false && b9.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b9.kill();
			}
			if (b10.dead() == false && b10.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b10.kill();
			}
			if (b11.dead() == false && b11.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b11.kill();

			}
			if (b12.dead() == false && b12.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b12.kill();

			}
			if (b13.dead() == false && b13.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b13.kill();

			}
			if (b14.dead() == false && b14.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b14.kill();

			}
			if (b15.dead() == false && b15.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b15.kill();

			}
			if (b16.dead() == false && b16.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b16.kill();

			}
			if (b17.dead() == false && b17.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b17.kill();
			}
			if (b18.dead() == false && b18.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b18.kill();
			}
			if (b19.dead() == false && b18.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b19.kill();
			}
			if (b20.dead() == false && b20.brickcollision(ball_x, ball_y, 32, 32) == true) {//changed to == from =
				ball_dy = -ball_dy;
				ball_dx = -ball_dx;
				b20.kill();
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_A:
				key2[KEY_A] = true;

				break;

			case ALLEGRO_KEY_D:
				key2[KEY_D] = true;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_A:
				key2[KEY_A] = false;
				break;

			case ALLEGRO_KEY_D:
				key2[KEY_D] = false;
				break;


			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;


			}
		}
		//render section//////////////////////////////////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));


			al_draw_filled_rectangle(paddle2_x, paddle2_y, paddle2_x + 100, paddle2_y + 30, al_map_rgb(255, 255, 255));
			al_draw_bitmap(ball, ball_x, ball_y, 0);


		
			if (b1.dead() == false)
				b1.drawbrick();
			if (b2.dead() == false)
			b2.drawbrick();
			if (b3.dead() == false)
			b3.drawbrick();
			if (b4.dead() == false)
			b4.drawbrick();
			if (b5.dead() == false)
			b5.drawbrick();
			if (b6.dead() == false)
			b6.drawbrick();
			if (b7.dead() == false)
			b7.drawbrick();
			if (b8.dead() == false)
			b8.drawbrick();
			if (b9.dead() == false)
			b9.drawbrick();
			if (b10.dead() == false)
			b10.drawbrick();
			if (b11.dead() == false)
			b11.drawbrick();
			if (b12.dead() == false)
			b12.drawbrick();
			if (b13.dead() == false)
			b13.drawbrick();
			if (b14.dead() == false)
			b14.drawbrick();
			if (b15.dead() == false)
			b15.drawbrick();
			if (b16.dead() == false)
			b16.drawbrick();
			if (b17.dead() == false)
			b17.drawbrick();
			if (b18.dead() == false)
			b18.drawbrick();
			if (b19.dead() == false)
			b19.drawbrick();
			if (b20.dead() == false)
			b20.drawbrick();
			al_flip_display();
		}//end render section
	}//end game loop
	al_destroy_bitmap(paddle2);
	al_destroy_bitmap(ball);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


	return 0;
}
//function definition
bool PixelCollision(int x1, int y1, int w1, int hl, int x2, int y2, int w2, int h2) {

	if ((x1 + w1 > x2) && (x2 + w2 > x1) && (y2 + h2 > y1) && (y1 + hl > y2))

		return true;

	else
		return false;
}
void brick::drawbrick() {
	al_draw_rectangle(xpos, ypos, xpos + 80, ypos + 20, al_map_rgb(rand(), rand(), rand()), 5);
}

void brick::initbrick(int x, int y) {

	xpos = x;
	ypos = y;
	isdead = false;
}
bool brick::brickcollision(int ballx, int bally, int ballw, int ballh) {

	if ((xpos + 100 > ballx) && (ballx + 32 > xpos) && (bally + 32 > ypos) && (ypos + 32 > bally))

		return true;

	else
		return false;
}

//added by mo
bool brick::dead() {

	return isdead;

}

void  brick::kill() {

	isdead = true;


}