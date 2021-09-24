#ifndef TILES_H
#define TILES_H

typedef struct Tile Tile;

#define TILESIZE 4

/* Tetris pieces:
 * TILE_T:   TILE_I:    TILE_LR:    TILE_LL:
 *    @        @@@@         @@@          @@@
 *   @@@                      @            @
 *
 * TILE_SQ:  TILE_ZR:  TILE_ZL:
 *   @@          @@         @@
 *   @@           @@       @@
 */
typedef enum {
	TILE_T,
	TILE_I,
	TILE_LR,
	TILE_LL,
	TILE_SQ,
	TILE_ZR,
	TILE_ZL,
	COUNT_TILE,
} TileType;

/* GLOBAL VARIABLES */
extern Tile *cur_tile;

/* FUNCTION PROTOTYPES */
struct Tile *new_tile(TileType t);
TileType random_tiletype();
void destroy_tile(struct Tile *t);
void move_tile(struct Tile *t, Board *b, int offset);
void lower_tile(struct Tile *t, Board *b);
void rotate_tile(struct Tile *t);
void show_or_hide_tile(struct Tile *t, Board *b, int show);

#endif
