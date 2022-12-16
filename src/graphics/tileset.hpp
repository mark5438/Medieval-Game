/**
 * Tileset file.
 * Does everything that has to do with tilesets, including
 * parsing the tileset xml files and loading the graphics
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string.h>
#include <stdio.h>

#include <SFML/Graphics.hpp>

#include <rapidxml.hpp>
#include <list>

#include "animation.hpp"

/**
 * Storage for a tileset.
 * One tileset object must be initialized for each tileset needed in a specific scene
 */
class Tileset
{
private:
    unsigned int tile_width;  // The number of pixels representing one tile, in the tileset image
    unsigned int tile_height; // The number of pixels representing one tile, in the tileset image
    unsigned int tile_count;  // The amount of tiles in the loaded image
    unsigned int columns;     // Number of columns of tiles
    char file_path[512];      // The path to the tileset xml file. TODO: Not very efficient
    char *image_file_path;    // Path to the tileset image file
    unsigned int image_width;
    unsigned int image_height;
    char *tileset_name; // Each tileset has a name. Keeping the name, so different
                        // names can get different meanings. For example all tiles in
                        // a layer named animations will be animated if an animation is loaded.
                        // This way, if you need to load a tile with animation, but at other times
                        // you want to load it without animation, that is possible. You simply
                        // need to add the tiles to different layers in the map xml file

    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> *root_node = NULL;

    /**
     * Loads the xml document with the give file_path[] and saves the xml data to the variable
     * doc and the variable root_node
     */
    void load_xml_document();

    /**
     * Get an attribute from the rootnode as integer
     *
     * @param name The attribute name
     * @param length The attribute names length
     *
     * @return The integer value of the rootnodes first attribute with the given name
     */
    int get_integer_attribute(const char *name, int length);

    /**
     * Texture the image is loaded into
     */
    sf::Texture texture;

    /**
     * List of all created sprites for the tileset.
     * The list is 1 dimensional, which is way the number of
     * columns in the texturefile is kept
     */
    std::list<sf::Sprite *> sprites;

    /**
     * A list of all animations
     */
    std::list<t_animation> animations;

    /**
     * Loads the image
     */
    void load_image();

    /**
     * Loop through all tiles to check if any tiles should be animated
    */
    void read_tiles();

    /**
     * Load an animation and save it to the animations list
     */
    void load_animation(int, rapidxml::xml_node<> *);

    /**
     * Get the sprite that should be displayed one the next frame.
     *
     * @param animation A pointer to an instance of the animation struct
     *
     * @return A pointer to the sprite that should be drawn
     */
    sf::Sprite *get_animation_sprite_now(t_animation *animation);

    /**
     * Get a sprite from the sprite list at a given index,
     * the first sprite being at index 0.
     *
     * @param index The index of the sprite
     *
     * @return A pointer to the sprite at the given index
     */
    sf::Sprite *get_sprite_at_index(int index);

    /**
     *  With a given tileid, the animation is returnd
     *
     * @param tileid The tileid that the animation is bound to
     *
     * @return The anitaion object
     */
    t_animation *get_animation_tile(int tileid);

    /**
     * The index of the first sprite from this tileset in the virtual list containing
     * all the sprites. To get a sprite number at inde n, the sprite will be from this tileset
     * if (n - this->firstgid < this->tilecount); The sprite to return will have
     * this index [n - this->firstgid] in the sprite list of the object.
     */
    unsigned int firstgid;

public:
    /**
     * Construct a tileset
     *
     * @param filepath Path to the tileset xml file
     * @param firstgid The first tile id, that corresponds to the sprite this->sprites[0]
     */
    Tileset(char *filepath, int firstgid);

    /**
     * The tileset is initialized after, because only one xml file
     * can be loaded at once using rapidxml, so if I load the new file
     * in the constructor, the rest of the tilesets will be ignored.
     */
    void init();

    /**
     * Get a sprite with a given id n
     *
     * @param n The sprite id
     *
     * @return A pointer to the sprite if the id is within this tileset. NULL otherwise
     */
    sf::Sprite *get_sprite(int n);
};