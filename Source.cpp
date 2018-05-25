#include <stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include<iostream>
#include<allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>//sets up allegro to write words

#include <allegro5/allegro_ttf.h>//sets up allegro to import cool fonts
using namespace std;
const int PACSIZE = 20;
const float FPS = 60;
const int SCREEN_W =800;
const int SCREEN_H = 800;
//const int pacman_SIZE = 60;

//put ghost class here
class ghost{
public:
void initghost(int x, int y, char c, int dir);
void drawghost();
void chase(int x, int y, int field[19][21]);
void chase2(int x, int y, int field[19][21]);
void chase3(int x, int y, int field[19][21]);
void chase4(int x, int y, int field[19][21]);
int xpos;
int ypos;
private:
	
	char color;
	int direction;
};
bool PixelCollision(int x1, int y1, int w1, int hl, int x2, int y2, int w2, int h2);
int score = 0;


enum dir {
	UP, DOWN, LEFT,
	RIGHT
};
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int wallCollide(int x, int y, int dir, int level[19][21]);

int main(int argc, char **argv) {
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *pacman = NULL;
	ALLEGRO_BITMAP *pacman2 = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP*wall = NULL;
	//ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *sample2Instance = NULL;
	ALLEGRO_BITMAP*dots = NULL;
	ALLEGRO_BITMAP*dino = NULL;
	ALLEGRO_FONT *font = NULL;

	cout << "FLEGIN" << endl;
	int pacman_x = 305 - PACSIZE / 2;
	int pacman_y = 250 - PACSIZE / 2;
	float pacman_dx = -4.0, pacman_dy = 4.0;

	float pacman2_x = SCREEN_W / 4.0 - PACSIZE / 2.0;
	float pacman2_y = SCREEN_H / 4.0 - PACSIZE / 2.0;
	float pacman2_dx = -2.0, pacman2_dy = 4.0;

	int lives = 3;

	bool key[4] = { false, false, false, false };
	bool key2[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_init_font_addon();

	al_init_ttf_addon();
	timer = al_create_timer(1.0 / FPS);
	display = al_create_display(SCREEN_W, SCREEN_H);
	al_reserve_samples(2);
	sample2 = al_load_sample("pac.wav");
	font=al_load_ttf_font("dab.ttf", 72, 0);

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
	pacman = al_create_bitmap(PACSIZE, PACSIZE);
	pacman2 = al_create_bitmap(PACSIZE, PACSIZE);
	

	al_set_target_bitmap(pacman);
	al_clear_to_color(al_map_rgb(255, 255, 0));
	al_set_target_bitmap(pacman2);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
//splash screen
	dino = al_load_bitmap("dino.jpg");
	al_draw_bitmap(dino, 50, 50, 0);
	/*if (score=
	dino = al_load_bitmap("dino.jpg");
	al_draw_bitmap(dino, 50, 50, 0);*/
	al_flip_display();
	al_rest(1);

	ghost boi;
	boi.initghost(50, 200, 'r', UP);
	ghost yee;
	yee.initghost(350, 20, 'b', RIGHT);
	ghost dp;
	dp.initghost(35, 20, 'o', LEFT);
	ghost bm;
	bm.initghost(350, 200, 'p', DOWN);
	////////add 3 more^

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);
	int dotcounter = 0;
	int level[19][21] = {
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
		for (int j = 0; j < 21; j++) {
			cout << level[i][j];
			if(level[i][j]==0)
			dotcounter++;
		}
		cout << endl;

	}
	cout << "you have " << dotcounter << " dots" << endl;
	
	//create your ghosts


	while (lives>0 && score<256)
	{
		if (lives <= 0)
			doexit = true;
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (PixelCollision(pacman_x, pacman_y, 20, 20, boi.xpos, boi.ypos, 20, 20)) {
				pacman_x = 50;
				pacman_y = 50;
				lives--;
			
			}
			if (PixelCollision(pacman_x, pacman_y, 20, 20, yee.xpos, yee.ypos, 20, 20)) {
				pacman_x = 50;
				pacman_y = 50;
				lives--;

			}
			if (PixelCollision(pacman_x, pacman_y, 20, 20, dp.xpos, dp.ypos, 20, 20)) {
				pacman_x = 50;
				pacman_y = 50;
				lives--;

			}
			if (PixelCollision(pacman_x, pacman_y, 20, 20, bm.xpos, bm.ypos, 20, 20)) {
				pacman_x = 50;
				pacman_y = 50;
				lives--;

			}
			//call ghost chase
			boi.chase2(pacman_x+55, pacman_y+40, level);
			yee.chase2(pacman_x+15, pacman_y, level);
			dp.chase2(pacman_x+50, pacman_y+10, level);
			bm.chase2(yee.xpos, yee.ypos, level);

			//warp Zones!
			//cout << pacman_x << " , " << pacman_y << endl;
			if (pacman_x < -17)
				pacman_x = 567;
		if (pacman_x > 567)
				pacman_x = -17;
			//check if he goes off right side of screen, reset to left side

			if (key[KEY_UP] && !wallCollide(pacman_x, pacman_y, UP, level)) {
				pacman_y -= 4.0;
			}

			if (key[KEY_DOWN] && !wallCollide(pacman_x, pacman_y, DOWN, level)) {
				pacman_y += 4.0;
			}

			//go right

			if (key[KEY_RIGHT] && !wallCollide(pacman_x, pacman_y, RIGHT, level)) {
				pacman_x += 4.0;
			}

			if (key[KEY_LEFT] && !wallCollide(pacman_x, pacman_y, LEFT, level)) {
				pacman_x -= 4.0;
			}
			//eat dots
			if (level[pacman_x / 30][pacman_y / 30] == 0) {
				level[pacman_x / 30][pacman_y / 30] = score++;
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

			//al_draw_filled_circle(pacman_x, pacman_y, 15, al_map_rgb(255, 255, 0));
			al_draw_filled_rectangle(pacman_x, pacman_y, pacman_x + PACSIZE, pacman_y + PACSIZE, al_map_rgb(255, 255, 0));

			al_draw_textf(font, al_map_rgb(255, 255, 255), 750, 10, ALLEGRO_ALIGN_RIGHT, "%d", score);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 750, 500, ALLEGRO_ALIGN_RIGHT, "%d",  lives);

			
			for (int i = 0; i < 19; i++)
				for (int j = 0; j < 21; j++) {
					if (level[i][j] == 1)
						al_draw_bitmap(wall, i * 30, j * 30, 0);
					if (level[i][j] == 0)
						al_draw_bitmap(dots, i * 30 + 10, j * 30 + 10, 0);//dots
					boi.drawghost();
					yee.drawghost();
					dp.drawghost();
					bm.drawghost();
				}
			//call draw function
			al_flip_display();
		}
	}//end of game loop

	//end of game
	al_clear_to_color(al_map_rgb(0, 0, 0));
	if (lives <= 0)
		al_draw_text(font, al_map_rgb(200, 30, 30), 400, 400, ALLEGRO_ALIGN_CENTER, "GET YEETED KID");
	else if(score=256)
		al_draw_text(font, al_map_rgb(200, 30, 30), 400, 400, ALLEGRO_ALIGN_CENTER, "YEEEEEEEEEEEE");
	al_flip_display();


	al_rest(5);
	al_destroy_bitmap(pacman);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


	return 0;
}
//bool ghost::dead() {
//
//	return isdead;
//
//}
bool pixelCollision(int x1, int y1, int x2, int y2) {

	if (pixelCollision(x1, y1, x2, y2) == true)
	/*if (key[3] && !wallCollide(pacman_x, pacman_y, RIGHT, wall)) {
	pacman_x += 4.0;
	}*/
	return false;



}
int wallCollide(int x, int y, int dir, int level[19][21]) {
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
		y2 = y + PACSIZE / 2;
		y3 = y + PACSIZE;
		if ((level[x1 / 30][y1 / 30] == 1) || (level[x2 / 30][y2 / 30] == 1) || (level[x3 / 30][y3 / 30] == 1)) {

			cout << "right collision" << endl;
			return 1;
		}

		else {
			return 0;

		}
	}
	if (dir == LEFT) { 		// Moving Right
							// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		x1 = x - 5;
		x2 = x - 5;
		x3 = x - 5;
		// Check at three point along that edge
		y1 = y;
		y2 = y + PACSIZE / 2;
		y3 = y + PACSIZE;

		if ((level[x1 / 30][y1 / 30] == 1) || (level[x2 / 30][y2 / 30] == 1) || (level[x3 / 30][y3 / 30] == 1)) {
			cout << "left collision" << endl;
			return 1;
		}
		else {
			return 0;
		}

	}
	if (dir == UP) { 		// Moving Right
							// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		x1 = x;
		x2 = x + PACSIZE / 2;
		x3 = x + PACSIZE;
		// Check at three point along that edge
		y1 = y - 5;
		y2 = y - 5;
		y3 = y - 5;

		if ((level[x1 / 30][y1 / 30] == 1) || (level[x2 / 30][y2 / 30] == 1) || (level[x3 / 30][y3 / 30] == 1)) {
			cout << "up collision" << endl;
			return 1;
		}
		else {
			return 0;
		}
	}
	if (dir == DOWN) { 		// Moving Right
		x1 = x;
		x2 = x + 20 / 2;
		x3 = x + PACSIZE;
		// Check at three point along that edge
		y1 = y + 20 + 4;
		y2 = y + PACSIZE + 4;
		y3 = y + PACSIZE + 4;


		if ((level[x1 / 30][y1 / 30] == 1) || (level[x2 / 30][y2 / 30] == 1) || (level[x3 / 30][y3 / 30] == 1)) {
			cout << "down collision" << endl;
			return 1;
		}
		else {
			return 0;
		}
	}
}
void ghost::drawghost() {
	if(color == 'r')
		al_draw_filled_rectangle(xpos,ypos, xpos + 20, ypos + 20, al_map_rgb(255, 0, 0));

	else if (color == 'b')
		al_draw_filled_rectangle(xpos, ypos, xpos + 20, ypos + 20, al_map_rgb(0, 0, 255));
	else if (color == 'o')
	al_draw_filled_rectangle(xpos, ypos, xpos + 20, ypos + 20, al_map_rgb(237, 145, 33));
	else if (color == 'p')
	al_draw_filled_rectangle(xpos, ypos, xpos + 20, ypos + 20, al_map_rgb(248, 24, 148));


}
void ghost::initghost(int x, int y, char c, int dir) {
	xpos = x;
	ypos = y;
	color = c;
	direction = dir;

}
bool PixelCollision(int x1, int y1, int w1, int hl, int x2, int y2, int w2, int h2) {

	if ((x1 + w1 > x2) && (x2 + w2 > x1) && (y2 + h2 > y1) && (y1 + hl > y2))

		return true;

	else
		return false;
}

//put ghost init function here, put ghost draw, paste chase function here too
void ghost::chase(int x, int y, int field[19][21]) {



	/* Directions

	1 = left

	2 = up

	3 = right

	4 = down*/


	//this is just for testing

	/*  cout << "state is " << direction << endl;

	if (wallCollide(xpos, ypos, 1, level))

	cout << "there's a wall to the left of me" << endl;

	if (wallCollide(xpos, ypos, 2, level))

	cout << "there's a wall above me" << endl;

	if (wallCollide(xpos, ypos, 3, level))

	cout << "there's a wall to the right of me" << endl;

	if (wallCollide(xpos, ypos, 4, level))

	cout << "there's a wall below me" << endl;*/


	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////


	//if we're moving left and there's an opening above and pacman is above, move up

	if ((direction == LEFT) && !wallCollide(xpos, ypos, UP, field) && y<ypos)

		while (!wallCollide(xpos, ypos, 2, field)) {

			// cout << "trying to move through hole above!" << endl;

			direction = UP;

			ypos += 4;

			return;

		}


	//if we're moving left and there's an opening below and pacman is below, move down

	if ((direction == LEFT) && !wallCollide(xpos, ypos, DOWN, field) && y>ypos)

		while (!wallCollide(xpos, ypos, 4, field)) {

			//  cout << "trying to move through hole below!" << endl;

			direction = DOWN;

			ypos += 4;

			return;

		}



	if (direction == LEFT)//left

		while (!wallCollide(xpos, ypos, LEFT, field)) {

			xpos += 4;

			return;

		}


	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////


	//if we're moving up and there's an opening left and pacman is left, move left

	if ((direction == UP) && !wallCollide(xpos, ypos, LEFT, field) && x<xpos)

		while (!wallCollide(xpos, ypos, LEFT, field)) {

			//   cout << "trying to move through hole to left!" << endl;

			direction = LEFT;

			xpos -= 4;

			return;

		}

	//if we're moving up and there's an opening right and pacman is right, move right

	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x>xpos)

		while (!wallCollide(xpos, ypos, 3, field)) {

			// cout << "trying to move through hole to right!" << endl;

			direction = RIGHT;

			xpos += 4;

			return;

		}

	if (direction == UP)//up

		while (!wallCollide(xpos, ypos, 2, field)) {

			ypos -= UP;

			return;

		}


	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////

	//if we're moving right and there's an opening above and pacman is above, move up

	if ((direction == RIGHT) && !wallCollide(xpos, ypos, UP, field) && y<ypos)

		while (!wallCollide(xpos, ypos, 2, field)) {

			//   cout << "trying to move through hole above!" << endl;

			direction = UP;

			ypos -= 4;

			return;

		}


	//if we're moving right and there's an opening below and pacman is below, move down

	if ((direction == RIGHT) && !wallCollide(xpos, ypos, DOWN, field) && y>ypos)

		while (!wallCollide(xpos, ypos, DOWN, field)) {

			//  cout << "trying to move through hole below!" << endl;

			direction = DOWN;

			ypos += 4;

			return;

		}



	if (direction == RIGHT)//right

		while (!wallCollide(xpos, ypos, RIGHT, field)) {

			xpos += 4;

			return;

		}



	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left

	if ((direction == DOWN) && !wallCollide(xpos, ypos, LEFT, field) && x<xpos)

		while (!wallCollide(xpos, ypos, LEFT, field)) {

			// cout << "trying to move through hole to left!" << endl;

			direction = LEFT;

			xpos -= 4;

			return;

		}

	//if we're moving up and there's an opening right and pacman is right, move right

	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x>xpos)

		while (!wallCollide(xpos, ypos, RIGHT, field)) {

			//   cout << "trying to move through hole to right!" << endl;

			direction = RIGHT;

			xpos += 4;

			return;

		}


	if (direction == DOWN)//down

		while (!wallCollide(xpos, ypos, DOWN, field)) {

			ypos += 4;

			return;

		}






	///////////////////////////////////////////////////////////////////////////////////////

	//if pacman is above and there's no wall there, move up

	if ((y<ypos) && !wallCollide(xpos, ypos, UP, field)) {

		//  cout << "direction is up" << endl;

		direction = UP;

		return;

	}



	//if pacman is below and there's no wall there, move down

	if ((y>ypos) && !wallCollide(xpos, ypos, DOWN, field)) {

		direction = DOWN;

		//   cout << "direction is down" << endl;

		return;

	}


	//if pacman is right and there's no wall there, move right

	if ((x>xpos) && !wallCollide(xpos, ypos, RIGHT, field)) {

		direction = RIGHT;

		//  cout << "direction is right" << endl;

		return;

	}


	//if pacman is left and there's no wall there, move left

	if ((x<xpos) && !wallCollide(xpos, ypos, LEFT, field)) {

		direction = LEFT;

		// cout << "direction is left" << endl;

		return;


	}


	//if pacman is above and there's no wall there, move up

	if (!wallCollide(xpos, ypos, UP, field)) {

		// cout << "direction is up" << endl;

		direction = UP;

		return;

	}



	//if pacman is below and there's no wall there, move down

	if (!wallCollide(xpos, ypos, DOWN, field)) {

		direction = DOWN;

		//cout << "direction is down" << endl;

		return;

	}


	//if pacman is right and there's no wall there, move right

	if (!wallCollide(xpos, ypos, RIGHT, field)) {

		direction = RIGHT;

		//  cout << "direction is right" << endl;

		return;

	}


	//if pacman is left and there's no wall there, move left

	if (!wallCollide(xpos, ypos, LEFT, field)) {

		direction = LEFT;

		// cout << "direction is left" << endl;

		return;


	}


}

void ghost::chase2(int x, int y, int field[19][21]) {



	/* Directions

	1 = left

	2 = up

	3 = right

	4 = down*/


	//this is just for testing

	/*  cout << "state is " << direction << endl;

	if (wallCollide(xpos, ypos, 1, level))

	cout << "there's a wall to the left of me" << endl;

	if (wallCollide(xpos, ypos, 2, level))

	cout << "there's a wall above me" << endl;

	if (wallCollide(xpos, ypos, 3, level))

	cout << "there's a wall to the right of me" << endl;

	if (wallCollide(xpos, ypos, 4, level))

	cout << "there's a wall below me" << endl;*/


	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////


	//if we're moving left and there's an opening above and pacman is above, move up

	if ((direction == LEFT) && !wallCollide(xpos, ypos, UP, field) && y<ypos)

		while (!wallCollide(xpos, ypos, 2, field)) {

			// cout << "trying to move through hole above!" << endl;

			direction = UP;

			ypos -= 2;

			return;

		}


	//if we're moving left and there's an opening below and pacman is below, move down

	if ((direction == LEFT) && !wallCollide(xpos, ypos, LEFT, field) && y>ypos)

		while (!wallCollide(xpos, ypos, 6, field)) {

			//  cout << "trying to move through hole below!" << endl;

			direction = UP;

			ypos += 3;

			return;

		}



	if (direction == LEFT)//left

		while (!wallCollide(xpos, ypos, LEFT, field)) {

			xpos -= 3;

			return;

		}


	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////


	//if we're moving up and there's an opening left and pacman is left, move left

	if ((direction == UP) && !wallCollide(xpos, ypos, UP, field) && x<xpos)

		while (!wallCollide(xpos, ypos, 4, field)) {

			//   cout << "trying to move through hole to left!" << endl;

			direction = RIGHT;

			xpos -= 3;

			return;

		}

	//if we're moving up and there's an opening right and pacman is right, move right

	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x>xpos)

		while (!wallCollide(xpos, ypos, 3, field)) {

			// cout << "trying to move through hole to right!" << endl;

			direction = RIGHT;

			xpos += 3;

			return;

		}

	if (direction == UP)//up

		while (!wallCollide(xpos, ypos, 4, field)) {

			ypos -= UP;

			return;

		}


	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////

	//if we're moving right and there's an opening above and pacman is above, move up

	if ((direction == RIGHT) && !wallCollide(xpos, ypos, UP, field) && y<ypos)

		while (!wallCollide(xpos, ypos, 2, field)) {

			//   cout << "trying to move through hole above!" << endl;

			direction = UP;

			ypos -= 3;

			return;

		}


	//if we're moving right and there's an opening below and pacman is below, move down

	if ((direction == RIGHT) && !wallCollide(xpos, ypos, DOWN, field) && y>ypos)

		while (!wallCollide(xpos, ypos, DOWN, field)) {

			//  cout << "trying to move through hole below!" << endl;

			direction = DOWN;

			ypos += 3;

			return;

		}



	if (direction == RIGHT)//right

		while (!wallCollide(xpos, ypos, RIGHT, field)) {

			xpos += 4;

			return;

		}



	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left

	if ((direction == DOWN) && !wallCollide(xpos, ypos, LEFT, field) && x<xpos)

		while (!wallCollide(xpos, ypos, LEFT, field)) {

			// cout << "trying to move through hole to left!" << endl;

			direction = LEFT;

			xpos -= 3;

			return;

		}

	//if we're moving up and there's an opening right and pacman is right, move right

	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x>xpos)

		while (!wallCollide(xpos, ypos, RIGHT, field)) {

			//   cout << "trying to move through hole to right!" << endl;

			direction = RIGHT;

			xpos += 3;

			return;

		}


	if (direction == DOWN)//down

		while (!wallCollide(xpos, ypos, DOWN, field)) {

			ypos += 3;

			return;

		}






	///////////////////////////////////////////////////////////////////////////////////////

	//if pacman is above and there's no wall there, move up

	if ((y<ypos) && !wallCollide(xpos, ypos, UP, field)) {

		//  cout << "direction is up" << endl;

		direction = UP;

		return;

	}



	//if pacman is below and there's no wall there, move down

	if ((y>ypos) && !wallCollide(xpos, ypos, DOWN, field)) {

		direction = DOWN;

		//   cout << "direction is down" << endl;

		return;

	}


	//if pacman is right and there's no wall there, move right

	if ((x>xpos) && !wallCollide(xpos, ypos, RIGHT, field)) {

		direction = RIGHT;

		//  cout << "direction is right" << endl;

		return;

	}


	//if pacman is left and there's no wall there, move left

	if ((x<xpos) && !wallCollide(xpos, ypos, LEFT, field)) {

		direction = LEFT;

		// cout << "direction is left" << endl;

		return;


	}


	//if pacman is above and there's no wall there, move up

	if (!wallCollide(xpos, ypos, UP, field)) {

		// cout << "direction is up" << endl;

		direction = UP;

		return;

	}



	//if pacman is below and there's no wall there, move down

	if (!wallCollide(xpos, ypos, DOWN, field)) {

		direction = DOWN;

		//cout << "direction is down" << endl;

		return;

	}


	//if pacman is right and there's no wall there, move right

	if (!wallCollide(xpos, ypos, RIGHT, field)) {

		direction = RIGHT;

		//  cout << "direction is right" << endl;

		return;

	}


	//if pacman is left and there's no wall there, move left

	if (!wallCollide(xpos, ypos, LEFT, field)) {

		direction = LEFT;

		// cout << "direction is left" << endl;

		return;


	}


}
void ghost::chase3(int x, int y, int field[19][21]) {



	/* Directions

	1 = left

	2 = up

	3 = right

	4 = down*/


	//this is just for testing

	/*  cout << "state is " << direction << endl;

	if (wallCollide(xpos, ypos, 1, level))

	cout << "there's a wall to the left of me" << endl;

	if (wallCollide(xpos, ypos, 2, level))

	cout << "there's a wall above me" << endl;

	if (wallCollide(xpos, ypos, 3, level))

	cout << "there's a wall to the right of me" << endl;

	if (wallCollide(xpos, ypos, 4, level))

	cout << "there's a wall below me" << endl;*/


	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////


	//if we're moving left and there's an opening above and pacman is above, move up

	if ((direction == LEFT) && !wallCollide(xpos, ypos, UP, field) && y<ypos)

		while (!wallCollide(xpos, ypos, 2, field)) {

			// cout << "trying to move through hole above!" << endl;

			direction = UP;

			ypos -= 4;

			return;

		}


	//if we're moving left and there's an opening below and pacman is below, move down

	if ((direction == LEFT) && !wallCollide(xpos, ypos, DOWN, field) && y>ypos)

		while (!wallCollide(xpos, ypos, 4, field)) {

			//  cout << "trying to move through hole below!" << endl;

			direction = DOWN;

			ypos += 4;

			return;

		}



	if (direction == LEFT)//left

		while (!wallCollide(xpos, ypos, RIGHT, field)) {

			xpos -= 4;

			return;

		}


	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////


	//if we're moving up and there's an opening left and pacman is left, move left

	if ((direction == UP) && !wallCollide(xpos, ypos, LEFT, field) && x<xpos)

		while (!wallCollide(xpos, ypos, LEFT, field)) {

			//   cout << "trying to move through hole to left!" << endl;

			direction = LEFT;

			xpos -= 4;

			return;

		}

	//if we're moving up and there's an opening right and pacman is right, move right

	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x>xpos)

		while (!wallCollide(xpos, ypos, 3, field)) {

			// cout << "trying to move through hole to right!" << endl;

			direction = RIGHT;

			xpos += 4;

			return;

		}

	if (direction == UP)//up

		while (!wallCollide(xpos, ypos, 2, field)) {

			ypos -= UP;

			return;

		}


	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////

	//if we're moving right and there's an opening above and pacman is above, move up

	if ((direction == RIGHT) && !wallCollide(xpos, ypos, UP, field) && y<ypos)

		while (!wallCollide(xpos, ypos, 2, field)) {

			//   cout << "trying to move through hole above!" << endl;

			direction = UP;

			ypos -= 2;

			return;

		}


	//if we're moving right and there's an opening below and pacman is below, move down

	if ((direction == RIGHT) && !wallCollide(xpos, ypos, DOWN, field) && y>ypos)

		while (!wallCollide(xpos, ypos, DOWN, field)) {

			//  cout << "trying to move through hole below!" << endl;

			direction = DOWN;

			ypos += 2;

			return;

		}



	if (direction == RIGHT)//right

		while (!wallCollide(xpos, ypos, RIGHT, field)) {

			xpos += 2;

			return;

		}



	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left

	if ((direction == DOWN) && !wallCollide(xpos, ypos, LEFT, field) && x<xpos)

		while (!wallCollide(xpos, ypos, LEFT, field)) {

			// cout << "trying to move through hole to left!" << endl;

			direction = LEFT;

			xpos -= 2;

			return;

		}

	//if we're moving up and there's an opening right and pacman is right, move right

	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x>xpos)

		while (!wallCollide(xpos, ypos, RIGHT, field)) {

			//   cout << "trying to move through hole to right!" << endl;

			direction = RIGHT;

			xpos += 2;

			return;

		}


	if (direction == DOWN)//down

		while (!wallCollide(xpos, ypos, DOWN, field)) {

			ypos += 2;

			return;

		}






	///////////////////////////////////////////////////////////////////////////////////////

	//if pacman is above and there's no wall there, move up

	if ((y<ypos) && !wallCollide(xpos, ypos, UP, field)) {

		//  cout << "direction is up" << endl;

		direction = UP;

		return;

	}



	//if pacman is below and there's no wall there, move down

	if ((y>ypos) && !wallCollide(xpos, ypos, DOWN, field)) {

		direction = DOWN;

		//   cout << "direction is down" << endl;

		return;

	}


	//if pacman is right and there's no wall there, move right

	if ((x>xpos) && !wallCollide(xpos, ypos, RIGHT, field)) {

		direction = RIGHT;

		//  cout << "direction is right" << endl;

		return;

	}


	//if pacman is left and there's no wall there, move left

	if ((x<xpos) && !wallCollide(xpos, ypos, LEFT, field)) {

		direction = LEFT;

		// cout << "direction is left" << endl;

		return;


	}


	//if pacman is above and there's no wall there, move up

	if (!wallCollide(xpos, ypos, UP, field)) {

		// cout << "direction is up" << endl;

		direction = UP;

		return;

	}



	//if pacman is below and there's no wall there, move down

	if (!wallCollide(xpos, ypos, DOWN, field)) {

		direction = DOWN;

		//cout << "direction is down" << endl;

		return;

	}


	//if pacman is right and there's no wall there, move right

	if (!wallCollide(xpos, ypos, RIGHT, field)) {

		direction = RIGHT;

		//  cout << "direction is right" << endl;

		return;

	}


	//if pacman is left and there's no wall there, move left

	if (!wallCollide(xpos, ypos, LEFT, field)) {

		direction = LEFT;

		// cout << "direction is left" << endl;

		return;


	}


}

void ghost::chase4(int x, int y, int field[19][21]) {



	/* Directions

	1 = left

	2 = up

	3 = right

	4 = down*/


	//this is just for testing

	/*  cout << "state is " << direction << endl;

	if (wallCollide(xpos, ypos, 1, level))

	cout << "there's a wall to the left of me" << endl;

	if (wallCollide(xpos, ypos, 2, level))

	cout << "there's a wall above me" << endl;

	if (wallCollide(xpos, ypos, 3, level))

	cout << "there's a wall to the right of me" << endl;

	if (wallCollide(xpos, ypos, 4, level))

	cout << "there's a wall below me" << endl;*/


	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////


	//if we're moving left and there's an opening above and pacman is above, move up

	if ((direction == LEFT) && !wallCollide(xpos, ypos, UP, field) && y<ypos)

		while (!wallCollide(xpos, ypos, 2, field)) {

			// cout << "trying to move through hole above!" << endl;

			direction = UP;

			ypos -= 4;

			return;

		}


	//if we're moving left and there's an opening below and pacman is below, move down

	if ((direction == LEFT) && !wallCollide(xpos, ypos, DOWN, field) && y>ypos)

		while (!wallCollide(xpos, ypos, 4, field)) {

			//  cout << "trying to move through hole below!" << endl;

			direction = DOWN;

			ypos += 4;

			return;

		}



	if (direction == LEFT)//left

		while (!wallCollide(xpos, ypos, LEFT, field)) {

			xpos -= 4;

			return;

		}


	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////


	//if we're moving up and there's an opening left and pacman is left, move left

	if ((direction == UP) && !wallCollide(xpos, ypos, LEFT, field) && x<xpos)

		while (!wallCollide(xpos, ypos, LEFT, field)) {

			//   cout << "trying to move through hole to left!" << endl;

			direction = LEFT;

			xpos -= 4;

			return;

		}

	//if we're moving up and there's an opening right and pacman is right, move right

	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x>xpos)

		while (!wallCollide(xpos, ypos, 3, field)) {

			// cout << "trying to move through hole to right!" << endl;

			direction = RIGHT;

			xpos += 4;

			return;

		}

	if (direction == UP)//up

		while (!wallCollide(xpos, ypos, 2, field)) {

			ypos -= UP;

			return;

		}


	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////

	//if we're moving right and there's an opening above and pacman is above, move up

	if ((direction == RIGHT) && !wallCollide(xpos, ypos, UP, field) && y<ypos)

		while (!wallCollide(xpos, ypos, 2, field)) {

			//   cout << "trying to move through hole above!" << endl;

			direction = UP;

			ypos -= 5;

			return;

		}


	//if we're moving right and there's an opening below and pacman is below, move down

	if ((direction == RIGHT) && !wallCollide(xpos, ypos, DOWN, field) && y>ypos)

		while (!wallCollide(xpos, ypos, DOWN, field)) {

			//  cout << "trying to move through hole below!" << endl;

			direction = DOWN;

			ypos += 5;

			return;

		}



	if (direction == RIGHT)//right

		while (!wallCollide(xpos, ypos, RIGHT, field)) {

			xpos += 5;

			return;

		}



	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left

	if ((direction == DOWN) && !wallCollide(xpos, ypos, LEFT, field) && x<xpos)

		while (!wallCollide(xpos, ypos, LEFT, field)) {

			// cout << "trying to move through hole to left!" << endl;

			direction = LEFT;

			xpos -= 5;

			return;

		}

	//if we're moving up and there's an opening right and pacman is right, move right

	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x>xpos)

		while (!wallCollide(xpos, ypos, RIGHT, field)) {

			//   cout << "trying to move through hole to right!" << endl;

			direction = RIGHT;

			xpos += 5;

			return;

		}


	if (direction == DOWN)//down

		while (!wallCollide(xpos, ypos, DOWN, field)) {

			ypos += 5;

			return;

		}






	///////////////////////////////////////////////////////////////////////////////////////

	//if pacman is above and there's no wall there, move up

	if ((y<ypos) && !wallCollide(xpos, ypos, UP, field)) {

		//  cout << "direction is up" << endl;

		direction = UP;

		return;

	}



	//if pacman is below and there's no wall there, move down

	if ((y>ypos) && !wallCollide(xpos, ypos, DOWN, field)) {

		direction = DOWN;

		//   cout << "direction is down" << endl;

		return;

	}


	//if pacman is right and there's no wall there, move right

	if ((x>xpos) && !wallCollide(xpos, ypos, RIGHT, field)) {

		direction = RIGHT;

		//  cout << "direction is right" << endl;

		return;

	}


	//if pacman is left and there's no wall there, move left

	if ((x<xpos) && !wallCollide(xpos, ypos, LEFT, field)) {

		direction = LEFT;

		// cout << "direction is left" << endl;

		return;


	}


	//if pacman is above and there's no wall there, move up

	if (!wallCollide(xpos, ypos, UP, field)) {

		// cout << "direction is up" << endl;

		direction = UP;

		return;

	}



	//if pacman is below and there's no wall there, move down

	if (!wallCollide(xpos, ypos, DOWN, field)) {

		direction = DOWN;

		//cout << "direction is down" << endl;

		return;

	}


	//if pacman is right and there's no wall there, move right

	if (!wallCollide(xpos, ypos, RIGHT, field)) {

		direction = RIGHT;

		//  cout << "direction is right" << endl;

		return;

	}


	//if pacman is left and there's no wall there, move left

	if (!wallCollide(xpos, ypos, LEFT, field)) {

		direction = LEFT;

		// cout << "direction is left" << endl;

		return;


	}


}