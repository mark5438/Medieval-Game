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
    int k = 0;

    // std::cout << this->x << " : " << this->y << std::endl;
    // std::cout << node->value_size() << std::endl << std::endl;

    for (int i = 0; i < node->value_size(); i++)
    {
        if ((s[i] == ',') || (i == node->value_size() - 1))
        {
            this->values[k++] = atoi(value_buffer);
            for (int j = 0; j < 8; j++)
                value_buffer[j] = 0x00;
            curser = 0;
        }
        else
        {
            if (s[i] != 0x2C)   // ignore new line characters
                value_buffer[curser++] = s[i];
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