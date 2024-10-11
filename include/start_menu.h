#ifndef GUARD_START_MENU_H
#define GUARD_START_MENU_H

#include "global.h" 
#include "sprite.h" 
#include "bg.h" 
#include "window.h" 
#include "text.h"

#define PANEL_X 35
#define PANEL_Y 42 
#define HSPACING 21
#define VSPACING 5 


#define icon_template(gfxtag) {.tileTag = (u16) gfxtag, .paletteTag = (u16) gfxtag, .oam = &sIconOamData, .anims = sAnimCmdTable_Icon, .images = NULL,.affineAnims = gDummySpriteAffineAnimTable, .callback = StartMenuIconCallback}
enum BGs
{
	BG_TEXT,
	BG_1,
	BG_2,
	BG_BACKGROUND,
}; 

enum 
{
  GFXTAG_PANEL,
  GFXTAG_EXIT,
  GFXTAG_POKEDEX,
  GFXTAG_POKEMON,
  GFXTAG_BAG,
  GFXTAG_PLAYER,
  GFXTAG_SAVE,
  GFXTAG_OPTIONS,
};

enum 
{
  STARTMENU_POKEDEX = 0,
  STARTMENU_POKEMON,
  STARTMENU_BAG,
  STARTMENU_PLAYER, 
  STARTMENU_SAVE,
  STARTMENU_OPTION,
  STARTMENU_OPTION2,
  MAX_STARTMENU_ITEMS
} ;

struct StartMenuIcon
{
  const struct SpriteSheet spritesheet;
  const struct SpritePalette spritepalette;
  const struct SpriteTemplate sprtemplate;
}; 


extern void Field_AskSaveTheGame(void);
void PanelCallBack(struct Sprite *sprite);
void StartMenuIconCallback(struct Sprite *sprite);
u8* __attribute__((long_call)) GetMapName(u8* dest, u16 regionMapId, u16 padLength);
u8 __attribute__((long_call)) GetCurrentRegionMapSectionId(void);
s16 __attribute__((long_call)) Sin2(u16 angle); 
extern void CB2_OpenPokedexFromStartMenu(void);
extern void CB2_PartyMenuFromStartMenu(void);
extern void CB2_BagMenuFromStartMenu(void); 
extern void CB2_OptionsMenuFromStartMenu(void); 
extern const u8 Script_SaveGame[];  
void __attribute__((long_call)) CB2_ReturnToField(void);
bool8 __attribute__((long_call)) StartMenuPokedexCallback(void);
bool8 __attribute__((long_call)) StartMenuPokemonCallback(void);
bool8 __attribute__((long_call)) StartMenuBagCallback(void);
bool8 __attribute__((long_call)) StartMenuPlayerCallback(void);
bool8 __attribute__((long_call)) StartMenuOptionCallback(void);


//Gfx Data
extern const u8 panelTiles[]; 
extern const u16 panelPal[];  
extern const u8 exitTiles[];
extern const u16 exitPal[];
extern const u8 pokedexTiles[];
extern const u16 pokedexPal[];
extern const u8 pokemonTiles[];
extern const u16 pokemonPal[];
extern const u8 bagTiles[];
extern const u16 bagPal[];
extern const u8 playerTiles[];
extern const u16 playerPal[];
extern const u8 saveTiles[];
extern const u16 savePal[];
extern const u8 optionsTiles[];
extern const u16 optionsPal[];

extern const u8 StartMenuBgTiles[]; 
extern const u8 StartMenuBgMap[];
extern const u16 StartMenuBgPal[];


// Text
extern const u8 gText_StartMenu_Pokedex[];
extern const u8 gText_StartMenu_Pokemon[];
extern const u8 gText_StartMenu_Bag[];
extern const u8 gText_StartMenu_Player[];
extern const u8 gText_StartMenu_Save[];
extern const u8 gText_StartMenu_Option[]; 
extern const u8 gText_Sun[];
extern const u8 gText_Mon[];
extern const u8 gText_Tue[];
extern const u8 gText_Wed[];
extern const u8 gText_Thu[];
extern const u8 gText_Fri[];
extern const u8 gText_Sat[]; 
extern const u8 gText_AM[]; 
extern const u8 gText_PM[]; 
extern const u8 gText_StartMenu_Option2[];

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

static const struct SpriteSheet PanelSpriteSheet = {panelTiles, (64*64*4)/2, GFXTAG_PANEL };
static const struct SpritePalette PanelSpritePalette = {panelPal, GFXTAG_PANEL};
static const struct OamData sPanelOam =
{
	.affineMode = ST_OAM_AFFINE_OFF,
	.objMode = ST_OAM_OBJ_NORMAL,
	.shape = SPRITE_SHAPE(64x64),
	.size = SPRITE_SIZE(64x64),
	.priority = 1, //Above other sprites
};

static const union AnimCmd sAnimCmdPanelUnselected1[] =
{
	ANIMCMD_FRAME(0, 0),
	ANIMCMD_END
}; 

static const union AnimCmd sAnimCmdPanelUnselected2[] =
{
	ANIMCMD_FRAME(64, 0),
	ANIMCMD_END
};  
static const union AnimCmd sAnimCmdPanelSelected1[] =
{
	ANIMCMD_FRAME(128, 0),
	ANIMCMD_END
}; 

static const union AnimCmd sAnimCmdPanelSelected2[] =
{
	ANIMCMD_FRAME(192, 0),       
	ANIMCMD_END
};  

static const union AnimCmd *const sAnimCmdTable_Panel1[] =
{
	sAnimCmdPanelUnselected1,
	sAnimCmdPanelSelected1
}; 

static const union AnimCmd *const sAnimCmdTable_Panel2[] =
{
	sAnimCmdPanelUnselected2,
	sAnimCmdPanelSelected2
};  

static const struct SpriteTemplate sPanel1SpriteTemplate =
{
	.tileTag = GFXTAG_PANEL,
	.paletteTag = GFXTAG_PANEL,
	.oam = &sPanelOam,
	.anims = sAnimCmdTable_Panel1,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = PanelCallBack,
}; 
static const struct SpriteTemplate sPanel2SpriteTemplate =
{
	.tileTag = GFXTAG_PANEL,
	.paletteTag = GFXTAG_PANEL,
	.oam = &sPanelOam,
	.anims = sAnimCmdTable_Panel2,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = PanelCallBack,
}; 


// Exit Sprite
static const struct SpriteSheet ExitSpriteSheet = {exitTiles, 16*16, GFXTAG_EXIT };
static const struct SpritePalette ExitSpritePalette = {exitPal, GFXTAG_EXIT};
static const struct OamData sExitIconOam =
{
	.affineMode = ST_OAM_AFFINE_OFF,
	.objMode = ST_OAM_OBJ_NORMAL,
	.shape = SPRITE_SHAPE(16x16),
	.size = SPRITE_SIZE(16x16),
	.priority = 1, //Above other sprites
};

static const union AnimCmd sAnimCmdExit[] =
{
	ANIMCMD_FRAME(0, 0),
	ANIMCMD_END
};
static const union AnimCmd sAnimCmdExitSelected[] =
{
	ANIMCMD_FRAME(4, 0),
	ANIMCMD_END
}; 
static const union AnimCmd *const sAnimCmdTable_Exit[] =
{
	sAnimCmdExit,
	sAnimCmdExitSelected
};   

static const struct SpriteTemplate ExitSpriteTemplate =
{
	.tileTag = GFXTAG_EXIT,
	.paletteTag = GFXTAG_EXIT,
	.oam = &sExitIconOam,
	.anims = sAnimCmdTable_Exit,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = PanelCallBack,
}; 

// Pokedex Sprite

static const struct OamData sIconOamData =
{
	.affineMode = ST_OAM_AFFINE_OFF,
	.objMode = ST_OAM_OBJ_NORMAL,
	.shape = SPRITE_SHAPE(32x32),
	.size = SPRITE_SIZE(32x32),
	.priority = 1, //Above other sprites
};

static const union AnimCmd sAnimCmdIcon[] =
{
	ANIMCMD_FRAME(0, 0),
	ANIMCMD_END
};
static const union AnimCmd sAnimCmdIconSelected[] =
{
	ANIMCMD_FRAME(16, 0),
	ANIMCMD_END
}; 
static const union AnimCmd *const sAnimCmdTable_Icon[] =
{
	sAnimCmdIcon,
	sAnimCmdIconSelected
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
  [STARTMENU_OPTION2] =
  {
    .spritesheet = {optionsTiles, 32*32, GFXTAG_OPTIONS},
    .spritepalette = {optionsPal, GFXTAG_OPTIONS},
    .sprtemplate = icon_template(GFXTAG_OPTIONS)
  },
};

// Text 
static const struct TextColor sWhiteText =
{
	.bgColor = TEXT_COLOR_TRANSPARENT,
	.fgColor = TEXT_COLOR_WHITE,
	.shadowColor = TEXT_COLOR_DARK_GRAY,
}; 


struct StartMenuOption 
{
  u8 id;
  u8 * text;
  u16 flag; 
  u8 * script;
  void (*func);
};

#define startmenu_option(a, b, c, d, e) \
{.id = (u8) a,.text = (u8*) b,\
.flag = (u16) c, .script = (u8*) d,\
.func = (void*) e} 



#endif // GUARD_START_MENU_H