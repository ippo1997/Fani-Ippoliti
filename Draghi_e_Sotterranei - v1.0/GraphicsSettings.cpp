//
// Created by alpacox on 15/10/21.
//

#include "precompiler.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings() {
    title = "DEFAULT";
    resolution = sf:: VideoMode::getDesktopMode();
    fullscreen = false;
    frameRateLimit = 120;
}

void GraphicsSettings::loadFromFile(const std::string& path) {
    std::ifstream ifs(path);

    if (ifs.is_open()){
        std::getline(ifs, title);
        ifs >> resolution.width >> resolution.height;
        ifs >> fullscreen;
        ifs >> frameRateLimit;
    }

    ifs.close();
}
