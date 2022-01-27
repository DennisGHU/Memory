#pragma once

class memory_cards
{

	private:
		int cards[13];
		int card_data[24];
		bool cleared_cards[24];

		// Card settings
		double scale;
		int spacing;
		int xpos;
		int ypos;
		int totalSz;

		int cards_left;

	public:
		//load_cards();
		void load_cards();
		void shuffle_cards();
		void draw_cards();
		int card_flip(int card_id);
		int get_card_pressed();
		void clear_cards(int card1, int card2);
		void draw_cleared_cards();
		void selected_card(int thisCard);
		void unflip_cards(int card1, int card2);
		bool is_cleared(int card_id);
		bool isGameCleared();
		void reset_game();
		//void hitbox_debugging();
};