#pragma once

#include <map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace as
{
    class AssetManager
    {
    public:
        AssetManager() {}
        ~AssetManager() {}

        void LoadTexture(std::string name,std::string fileName);
        sf::Texture &GetTexture(std::string name);

        void LoadFont(std::string name,std::string fileName);
        sf::Font &GetFont(std::string name);

         void LoadSound(std::string name,std::string fileName);
        sf::SoundBuffer &GetSound(std::string name);

    private:
        std::map<std::string,sf::Texture> _textures;
        std::map<std::string,sf::Font> _fonts;
        std::map<std::string,sf::SoundBuffer> _sounds;


    };
}
