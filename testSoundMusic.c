//*****************************************
//		testSoundMusic for GameBoy. 
// Programmed by jduranmaster a.k.a. Ryoga
//*****************************************

#include <gb/gb.h>
#include <gb/drawing.h>
#include "gbt_player.h"
#include "_SMUSIC.h"

UBYTE tile_offset = 1;
UBYTE tile_height = 18;

static const unsigned char TEXT_cEMPTY[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

extern const unsigned char * song_Data[];
extern const unsigned char * songb_Data[];

void PRINT_MAIN_SFX_MENU(void);
void CLEAR_SCREEN_LINE (UBYTE y);
void PLAY_SONG_FROM_MBC1_BANK_1();
void PLAY_SONG_FROM_MBC1_BANK_2();
void STOP_SONG_FROM_MBC1_BANK_X();
void CLEAR_SCREEN_BACKGROUND (void);
void PRINT_MESSAGE(int x, int y, char *c);
void PLOT_BACKGROUND_IMAGE(int coord_X, int coord_Y, int tam_tile_X, int tam_tile_Y, unsigned char *tile_data, unsigned char *map_data);

void main(){
	
	UBYTE key_pressed = 0;
	UBYTE gbt_update_released = 0;
	UBYTE MBC_BANK_ID = 0;
	
	PLOT_BACKGROUND_IMAGE(0, 0, 20, 18, _SMUSIC_tile_data, _SMUSIC_map_data);
	PRINT_MAIN_SFX_MENU();
    
	while(1){
		key_pressed = joypad();
		
		if(key_pressed & (J_A)){
			MBC_BANK_ID = 0;
			STOP_SONG_FROM_MBC1_BANK_X();
			PLAY_SONG_FROM_MBC1_BANK_2();
			PRINT_MESSAGE(1, 6,"MBC1-Bank1 B : NP");
			PRINT_MESSAGE(1, 10,"Playing MBC1-BANK 2");
			PRINT_MESSAGE(1, 7,"MBC1-Bank2 A : P ");
			if(gbt_update_released == 0){
				gbt_update_released = 1;
				add_VBL(gbt_update);
			}
		}
		
		if(key_pressed & (J_B)){
			MBC_BANK_ID = 1;
			STOP_SONG_FROM_MBC1_BANK_X();
			PLAY_SONG_FROM_MBC1_BANK_1();
			PRINT_MESSAGE(1, 6,"MBC1-Bank1 B : P ");
			PRINT_MESSAGE(1, 10,"Playing MBC1-BANK 1");
			PRINT_MESSAGE(1, 7,"MBC1-Bank2 A : NP");
			if(gbt_update_released == 0){
				gbt_update_released = 1;
				add_VBL(gbt_update);
			}
		}
		
		if(key_pressed & (J_START)){
			STOP_SONG_FROM_MBC1_BANK_X();
			PRINT_MESSAGE(1, 6,"MBC1-Bank1 B : NP");
			PRINT_MESSAGE(1, 7,"MBC1-Bank2 A : NP");
			PRINT_MESSAGE(1, 10,"                   ");
			if(MBC_BANK_ID){
				PRINT_MESSAGE(1, 10,"Stopping MBC1-Bank1");
			}else{
				PRINT_MESSAGE(1, 10,"Stopping MBC1-Bank2");
			}
			delay(1000);
			PRINT_MESSAGE(1, 10,"                   ");
		}
		
		wait_vbl_done();
	}
}

void PLAY_SONG_FROM_MBC1_BANK_1(){
	SWITCH_ROM_MBC1(1);
	gbt_play(song_Data, 1, 7);
	gbt_loop(0);
}

void PLAY_SONG_FROM_MBC1_BANK_2(){
	SWITCH_ROM_MBC1(2);
	gbt_play(song_Data, 2, 7);
	gbt_loop(0);
}

void STOP_SONG_FROM_MBC1_BANK_X(){
	gbt_stop();
}

void PRINT_MAIN_SFX_MENU(void){
	PRINT_MESSAGE(0, 1, "-------------------");
	PRINT_MESSAGE(0, 2, " MUSIC FOR GAMEBOY");
	PRINT_MESSAGE(0, 3, "-------------------");
	PRINT_MESSAGE(1, 6,"MBC1-Bank1 A : NP");
	PRINT_MESSAGE(1, 7,"MBC1-Bank2 B : NP");
	PRINT_MESSAGE(2, 14, "----------------");
	PRINT_MESSAGE(5, 15, "RYOGA 2014");
	PRINT_MESSAGE(2, 16, "----------------");
}

void PRINT_MESSAGE(int x, int y, char *c){
	gotogxy(x,y);
	gprintf(c);
}

void CLEAR_SCREEN_LINE ( UBYTE y ){
	UBYTE x;
	for (x = y*20 ; x < (y+1)*20 ; x++ ){
		set_bkg_data (x+tile_offset,1,(unsigned char *)TEXT_cEMPTY);
	}
}

void CLEAR_SCREEN_BACKGROUND(void){
	UBYTE x;
	for ( x = 0 ; x < tile_height ; x++ ){
		CLEAR_SCREEN_LINE ( x );
	}
}

void PLOT_BACKGROUND_IMAGE(int coord_X, int coord_Y, int tam_tile_X, int tam_tile_Y, unsigned char *tile_data, unsigned char *map_data){
	set_bkg_data(coord_X, coord_Y, tile_data);
	set_bkg_tiles(coord_X, coord_Y, tam_tile_X, tam_tile_Y, map_data);
	SHOW_BKG;
	DISPLAY_ON;
	delay(2000);
}