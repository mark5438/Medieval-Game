#include <list>

#include "../clock/clock.hpp"

/**
 * A structure used for tilesets with animated tiles
 *
 * contains a tile_id referring to the tiles index in the maps sprite list,
 * and a duration dictating how many miliseconds thisframe will be visible,
 * before moving on to next frame.
 */
typedef struct frame
{
    int tile_id;
    int duration;
} t_frame;

/**
 * A structure defining one animated tile
 */
typedef struct animation
{
    /**
     * The tile id tells what tile will trigger this animation.
     * If a tile is present in an animation layer of the map csv files,
     * which id matches this, it will be replaced by this animation,
     * instead of the static file
     */
    int tile_id;

    /**
     * Duration is the total duration of one animation cycle,
     * hence the sum of all frames duration
     */
    int duration;

    /**
     * Ordered list of frames. Frames will be shown in the same order, as they are present in the list
     */
    std::list<t_frame> frames;
} t_animation;

int get_animation_sprite_id_now(t_animation*);