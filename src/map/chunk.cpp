#include "chunk.hpp"

void comma_seperated_string_to_integer_array(int arr[256], char *s, std::size_t size)
{

    char value_buffer[8]; // Biggest integer 10⁸
    int curser = 0;
    int k = 0;

    for (int i = 0; i < size; i++)
    {
        if ((s[i] == ',') || (i == size - 1))
        {
            arr[k++] = atoi(value_buffer);
            for (int j = 0; j < 8; j++)
                value_buffer[j] = 0x00;
            curser = 0;
        }
        else
        {
            if (s[i] != 0x2C) // ignore new line characters
            {
                value_buffer[curser++] = s[i];
            }
        }
    }
}

Chunk::Chunk(rapidxml::xml_node<> *node)
{
    this->x = atoi(node->first_attribute("x")->value());
    this->y = atoi(node->first_attribute("y")->value());
    this->width = atoi(node->first_attribute("width")->value());
    this->height = atoi(node->first_attribute("height")->value());

    char *s = node->value();
    comma_seperated_string_to_integer_array(this->values, s, node->value_size());
}

void Chunk::add_npcs_to_list(std::list<NPC *> *list, rapidxml::xml_node<> *chunk, int start_x, int start_y)
{
    int tiles[256];
    comma_seperated_string_to_integer_array(tiles, chunk->value(), chunk->value_size());
    for (int i = 0; i < 256; i++)
    {
        if (tiles[i] != 0)
        {
            list->push_back(new NPC(start_x + (int)(i % 16), start_y + (int)(i / 16), tiles[i]));
        }
    }
}

int Chunk::get_texture_at(int x, int y)
{
    if (this->x <= x && x < this->x + this->width && this->y <= y && y < this->y + this->height)
    {
        int index = (y - this->y) * this->width + (x - this->x);
        return values[index];
    }
    else
    {
        return -1;
    }
}