
//{{BLOCK(panel)

//======================================================================
//
//	panel, 64x256@4, 
//	+ palette 16 entries, not compressed
//	+ 256 tiles not compressed
//	Total size: 32 + 8192 = 8224
//
//	Time-stamp: 2024-10-07, 16:47:12
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PANEL_H
#define GRIT_PANEL_H

#define panelTilesLen 8192
extern const unsigned char panelTiles[8192];

#define panelPalLen 32
extern const unsigned short panelPal[16];

#endif // GRIT_PANEL_H

//}}BLOCK(panel)
