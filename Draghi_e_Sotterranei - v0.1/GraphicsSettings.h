//
// Created by alpacox on 15/10/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_GRAPHICSSETTINGS_H
#define DRAGHI_E_SOTTERRANEI_GRAPHICSSETTINGS_H


class GraphicsSettings{
public:
    GraphicsSettings();

    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;

    void loadFromFile(const std::string& path);

};



#endif //DRAGHI_E_SOTTERRANEI_GRAPHICSSETTINGS_H
