#pragma once
#include "UIElement.hpp"

namespace engine::gui::elements
{
    class ImageElement : public UIElement
    {
    public:
        ImageElement(uint16_t id, const std::string &imagePath, const sf::Vector2f &position);

        /// @brief Set the image to given url, throws if image not found at path
        /// @param newPath image path full, in project use relative `assets/image.jpeg`
        inline void setImage(const std::string &newPath);

    private:
        sf::Texture m_texture;
        std::optional<sf::Sprite> m_sprite;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
