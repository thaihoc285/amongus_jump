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
    // Menu drawing code
    // ...
}

void Game::drawGameover() {
    // Gameover drawing code
    // ...
}

void Game::handleMenuInput(SDL_Event& e) {
    // Menu input handling code
    // ...
}

void Game::handlePlayingInput(SDL_Event& e) {
    // Playing input handling code
    // ...
}

void Game::handleGameoverInput(SDL_Event& e) {
    // Gameover input handling code
    // ...
}

void Game::update() {
    // Game logic update code
    // ...
}

void Game::render() {
    // Rendering code
    // ...
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
