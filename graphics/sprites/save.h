
//{{BLOCK(save)

//======================================================================
//
//	save, 32x64@4, 
//	+ palette 16 entries, not compressed
//	+ 32 tiles not compressed
//	Total size: 32 + 1024 = 1056
//
//	Time-stamp: 2024-10-07, 16:47:11
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SAVE_H
#define GRIT_SAVE_H

#define saveTilesLen 1024
extern const unsigned char saveTiles[1024];

#define savePalLen 32
extern const unsigned short savePal[16];

#endif // GRIT_SAVE_H

//}}BLOCK(save)
