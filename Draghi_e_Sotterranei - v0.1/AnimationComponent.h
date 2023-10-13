//
// Created by gabriele on 02/10/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_ANIMATIONCOMPONENT_H
#define DRAGHI_E_SOTTERRANEI_ANIMATIONCOMPONENT_H

class AnimationComponent {

public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
    virtual ~AnimationComponent();

    void addAnimation(std::string key, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);
    bool play(std::string key, const float& dt, bool priority = false);
    bool play(std::string key, const float& dt, const float& modifier, const float& modifier_max, bool priority = false);

private:
    class Animation {
    public:
        sf::Sprite& sprite;
        sf::Texture& textureSheet;
        float animationTimer;
        float timer;
        bool done;
        int width;
        int height;
        sf::IntRect startRect;
        sf::IntRect currentRect;
        sf::IntRect endRect;

        Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
                : sprite(sprite), textureSheet(texture_sheet),
                animationTimer(animation_timer), timer(0.f), done(false),
                width(width), height(height){
            timer = 0.f;
            startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
            currentRect = startRect;
            endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

            sprite.setTexture(textureSheet, true);
            sprite.setTextureRect(startRect);
        }

        [[nodiscard]] const bool& isDone() const{
            return done;
        }

        const bool& play(const float& dt){
            done = false;
            timer += 100.f * dt;
            if (timer >= animationTimer){
                timer = 0.f;

                if (currentRect != endRect) {
                    currentRect.left += width;
                }
                else {
                    currentRect.left = startRect.left;
                    done = true;
                }
                sprite.setTextureRect(currentRect);
            }
            return done;
        }

        const bool& play(const float& dt,  float mod_percent){
            if(mod_percent < 0.5f)
                mod_percent = 0.5f;

            done = false;
            timer += mod_percent * 100.f * dt;
            if (timer >= animationTimer){
                timer = 0.f;

                if (currentRect != endRect) {
                    currentRect.left += width;
                }
                else {
                    currentRect.left = startRect.left;
                    done = true;
                }
                sprite.setTextureRect(currentRect);
            }
            return done;
        }

        void reset(){
            timer = animationTimer;
            currentRect = startRect;
        }
    };

    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    std::map<std::string, Animation*> animations;
    Animation* lastAnimation;
    Animation* priorityAnimation;
};


#endif //DRAGHI_E_SOTTERRANEI_ANIMATIONCOMPONENT_H
