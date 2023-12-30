#ifndef GUARD_POKEMON_ICON_H
#define GUARD_POKEMON_ICON_H

u16 GetUnownLetterByPersonality(u32 personality);
void LoadMonIconPalettes(void);
u8 CreateMonIcon(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, u32 personality, bool32 extra);
void SpriteCB_PokeIcon(struct Sprite *sprite);
#endif // GUARD_POKEMON_ICON_H