#include "StaticObject.h"

StaticObject::StaticObject(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int row)
    : GameObject(texture, position, size)
{
    int tileWidth = texture->getSize().x;  
    int tileHeight = texture->getSize().y / 12;  // 12 rows in texture
    
    m_character.setTextureRect(sf::IntRect(0, row * tileHeight, tileWidth, tileHeight));
}

std::vector<sf::Vector2f> StaticObject::readPositionsFromFile(const std::string& objectType)
{
    std::vector<sf::Vector2f> positions;
    std::ifstream file("positions.txt");
    std::string line;

    
    if (!file.is_open()) {
        throw std::ios_base::failure("Error opening file");
    }

    bool objectFound = false;

    // Find objectType section in file
    while (std::getline(file, line)) {
        if (line == objectType) {
            objectFound = true;
            break;
        }
    }

    // Read positions for objectType
    while (std::getline(file, line) && !line.empty() && objectFound) {
        std::istringstream iss(line);
        float x, y;
        if (iss >> x >> y) {
            positions.emplace_back(x, y);
        }
    }

    file.close();
    

    return positions;

}

