//
// Created by gabriele on 02/10/21.
//

#include "precompiler.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
    :sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent() {
    for (auto &i : animations){
        delete i.second;
    }
}

void AnimationComponent::addAnimation(const std::string key, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height) {
    animations[key] = new Animation(sprite, textureSheet, animation_timer, start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

bool AnimationComponent::play(const std::string key, const float &dt, const bool priority) {
    if(priorityAnimation){
        if(priorityAnimation == animations[key]){
            if (lastAnimation != animations[key]) {
                if (lastAnimation == nullptr)
                    lastAnimation = animations[key];
                else {
                    lastAnimation->reset();
                    lastAnimation = animations[key];
                }
            }
            if(animations[key]->play(dt)){
                priorityAnimation = nullptr;
            }
        }
    }
    else {
        if(priority){
            priorityAnimation = animations[key];
        }
        if (lastAnimation != animations[key]) {
            if (lastAnimation == nullptr)
                lastAnimation = animations[key];
            else {
                lastAnimation->reset();
                lastAnimation = animations[key];
            }
        }
        animations[key]->play(dt);
    }
    return animations[key]->isDone();
}

bool AnimationComponent::play(const std::string key, const float &dt, const float &modifier, const float &modifier_max, const bool priority) {
    if(priorityAnimation){
        if(priorityAnimation == animations[key]){
            if (lastAnimation != animations[key]) {
                if (lastAnimation == nullptr)
                    lastAnimation = animations[key];
                else {
                    lastAnimation->reset();
                    lastAnimation = animations[key];
                }
            }
            if(animations[key]->play(dt, std::abs(modifier / modifier_max))) {
                priorityAnimation = nullptr;
            }
        }
    }
    else {
        if(priority){
            priorityAnimation = animations[key];
        }
        if (lastAnimation != animations[key]) {
            if (lastAnimation == nullptr)
                lastAnimation = animations[key];
            else {
                lastAnimation->reset();
                lastAnimation = animations[key];
            }
        }
        animations[key]->play(dt, std::abs(modifier / modifier_max));
    }
    return animations[key]->isDone();
}
