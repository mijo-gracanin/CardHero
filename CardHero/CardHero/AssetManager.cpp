#include <SFML/Graphics.hpp>
#include "AssetManager.h"


namespace as
{
    void AssetManager::LoadTexture(std::string name,std::string fileName)
    {
      sf::Texture tex;
      if(tex.loadFromFile(fileName))
      {
          this->_textures[name]=tex;
      }

    }
    sf::Texture &AssetManager::GetTexture(std::string name)
    {
        return this->_textures.at(name);
    }

    void AssetManager::LoadFont(std::string name,std::string fileName)
    {
      sf::Font font;
      if(font.loadFromFile(fileName))
      {
          this->_fonts[name]=font;
      }

    }
    sf::Font &AssetManager::GetFont(std::string name)
    {
        return this->_fonts.at(name);
    }

    void AssetManager::LoadSound(std::string name,std::string fileName)
    {
        sf::SoundBuffer sound;
        if(sound.loadFromFile(fileName))
        {
            this->_sounds[name]=sound;
        }

    }
    sf::SoundBuffer &AssetManager::GetSound(std::string name)
    {
        return this->_sounds.at(name);
    }

}
