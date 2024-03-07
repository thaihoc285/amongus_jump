#include "Game.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SQUARE_SIZE = 50;
const string WINDOW_TITLE = "Block Game";
Uint32 enemy1StartTime = 14000;
Uint32 enemy2StartTime = 8000;
Uint32 enemy3StartTime = 3000;
Uint32 enemy4StartTime = 20000;
Game::Game()
    : window(nullptr),
      renderer(nullptr),
      player(SCREEN_WIDTH / 2 - SQUARE_SIZE / 2, SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2, 0, 0, {50, 50, 50, 0}),
      player2(SCREEN_WIDTH / 2 + SQUARE_SIZE / 2, SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2, 0, 0, {250, 250, 250, 100}),
      enemy1(SCREEN_WIDTH - SQUARE_SIZE, SCREEN_HEIGHT - SQUARE_SIZE, 5, 5),
      enemy2(SCREEN_WIDTH - SQUARE_SIZE, SCREEN_HEIGHT - SQUARE_SIZE, 3, 3),
      enemy3(0, SCREEN_HEIGHT - SQUARE_SIZE, 3, 3),
      enemy4(0, 0, 3, 3),
      startTime(0),
      lastPlayTime(0),
      numLives(1),
      font(nullptr),
      heartTexture(nullptr),
      menuWidth(0),
      menuHeight(0),
      gameState(MENU) {
    initSDL();
}

Game::~Game() {
    quitSDL();
}

void Game::run() {
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        if (gameState == MENU) {
            drawMenu();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    SDL_Rect multiButtonRect = {(SCREEN_WIDTH - menuWidth) / 2, SCREEN_HEIGHT * 2 / 3, menuWidth, menuHeight};
                    if (mouseX >= multiButtonRect.x &&
                        mouseX <= multiButtonRect.x + multiButtonRect.w &&
                        mouseY >= multiButtonRect.y &&
                        mouseY <= multiButtonRect.y + multiButtonRect.h) {
                        gameState = PLAYING;
                        startTime = SDL_GetTicks();
                    }
                }
            }
        } else if (gameState == PLAYING && !quit) {
            Uint32 elapsedTime = getElapsedTime();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    player.isKeyPressed[e.key.keysym.scancode] = {true};
                    player2.isKeyPressed[e.key.keysym.scancode] = {true};
                } else if (e.type == SDL_KEYUP) {
                    player.isKeyPressed[e.key.keysym.scancode] = {false};
                    player2.isKeyPressed[e.key.keysym.scancode] = {false};
                    player.isJumping = false;
                    player2.isJumping2 = false;
                }
            }

            update();

            render();

            SDL_Delay(10);
        } else if (gameState == GAMEOVER&& !quit) {
            numLives = 1;
            drawGameover();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    return;
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
void Game::logSDLError(std::ostream& os, const std::string& msg, bool fatal) {
    os << msg << " error: " << SDL_GetError() << std::endl;
    if (fatal) {
        quitSDL();
        exit(1);
    }
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

    std::string multistart = "Multiplayer";
    SDL_Surface* multiSurface = TTF_RenderText_Solid(menuFont, multistart.c_str(), textColor);
    SDL_Texture* multiTexture = SDL_CreateTextureFromSurface(renderer, multiSurface);
    SDL_QueryTexture(multiTexture, NULL, NULL, &menuWidth, &menuHeight);
    SDL_Rect multiRect = {(SCREEN_WIDTH - menuWidth) / 2, SCREEN_HEIGHT * 2 / 3, menuWidth, menuHeight};
    SDL_RenderCopy(renderer, multiTexture, NULL, &multiRect);

    std::string singerstart = "Singerplayer";
    SDL_Surface* singerSurface = TTF_RenderText_Solid(menuFont, singerstart.c_str(), textColor);
    SDL_Texture* singerTexture = SDL_CreateTextureFromSurface(renderer, singerSurface);
    SDL_QueryTexture(singerTexture, NULL, NULL, &menuWidth, &menuHeight);
    SDL_Rect singerRect = {(SCREEN_WIDTH - menuWidth) / 2, SCREEN_HEIGHT * 1 / 2, menuWidth, menuHeight};
    SDL_RenderCopy(renderer, singerTexture, NULL, &singerRect);

    // Release resources
    TTF_CloseFont(menuFont);
    SDL_FreeSurface(multiSurface);
    SDL_DestroyTexture(multiTexture);

    SDL_FreeSurface(singerSurface);
    SDL_DestroyTexture(singerTexture);
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

    if (gameState == PLAYING) {
        // Game logic update code
        // ...

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

        player.GravityCalculation();
        player.VelocityCalculation();
        player.PositionCalculation();
        player.handleInput();

        player2.GravityCalculation();
        player2.VelocityCalculation();
        player2.PositionCalculation();
        player2.handleInput2();

        SDL_Rect playerRect = {player.x, player.y, SQUARE_SIZE, SQUARE_SIZE};
        SDL_Rect player2Rect = {player2.x, player2.y, SQUARE_SIZE, SQUARE_SIZE};
        SDL_Rect enemy1Rect = {enemy1.x, enemy1.y, SQUARE_SIZE, SQUARE_SIZE};
        SDL_Rect enemy2Rect = {enemy2.x, enemy2.y, SQUARE_SIZE, SQUARE_SIZE};
        SDL_Rect enemy3Rect = {enemy3.x, enemy3.y, SQUARE_SIZE, SQUARE_SIZE};
        SDL_Rect enemy4Rect = {enemy4.x, enemy4.y, SQUARE_SIZE, SQUARE_SIZE};

        if (isCollision(playerRect, enemy1Rect) && elapsedTime >= enemy1StartTime ||
            isCollision(playerRect, enemy2Rect) && elapsedTime >= enemy2StartTime ||
            isCollision(playerRect, enemy3Rect) && elapsedTime >= enemy3StartTime ||
            isCollision(playerRect, enemy4Rect) && elapsedTime >= enemy4StartTime ||
            isCollision(player2Rect, enemy1Rect) && elapsedTime >= enemy1StartTime ||
            isCollision(player2Rect, enemy2Rect) && elapsedTime >= enemy2StartTime ||
            isCollision(player2Rect, enemy3Rect) && elapsedTime >= enemy3StartTime ||
            isCollision(player2Rect, enemy4Rect) && elapsedTime >= enemy4StartTime) {
            numLives--;
            if (numLives == 0) {
                gameState = GAMEOVER;
                lastPlayTime = elapsedTime;
            }
        }
    }
}

void Game::render() {
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    std::string timerText = "" + std::to_string(getElapsedTime() / 1000) + ":" + to_string(getElapsedTime() % 1000); // Convert milliseconds to seconds
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, timerText.c_str(), textColor);

    if (!textSurface) {
        logSDLError(std::cout, "TTF_RenderText_Solid", true);
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (!textTexture) {
        logSDLError(std::cout, "SDL_CreateTextureFromSurface", true);
    }

    SDL_QueryTexture(textTexture, NULL, NULL, &menuWidth, &menuHeight);
    SDL_Rect textRect = {(SCREEN_WIDTH - menuWidth) / 2, 10, menuWidth, menuHeight};

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
    SDL_RenderClear(renderer);

    if (gameState == PLAYING) {
        if (getElapsedTime() >= enemy3StartTime) {
            enemy3.render(renderer);
        }

        if (getElapsedTime() >= enemy2StartTime) {
            enemy2.render(renderer);
        }

        if (getElapsedTime() >= enemy1StartTime) {
            enemy1.render(renderer);
        }

        if (getElapsedTime() >= enemy4StartTime) {
            enemy4.render(renderer);
        }

        player.render(renderer);
        player2.render(renderer);

        // Render the timer
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    } else if (gameState == MENU) {
        // Render the menu
        drawMenu();
    } else if (gameState == GAMEOVER) {
        // Render the gameover screen
        drawGameover();
    }

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
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
bool Game::isCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
        return (rect1.x < rect2.x + rect2.w &&
                rect1.x + rect1.w > rect2.x &&
                rect1.y < rect2.y + rect2.h &&
                rect1.y + rect1.h > rect2.y);
    }
void Game::waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)) {
            return;
        }
    }
}
void Game::initElement() {
    startTime = SDL_GetTicks();
    lastPlayTime = 0;
    numLives = 1;

    // Khởi tạo lại các thành viên của đối tượng player và player2
    player.x = SCREEN_WIDTH / 2 - SQUARE_SIZE / 2;
    player.y = SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2;
    player.velX = 0;
    player.velY = 0;
    player.isJumping = false;
    fill(begin(player.isKeyPressed),end(player.isKeyPressed), false);

    player2.x = SCREEN_WIDTH / 2 + SQUARE_SIZE / 2;
    player2.y = SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2;
    player2.velX = 0;
    player2.velY = 0;
    player2.isJumping2 = false;
    fill(begin(player2.isKeyPressed),end(player2.isKeyPressed), false);

    // Khởi tạo lại các thành viên của đối tượng enemy1, enemy2, enemy3, và enemy4
    enemy1.x = SCREEN_WIDTH - SQUARE_SIZE;
    enemy1.y = SCREEN_HEIGHT - SQUARE_SIZE;
    enemy1.velX = 5;
    enemy1.velY = 5;

    enemy2.x = SCREEN_WIDTH - SQUARE_SIZE;
    enemy2.y = SCREEN_HEIGHT - SQUARE_SIZE;
    enemy2.velX = 3;
    enemy2.velY = 3;

    enemy3.x = 0;
    enemy3.y = SCREEN_HEIGHT - SQUARE_SIZE;
    enemy3.velX = 3;
    enemy3.velY = 3;

    enemy4.x = 0;
    enemy4.y = 0;
    enemy4.velX = 3;
    enemy4.velY = 3;
}

