#include "Game.h"
Game::Game()
    : window(nullptr),
      renderer(nullptr),
      player(SCREEN_WIDTH / 2 - SQUARE_SIZE / 2, SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2, 5, 0,0.6,{50, 50, 50, 0},"image/spiderleft.png","image/spiderright.png",1,SQUARE_SIZE),
      player2(SCREEN_WIDTH / 2 + SQUARE_SIZE / 2, SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2, 5, 0,0.6,{250, 250, 250, 100},"image/captainleft.png","image/captainright.png",1,SQUARE_SIZE),
      startTime(0),
      lastPlayTime(0),
      font(nullptr),
      resultSaved (false),
      lastEnemySpawnTime(0),
      lastItemSpawnTime(0),
      lastBigeSpawnTime(0),
      ismulti(true),
      player1lose(false),
      frameStart(0),
      frameTime(0),
      gameState(MENU){
        initSDL();
}

Game::~Game() {
    quitSDL();
}

void Game::run() {
    SDL_Event e;
    bool quit = false;
    while (!quit) {
            frameStart = SDL_GetTicks();
        if (gameState == MENU) {
            drawMenu();
            handleMenuInput(e,quit);
        } else if (gameState == PLAYING && !quit) {
            handlePlayingInput(e,quit);
        } else if (gameState == GAMEOVER&& !quit) {
            drawGameover();
            handleGameoverInput(e,quit);
        }else if(gameState == HIGHSCORE && !quit){
            drawHighscore();
            handleHighscore(e,quit);
        }
    }
}
void Game::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(cout, "SDL_Init", true);
    }
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logSDLError(cout, "CreateWindow", true);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError(cout, "CreateRenderer", true);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (TTF_Init() == -1) {
        logSDLError(cout, "TTF_Init", true);
    }
    font = TTF_OpenFont("zebulon_6918646/Zebulon.otf", 24);
    font36 = TTF_OpenFont("zebulon_6918646/Zebulon.otf", 36);
    font68 = TTF_OpenFont("zebulon_6918646/Zebulon Hollow.otf", 68);
    font28 = TTF_OpenFont("zebulon_6918646/Zebulon.otf", 28);
    font32 = TTF_OpenFont("zebulon_6918646/Zebulon.otf", 32);
    if (!font28 || !font36 || !font || !font68 || !font32) {
        logSDLError(cout, "TTF_OpenFont", true);
    }
    if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1)logSDLError(cout, "TTF_Mixer", true);
    sound_cls_item[0]=Mix_LoadWAV("sound/explosion.wav");
    sound_cls_item[1]=Mix_LoadWAV("sound/ghost.wav");
    sound_cls_item[2]=Mix_LoadWAV("sound/monster.wav");
    sound_cls_item[3]=Mix_LoadWAV("sound/fly.wav");
    sound_gameover = Mix_LoadWAV("sound/gameover.wav");
    sound_monstereat = Mix_LoadWAV("sound/monstereat.wav");
    sound_mouseclick = Mix_LoadWAV("sound/mouseclick.wav");
    sound_jump = Mix_LoadWAV("sound/jump.wav");
    Mix_VolumeChunk(sound_mouseclick, MIX_MAX_VOLUME /4);
    Mix_VolumeChunk(sound_cls_item[0], MIX_MAX_VOLUME /6);
    Mix_VolumeChunk(sound_cls_item[2], MIX_MAX_VOLUME /3);
    Mix_VolumeChunk(sound_cls_item[1], MIX_MAX_VOLUME /2);
    Mix_VolumeChunk(sound_monstereat, MIX_MAX_VOLUME /3);
}
void Game::logSDLError(ostream& os, const string& msg, bool fatal) {
    os << msg << " error: " << SDL_GetError() << endl;
    if (fatal) {
        quitSDL();
        exit(1);
    }
}
 void Game::buttoncanclick(const string& text, SDL_Color color, int x,int y, TTF_Font* font,int &widthtexture,int &heighttexture) {
     SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
     SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
     SDL_QueryTexture(texture, NULL, NULL, &widthtexture, &heighttexture);
     SDL_Rect rect = {x,y, widthtexture, heighttexture};
     SDL_RenderCopy(renderer, texture, nullptr, &rect);
     SDL_FreeSurface(surface);
     SDL_DestroyTexture(texture);
 }
 void Game::buttoncantclick(const string& text, SDL_Color color, int x, int y, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    int xPos = (x == 0) ? (SCREEN_WIDTH - surface->w) / 2 : x;
    SDL_Rect rect = {xPos, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void Game::drawMenu() {
    SDL_RenderClear(renderer);
    string path = "image/amongusbg1.jpg";
    SDL_Surface* menuSurface = IMG_Load( path.c_str());
    SDL_Texture* menuTexture = SDL_CreateTextureFromSurface( renderer, menuSurface );
    SDL_Rect menuRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, menuTexture, NULL, &menuRect);
    buttoncanclick("Multiplayer",textColor,(SCREEN_WIDTH - widhbutton2) / 2, SCREEN_HEIGHT * 2 / 3,font36,widhbutton2,heightbutton2);
    buttoncanclick("Singerplayer",textColor,(SCREEN_WIDTH - widthbutton1) / 2, SCREEN_HEIGHT * 1 / 2,font36,widthbutton1,heightbutton1);
    buttoncanclick("Highscore",textColor,(SCREEN_WIDTH - widthbutton3) / 2, SCREEN_HEIGHT * 4 / 5,font36,widthbutton3,heightbutton3);
    SDL_FreeSurface(menuSurface);
    SDL_DestroyTexture(menuTexture);
    // Present the renderer
    SDL_RenderPresent(renderer);
}

void Game::drawGameover() {
    SDL_RenderClear(renderer);
    int timeposition = SCREEN_HEIGHT * 1/3;
    string path = "image/gameoveramongus1.png";
    SDL_Surface* gameoverSurface = IMG_Load( path.c_str());
    SDL_Texture* gameoverTexture = SDL_CreateTextureFromSurface( renderer, gameoverSurface );
    SDL_Rect gameoverRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, gameoverTexture, NULL, &gameoverRect);
    if(ismulti){
        timeposition=SCREEN_HEIGHT * 1/10;
        string restartText = "Winner";
        buttoncantclick("Winner",textColor,0, SCREEN_HEIGHT * 1/4,font36);
        string path ;
        if(player1lose){
        path = "image/captainright.png";
        }else path = "image/spiderright.png";
        SDL_Surface* playerwinSurface = IMG_Load( path.c_str());
        SDL_Texture* playerwinTexture = SDL_CreateTextureFromSurface( renderer, playerwinSurface );
        SDL_Rect playerwinRect = {(SCREEN_WIDTH - 170) / 2, SCREEN_HEIGHT *7/20, 150, 150};
        SDL_RenderCopy(renderer, playerwinTexture, NULL, &playerwinRect);
        SDL_FreeSurface( playerwinSurface );
        SDL_DestroyTexture(playerwinTexture);
    }
    string scoretime = formatTime(lastPlayTime / 1000);
    if(!resultSaved&&!ismulti){
        ofstream file("score.txt",ios::app);
        file << scoretime<<endl;
        file.close();
        resultSaved = true;
    }

    buttoncantclick("Time Over: " + scoretime,textColor,0, timeposition,font);
    buttoncanclick("Restart",textColor,(SCREEN_WIDTH - widthbutton1) / 2, SCREEN_HEIGHT * 3 / 5,font36,widthbutton1,heightbutton1);
    buttoncanclick("Menu",textColor,(SCREEN_WIDTH - widhbutton2) / 2, SCREEN_HEIGHT * 3 / 4,font28,widhbutton2,heightbutton2);
    SDL_FreeSurface( gameoverSurface );
    SDL_DestroyTexture(gameoverTexture);
    SDL_RenderPresent(renderer);
}

void Game::drawHighscore(){
    SDL_RenderClear(renderer);
    string path = "image/playingbg2.png";
    SDL_Surface* highscoreSurface = IMG_Load( path.c_str());
    SDL_Texture* highscoreTexture = SDL_CreateTextureFromSurface( renderer, highscoreSurface );
    SDL_Rect menuRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, highscoreTexture, NULL, &menuRect);
    if (!font28) {
        logSDLError(cout, "TTF_OpenFont", true);
    }
    ifstream file("score.txt");
    vector<string> scores;
    string score;
    while (file >> score) {
        scores.push_back(score);
    }
    file.close();
    sort(scores.begin(), scores.end(), greater<string>());
    const int maxPlayers = min(5, (int)scores.size());
    for (int i = 0; i < maxPlayers; ++i) {
        buttoncantclick(to_string(i + 1),textColor,0.1 * SCREEN_WIDTH,(i + 1) * 0.14 * SCREEN_HEIGHT + 50,font32);
        buttoncantclick(scores[i],textColor,0.75 * SCREEN_WIDTH,(i + 1) * 0.14 * SCREEN_HEIGHT + 50,font32);
    }
    buttoncanclick("Exit",textColor,0.87*SCREEN_WIDTH, 0.9*SCREEN_HEIGHT,font28,widthbutton1,heightbutton1);
    buttoncantclick("Highscore",textColor,0, .02*SCREEN_HEIGHT,font68);
    SDL_FreeSurface(highscoreSurface);
    SDL_DestroyTexture(highscoreTexture);
    SDL_RenderPresent(renderer);
}
void Game::handleMenuInput(SDL_Event& e,bool& quit) {
while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
        quit = true;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Rect multiButtonRect = {(SCREEN_WIDTH - widhbutton2) / 2, SCREEN_HEIGHT * 2 / 3, widhbutton2, heightbutton2};
        SDL_Rect singerButtonRect = {(SCREEN_WIDTH - widthbutton1) / 2, SCREEN_HEIGHT * 1 / 2, widthbutton1, heightbutton1};
        SDL_Rect highscoreButtonRect = {(SCREEN_WIDTH - widthbutton3) / 2, SCREEN_HEIGHT * 4 / 5, widthbutton3, heightbutton3};
        if (mouseX >= multiButtonRect.x &&
            mouseX <= multiButtonRect.x + multiButtonRect.w &&
            mouseY >= multiButtonRect.y &&
            mouseY <= multiButtonRect.y + multiButtonRect.h) {
                Mix_PlayChannel(-1,sound_mouseclick,0);
                gameState = PLAYING;
                startTime = SDL_GetTicks();
        }else if(mouseX >= singerButtonRect.x &&
            mouseX <= singerButtonRect.x + singerButtonRect.w &&
            mouseY >= singerButtonRect.y &&
            mouseY <= singerButtonRect.y + singerButtonRect.h) {
                Mix_PlayChannel(-1,sound_mouseclick,0);
                singerplayer();
                gameState = PLAYING;
                startTime = SDL_GetTicks();
        }else if(mouseX >= highscoreButtonRect.x &&
            mouseX <= highscoreButtonRect.x + highscoreButtonRect.w &&
            mouseY >= highscoreButtonRect.y &&
            mouseY <= highscoreButtonRect.y + highscoreButtonRect.h){
                Mix_PlayChannel(-1,sound_mouseclick,0);
                gameState = HIGHSCORE;
        }
    }
}
}

void Game::handlePlayingInput(SDL_Event& e,bool& quit) {
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
    frameTime = SDL_GetTicks() - frameStart;
    if (FrameDelay > frameTime) {
        SDL_Delay(FrameDelay - frameTime);
    }
}

void Game::handleHighscore(SDL_Event& e,bool& quit){
  while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
          quit = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
          int mouseX, mouseY;
          SDL_GetMouseState(&mouseX, &mouseY);
          SDL_Rect exitButtonRect = {0.87*SCREEN_WIDTH, 0.9*SCREEN_HEIGHT, widthbutton1, heightbutton1};
          if (mouseX >= exitButtonRect.x &&
              mouseX <= exitButtonRect.x + exitButtonRect.w &&
              mouseY >= exitButtonRect.y &&
              mouseY <= exitButtonRect.y + exitButtonRect.h) {
                  Mix_PlayChannel(-1,sound_mouseclick,0);
                    gameState = MENU;
            }
      }
  }
}

void Game::handleGameoverInput(SDL_Event& e,bool& quit) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Rect restartButtonRect = {(SCREEN_WIDTH - widthbutton1) / 2, SCREEN_HEIGHT * 3 / 5, widthbutton1, heightbutton1};
            SDL_Rect backmenuButtonRect = {(SCREEN_WIDTH - widhbutton2) / 2, SCREEN_HEIGHT * 3 / 4, widhbutton2, heightbutton2};
            if (mouseX >= restartButtonRect.x &&
                mouseX <= restartButtonRect.x + restartButtonRect.w &&
                mouseY >= restartButtonRect.y &&
                mouseY <= restartButtonRect.y + restartButtonRect.h) {
                    Mix_PlayChannel(-1,sound_mouseclick,0);
                initElement();
                gameState = PLAYING;
                resultSaved = false;
            }else if (mouseX >= backmenuButtonRect.x &&
                mouseX <= backmenuButtonRect.x + backmenuButtonRect.w &&
                mouseY >= backmenuButtonRect.y &&
                mouseY <= backmenuButtonRect.y + backmenuButtonRect.h) {
                    Mix_PlayChannel(-1,sound_mouseclick,0);
                    ismulti = true;
                    initElement();
                    gameState = MENU;
                    resultSaved = false;
                }
        }
    }
}

void Game::update() {
    Uint32 elapsedTime = getElapsedTime();

    if (elapsedTime - lastEnemySpawnTime >= ENEMY_SPAWN_INTERVAL ) {
        spawnEnemy();
        lastEnemySpawnTime = elapsedTime;
    }
    if (elapsedTime - lastBigeSpawnTime >= BIGE_SPAWN_INTERVAL ) {
        spawnBigE();
        lastBigeSpawnTime = elapsedTime;
    }
    if (elapsedTime - lastItemSpawnTime >= ITEM_SPAWN_INTERVAL ) {
        spawnItem();
        lastItemSpawnTime = elapsedTime;
    }
    for (auto& enemy : enemies) {
        enemy.move();
    }
    for (auto& bige : biges) {
        bige.move();
    }
    player.GravityCalculation();
    player.VelocityCalculation();
    player.PositionCalculation();
    player.handleInput();
    if(ismulti){
        player2.GravityCalculation();
        player2.VelocityCalculation();
        player2.PositionCalculation();
        player2.handleInput2();
    }
    SDL_Rect playerRect = {player.x, player.y, player.playersize, player.playersize};
    SDL_Rect player2Rect = {player2.x, player2.y, player2.playersize, player2.playersize};
    for (auto it = skills.begin(); it != skills.end();) {
        if (isCollision(playerRect, {it->x, it->y, ITEM_SIZE, ITEM_SIZE})) {
            it->power(enemies,player);
            if(it->option == "bomb"){
                Explosion explosion(player.x, player.y, "image/explosion.png",SDL_GetTicks());
                explosion.init(renderer);
                explosions.push_back(explosion);
                Mix_PlayChannel(-1,sound_cls_item[0],0);
            }else if (it->option == "invisible"){
                Invisible invisible(player,SDL_GetTicks());
                invisible.initplayer("image/spiderleft.png","image/spiderright.png");
                Mix_PlayChannel(-1,sound_cls_item[1],0);
                invisibles.push_back(invisible);
            }else if (it->option == "monster"){
                Monster monster(player);
                monster.initplayer("image/spiderleft.png","image/spiderright.png");
                monsters.push_back(monster);
                Mix_PlayChannel(-1,sound_cls_item[2],0);
            }else if (it -> option == "nogravity"){
                Nogravity nogravity(player,SDL_GetTicks());
                nogravity.initplayer();
                nogravities.push_back(nogravity);
                Mix_PlayChannel(-1,sound_cls_item[3],0);
            }
            skills.erase(it);
        }else if(isCollision(player2Rect, {it->x, it->y, ITEM_SIZE, ITEM_SIZE})){
            it->power(enemies,player2);
            if(it->option == "bomb"){
                Explosion explosion(player2.x, player2.y, "image/explosion.png",SDL_GetTicks());
                explosion.init(renderer);
                explosions.push_back(explosion);
                Mix_PlayChannel(-1,sound_cls_item[0],0);
            }else if (it->option == "invisible"){
                Invisible invisible(player2,SDL_GetTicks());
                invisible.initplayer("image/captainleft.png","image/captainright.png");
                Mix_PlayChannel(-1,sound_cls_item[1],0);
                invisibles.push_back(invisible);
            }else if (it->option == "monster"){
                Monster monster(player2);
                monster.initplayer("image/captainleft.png","image/captainright.png");
                monsters.push_back(monster);
                Mix_PlayChannel(-1,sound_cls_item[2],0);
            }else if (it -> option == "nogravity"){
                Nogravity nogravity(player2,SDL_GetTicks());
                nogravity.initplayer();
                nogravities.push_back(nogravity);
                Mix_PlayChannel(-1,sound_cls_item[3],0);
            }
            skills.erase(it);
        }
        else {
             ++it;
        }
    }
   for (auto& enemy : enemies) {
       if((checkPlayerEnemyCollision(player, enemy)&&!player.ismonster)){
           player1lose = true;
           player.numlives-- ;
       }else if((checkPlayerEnemyCollision(player2, enemy)&&!player2.ismonster)&&ismulti){
           player2.numlives-- ;
       }
   }
   for (auto& bige : biges) {
       if((checkPlayerBigeCollision(player, bige))
       ||(player2.ismonster&&checkPlayerCharacterCollision(player, player2))){
           player1lose = true;
           player.numlives-- ;
       }else if((checkPlayerBigeCollision(player2, bige))&&ismulti){
           player2.numlives-- ;
       }
   }
   if(player2.ismonster&&checkPlayerCharacterCollision(player, player2)){
        player1lose = true;
        player.numlives-- ;
   }else if((player.ismonster&&checkPlayerCharacterCollision(player2,player))&&ismulti)player2.numlives--;
   if (!(player.numlives&&player2.numlives)) {
            Mix_HaltChannel(-1);
            Mix_PlayChannel(-1,sound_gameover,0);
            gameState = GAMEOVER;
            lastPlayTime = elapsedTime;
       }
}
string Game::formatTime(int timeInSeconds) {
    int minutes = timeInSeconds / 60;
    int seconds = timeInSeconds % 60;
    string formattedMinutes = (minutes < 10) ? "0" + to_string(minutes) : to_string(minutes);
    string formattedSeconds = (seconds < 10) ? "0" + to_string(seconds) : to_string(seconds);
    return formattedMinutes + ":" + formattedSeconds;
}
void Game::render() {
    SDL_RenderClear(renderer);
    string path = "image/playingbg2.png";
    SDL_Surface* gameSurface = IMG_Load( path.c_str());
    SDL_Texture* gameTexture = SDL_CreateTextureFromSurface( renderer, gameSurface );
    SDL_Rect gameRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, gameTexture, NULL, &gameRect);
    string timerText = formatTime(getElapsedTime()/1000);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, timerText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//    SDL_QueryTexture(textTexture, NULL, NULL, &menuWidth, &menuHeight);
    SDL_Rect textRect = {(SCREEN_WIDTH - textSurface->w) / 2, 10, textSurface->w, textSurface->h};

    for (auto& skill : skills)skill.render(renderer);
    for (auto& enemy : enemies)enemy.render(renderer);
    for (auto& bige : biges)bige.render(renderer);
    for (auto& explosion : explosions) {
        if(SDL_GetTicks() - explosion.inittime<360)
            explosion.render(renderer);
    }
    for(auto it = monsters.begin(); it != monsters.end();) {
        if(!player.ismonster && it->playermon==&player && !player.isghost || (!player2.ismonster && it->playermon == &player2 && !player2.isghost)){
                it->endtime();
                monsters.erase(it);
        }
        else it++;
    }
    for (auto it = enemies.begin(); it!= enemies.end();) {
        if(checkPlayerEnemyCollision(player, *it)&&player.ismonster&&!player.isghost){
            enemies.erase(it);
            Mix_PlayChannel(-1,sound_monstereat,0);
            player.ismonster = false;
        }else if(checkPlayerEnemyCollision(player2, *it)&&ismulti&&player2.ismonster&&!player2.isghost){
            enemies.erase(it);
            player2.ismonster = false;
            Mix_PlayChannel(-1,sound_monstereat,0);
        }else it++;
    }
    for(auto it = invisibles.begin(); it != invisibles.end();){
        if(SDL_GetTicks() - it->inittime > 4000){
            it->endtime();
            invisibles.erase(it);
        }else {
            it++;
        }
    }
    for(auto it = nogravities.begin(); it != nogravities.end();){
        if(SDL_GetTicks() - it->inittime > 7000){
            it->endtime();
            nogravities.erase(it);
        }else {
            it++;
        }
    }
    player.render(renderer);
    player2.render(renderer);
        // Render the timer
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface( gameSurface );
    SDL_DestroyTexture(gameTexture);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
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
    (font);
    TTF_Quit();
}

Uint32 Game::getElapsedTime() {
    return SDL_GetTicks() - startTime;
}
bool Game::isCollision(const SDL_Rect& rect1,const SDL_Rect& rect2) {
        return (rect1.x < rect2.x + rect2.w &&
                rect1.x + rect1.w > rect2.x &&
                rect1.y < rect2.y + rect2.h &&
                rect1.y + rect1.h > rect2.y);
    }
bool Game::checkPlayerEnemyCollision( Character& player,  Enemy& enemy) {
    SDL_Rect playerRect = {player.x, player.y, player.playersize, player.playersize};
    SDL_Rect enemyRect = {enemy.x, enemy.y, SQUARE_SIZE, SQUARE_SIZE};
    return isCollision(playerRect, enemyRect);
}
bool Game::checkPlayerBigeCollision( Character& player,  BigE& bige) {
    SDL_Rect playerRect = {player.x, player.y, player.playersize, player.playersize};
    SDL_Rect bigeRect = {bige.x, bige.y, BIGE_SIZE, BIGE_SIZE};
    return isCollision(playerRect, bigeRect);
}
bool Game::checkPlayerCharacterCollision( Character& player,  Character& player2) {
    SDL_Rect playerRect = {player.x, player.y, player.playersize, player.playersize};
    SDL_Rect player2Rect = {player2.x, player2.y, player2.playersize, player2.playersize};
    return isCollision(playerRect, player2Rect);
}
bool Game::checkPlayerSkillCollision( Character& player,  Skill& skill) {
    SDL_Rect playerRect = {player.x, player.y, player.playersize, player.playersize};
    SDL_Rect skillRect = {skill.x, skill.y, ITEM_SIZE, ITEM_SIZE};
    return isCollision(playerRect, skillRect);
}
void Game::singerplayer() {
    player2.x = SCREEN_WIDTH + player2.playersize*2 ;
    player2.y = SCREEN_HEIGHT + player2.playersize*2 ;
    ismulti = false;
}

void Game::initElement() {
    startTime = SDL_GetTicks();
    lastPlayTime = 0;
    player.numlives = 1;
    player2.numlives = 1;
    player1lose = false;
    lastEnemySpawnTime = 0;
    lastItemSpawnTime = 0;
    lastBigeSpawnTime = 0;
    player.x = SCREEN_WIDTH / 2 - SQUARE_SIZE / 2;
    player.y = SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2;
    player.velX = 0;
    player.velY = 0;
    player.isJumping = false;
    fill(begin(player.isKeyPressed),end(player.isKeyPressed), false);

    if(ismulti){
        player2.x = SCREEN_WIDTH / 2 + SQUARE_SIZE / 2;
        player2.y = SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2;
        player2.velX = 0;
        player2.velY = 0;
        player2.isJumping2 = false;
        fill(begin(player2.isKeyPressed),end(player2.isKeyPressed), false);
    }
    enemies.clear();
    biges.clear();
    skills.clear();
    explosions.clear();
    for(auto invisible : invisibles)invisible.endtime();
    invisibles.clear();
    for(auto monster : monsters)monster.endtime();
    monsters.clear();
    player.ismonster=player2.ismonster=player.isghost=player2.isghost=false;
    for(auto nogravity : nogravities)nogravity.endtime();
    player.isgravity = player2.isgravity = true;
}

void Game::spawnItem() {
    int spawnX, spawnY;
    string itempic;
    string status;
    int random;
    srand(time(0));
    random = rand() % 4;
    switch(random){
        case 0:
            status = "monster";
            itempic = "image/monster.png";
            break;
        case 1:
            status = "invisible";
            itempic = "image/invisible.png";
            break;
        case 2:
            status = "bomb";
            itempic = "image/time-bomb.png";
            break;
        case 3:
            status = "nogravity";
            itempic = "image/nogravity.png";
            break;
        default:
            break;
    }
    spawnX = rand() % (SCREEN_WIDTH - ITEM_SIZE);
    spawnY = rand() % (SCREEN_HEIGHT - ITEM_SIZE-SQUARE_SIZE);

    Skill newSkill(spawnX, spawnY, itempic,status);
    newSkill.init(renderer);
    skills.push_back(newSkill);
}


void Game::spawnBigE() {
    int spawnX, spawnY,spawnVelX,spawnVelY;
    string color;
    int corner = rand() % 6;
    int ran2 = rand() %2;
    switch (corner) {
        case 0:
            // spawnX = SCREEN_WIDTH - BIGE_SIZE;
            spawnX = SCREEN_WIDTH;
            // spawnY = rand() % (SCREEN_HEIGHT - BIGE_SIZE);
            spawnY = rand() % (BIGE_SIZE/4)+BIGE_SIZE;
            color = "image/bigemerarball.png";
            spawnVelX = -2;
            spawnVelY = 2;
            break;
        case 1:
            // spawnX = 0;
            spawnX = -BIGE_SIZE;
            spawnY = rand() % (BIGE_SIZE/4)+BIGE_SIZE;
            color = "image/biggrayball.png";
            spawnVelX = 3;
            spawnVelY = 3;
            break;
        case 2:
            // spawnY = 0;
            // spawnX = rand() % (SCREEN_WIDTH - BIGE_SIZE);
            spawnX = rand() % (SCREEN_WIDTH - 3*BIGE_SIZE)+BIGE_SIZE;
            spawnY = -BIGE_SIZE;
            color = "image/bigredball.png";
            spawnVelX = 5;
            spawnVelY = 5;
            break;
        case 3:
            if(ran2){
                // spawnX = SCREEN_WIDTH - SQUARE_SIZE;
                spawnX = SCREEN_WIDTH;
                spawnVelX = -3;
            }else {
                // spawnX = 0;
                spawnX = -BIGE_SIZE;
                spawnVelX = 3;
            }
            spawnY = SCREEN_HEIGHT - BIGE_SIZE;
            color = "image/biggreenball.png";
            spawnVelY = 0;
            break;
        case 4:
            // spawnY = 0;
            // spawnX = rand() % (SCREEN_WIDTH - BIGE_SIZE);
            spawnX = rand() % (SCREEN_WIDTH - 3*BIGE_SIZE)+BIGE_SIZE;
            spawnY = -BIGE_SIZE;
            color = "image/bigorangeball.png";
            spawnVelX = 2;
            spawnVelY = 1;
            break;
        case 5:
            // spawnY = 0;
            // spawnX = rand() % (SCREEN_WIDTH - BIGE_SIZE);
            spawnX = rand() % (SCREEN_WIDTH - 3*BIGE_SIZE)+BIGE_SIZE;
            spawnY = -BIGE_SIZE;
            color  = "image/bigblueball.png";
            spawnVelX = 4;
            spawnVelY = 4;
            break;
        default:
            break;
    }
    cout<<corner<<" "<<spawnX<<" "<<spawnY<<endl;
    BigE newBigE(spawnX, spawnY, spawnVelX, spawnVelY , color);
    newBigE.init(renderer);
    biges.push_back(newBigE);
}

void Game::spawnEnemy() {
    int spawnX, spawnY,spawnVelX,spawnVelY;
    string color;
    int corner = rand() % 6;
    int ran1 = rand() % 2;
    int ran2 = rand() %2;
    switch (corner) {
        case 0:
            spawnX = SCREEN_WIDTH - SQUARE_SIZE;
            spawnY = rand() % (SCREEN_HEIGHT - SQUARE_SIZE);
            color = "image/emerarball.png";
            spawnVelX = 2;
            spawnVelY = 2;
            break;
        case 1:
            spawnX = 0;
            spawnY = rand() % (SCREEN_HEIGHT - SQUARE_SIZE);
            color = "image/grayball.png";
            spawnVelX = 3;
            spawnVelY = 3;
            break;
        case 2:
            spawnX = rand() % (SCREEN_WIDTH - SQUARE_SIZE);
            spawnY = 0;
            color = "image/redball.png";
            spawnVelX = 5;
            spawnVelY = 5;
            break;
        case 3:
            if(ran1){
                if(ran2){
                    spawnX = SCREEN_WIDTH - SQUARE_SIZE;
                    spawnVelX = -2;
                }else {
                    spawnX = 0;
                    spawnVelX = 2;
                }
                spawnY = SCREEN_HEIGHT - SQUARE_SIZE;
                color = "image/greenball.png";
                spawnVelY = 0;
            }
            else {
                spawnX = SCREEN_WIDTH - SQUARE_SIZE;
                spawnY = rand() % (SCREEN_HEIGHT - SQUARE_SIZE);
                color = "image/emerarball.png";
                spawnVelX = 2;
                spawnVelY = 2;
            }
            break;
        case 4:
            spawnX = rand() % (SCREEN_WIDTH - SQUARE_SIZE);
            spawnY = 0;
            color = "image/orangeball.png";
            spawnVelX = 2;
            spawnVelY = 1;
            break;
        case 5:
            spawnX = rand() % (SCREEN_WIDTH - SQUARE_SIZE);
            spawnY = 0;
            color  = "image/blueball.png";
            spawnVelX = 4;
            spawnVelY = 4;
            break;
        default:
            break;
    }
    Enemy newEnemy(spawnX, spawnY, spawnVelX, spawnVelY , color);
    newEnemy.init(renderer);
    enemies.push_back(newEnemy);
}
