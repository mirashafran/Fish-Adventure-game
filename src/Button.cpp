#include "Button.h"

//Button constructor
Button::Button(const sf::Text& text, std::unique_ptr<Command> command)
    : m_text(text), m_command(std::move(command))
{
    if (!m_command) {
        throw std::invalid_argument("Invalid command provided");
    }

    m_button.setSize(BUTTON_SIZE);
    m_button.setScale(SCALE_BUTTON);
    m_button.setTexture(ResourceManager::getInstance().getTexture("buttonTexture"));
}

//Button constructor
Button::Button(const sf::Texture& texture, std::unique_ptr<Command> command)
    :m_command(std::move(command))
{
    m_button.setSize(BOARD_BUTTON_SIZE);
    m_button.setScale(SCALE_B);
    m_button.setTexture(&texture);
}

//Button constructor
Button::Button(const sf::Texture& texture)
{
    m_button.setSize(BOARD_BUTTON_SIZE);
    m_button.setScale(SCALE_B);
    m_button.setTexture(&texture);
}

void Button::setPosition(const sf::Vector2f& position)
{  
    m_position = position;
    m_button.setPosition(m_position);

    sf::FloatRect textBounds = m_text.getLocalBounds();
    float offsetX = (m_button.getSize().x - textBounds.width) / 2.0f;
    float offsetY = (m_button.getSize().y - textBounds.height) / 11.0f;
    m_text.setPosition(m_position + sf::Vector2f(offsetX, offsetY));
}

//draw the button
void Button::draw(sf::RenderWindow& window, const sf::Vector2f& mousePosition) {
    updateHover(mousePosition);
    setPosition(m_position);
    window.draw(m_button);
    window.draw(m_text);
}

//check if the button is clicked
bool Button::isClicked(const sf::Vector2f& location) const
{
    return m_button.getGlobalBounds().contains(location);
}

void Button::updateHover(const sf::Vector2f& mousePosition) 
{
    if (m_button.getGlobalBounds().contains(mousePosition))
    {
        m_button.setSize(HOVERD);
    }
    else
    {
        m_button.setSize(BUTTON_SIZE);
    }
}

//execute the command of the button
void Button::execute() const
{
    m_command->execute();
}


