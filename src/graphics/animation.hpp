#include <list>

#include <rapidxml.hpp>

#include "../clock/clock.hpp"

/**
 * A structure used for tilesets with animated tiles
 *
 * contains a tile_id referring to the tiles index in the maps sprite list,
 * and a duration dictating how many miliseconds thisframe will be visible,
 * before moving on to next frame.
 */
class Frame
{
private:
    int tile_id;
    int duration;

public:
    Frame(int, int);
    int get_tile_id() { return this->tile_id; };
    int get_duration() { return this->duration; };
};

/**
 * A structure defining one animated tile
 */
class Animation
{
private:
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
    int duration = 0;

    /**
     * Ordered list of frames. Frames will be shown in the same order, as they are present in the list
     */
    std::list<Frame *> frames;

public:
    Animation(int, rapidxml::xml_node<> *);
    /**
     * Get the id of the next sprite to show, for any given animation.
     * Function knows the clock.
     *
     * @return The id of next frame
     */
    int get_animation_sprite_id_now();
    int get_tile_id() { return this->tile_id; };
};