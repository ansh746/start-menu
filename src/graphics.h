#include "../include/global.h" 
#include "../include/sprite.h" 
#include "../include/bg.h" 

enum GfxTags
{
  GFXTAG_PANEL,
  GFXTAG_EXIT,
  GFXTAG_POKEDEX,
  GFXTAG_POKEMON,
  GFXTAG_BAG,
  GFXTAG_PLAYER,
  GFXTAG_SAVE,
  GFXTAG_OPTIONS,
  GFXTAG_SCROLLBAR,
  GFXTAG_RETIRE
};



//Gfx Data
extern const u8 panelTiles[]; 
extern const u16 panelPal[];  

// Exit Button Gfx Data
extern const u8 exitTiles[];
extern const u16 exitPal[];

// BG Gfx data
extern const u8 StartMenuBgTiles[]; 
extern const u8 StartMenuBgMap[];
extern const u16 StartMenuBgPal[];

// Pokedex Icon Gfx Data
extern const u8 pokedexTiles[];
extern const u16 pokedexPal[];

// Pokemon Icon Gfx Data
extern const u8 pokemonTiles[];
extern const u16 pokemonPal[];

// Bag Icon Gfx data 
extern const u8 bagTiles[];
extern const u16 bagPal[];

// Trainer Card Icon Gfx data
extern const u8 playerTiles[];
extern const u16 playerPal[];

// Save Icon Gfx Data
extern const u8 saveTiles[];
extern const u16 savePal[];

// Options Icon Gfx data
extern const u8 optionsTiles[];
extern const u16 optionsPal[];

// Scrollbar Gfx data
extern const u8 scrollbarTiles[];
extern const u16 scrollbarPal[];




//================================================================================================
void PanelCallBack(struct Sprite *sprite);
void StartMenuIconCallback(struct Sprite *sprite);
void ScrollBarCallback(struct Sprite *sprite);

//=================================================================================================
static const struct SpriteSheet PanelSpriteSheet = {panelTiles, (64*64*4)/2, GFXTAG_PANEL };
static const struct SpritePalette PanelSpritePalette = {panelPal, GFXTAG_PANEL};
static const struct OamData sPanelOam =
{
	.affineMode = ST_OAM_AFFINE_OFF,
	.objMode = ST_OAM_OBJ_BLEND,
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
	ANIMCMD_JUMP(0) 
};  


static const union AnimCmd *const sAnimCmdTable_Panel1[] =
{
	sAnimCmdPanelUnselected1,
	sAnimCmdPanelSelected1,
	
}; 

static const union AnimCmd *const sAnimCmdTable_Panel2[] =
{
	sAnimCmdPanelUnselected2,
	sAnimCmdPanelSelected2,
	
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
static const struct OamData ScrollBarOamData =
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

static const struct SpriteSheet ScrollBarSpriteSheet = {scrollbarTiles, 32*16, GFXTAG_SCROLLBAR};
static const struct SpritePalette ScrollBarSpritePalette = {scrollbarPal, GFXTAG_SCROLLBAR};

static const union AnimCmd AnimCmdScrollbar[] = 
{
  ANIMCMD_FRAME(0, 0),
  ANIMCMD_END,
}; 
static const union AnimCmd *const sAnimCmdTable_Scrollbar[] =
{
	AnimCmdScrollbar
};   


static const struct SpriteTemplate ScrollBarSpriteTemplate =
{
  .tileTag = GFXTAG_SCROLLBAR,
	.paletteTag = GFXTAG_SCROLLBAR,
	.oam = &ScrollBarOamData,
	.anims = sAnimCmdTable_Scrollbar,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = ScrollBarCallback,
};