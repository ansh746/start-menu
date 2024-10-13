#include "../include/global.h" 
#include "../include/start_menu.h" 
#include "../include/bg.h"
#include "../include/data.h"
#include "../include/decompress.h"
#include "../include/event_data.h"
#include "../include/gpu_regs.h"
#include "../include/graphics.h"
#include "../include/item.h"
#include "../include/list_menu.h"
#include "../include/international_string_util.h"
#include "../include/main.h"
#include "../include/malloc.h"
#include "../include/menu.h"
#include "../include/menu_helpers.h" 
#include "../include/palette.h"
#include "../include/party_menu.h"
#include "../include/scanline_effect.h"
#include "../include/script.h"
#include "../include/sound.h"
#include "../include/string_util.h"
#include "../include/strings.h"
#include "../include/pokedex.h"
#include "../include/task.h"
#include "../include/text_window.h"
#include "../include/event_data.h"
#include "../include/overworld.h"
#include "../include/constants/items.h"
#include "../include/constants/field_weather.h"
#include "../include/constants/songs.h"
#include "../include/constants/flags.h"
#include "../include/gba/types.h"
#include "../include/new/Vanilla_functions.h"


#define cpos sStartMenuPtr->cursorpos[0]
#define scrolloffset sStartMenuPtr->cursorpos[1]
#define numitems sStartMenuPtr->NumStartMenuItems[0]
#define numonscreenitems sStartMenuPtr->NumStartMenuItems[1]
#define menuitems sStartMenuPtr->CurrentOptionsTable[0] 
#define onscreenmenuitems sStartMenuPtr->CurrentOptionsTable[1]



enum WindowIds
{
    WIN_TOPBAR,
    WIN_ITEMS,
    WIN_BOTTOMBAR,
    WIN_COUNT
};  


struct StartMenuResources
{
  u8 cursorpos[2];
  u8* sBgTilemapBuffer;
  u8 NumStartMenuItems[2];
  u8 CurrentOptionsTable[2][MAX_STARTMENU_ITEMS]; 
  u8 IconSpriteIds[6];
};   

#define sStartMenuPtr (*((struct StartMenuResources**) 0x203E038))  

extern u16 StdTextPal[];
static const struct WindowTemplate sMenuWindowTemplates[] = 
{
    [WIN_TOPBAR] = 
    {
        .bg = BG_TEXT,      // which bg to print text on
        .tilemapLeft = 0,   // position from left (per 8 pixels)
        .tilemapTop = 0,    // position from top (per 8 pixels)
        .width = 30,        // width (per 8 pixels)
        .height = 4,        // height (per 8 pixels)
        .paletteNum = 14,   // palette index to use for text
        .baseBlock = 1,     // tile start in VRAM
    }, 
    [WIN_ITEMS] = 
    {
        .bg = BG_TEXT,      // which bg to print text on
        .tilemapLeft = 0,   // position from left (per 8 pixels)
        .tilemapTop = 4,    // position from top (per 8 pixels)
        .width = 30,        // width (per 8 pixels)
        .height = 12,        // height (per 8 pixels)
        .paletteNum = 14,   // palette index to use for text
        .baseBlock = 121,     // tile start in VRAM
    },            
    [WIN_BOTTOMBAR] = 
    {
        .bg = BG_TEXT,      // which bg to print text on
        .tilemapLeft = 0,   // position from left (per 8 pixels)
        .tilemapTop = 16,    // position from top (per 8 pixels)
        .width = 30,        // width (per 8 pixels)
        .height = 4,        // height (per 8 pixels)
        .paletteNum = 14,   // palette index to use for text
        .baseBlock = 482,     // tile start in VRAM
    }, 
    DUMMY_WIN_TEMPLATE,
}; 



//This file's functions
void CB2_ReturnToFieldWithOpenMenu(void); 
static void CB2_OptionMenuFromStartMenu(void); 
static void CB2_PlayerTrainerCardFromStartMenu(void);
static void ClearTasksAndGraphicalStructs(void); 
static void ClearVramOamPlttRegs(void);
static void VBlankCB_StartMenu(void); 
static void MainCB2_StartMenu(void);
static bool8 InitStartMenuGUI(void); 
static void Task_StartMenuFadeIn(u8 taskId); 
static void Task_StartMenuWaitForKeyPress(u8 taskId); 
static void LoadStartMenuBgGfx(void);
static void SetUpStartMenu_NormalField(void); 
static void DrawPanels(void); 
static void Task_StartMenuFadeOut(u8 taskId); 
static void FreeAndCloseStartMenu(u8 taskId); 
static void PrintGUIMapName(void);
static void CleanWindow(u8 windowId); 
static void CommitWindow(u8 windowId); 
static void CleanWindows(void); 
static void CommitWindows(void); 
static void PrintGUIMenuItemsName(void);
static void DrawIcons(void);
void CB2_SaveFromStartMenu(void);
void StartMenu_Init(void); 
static void CreateScrollbar(void) ;
static void CalculateAndConfigureOnScreenOptions(void);
static void Task_RunStartMenuOptionFuncOrScript(u8 taskId);
static void RefreshStartMenuOptions(void);

static const struct StartMenuOption sStartMenuOptionsTable[] = 
{
  [STARTMENU_POKEDEX] = startmenu_option(STARTMENU_POKEDEX, gText_StartMenu_Pokedex, FLAG_SYS_POKEDEX_GET, NULL, CB2_OpenPokedexFromStartMenu),
  [STARTMENU_POKEMON] = startmenu_option(STARTMENU_POKEMON, gText_StartMenu_Pokemon, FLAG_SYS_POKEMON_GET, NULL, CB2_PartyMenuFromStartMenu),
  [STARTMENU_BAG]     = startmenu_option(STARTMENU_BAG, gText_StartMenu_Bag, 0, NULL, CB2_BagMenuFromStartMenu),
  [STARTMENU_PLAYER]  = startmenu_option(STARTMENU_PLAYER, NULL , 0, NULL, CB2_PlayerTrainerCardFromStartMenu),
  [STARTMENU_SAVE]    = startmenu_option(STARTMENU_SAVE, gText_StartMenu_Save, 0, Script_SaveGame, NULL),
  [STARTMENU_OPTION]  = startmenu_option(STARTMENU_OPTION, gText_StartMenu_Option, 0, NULL, CB2_OptionMenuFromStartMenu),
}; 

static void ClearTasksAndGraphicalStructs(void)
{
	ScanlineEffect_Stop();
	ResetTasks();
	ResetSpriteData();
	ResetTempTileDataBuffers();
	ResetPaletteFade();
	FreeAllSpritePalettes();
} 
 
static void ClearVramOamPlttRegs(void)
{
	DmaFill16(3, 0, VRAM, VRAM_SIZE);
	DmaFill32(3, 0, OAM, OAM_SIZE);
	DmaFill16(3, 0, PLTT, PLTT_SIZE);
	SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
	SetGpuReg(REG_OFFSET_BG3CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG2CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG1CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG0CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG3HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG3VOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG2HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG2VOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG1HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG1VOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG0HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG0VOFS, DISPCNT_MODE_0);
}

static void VBlankCB_StartMenu(void)
{
	LoadOam();
	ProcessSpriteCopyRequests();
	TransferPlttBuffer();
}
static void MainCB2_StartMenu(void)
{
	RunTasks();
	AnimateSprites();
	BuildOamBuffer();
	UpdatePaletteFade();
}

void CB2_StartMenu(void)
{
	switch (gMain.state) {
		case 0:
		default:
			SetBGMVolume_SuppressHelpSystemReduction(160);
			SetVBlankCallback(NULL);
			ClearVramOamPlttRegs();
			gMain.state++;
			break;
		case 1:
			ClearTasksAndGraphicalStructs();
			gMain.state++;
			break;
		case 2:
			sStartMenuPtr->sBgTilemapBuffer = Malloc(0x1000);
			ResetBgsAndClearDma3BusyFlags(0);
			InitBgsFromTemplates(0, sStartMenuBgTemplates, NELEMS(sStartMenuBgTemplates));
			SetBgTilemapBuffer(BG_BACKGROUND, sStartMenuPtr->sBgTilemapBuffer);
			gMain.state++;
			break;
		case 3: 
		  if (!(cpos))
		     cpos = 0;
		  SetUpStartMenu_NormalField();
			LoadStartMenuBgGfx(); 
			gMain.state++;
			break;
		case 4:
			if (!free_temp_tile_data_buffers_if_possible())
			{
			  ShowBg(BG_TEXT);
				ShowBg(BG_BACKGROUND);
				CopyBgTilemapBufferToVram(BG_BACKGROUND);
				gMain.state++;
			}
			break;
		case 5:
	    Free(sStartMenuPtr->sBgTilemapBuffer);
			InitWindows(sMenuWindowTemplates);
			DeactivateAllTextPrinters();
			gMain.state++;
			break;
		case 6:
			BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
			gMain.state++;
			break;
		case 7:
			SetVBlankCallback(VBlankCB_StartMenu);
			InitStartMenuGUI();
			CreateTask(Task_StartMenuFadeIn, 0);
			SetMainCallback2(MainCB2_StartMenu);
			gMain.state = 0;
			break;
	}
} 

static void Task_StartMenuFadeIn(u8 taskId)
{
	if (!gPaletteFade.active)
	{
			gTasks[taskId].func = Task_StartMenuWaitForKeyPress;
	}
}  

static void LoadStartMenuBgGfx(void)
{
	const u8 *tiles, *map;
	const u16 *palette;
  tiles = StartMenuBgTiles; 
  map = StartMenuBgMap; 
  palette = StartMenuBgPal;
	DecompressAndCopyTileDataToVram(BG_BACKGROUND, tiles, 0, 0, 0);
	LZDecompressWram(map, sStartMenuPtr->sBgTilemapBuffer);
	LoadPalette(palette, 0, 0x20); 
	palette = StdTextPal;
	LoadPalette(palette, 14*16, 0x20);
} 

static bool8 InitStartMenuGUI(void)
{ 
  CleanWindows();
  DrawPanels(); 
  DrawIcons();
  PrintGUIMapName(); 
  PrintGUIMenuItemsName();
  CreateScrollbar();
  CommitWindows();
  return TRUE;
}
static void Task_StartMenuWaitForKeyPress(u8 taskId)
{ 
  // Handles Input
  if (JOY_NEW(B_BUTTON)) 
  { 
    cpos = 0xFF;
    PlaySE(SE_PC_OFF);
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
		gTasks[taskId].func = Task_StartMenuFadeOut;
  } 
  else if(JOY_NEW(A_BUTTON))
  {
    PlaySE(SE_SELECT);
    VarSet(0x8000, cpos);  
    VarSet(0x8001, scrolloffset);
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_RunStartMenuOptionFuncOrScript;
  }
  else if (JOY_NEW(DPAD_RIGHT)) 
  {
    if (!(cpos+1>= numonscreenitems) && !(cpos%2==1))
    {
      PlaySE(SE_SELECT);
      cpos++; 
    }
  } 
  else if (JOY_NEW(DPAD_LEFT))
  {
    if ((cpos-1>=0) && (cpos%2==1))
    {
      PlaySE(SE_SELECT);
      cpos--;
    }
  } 
  else if (JOY_NEW(DPAD_UP)) 
  {
    if (cpos>1 && cpos<4 && scrolloffset>0)
    {
      PlaySE(SE_SELECT);
      scrolloffset -= 1; 
      RefreshStartMenuOptions();
    }
    else if (cpos-2>=0)  
    {
      PlaySE(SE_SELECT);
      cpos -= 2; 
    }

  } 
  else if (JOY_NEW(DPAD_DOWN)) 
  {
    if (cpos>1 && cpos<4 && scrolloffset<numitems/2-3+numitems%2)
    {
      scrolloffset += 1; 
      PlaySE(SE_SELECT);
      RefreshStartMenuOptions();
    }
    else if (cpos+2<numonscreenitems)  
   {
      PlaySE(SE_SELECT);
      cpos += 2; 
   }
  }
} 


static void Task_RunStartMenuOptionFuncOrScript(u8 taskId)
{
  if (!gPaletteFade.active)
  { 
    if (sStartMenuOptionsTable[onscreenmenuitems[cpos]].func!=NULL) 
      SetMainCallback2(sStartMenuOptionsTable[onscreenmenuitems[cpos]].func);
    else
    {
      SetMainCallback2(CB2_ReturnToField);
      ScriptContext1_SetupScript(sStartMenuOptionsTable[onscreenmenuitems[cpos]].script); 
    }
    FreeAndCloseStartMenu(taskId);
  }
} 

void StartMenu_Init(void)
{
	if (!gPaletteFade.active)
	{
	  ResetBgsAndClearDma3BusyFlags(0);
		gHelpSystemEnabled = FALSE;
		CleanupOverworldWindowsAndTilemaps();
		sStartMenuPtr = Calloc(sizeof(struct StartMenuResources));
		PlaySE(SE_PC_LOGIN);
		SetMainCallback2(CB2_StartMenu);
	} 
}

static void SetUpStartMenu_NormalField(void) 
{
  u8 cursor = 0;
  for (u8 i = 0; i < MAX_STARTMENU_ITEMS; i++)
  { 
    if (sStartMenuOptionsTable[i].flag!=0 && !FlagGet(sStartMenuOptionsTable[i].flag)) 
      continue;
    menuitems[cursor] = sStartMenuOptionsTable[i].id;
    cursor++;
  } 
  numitems = cursor; 
  if (!scrolloffset)
    scrolloffset = 0;
  CalculateAndConfigureOnScreenOptions();
}

void PanelCallBack(struct Sprite *sprite) 
{ 
  if (sprite->data[0]>=numonscreenitems && sprite->data[0]!=0xFF)
    sprite->invisible = 1;
  else 
    sprite->invisible = 0;
  if(sprite->data[0] == cpos) 
    StartSpriteAnim(sprite, 1);
  else 
    StartSpriteAnim(sprite, 0);
}

void StartMenuIconCallback(struct Sprite *sprite) 
{ 
  if(sprite->data[0] == cpos)
  {
    StartSpriteAnim(sprite, 1);
    if (sprite->data[4]%5==0)
    {
      if(sprite->data[1]==0)
        sprite->data[3] = 1;
      else if(sprite->data[1]==3)
        sprite->data[3] = -1;
      sprite->data[1] += sprite->data[3];
      sprite->pos1.y = sprite->data[2] + sprite->data[1]; 
    }
  sprite->data[4]++;
  }
  else 
  {
    sprite->pos1.y = sprite->data[2];
    StartSpriteAnim(sprite, 0);
  }
}

static void DrawPanels(void)
{ 
  u16 x, y;
  u8 counter = 0; 
  LoadSpriteSheet(&PanelSpriteSheet);
  LoadSpritePalette(&PanelSpritePalette);
  for (u8 j = 0; j<3; j++) 
  {
    for (u8 i = 0; i<2; i++) 
    {
      x = PANEL_X + (HSPACING + 64/2 + 62)*i;
      y = (PANEL_Y + (VSPACING + 32)*j); 
      u8 SpriteId1 = CreateSprite(&sPanel1SpriteTemplate,x, y, 0);
      u8 SpriteId2 = CreateSprite(&sPanel2SpriteTemplate,x+64, y, 0); 
      gSprites[SpriteId1].data[0] = counter;
      gSprites[SpriteId2].data[0] = counter; 
      counter++; 
    }
  }
  LoadSpritePalette(&ExitSpritePalette);
  LoadSpriteSheet(&ExitSpriteSheet);
  u8 SpriteId = CreateSprite(&ExitSpriteTemplate, 240-16, 160-9, 0);
  gSprites[SpriteId].data[0] = 0xFF;
}

static void DrawIcons(void) 
{
  u16 x, y; 
  x = 0;
  y = 0;
  u8 counter = 0;
  for (u8 j = 0; j<3; j++) 
  {
    if(counter==numonscreenitems)
        break; 
    for (u8 i = 0; i<2; i++) 
    {
      if(counter==numonscreenitems)
        break; 
      x = (PANEL_X -11) + (HSPACING-2+ 64/2 + 64)*i;
      y = (PANEL_Y-3)+ (VSPACING +32)*j; 
      LoadSpriteSheet(&StartMenuIconTable[onscreenmenuitems[counter]].spritesheet); 
      LoadSpritePalette(&StartMenuIconTable[onscreenmenuitems[counter]].spritepalette);
      u8 SpriteId = CreateSprite(&StartMenuIconTable[onscreenmenuitems[counter]].sprtemplate , x, y, 0);
      gSprites[SpriteId].data[0] = counter;
      gSprites[SpriteId].data[1] = 3;
      gSprites[SpriteId].data[2] = y;
      gSprites[SpriteId].data[3] = -1; 
      sStartMenuPtr->IconSpriteIds[counter] = SpriteId;
      counter++; 
    }
  }
}


static void FreeAndCloseStartMenu(u8 taskId)
{
	Free(sStartMenuPtr);
	FreeAllWindowBuffers();
	BGMVolumeMax_EnableHelpSystemReduction();
	DestroyTask(taskId);
} 

static void Task_StartMenuFadeOut(u8 taskId)
{
	if (!gPaletteFade.active)
	{
	  gHelpSystemEnabled = TRUE;
		SetMainCallback2(CB2_ReturnToField);
		FreeAndCloseStartMenu(taskId); 
	}
}

static void CleanWindow(u8 windowId)
{
	FillWindowPixelBuffer(windowId, PIXEL_FILL(0));
}

static void CleanWindows(void)
{
	for (u32 i = 0; i < WIN_COUNT; ++i)
		CleanWindow(i);
}

static void CommitWindow(u8 windowId)
{
	CopyWindowToVram(windowId,COPYWIN_BOTH);
	PutWindowTilemap(windowId);
}

static void CommitWindows(void)
{
	for (u32 i = 0; i < WIN_COUNT; ++i)
		CommitWindow(i);
}

static void PrintGUIMapName(void)
{ 
  	GetMapName(gStringVar4, GetCurrentRegionMapSectionId(), 0); 
  	WindowPrint(WIN_TOPBAR, 1, 0, 0, &sWhiteText, 0, gStringVar4); 
}

static void PrintGUIMenuItemsName(void) 
{ 
  u16 x, y;
  x = 0; 
  y = 0; 
  u8 counter = 0;
  for (u8 row = 0;row<3; row++)
  { 
    if (counter==numonscreenitems) 
      break;
    for (u8 column = 0; column<2; column++) 
    {
      if (counter==numonscreenitems) 
        break; 
      x = (PANEL_X + (HSPACING + 64/2 + 64)*column) + 8;
      y = (PANEL_Y + (VSPACING + 32)*row) - 40;
      if (onscreenmenuitems[counter]==STARTMENU_PLAYER)
        WindowPrint(WIN_ITEMS, 1, x, y, &sWhiteText, 0, gSaveBlock2Ptr->playerName); 
      else
        WindowPrint(WIN_ITEMS, 1, x, y, &sWhiteText, 0, sStartMenuOptionsTable[onscreenmenuitems[counter]].text); 
      counter++;
    }
  }
} 

void CB2_ReturnToFieldWithOpenMenu(void)
{ 
  sStartMenuPtr = Calloc(sizeof(struct StartMenuResources));
  cpos = VarGet(0x8000); 
  scrolloffset = VarGet(0x8001);
  SetMainCallback2(CB2_StartMenu);
} 


static void CalculateAndConfigureOnScreenOptions(void) 
{
  u8 counter = 0;
  for (u8 i = 0; i<6; i++)
  {
    if (i+2*scrolloffset == numitems)
      break;
    onscreenmenuitems[i] = menuitems[i+scrolloffset*2];
    counter++;
  } 
  numonscreenitems = counter;
}

static void CB2_PlayerTrainerCardFromStartMenu(void)
{
  ShowPlayerTrainerCard(CB2_ReturnToFieldWithOpenMenu);
}

static void CB2_OptionMenuFromStartMenu(void)
{
  SetMainCallback2(CB2_OptionsMenuFromStartMenu); 
  gMain.savedCallback = CB2_ReturnToFieldWithOpenMenu;
}


static void RefreshStartMenuOptions(void) 
{
  CleanWindow(WIN_ITEMS);
  for (u8 i=0; i<numonscreenitems; i++) 
    DestroySpriteAndFreeResources(&gSprites[sStartMenuPtr->IconSpriteIds[i]]);
  CalculateAndConfigureOnScreenOptions();
  DrawIcons();
  PrintGUIMenuItemsName();
  CommitWindow(WIN_ITEMS);
} 
static void CreateScrollbar(void) 
{
  LoadSpriteSheet(&ScrollBarSpriteSheet);
  LoadSpritePalette(&ScrollBarSpritePalette); 
  CreateSprite(&ScrollBarSpriteTemplate, 240-4, 48, 0);

}

void ScrollBarCallback(struct Sprite *sprite) 
{
  u8 errorCorrection;
  if (scrolloffset==(numitems/2-3+numitems%2))
    errorCorrection = 62 - (62/(numitems/2-3+numitems%2))*(numitems/2-3+numitems%2);
  else 
    errorCorrection = 0;
  if (numitems/2-3+numitems%2<= 0) 
    sprite->invisible = TRUE;
  else
    sprite->pos1.y = 48 + 62/(numitems/2-3+numitems%2)*scrolloffset + errorCorrection;
}

 

