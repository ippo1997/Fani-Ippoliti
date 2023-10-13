//
// Created by gabriele on 06/12/21.
//

#include "precompiler.h"
#include "TextTagSystem.h"

TextTagSystem::TextTagSystem(std::string font_file) {
    if(!font.loadFromFile(font_file))
        std::cout << "ERROR::TEXTTAGSYSTEM::CONSTRUCTOR::Failed to load font" << font_file << "\n";

    initTagTemplates();
    initVariables();
}

TextTagSystem::~TextTagSystem() {
    for(auto *tag : tags){
        delete tag;
    }

    for(auto &tag : tagTemplates){
        delete tag.second;
    }
}

void TextTagSystem::initVariables() {

}

void TextTagSystem::initTagTemplates() {
    tagTemplates[TagTypes::DEFAULT_TAG] = new TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Yellow, 10, 50.f, true, 100.f, 50.f, 3);
    tagTemplates[TagTypes::NEGATIVE_TAG] = new TextTag(font, "", 0.f, 0.f, 0.f, 1.f, sf::Color::Red, 12, 100.f, true, 100.f, 50.f, 3);
    tagTemplates[TagTypes::EXPERIENCE_TAG] = new TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Cyan, 15, 70.f, true, 100.f, 50.f, 3);
    tagTemplates[TagTypes::EXPERIENCE_TAG] = new TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::Cyan, 15, 70.f, true, 100.f, 50.f, 3);
    tagTemplates[TagTypes::ACHIEVEMENT_TAG] = new TextTag(font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::White, 15, 300.f, true, 30.f, 20.f, 1);
}

void TextTagSystem::addTextTag(TagTypes tag_type, float pos_x, float pos_y, const std::string& str, const std::string& prefix, const std::string& postfix) {
    std::stringstream  ss;
    ss << prefix << " " << str << " " << postfix;
    tags.push_back(new TextTag(tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(TagTypes tag_type, float pos_x, float pos_y, int i, const std::string& prefix, const std::string& postfix) {
    std::stringstream  ss;
    ss << prefix << " " << i << " " << postfix;
    tags.push_back(new TextTag(tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(TagTypes tag_type, float pos_x, float pos_y, float f, const std::string& prefix, const std::string& postfix) {
    std::stringstream  ss;
    ss << prefix << " " << f << " " << postfix;
    tags.push_back(new TextTag(tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::update(const float &dt) {
    for(size_t i = 0; i < tags.size(); ++i) {
        tags[i]->update(dt);
        if(tags[i]->isExpired()){
            delete tags[i];
            tags.erase(tags.begin() + i);
        }
    }
}

void TextTagSystem::render(sf::RenderTarget &target) {
    for(auto &tag : tags){
        tag->render(target);
    }
}

/*****************************  TEXT TAG  *****************************/

TextTagSystem::TextTag::TextTag(sf::Font &font, std::string text,
                                float pos_x, float pos_y,
                                float dir_x, float dir_y,
                                sf::Color color,
                                unsigned int char_size,
                                float lifetime, bool reverse, float speed, float acceleration, int fade_value) {
    this->text.setFont(font);
    this->text.setPosition(pos_x, pos_y);
    this->text.setFillColor(color);
    this->text.setCharacterSize(char_size);
    this->text.setString(text);

    this->dirX = dir_x;
    this->dirY = dir_y;
    this->lifetime = lifetime;
    this->speed = speed;
    this->acceleration = acceleration;
    this->fadeValue = fade_value;
    this->reverse = reverse;

    if(this->reverse){
        this->velocity.x = this->dirX * this->speed;
        this->velocity.y = this->dirY * this->speed;
    }
}

TextTagSystem::TextTag::TextTag(TextTagSystem::TextTag* tag, float pos_x, float pos_y, std::string str) {
    this->text = tag->text;
    this->text.setString(str);
    this->text.setPosition(pos_x, pos_y);

    this->dirX = tag->dirX;
    this->dirY = tag->dirY;
    this->lifetime = tag->lifetime;
    this->speed = tag->speed;
    this->acceleration = tag->acceleration;
    this->fadeValue = tag->fadeValue;
    this->reverse = tag->reverse;
    this->velocity = tag->velocity;
}

TextTagSystem::TextTag::~TextTag() {

}

bool TextTagSystem::TextTag::isExpired() const {
    return lifetime <= 0.f;
}

void TextTagSystem::TextTag::update(const float &dt) {
    if(lifetime > 0.f){
        lifetime -= 100.f * dt;

        if(acceleration > 0.f){
            if(reverse){
                velocity.x -= dirX * acceleration * dt;
                velocity.y -= dirY * acceleration * dt;

                if(std::abs(velocity.x) < 0.f)
                    velocity.x = 0.f;

                if(std::abs(velocity.y) < 0.f)
                    velocity.y = 0.f;

                text.move(velocity * dt);
            }
            else{
                velocity.x += dirX * acceleration * dt;
                velocity.y += dirY * acceleration * dt;

                if(std::abs(velocity.x) > speed)
                    velocity.x = dirX * speed;

                if(std::abs(velocity.y) > speed)
                    velocity.y = dirY * speed;

                text.move(velocity * dt);
            }
        }
        else{
            text.move(dirX * speed * dt, dirY * speed * dt);
        }

        if(fadeValue > 0 && text.getFillColor().a >= fadeValue){
            text.setFillColor(
                    sf::Color(
                    text.getFillColor().r,
                    text.getFillColor().g,
                    text.getFillColor().b,
                    text.getFillColor().a - fadeValue
                    )
            );
        }
    }
}

void TextTagSystem::TextTag::render(sf::RenderTarget &target) {
    target.draw(text);
}




