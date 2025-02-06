#ifndef GUARD_START_MENU_H
#define GUARD_START_MENU_H

#include "global.h" 
#include "sprite.h" 
#include "bg.h" 
#include "window.h" 
#include "text.h"
#include "../src/graphics.h"

#define PANEL_X 34
#define PANEL_Y 41 
#define HSPACING 20
#define VSPACING 6
#define icon_template(gfxtag) {.tileTag = (u16) gfxtag, .paletteTag = (u16) gfxtag, .oam = &sIconOamData, .anims = sAnimCmdTable_Icon, .images = NULL,.affineAnims = gDummySpriteAffineAnimTable, .callback = StartMenuIconCallback}

extern u8* GetMapName(u8* dest, u16 regionMapId, u16 padLength);
extern u8  GetCurrentRegionMapSectionId(void);
extern void CB2_OpenPokedexFromStartMenu(void);
extern void CB2_PartyMenuFromStartMenu(void);
extern void CB2_BagMenuFromStartMenu(void); 
extern void CB2_OptionsMenuFromStartMenu(void);   
void CB2_ReturnToField(void);
extern bool8  StartMenuPokedexCallback(void);
extern bool8  StartMenuPokemonCallback(void);
extern bool8  StartMenuBagCallback(void);
extern bool8  StartMenuPlayerCallback(void);
extern bool8  StartMenuOptionCallback(void);



enum BGs
{
	BG_TEXT,
	BG_1,
	BG_2,
	BG_BACKGROUND,
}; 

enum StartMenuOptions
{
  STARTMENU_POKEDEX = 0,
  STARTMENU_POKEMON,
  STARTMENU_BAG,
  STARTMENU_PLAYER, 
  STARTMENU_SAVE,
  STARTMENU_OPTION,
  STARTMENU_RETIRE,
  MAX_STARTMENU_ITEMS
};

struct StartMenuIcon
{
  const struct SpriteSheet spritesheet;
  const struct SpritePalette spritepalette;
  const struct SpriteTemplate sprtemplate;
}; 

struct StartMenuOption 
{
  u8 id;
  u8 * text;
  u16 flag; 
  u8 * script;
  void (*func);
};


// Text
extern const u8 gText_StartMenu_Pokedex[];
extern const u8 gText_StartMenu_Pokemon[];
extern const u8 gText_StartMenu_Bag[];
extern const u8 gText_StartMenu_Player[];
extern const u8 gText_StartMenu_Save[];
extern const u8 gText_StartMenu_Option[]; 
extern const u8 gText_StartMenu_Retire[]; 

// Safari Zone Stats text
extern const u8 gText_SafariZoneStats[];

//Time strings
extern const u8 gText_Sun[];
extern const u8 gText_Mon[];
extern const u8 gText_Tue[];
extern const u8 gText_Wed[];
extern const u8 gText_Thu[];
extern const u8 gText_Fri[];
extern const u8 gText_Sat[]; 
extern const u8 gText_AM[]; 
extern const u8 gText_PM[]; 

// Scripts 
extern u8 Script_SaveGame[];
extern u8 Script_Retire[];

static const struct BgTemplate sStartMenuBgTemplates[] =
{
	[BG_TEXT] =
	{
		.bg = BG_TEXT,
		.charBaseIndex = 0,
		.mapBaseIndex = 31,
		.screenSize = 0,
		.paletteMode = 0,
		.priority = 0,
		.baseTile = 0,
	},
	[BG_1] =
	{
		.bg = BG_1,
		.charBaseIndex = 1,
		.mapBaseIndex = 30,
		.screenSize = 0,
		.paletteMode = 0,
		.priority = 1,
		.baseTile = 0,
	},
	[BG_2] =
	{
		.bg = BG_2,
		.charBaseIndex = 2,
		.mapBaseIndex = 29,
		.screenSize = 0,
		.paletteMode = 0,
		.priority = 2,
		.baseTile = 0,
	},
	[BG_BACKGROUND] =
	{
		.bg = BG_BACKGROUND,
		.charBaseIndex = 3,
		.mapBaseIndex = 28,
		.screenSize = 0,
		.paletteMode = 0,
		.priority = 3,
		.baseTile = 0,
	}, 
}; 


static struct StartMenuIcon StartMenuIconTable[] = 
{
  [STARTMENU_POKEDEX] = 
  {
    .spritesheet = {pokedexTiles, 32*32, GFXTAG_POKEDEX},
    .spritepalette =  {pokedexPal, GFXTAG_POKEDEX},
    .sprtemplate = icon_template(GFXTAG_POKEDEX)
  },
  [STARTMENU_POKEMON] = 
  {
    .spritesheet = {pokemonTiles, 32*32, GFXTAG_POKEMON},
    .spritepalette = {pokemonPal, GFXTAG_POKEMON},
    .sprtemplate = icon_template(GFXTAG_POKEMON)
  },
  [STARTMENU_BAG] =
  {
    .spritesheet = {bagTiles, 32*32, GFXTAG_BAG},
    .spritepalette = {bagPal, GFXTAG_BAG},
    .sprtemplate = icon_template(GFXTAG_BAG)
  },
  [STARTMENU_PLAYER] =
  {
    .spritesheet = {playerTiles, 32*32, GFXTAG_PLAYER},
    .spritepalette = {playerPal, GFXTAG_PLAYER},
    .sprtemplate = icon_template(GFXTAG_PLAYER)
  },
  [STARTMENU_SAVE] =
  {
    .spritesheet = {saveTiles, 32*32, GFXTAG_SAVE},
    .spritepalette = {savePal, GFXTAG_SAVE},
    .sprtemplate = icon_template(GFXTAG_SAVE)
  },
  [STARTMENU_OPTION] =
  {
    .spritesheet = {optionsTiles, 32*32, GFXTAG_OPTIONS},
    .spritepalette = {optionsPal, GFXTAG_OPTIONS},
    .sprtemplate = icon_template(GFXTAG_OPTIONS)
  },
  [STARTMENU_RETIRE] =
  {
    .spritesheet = {exitTiles, 16*16 , GFXTAG_RETIRE},
    .spritepalette = {exitPal, GFXTAG_RETIRE},
    .sprtemplate =
     {
        .tileTag = GFXTAG_RETIRE,
        .paletteTag = GFXTAG_RETIRE,
        .oam = &sExitIconOam,
        .anims = sAnimCmdTable_Exit,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = PanelCallBack,  
     },
  }
};

// Text fonts
static const struct TextColor sWhiteText =
{
	.bgColor = TEXT_COLOR_TRANSPARENT,
	.fgColor = TEXT_COLOR_WHITE,
	.shadowColor = TEXT_COLOR_DARK_GRAY,
}; 




#endif // GUARD_START_MENU_H