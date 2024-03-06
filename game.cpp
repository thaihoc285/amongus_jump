#include "Game.h"
Game::Game() {
    window = nullptr;
    renderer = nullptr;
    font = nullptr;
    gameState = MENU;
    menuWidth = 0;
    menuHeight = 0;
    startTime = 0;
    lastPlayTime = 0;
    numLives = 1;
}

Game::~Game() {
    quitSDL();
}

void Game::run() {
    initSDL();
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        if (gameState == MENU) {
            drawMenu();
            handleMenuInput(e);
        } else if (gameState == PLAYING) {
            Uint32 elapsedTime = getElapsedTime();
            update();
            render();
            handlePlayingInput(e);

            if (elapsedTime >= enemy3StartTime) {
                enemy3.move2();
            }

            if (elapsedTime >= enemy2StartTime) {
                enemy2.move();
            }

            if (elapsedTime >= enemy1StartTime) {
                enemy1.move();
            }

            if (elapsedTime >= enemy4StartTime) {
                enemy4.move2();
            }

            SDL_Delay(10);
        } else if (gameState == GAMEOVER) {
            drawGameover();
            handleGameoverInput(e);
        }
    }
}

void Game::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(std::cout, "SDL_Init", true);
    }

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logSDLError(std::cout, "CreateWindow", true);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError(std::cout, "CreateRenderer", true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (TTF_Init() == -1) {
        logSDLError(std::cout, "TTF_Init", true);
    }

    font = TTF_OpenFont("zebulon_6918646/Zebulon.otf", 24);
    if (!font) {
        logSDLError(std::cout, "TTF_OpenFont", true);
    }
    // Load other resources and initialize variables as needed
}

void Game::drawMenu() {
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw "Start" button in the center
    SDL_Color textColor = {255, 255, 255, 255};  // White color
    TTF_Font* menuFont = TTF_OpenFont("zebulon_6918646/Zebulon.otf", 36);
    if (!menuFont) {
        logSDLError(std::cout, "TTF_OpenFont", true);
    }

    std::string startText = "Start";
    SDL_Surface* textSurface = TTF_RenderText_Solid(menuFont, startText.c_str(), textColor);
    if (!textSurface) {
        logSDLError(std::cout, "TTF_RenderText_Solid", true);
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        logSDLError(std::cout, "SDL_CreateTextureFromSurface", true);
    }

    SDL_QueryTexture(textTexture, NULL, NULL, &menuWidth, &menuHeight);
    SDL_Rect textRect = {(SCREEN_WIDTH - menuWidth) / 2, (SCREEN_HEIGHT - menuHeight) / 2, menuWidth, menuHeight};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Release resources
    TTF_CloseFont(menuFont);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void Game::drawGameover() {
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw "Start" button in the center
    SDL_Color textColor = {255, 255, 255, 255};  // White color
    TTF_Font* menuFont = TTF_OpenFont("zebulon_6918646/Zebulon.otf", 36);
    if (!menuFont) {
        logSDLError(std::cout, "TTF_OpenFont", true);
    }

    std::string timerOver = "Time Over: " + std::to_string(lastPlayTime / 1000) + ":" + std::to_string(lastPlayTime % 1000);  // Convert milliseconds to seconds
    SDL_Surface* toSurface = TTF_RenderText_Solid(font, timerOver.c_str(), textColor);
    SDL_Texture* toTexture = SDL_CreateTextureFromSurface(renderer, toSurface);
    int toWidth, toHeight;
    SDL_QueryTexture(toTexture, NULL, NULL, &toWidth, &toHeight);
    SDL_Rect toRect = {(SCREEN_WIDTH - toWidth) / 2, SCREEN_HEIGHT * 1 / 3, toWidth, toHeight};
    SDL_RenderCopy(renderer, toTexture, NULL, &toRect);

    std::string restartText = "Restart";
    SDL_Surface* rtextSurface = TTF_RenderText_Solid(menuFont, restartText.c_str(), textColor);
    SDL_Texture* rtextTexture = SDL_CreateTextureFromSurface(renderer, rtextSurface);

    SDL_QueryTexture(rtextTexture, NULL, NULL, &menuWidth, &menuHeight);
    SDL_Rect rtextRect = {(SCREEN_WIDTH - menuWidth) / 2, SCREEN_HEIGHT * 2 / 3, menuWidth, menuHeight};
    SDL_RenderCopy(renderer, rtextTexture, NULL, &rtextRect);

    // Release resources
    TTF_CloseFont(menuFont);
    SDL_FreeSurface(toSurface);
    SDL_DestroyTexture(toTexture);
    SDL_FreeSurface(rtextSurface);
    SDL_DestroyTexture(rtextTexture);

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void Game::handleMenuInput(SDL_Event& e) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quitSDL();
            exit(0);
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (mouseX >= (SCREEN_WIDTH - menuWidth) / 2 &&
                mouseX <= (SCREEN_WIDTH + menuWidth) / 2 &&
                mouseY >= (SCREEN_HEIGHT - menuHeight) / 2 &&
                mouseY <= (SCREEN_HEIGHT + menuHeight) / 2) {
                gameState = PLAYING;
                startTime = SDL_GetTicks();
            }
        }
    }
}


void Game::handlePlayingInput(SDL_Event& e) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quitSDL();
            exit(0);
        } else if (e.type == SDL_KEYDOWN) {
            player.isKeyPressed[e.key.keysym.scancode] = true;
            player2.isKeyPressed[e.key.keysym.scancode] = true;
        } else if (e.type == SDL_KEYUP) {
            player.isKeyPressed[e.key.keysym.scancode] = false;
            player2.isKeyPressed[e.key.keysym.scancode] = false;
            player.isJumping = false;
            player2.isJumping2 = false;
        }
    }
}

void Game::handleGameoverInput(SDL_Event& e) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quitSDL();
            exit(0);
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Rect restartButtonRect = {(SCREEN_WIDTH - menuWidth) / 2, SCREEN_HEIGHT * 2 / 3, menuWidth, menuHeight};
            if (mouseX >= restartButtonRect.x &&
                mouseX <= restartButtonRect.x + restartButtonRect.w &&
                mouseY >= restartButtonRect.y &&
                mouseY <= restartButtonRect.y + restartButtonRect.h) {
                initElement();
                gameState = PLAYING;
            }
        }
    }
}

void Game::update() {
    Uint32 elapsedTime = getElapsedTime();
    // Update game logic based on elapsed time
    // ...
}

void Game::render() {
    Uint32 elapsedTime = getElapsedTime();
    SDL_Color textColor = {255, 255, 255, 255};  // White color
    std::string timerText = "" + std::to_string(elapsedTime / 1000) + ":" + std::to_string(elapsedTime % 1000);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, timerText.c_str(), textColor);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int timeWidth, timeHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &timeWidth, &timeHeight);
    SDL_Rect textRect = {(SCREEN_WIDTH - timeWidth) / 2, 10, timeWidth, timeHeight};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Render other game elements based on the current state
    if (gameState == PLAYING) {
        // Render player, enemies, etc.
        // ...
    }

    // Release resources
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void Game::quitSDL() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
}

Uint32 Game::getElapsedTime() {
    return SDL_GetTicks() - startTime;
}
