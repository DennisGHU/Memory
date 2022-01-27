#include "memory_cards.h"
#include "agk.h"
#include "algorithm"
//#include "chrono"
//#include "random"
#include "windows.h"

void memory_cards::load_cards()
{
	// Laad textures in een array
	cards[0] = agk::LoadImage("textures/back.png");
	cards[1] = agk::LoadImage("textures/boxes.png");
	cards[2] = agk::LoadImage("textures/broken_wall.png");
	cards[3] = agk::LoadImage("textures/computer.png");
	cards[4] = agk::LoadImage("textures/dynamite.png");
	cards[5] = agk::LoadImage("textures/factory.png");
	cards[6] = agk::LoadImage("textures/food.png");
	cards[7] = agk::LoadImage("textures/hand.png");
	cards[8] = agk::LoadImage("textures/lab.png");
	cards[9] = agk::LoadImage("textures/mechanic.png");
	cards[10] = agk::LoadImage("textures/old_computer.png");
	cards[11] = agk::LoadImage("textures/planning.png");
	cards[12] = agk::LoadImage("textures/prototype.png");

	// Init cleared cards bool array en zet alles naar false
	bool cleared_cards[24];
	for (int i = 0; i < 24; i++) {
		cleared_cards[i] = false;
	}
}


void memory_cards::draw_cards() 
{
	// Settings voor de kaarten
	double scale = 3.5;
	int spacing = 20;
	int xpos, ypos;
	totalSz = 160;

	// Plaats kaarten in een grid
	for (int i = 1; i <= 24; i++) {
		xpos = 170 +  ((i-1) % 6) * totalSz;
		ypos = 50 + floor((i-1) / 6) * totalSz;

		agk::CreateSprite(i, cards[0]); // back
		agk::SetSpritePosition(i, xpos, ypos);
		agk::SetSpriteScale(i, scale, scale);
	}
}


void memory_cards::shuffle_cards()
{
	int x = 1;
	
	// Zet kaarten op volgorde met juiste texture. Twee keer gebruikt per texture
	for (int i = 1; i <= 25; i += 2) {
		card_data[i-1] = x;
		card_data[i] = x;
		x++;
	}

	// Shuffle array met verwijzing naar texture id en maak compleet random
	srand(time(NULL));
	std::random_shuffle(&card_data[0], &card_data[24]);
}

int memory_cards::card_flip(int card_id)
{
	agk::SetSpriteImage(card_id, cards[ card_data[ card_id-1 ] ]);
	return card_data[card_id - 1];
}

int memory_cards::get_card_pressed()
{
	// Als de muis is losgelaten ontvang op welke kaart is gedrukt of geen kaart.

	int mouse_x, mouse_y;
	mouse_x = agk::GetRawMouseX();
	mouse_y = agk::GetRawMouseY();

	int tSize = 140;

	for (int i = 1; i <= 24; i++) {
		xpos = 170 + ((i - 1) % 6) * totalSz;
		ypos = 50 + floor((i - 1) / 6) * totalSz;

		if (mouse_x > xpos && mouse_x < (xpos + tSize) ) {
			if (mouse_y > ypos && mouse_y < (ypos + tSize) ) {
				return i;
			}
		}
	}

	return 0;
}

void memory_cards::clear_cards(int card1, int card2) {
	// Wanneer goeie combi blokeer deze en zet open
	cleared_cards[card1] = true;
	cleared_cards[card2] = true;
}


void memory_cards::selected_card(int thisCard)
{
	int selIndi = agk::MakeColor(247, 220, 111);

	// Indicatie voor openstaande kaarten
	xpos = 170 + ((thisCard-1) % 6) * totalSz;
	ypos = 50 + floor((thisCard-1) / 6) * totalSz;

	// top
	agk::DrawBox(xpos - 8, ypos - 8, xpos + 148, ypos, selIndi, selIndi, selIndi, selIndi, true);
	// bottom
	agk::DrawBox(xpos, ypos + 140, xpos + 148, ypos + 148, selIndi, selIndi, selIndi, selIndi, true);
	// left
	agk::DrawBox(xpos - 8, ypos, xpos, ypos + 148, selIndi, selIndi, selIndi, selIndi, true);
	// bottom
	agk::DrawBox(xpos + 140, ypos, xpos + 148, ypos + 148, selIndi, selIndi, selIndi, selIndi, true);
}

void memory_cards::draw_cleared_cards() 
{
	int indi = agk::MakeColor(213, 245, 227);

	// Indicatie voor openstaande kaarten
	for (int i = 1; i <= 24; i++) {
		if (cleared_cards[i] == true) {
			xpos = 170 + ((i - 1) % 6) * totalSz;
			ypos = 50 + floor((i - 1) / 6) * totalSz;

			// top
			agk::DrawBox(xpos - 8, ypos - 8, xpos + 148, ypos, indi, indi, indi, indi, true);
			// bottom
			agk::DrawBox(xpos, ypos + 140, xpos + 148, ypos + 148, indi, indi, indi, indi, true);
			// left
			agk::DrawBox(xpos - 8, ypos, xpos, ypos + 148, indi, indi, indi, indi, true);
			// bottom
			agk::DrawBox(xpos + 140, ypos, xpos + 148, ypos + 148, indi, indi, indi, indi, true);
		}
	}
}

void memory_cards::unflip_cards(int card1, int card2) 
{
	agk::SetSpriteImage(card1, cards[0]);
	agk::SetSpriteImage(card2, cards[0]);
}

bool memory_cards::is_cleared(int card_id)
{
	if (cleared_cards[card_id] == true) {
		return true;
	} else {
		return false;
	}
}

bool memory_cards::isGameCleared() 
{
	cards_left = false;

	for (int i = 1; i < 24; i++) {
		if (cleared_cards[i] == false) {
			cards_left = true;
		}
	}

	if (cards_left == true) {
		return false; // game_cleared = false
	} else {
		return true;
	}

}

void memory_cards::reset_game() {
	
	// Unflip alle kaarten
	for (int i = 0; i <= 24; i++) {
		cleared_cards[i] = false;
		// Reset textures
		agk::SetSpriteImage(i, cards[0]);
	}

	// Shuffle array met verwijzing naar texture id en maak compleet random
	srand(time(NULL));
	std::random_shuffle(&card_data[0], &card_data[24]);

}


// Debugger gebruikt om bug te fixen met hitboxes

/*void memory_cards::hitbox_debugging() 
{
	int mouse_x, mouse_y;
	mouse_x = agk::GetRawMouseX();
	mouse_y = agk::GetRawMouseY();

	// Cols
	int red = agk::MakeColor(255, 0, 0);
	int blue = agk::MakeColor(0, 0, 255);

	//int tSize = 40 * scale;
	int tSize = 140;

	for (int i = 1; i <= 24; i++) {
		xpos = 170 + ((i - 1) % 6) * totalSz;
		ypos = 50 + floor((i - 1) / 6) * totalSz;

		// Debugging mouse_hitbox
		agk::DrawBox(mouse_x - 8, mouse_y - 8, mouse_x + 8, mouse_y + 8, blue, blue, blue, blue, true);

		// Debugging hitbox
		//agk::DrawBox(xpos, ypos, xpos + tSize, ypos + tSize, red, red, red, red, false);

		agk::DrawBox(xpos, ypos, xpos + tSize, ypos + tSize, red, red, red, red, true);

		int _xpos = (3 % 6) * totalSz; //+ 170;
		int _ypos = 50 + floor((3-1) / 6) * totalSz;

		agk::DrawBox(_xpos, _ypos, _xpos + tSize, _ypos + tSize, blue, blue, blue, blue, true);

	}
}*/