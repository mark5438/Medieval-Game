#include "chunk.hpp"

Chunk::Chunk(rapidxml::xml_node<> *node)
{
    this->x = atoi(node->first_attribute("x")->value());
    this->y = atoi(node->first_attribute("y")->value());
    this->width = atoi(node->first_attribute("width")->value());
    this->height = atoi(node->first_attribute("height")->value());

    char *s = node->value();

    char value_buffer[8]; // Biggest integer 10⁸
    int curser = 0;

    for (int i = 0, k = 0; i < node->value_size(); i++)
    {
        if (s[0] == ',')
        {
            this->values[k++] = atoi(value_buffer);
            for (int j = 0; j < 8; j++)
                value_buffer[j] = 0x00;
            curser = 0;
        }
        else
        {
            value_buffer[curser++] = s[0];
        }

        s++;
    }
}

int Chunk::get_texture_at(int x, int y)
{
    if (this->x <= x < this->x + this->width && this->y <= y < this->y + this->height)
    {
        int index = (y - this->y) * this->width + (x - this->x);
        return values[index];
    }
    else
    {
        return -1;
    }
}