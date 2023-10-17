//
// Created by alpacox on 28/09/21.
//

#include "precompiler.h"
#include "Gui.h"

float gui::p2pX(const float perc, const sf::VideoMode& vm) {
    /*
     * Convertire un valore percentuale in pixelsrelativamente alla risoluzione corrente nelle ascisse x.
     *
     * @param float perc            Il valore percentuale.
     * @param sf::VideoMode& vm     Attuale risoluzione della finestra.
     *
     * @return float                Il valore calcolato in pixels.
     */
    return std::floor(static_cast<float>(vm.width) * (perc/100.f));
}

float gui::p2pY(const float perc, const sf::VideoMode& vm) {
    /*
    * Convertire un valore percentuale in pixelsrelativamente alla risoluzione corrente nelle ordinate y.
    *
    * @param float perc             Il valore percentuale.
     * @param sf::VideoMode& vm     Attuale risoluzione della finestra.
     *
    * @return float                 Il valore calcolato in pixels.
    */
    return std::floor(static_cast<float>(vm.height) * (perc/100.f));

}

unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier) {
    /*
    * Calcola la dimensione del testo usando la risoluzione corrente e una costante
    *
    * @param sf::VideoMode& vm     Attuale risoluzione della finestra.
    * @param unsigned modifier     Usato per modificare la grandezza del testo.
    *
    *
    * @return unsigned             Il valore calcolato della dimensione del testo.
    */

    return static_cast<unsigned>((vm.width + vm.height)/modifier); // (1280 + 720) / 50 = 40 dove 50 è la vecchia dimensione de testo standard
}

gui::Button::Button(float x, float y, float width, float height,
              sf::Font* font, std::string text, unsigned character_size,
              sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
              sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
              sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
              short unsigned id){

    buttonState = ButtonStates::BTN_IDLE;
    this->id = id;

    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idle_color);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(outline_idle_color);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
            shape.getPosition().x + (shape.getGlobalBounds().width/ 2) - this->text.getGlobalBounds().width / 2,
            shape.getPosition().y
            );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;

    this->outlineIdleColor = outline_idle_color;
    this->outlineHoverColor = outline_hover_color;
    this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button() {

}

bool gui::Button::isPressed() const {
    if(buttonState == ButtonStates::BTN_ACTIVE)
        return true;

    return false;
}

std::string gui::Button::getText() const {
    return this->text.getString();
}

void gui::Button::setText(const std::string text) {
    this->text.setString(text);
}

const short unsigned &gui::Button::getId() const {
    return id;
}

void gui::Button::setId(const unsigned short id) {
    this->id = id;
}

void gui::Button::render(sf::RenderTarget& target) {

    target.draw(shape);
    target.draw(text);
}

void gui::Button::update(const sf::Vector2i& mousePosWindow) {

    //Idle
    buttonState = ButtonStates::BTN_IDLE;

    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))){
        //Hover
        buttonState = ButtonStates::BTN_HOVER;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            //Active
            buttonState = ButtonStates::BTN_ACTIVE;
        }
    }

    switch (buttonState){
        case ButtonStates::BTN_IDLE:
            shape.setFillColor(idleColor);
            text.setFillColor(textIdleColor);
            shape.setOutlineColor(outlineIdleColor);
            break;

        case ButtonStates::BTN_HOVER:
            shape.setFillColor(hoverColor);
            text.setFillColor(textHoverColor);
            shape.setOutlineColor(outlineHoverColor);
            break;

        case ButtonStates::BTN_ACTIVE:
            shape.setFillColor(activeColor);
            text.setFillColor(textActiveColor);
            shape.setOutlineColor(outlineActiveColor);
            break;
    }
}


///**************************** DROP DOWN LIST *********************************

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned elements, unsigned default_index)
: font(font), showList(false), keytimeMax(3.f), keytime(0.f){

    activeElement = new gui::Button(
            x, y, width, height,
            &this->font, list[default_index], 25,
            sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 250), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
            sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
    );

    for(unsigned i = 0; i < elements; i++) {

        this->list.push_back(
                new gui::Button(
                        x, y + (i+1) * height, width, height,
                        &this->font, list[i], 25,
                        sf::Color(255, 255, 255, 150), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                        sf::Color(70, 70, 70, 250), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                        sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
                        i
                )
        );
    }
}

gui::DropDownList::~DropDownList() {
    delete activeElement;
    for(size_t i = 0; i < list.size(); i++){
        delete list[i];
    }
}

const unsigned short &gui::DropDownList::getActiveElementId() const {

    return activeElement->getId();
}

bool gui::DropDownList::getKeytime() {
    if(keytime >= keytimeMax){
        keytime = 0.f;
        return true;
    }
    return false;
}

void gui::DropDownList::updateKeytime(const float& dt) {
    if(keytime < keytimeMax)
        keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2i &mousePosWindow, const float& dt) {
    updateKeytime(dt);
    activeElement->update(mousePosWindow);

    if(activeElement->isPressed() && getKeytime()){
        if(showList)
            showList = false;
        else
            showList = true;
    }
    if(showList) {
        for (auto &i: list) {
            i->update(mousePosWindow);

            if (i->isPressed() && getKeytime()){
                showList = false;
                activeElement->setText(i->getText());
                activeElement->setId(i->getId());
            }
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget &target) {
    activeElement->render(target);

    if(showList) {
        for (auto &i: list) {
            i->render(target);
        }
    }
}


///**************************** TEXTURE SELECTOR *********************************

gui::TextureSelector::TextureSelector(float x, float y, float width, float height,
                                      float gridSize, const sf::Texture* texture_sheet,
                                      sf::Font& font, std::string text):
                                      keytimeMax(3.f), keytime(0.f){
    this->gridSize = gridSize;
    active = false;
    hidden = false;
    float offset = gridSize;

    bounds.setSize(sf::Vector2f(width, height));
    bounds.setPosition(x + offset, y);
    bounds.setFillColor(sf::Color(50, 50, 50, 100));
    bounds.setOutlineThickness(1.f);
    bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    sheet.setTexture(*texture_sheet);
    sheet.setPosition(x + offset, y);

    if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width)
        sheet.setTextureRect(
                sf::IntRect(0, 0, static_cast<int>(bounds.getGlobalBounds().width), static_cast<int>(sheet.getGlobalBounds().height)));

    if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
        sheet.setTextureRect(
                sf::IntRect(0, 0, static_cast<int>(bounds.getGlobalBounds().width), static_cast<int>(sheet.getGlobalBounds().height)));

    selector.setPosition(x+ offset, y);
    selector.setSize(sf::Vector2f(gridSize, gridSize));
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineThickness(1.f);
    selector.setOutlineColor(sf::Color::Red);

    textureRect.width = static_cast<int>(gridSize);
    textureRect.height = static_cast<int>(gridSize);

    hideButton =  new gui::Button(
            x - 40, y, 50.f, 50.f,
            &font, text, 30,
            sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
            sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));
}

gui::TextureSelector::~TextureSelector() {
    delete hideButton;
}

const bool &gui::TextureSelector::getActive() const {
    return active;
}

const sf::IntRect &gui::TextureSelector::getTextureRect() const {
    return textureRect;
}

bool gui::TextureSelector::getKeytime() {
    if(keytime >= keytimeMax){
        keytime = 0.f;
        return true;
    }
    return false;
}

void gui::TextureSelector::updateKeytime(const float& dt) {
    if(keytime < keytimeMax)
        keytime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt) {
    updateKeytime(dt);
    hideButton->update(mousePosWindow);

    if(hideButton->isPressed() && getKeytime()){
        if(hidden)
            hidden = false;
        else
            hidden = true;
    }

    if(!hidden){
        active = false;
        if(bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
            active = true;

            mousePosGrid.x = (mousePosWindow.x - static_cast<int>(bounds.getPosition().x)) / static_cast<unsigned>(gridSize);
            mousePosGrid.y = (mousePosWindow.y - static_cast<int>(bounds.getPosition().y)) / static_cast<unsigned>(gridSize);

            selector.setPosition(
                    bounds.getPosition().x + mousePosGrid.x * gridSize,
                    bounds.getPosition().y + mousePosGrid.y * gridSize);

            textureRect.left = static_cast<int>(selector.getPosition().x - bounds.getPosition().x);
            textureRect.top = static_cast<int>(selector.getPosition().y - bounds.getPosition().y);
    }
}

void gui::TextureSelector::render(sf::RenderTarget &target) {
    hideButton->render(target);

    if(!hidden){
        target.draw(bounds);
        target.draw(sheet);

        if(active)
            target.draw(selector);
    }
    hideButton->render(target);
}


///**************************** PROGRESS BAR *********************************

gui::ProgressBar::ProgressBar(float _x, float _y, float _width, float _height, int max_value,
                              sf::Color color,
                              sf::VideoMode& vm, unsigned character_size,
                              sf::Font* font) {

    float width = gui::p2pX(_width, vm);
    float height = gui::p2pY(_height, vm);
    float x = gui::p2pX(_x, vm);
    float y = gui::p2pY(_y, vm);

    maxWidth = width;
    maxValue = max_value;

    back.setSize(sf::Vector2f(width, height));
    back.setFillColor(sf::Color(0, 0, 0, 200));
    back.setOutlineThickness(2);
    back.setOutlineColor(sf::Color::White);
    back.setPosition(x, y);

    inner.setSize(sf::Vector2f(width, height));
    inner.setFillColor(color);
    inner.setPosition(this->back.getPosition());

    if(font){
        text.setFont(*font);
        text.setCharacterSize(gui::calcCharSize(vm, character_size));
        text.setPosition(
                inner.getPosition().x + gui::p2pX(0.78f, vm),
                inner.getPosition().y - gui::p2pY(0.69f, vm)
        );
    }
}

gui::ProgressBar::~ProgressBar() {

}

void gui::ProgressBar::update(const int current_value) {
    float percent = static_cast<float>(current_value) / static_cast<float>(maxValue);

    inner.setSize(sf::Vector2f(static_cast<float>(std::floor(maxWidth * percent)), inner.getSize().y));

    barString = std::to_string(current_value) + "/" + std::to_string(maxValue);
    text.setString(barString);
}

void gui::ProgressBar::render(sf::RenderTarget& target) {
    target.draw(back);
    target.draw(inner);
    target.draw(text);
}
