//
// Created by alpacox on 28/09/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_GUI_H
#define DRAGHI_E_SOTTERRANEI_GUI_H


enum class ButtonStates {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui {
    float p2pX( float perc, const sf::VideoMode& vm);
    float p2pY( float perc, const sf::VideoMode& vm);
    unsigned calcCharSize(const sf::VideoMode& vm,  unsigned modifier = 40);

    class Button {
    public:
        Button(float x, float y, float width, float height,
            sf::Font *font, std::string text, unsigned character_size,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
            sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
            short unsigned id = 0);

        ~Button();

        bool isPressed() const;
        std::string getText() const;
        void setText( std::string text);
        const short unsigned& getId() const;
        void setId( short unsigned id);
        void update(const sf::Vector2i &mousePosWindow);
        void render(sf::RenderTarget &target);

    private:
        ButtonStates buttonState;
        short unsigned id;

        sf::RectangleShape shape;
        sf::Font *font;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;
    };

//**************************** DROP DOWN LIST *********************************

    class DropDownList{

    public:
        DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned elements, unsigned default_index = 0);
        ~DropDownList();

        const unsigned short& getActiveElementId() const;
        bool getKeytime();
        void updateKeytime(const float& dt);
        void update(const sf::Vector2i &mousePosWindow, const float& dt);
        void render(sf::RenderTarget &target);

    private:
        float keytime;
        float keytimeMax;

        sf::Font& font;
        gui::Button* activeElement;
        std::vector<gui::Button*> list;
        bool showList;

    };

//**************************** TEXTURE SELECTOR *********************************


    class TextureSelector{
    public:
        TextureSelector(float x, float y, float width, float height,
                        float gridSize, const sf::Texture* texture_sheet,
                        sf::Font& font, std::string text);
        ~TextureSelector();

        const bool& getActive() const;
        const sf::IntRect& getTextureRect() const;

        bool getKeytime();
        void updateKeytime(const float& dt);
        void update(const sf::Vector2i& mousePosWindow, const float& dt);
        void render(sf::RenderTarget &target);

    private:
        float keytime;
        const float keytimeMax;
        float gridSize;
        bool active;
        bool hidden;
        gui::Button* hideButton;
        sf::RectangleShape bounds;
        sf::Sprite sheet;
        sf::RectangleShape selector;
        sf::Vector2u mousePosGrid;
        sf::IntRect textureRect;

    };

    //**************************** PROGRESS BAR *********************************

    class ProgressBar{
    public:
        ProgressBar(float x, float y, float width, float height, int max_value,
                    sf::Color inner_color,
                    sf::VideoMode& vm, unsigned character_size,
                    sf::Font* font = nullptr
                            );
        ~ProgressBar();

        void update( int current_value);
        void render(sf::RenderTarget& target);

    private:

        std::string barString;
        sf::Text text;
        float maxWidth;
        int maxValue;
        sf::RectangleShape back;
        sf::RectangleShape inner;

    };
}
#endif //DRAGHI_E_SOTTERRANEI_GUI_H
