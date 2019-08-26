//#define MIN_FRAMETIME_MSECS 16

#include <iostream>
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace std;

//start values
int width = 640;
int height = 480;
bool fscreen = false;
int speed = 5;
int car_pos = 5;
int player_pos = (width - 50) / 2;


void renderNewObj(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rectangle)
{
    SDL_RenderCopy(renderer, texture, NULL, &rectangle);
}

//when game over // start new game
void game_counters_reset (int & c1, int & c2, int & c3, int & c4, bool & flag, int & c1_1, int & c2_2, int & c3_3, int & c4_4)
{
    c1 = -100;
    c2 = -100;
    c3 = -100;
    c4 = -100;
    flag = true;
    c1_1 = -100;
    c2_2 = -100;
    c3_3 = -100;
    c4_4 = -100;
}

//display game over word
void game_over(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rectangle)
{
    renderNewObj(renderer, texture, rectangle);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
    SDL_RenderClear(renderer);
}

// 10 car positions lottery
int getCarPosition(SDL_Rect rectangle)
{
    car_pos = rand() * time(NULL) % 10 + 1;
    //set car position
            switch(car_pos)
                    {
                    case 1:
                        {
                            rectangle.x = 640-10*64;
                            break;
                        }
                    case 2:
                        {
                            rectangle.x = 640-9*64;
                            break;
                        }
                    case 3:
                        {
                            rectangle.x = 640-8*64;
                            break;
                        }
                    case 4:
                        {
                            rectangle.x = 640-7*64;
                            break;
                        }
                    case 5:
                        {
                            rectangle.x = 640-6*64;
                            break;
                        }
                    case 6:
                        {
                            rectangle.x = 640-5*64;
                            break;
                        }
                    case 7:
                        {
                            rectangle.x = 640-4*64;
                            break;
                        }
                    case 8:
                        {
                            rectangle.x = 640-3*64;
                            break;
                        }
                    case 9:
                        {
                            rectangle.x = 640-2*64;
                            break;
                        }
                    case 10:
                        {
                            rectangle.x = 640-64;
                            break;
                        }
                    }
        return rectangle.x;
}


int main(int argc, char * argv[])
{
    //init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL not initialize" << SDL_GetError() << std::endl;
    }

    //delay configuration
    using FrameDuration = std::chrono::duration<int, std::ratio<1, 60>>;


      //init main window
      SDL_Window* window = SDL_CreateWindow(
      "Cars race", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, width, height,
      SDL_WINDOW_SHOWN | (fscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));

      //init render
      SDL_Renderer* renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC );

      //add cars texture for render
      SDL_Surface* bitmap = SDL_LoadBMP ("car.bmp");
      SDL_Texture* tex_1 = SDL_CreateTextureFromSurface(renderer, bitmap);
      SDL_FreeSurface(bitmap);

      //add player car texture for render
      bitmap = SDL_LoadBMP ("car_2.bmp");
      SDL_Texture* tex_2 = SDL_CreateTextureFromSurface(renderer, bitmap);
      SDL_FreeSurface(bitmap);

      //add game over texture for render
      bitmap = SDL_LoadBMP ("try_again.bmp");
      SDL_Texture* tex_3_g_over = SDL_CreateTextureFromSurface(renderer, bitmap);
      SDL_FreeSurface(bitmap);

      //start position variables
      int y2 = -100; //0
      int y3 = -100; //0
      int y4 = -100; //0
      int y5 = -100; //0

      //start variables
      bool firstRun = true;
      SDL_Event event;
      bool exit = false;
      SDL_Rect SrcR_2;
      SDL_Rect SrcR_3;
      SDL_Rect SrcR_4;
      SDL_Rect SrcR_5;

      //game over texture position
       SDL_Rect SrcR_g_over;
        SrcR_g_over.x = (width - 300) / 2;
        SrcR_g_over.y = (height - 70) / 2;
        SrcR_g_over.w = 300;
        SrcR_g_over.h = 70;

       // main loop
    bool exit_flag = false;
      while(!exit)
      {
          //events
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    exit = true;
                }

                if( event.type == SDL_KEYDOWN )
                {
                    switch( event.key.keysym.sym )
                    {
                        //cars speed up handler
                        case SDLK_UP:
                        {
                            if(speed == 0)
                            {
                                break;
                            }
                            else
                            {
                                speed--;
                            }
                            break;
                        }

                        //cars speed down handler
                        case SDLK_DOWN:
                        {
                            if(speed == 5)
                            {
                                break;
                            }
                            else
                            {
                                speed++;
                            }
                            break;
                        }

                        //car turn left
                        case SDLK_LEFT:
                        {
                            if(player_pos == 0)
                            {
                                break;
                            }
                            else
                            {
                                player_pos--;
                            }
                            break;
                        }

                        //car turn right
                        case SDLK_RIGHT:
                        {
                            if(player_pos == width-50)
                            {
                                break;
                            }
                            else
                            {
                                player_pos++;
                            }
                            break;
                        }
                    }
                }
            }

                //cars speed // delay value
               auto next_start = std::chrono::steady_clock::now() + FrameDuration{speed};

            //player texture rectangle coverage
            SDL_Rect SrcR_1;
            SrcR_1.x = player_pos;
            SrcR_1.y = 380;
            SrcR_1.w = 50;
            SrcR_1.h = 100;

            //player car render
            SDL_RenderCopy(renderer, tex_1, NULL, &SrcR_1);

                    //move first car
                    if(y2 == -100) //0
                    {
                        SrcR_2.x = getCarPosition(SrcR_2);
                    }
                    if(y2 <= 480)
                    {
                        SrcR_2.y = y2++;
                        SrcR_2.w = 50;
                        SrcR_2.h = 100;
                        renderNewObj(renderer, tex_2, SrcR_2);
                    }
                    if(y2 > 480)
                    {
                        y2 = -100; //0
                        firstRun = false;
                    }


                    //move second car
                    if(y2 == 160)
                    {
                       SrcR_3.x = getCarPosition(SrcR_3);
                    }
                    if( y2 >= 160 || (y2 < 160 && !firstRun) )
                    {
                        SrcR_3.y = y3++;
                        SrcR_3.w = 50;
                        SrcR_3.h = 100;
                        renderNewObj(renderer, tex_2, SrcR_3);
                    }
                    if(y3 > 480)
                    {
                        y3 = -100; //0
                    }


                    //move third car
                    if(y2 == 320)
                    {
                       SrcR_4.x = getCarPosition(SrcR_4);
                    }
                    if(y2 >= 320 || (y2 < 320 && !firstRun))
                    {
                        SrcR_4.y = y4++;
                        SrcR_4.w = 50;
                        SrcR_4.h = 100;
                        renderNewObj(renderer, tex_2, SrcR_4);
                    }
                    if(y4 > 480)
                    {
                        y4 = -100; //0
                    }


                    //move fourth car
                    if(y2 == 50)
                    {
                       SrcR_5.x = getCarPosition(SrcR_5);
                    }
                    if(y2 >= 50 || (y2 < 50 && !firstRun))
                    {
                        SrcR_5.y = y5++;
                        SrcR_5.w = 50;
                        SrcR_5.h = 100;
                        renderNewObj(renderer, tex_2, SrcR_5);
                    }
                    if(y5 > 480)
                    {
                        y5 = -100;
                    }


                //first car collisions
                if((((SrcR_2.y + 100) >= SrcR_1.y) && (SrcR_2.y <= (SrcR_1.y + 100)))
                   && (((((SrcR_2.x + 50) >= SrcR_1.x) && (SrcR_2.x + 50) <= (SrcR_1.x + 50)))
                   || ((SrcR_2.x <= (SrcR_1.x + 50)) && ((SrcR_2.x + 50) >= (SrcR_1.x)))))
                {
                    game_counters_reset(SrcR_2.y, SrcR_3.y, SrcR_4.y, SrcR_5.y, firstRun, y2, y3, y4, y5);
                    game_over(renderer, tex_3_g_over, SrcR_g_over);
                    exit_flag = true;
                }

                //second car collisions
                if((((SrcR_3.y + 100) >= SrcR_1.y) && (SrcR_3.y <= (SrcR_1.y + 100)))
                   && (((((SrcR_3.x + 50) >= SrcR_1.x) && (SrcR_3.x + 50) <= (SrcR_1.x + 50)))
                   || ((SrcR_3.x <= (SrcR_1.x + 50)) && ((SrcR_3.x + 50) >= (SrcR_1.x)))))
                {
                    game_counters_reset(SrcR_2.y, SrcR_3.y, SrcR_4.y, SrcR_5.y, firstRun, y2, y3, y4, y5);
                    game_over(renderer, tex_3_g_over, SrcR_g_over);
                    exit_flag = true;
                }

                //third car collisions
                if((((SrcR_4.y + 100) >= SrcR_1.y) && (SrcR_4.y <= (SrcR_1.y + 100)))
                   && (((((SrcR_4.x + 50) >= SrcR_1.x) && (SrcR_4.x + 50) <= (SrcR_1.x + 50)))
                   || ((SrcR_4.x <= (SrcR_1.x + 50)) && ((SrcR_4.x + 50) >= (SrcR_1.x)))))
                {
                    game_counters_reset(SrcR_2.y, SrcR_3.y, SrcR_4.y, SrcR_5.y, firstRun, y2, y3, y4, y5);
                    game_over(renderer, tex_3_g_over, SrcR_g_over);
                    exit_flag = true;
                }

                //fourth car collisions
                if((((SrcR_5.y + 100) >= SrcR_1.y) && (SrcR_5.y <= (SrcR_1.y + 100)))
                   && (((((SrcR_5.x + 50) >= SrcR_1.x) && (SrcR_5.x + 50) <= (SrcR_1.x + 50)))
                   || ((SrcR_5.x <= (SrcR_1.x + 50)) && ((SrcR_5.x + 50) >= (SrcR_1.x)))))
                {
                    game_counters_reset(SrcR_2.y, SrcR_3.y, SrcR_4.y, SrcR_5.y, firstRun, y2, y3, y4, y5);
                    game_over(renderer, tex_3_g_over, SrcR_g_over);
                    exit_flag = true;
                }



                //display textures
                SDL_RenderPresent(renderer);

                //clear render
                SDL_RenderClear(renderer);

                //delay // cars speed
                std::this_thread::sleep_until(next_start);

                //game over // collision
                if(exit_flag)
                {
                    continue;
                }

}

    //free resources
    SDL_DestroyTexture(tex_1);
    SDL_DestroyTexture(tex_2);
    SDL_DestroyTexture(tex_3_g_over);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return EXIT_SUCCESS;
}
