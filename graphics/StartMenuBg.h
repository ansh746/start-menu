
//{{BLOCK(StartMenuBg)

//======================================================================
//
//	StartMenuBg, 256x160@4, 
//	+ palette 16 entries, not compressed
//	+ 34 tiles (t|f|p reduced) lz77 compressed
//	+ regular map (flat), lz77 compressed, 32x20 
//	Total size: 32 + 228 + 340 = 600
//
//	Time-stamp: 2024-10-07, 16:47:11
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STARTMENUBG_H
#define GRIT_STARTMENUBG_H

#define StartMenuBgTilesLen 228
extern const unsigned char StartMenuBgTiles[228];

#define StartMenuBgMapLen 340
extern const unsigned short StartMenuBgMap[170];

#define StartMenuBgPalLen 32
extern const unsigned char StartMenuBgPal[32];

#endif // GRIT_STARTMENUBG_H

//}}BLOCK(StartMenuBg)
