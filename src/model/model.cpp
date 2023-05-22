#include "model.hpp"

Model::Model(){}
void Model::loadTextureFromFile(const char *path)
{
    GLuint textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(textureID == 0)
    {
        std::cout << "could not find texture file: " << path << "\n";
    }
    m_TextureID = textureID;
}
