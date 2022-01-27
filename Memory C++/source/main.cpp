// Includes
#include "main.h"
#include "memory_cards.h"

// Namespace
using namespace AGK;

app App;


/*
AF - Het speelveld bevat 24 kaarten in 4 rijen van 6.
AF - In het spel komen dubbele kaarten voor; er bestaan dus 12 verschillende afbeel-
  dingen. Je mag zelf bepalen welke afbeeldingen dat zijn.
AF - Kies wel voor een categorie, b.v. boerderijdieren. Let bij de keuze van de afbeel-
  dingen op de doelgroep.
AF - De kaarten hebben een neutrale achterkant; je kiest zelf hiervoor een
  afbeelding.
AF - Iedere keer als het spel gestart wordt, liggen de kaarten anders gerangschikt
  met de neutrale achterkant zichtbaar.
- Als de speler op een kaart klikt, wordt de afbeelding zichtbaar (‘omgedraaid’).
AF - Dit gebeurt ook bij de volgende klik op een andere kaart. Er zijn dan twee
  kaarten omgedraaid.
AF - Als de afbeelding op de beide openliggende kaarten gelijk is, dan blijven de
  kaarten geopend liggen.
AF - Heeft de speler niet twee dezelfde kaarten omgedraaid, dan worden ze bij de
  volgende klik weer ‘teruggedraaid’.
AF - Als alle kaarten open liggen, volgt de volgende melding:
AF - Klikt de speler bij de vraag ‘Nog een keer?’ op ‘Ja’,  dan wordt een nieuw spel
  gestart, anders wordt de applicatie afgesloten.
*/

// Create instance
memory_cards mc;

int result_id = 0;
double xscale = 0;
int card_id = 0;
int prevCard_id = 0;
bool next_click_reset = false;
bool game_cleared = false;

void app::Begin(void)
{
	// Settings
	agk::SetWindowTitle("Dennis C++ Schoolopdracht: memory");
	agk::SetVirtualResolution (1280, 720);
	agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetSyncRate(60,0);
	agk::SetScissor(0,0,0,0);
	agk::SetWindowAllowResize(true);

	// Disable smoothing
	agk::SetDefaultMagFilter(0);
	agk::SetDefaultMinFilter(0);

	// Init card textures
	mc.load_cards();
	mc.draw_cards();

	// Shuffle kaarten
	mc.shuffle_cards();

}

void app::Loop (void)
{

	// Debugging
	//mc.hitbox_debugging();

	// Unflip en reset cards
	if (next_click_reset == true) {
		if (agk::GetRawMouseLeftReleased()) {
			mc.unflip_cards(card_id, prevCard_id);
			card_id = 0;
			prevCard_id = 0;
			result_id = 0;
			next_click_reset = false;
		}
	}


	// Popup
	if (game_cleared == true) {
		const int opnieuw = MessageBox(NULL, "Nog een keer?", "Melding", MB_YESNO);
		switch (opnieuw) {
		case IDYES:
			// Reset spel
			card_id = 0;
			prevCard_id = 0;
			result_id = 0;
			next_click_reset = false;
			game_cleared = false;
			mc.reset_game();
			break;

		case IDNO:
			// Sluit applicatie
			exit(0);
			break;
		}
	}


	// flip card
	if (agk::GetRawMouseLeftReleased()) {
		int valid_card_pressed;
		
		valid_card_pressed = mc.get_card_pressed();

		if (valid_card_pressed != 0 && mc.is_cleared(valid_card_pressed) == false) {
			card_id = valid_card_pressed;
			valid_card_pressed = NULL;

			if (result_id == 0) {
				result_id = mc.card_flip(card_id);
				prevCard_id = card_id;
			} else {
				if (result_id == mc.card_flip(card_id) && card_id != prevCard_id) {
					mc.clear_cards(card_id, prevCard_id);
					card_id = 0;
					prevCard_id = 0;
					result_id = 0;

					// Check of game klaar is
					game_cleared = mc.isGameCleared();
				} else {
					next_click_reset = true;
				}
			}

		}

	}


	// Selected card
	if (card_id != 0) {
		mc.selected_card(card_id);
	}
	if (prevCard_id != 0) {
		mc.selected_card(prevCard_id);
	}


	// Draw cleared cards
	mc.draw_cleared_cards();

	// Exit when esc pressed
	if (agk::GetRawKeyReleased(27)) {
		exit(0);
	}

	// Sync frame
	agk::Sync();
}


void app::End (void)
{
	
}
