/**
* Author: William Wei
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm, (2025-04-07, 11:59pm, 2 Day Extension)
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
* 
* Resources Cited
* Sonic Tilesheet: https://info.sonicretro.org/Sonic_the_Hedgehog_(16-bit)/Maps
* Sonic Spritesheet: https://www.deviantart.com/facundogomez/art/Sonic-3-Custom-Sprites-659598886
* Sonic Motobug Sprite: https://gamebanana.com/requests/51643
* Mario Tilesheets: https://www.spriters-resource.com/nes/supermariobros/sheet/52571 and https://www.pinterest.com/pin/215187688422562368/
* Goomba Sprite: https://abobo.fandom.com/wiki/Goomba
* Falling Platform Sprite: https://www.spriters-resource.com/custom_edited/mariocustoms/sheet/181671/
* Koopa Sprite: https://vovatia.wordpress.com/2013/06/06/evil-koopa-and-his-troopas/
* Jump sound effect: https://freesound.org/people/jalastram/packs/21727/
* Sonic Hit Sound effect https://www.youtube.com/watch?v=EQszdh6BZXI
* Goal Reached / Win Sound effect https://freesound.org/people/Fupicat/sounds/607207/
* BGM: https://freesound.org/people/Migfus20/sounds/560738/
**/


#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f
#define LEVEL1_LEFT_EDGE 6.0f
#define LEVEL1_RIGHT_EDGE 10.0f
#define LEVEL1_BOTTOM_EDGE -12.5f

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Entity.h"
#include "Map.h"
#include "Utility.h"
#include "Scene.h"
#include "MainMenu.h"
#include "LevelA.h"
#include "LevelB.h"
#include "LevelC.h"


// ————— CONSTANTS ————— //
constexpr int WINDOW_WIDTH  = 640*1.6,
          WINDOW_HEIGHT = 480*1.6;

constexpr float BG_RED     = 92.0 / 252,
            BG_BLUE    = 252.0 / 252,
            BG_GREEN   = 148.0 / 252,
            BG_OPACITY = 1.0f;

constexpr int VIEWPORT_X = 0,
          VIEWPORT_Y = 0,
          VIEWPORT_WIDTH  = WINDOW_WIDTH,
          VIEWPORT_HEIGHT = WINDOW_HEIGHT;

constexpr char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
           F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

constexpr float MILLISECONDS_IN_SECOND = 1000.0;

constexpr float CAMERA_SCALE = 5.0f;

enum AppStatus { RUNNING, TERMINATED };

// ————— GLOBAL VARIABLES ————— //
Scene *g_current_scene;
MainMenu *g_main_menu;
LevelA *g_level_a;
LevelB *g_level_b;
LevelC *g_level_c;

Scene* g_levels[4];


SDL_Window* g_display_window;

AppStatus g_app_status = RUNNING;
ShaderProgram g_shader_program;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;


void switch_to_scene(Scene *scene)
{
    g_current_scene = scene;
    g_current_scene->initialise();
}

void initialise();
void process_input();
void update();
void render();
void shutdown();


void initialise()
{
    // ————— VIDEO ————— //
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("Hello, Scenes!",
                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      WINDOW_WIDTH, WINDOW_HEIGHT,
                                      SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    if (context == nullptr)
    {
        shutdown();
    }
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    // ————— GENERAL ————— //
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    
    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);
    
    g_view_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f*CAMERA_SCALE, 5.0f * CAMERA_SCALE, -3.75f * CAMERA_SCALE, 3.75f * CAMERA_SCALE, -1.0f, 1.0f);
    
    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);

    glUseProgram(g_shader_program.get_program_id());
    
    glClearColor(BG_RED, BG_GREEN, BG_BLUE, BG_OPACITY);

    
    // ----- LEVELS SETUP ------ //

    g_main_menu = new MainMenu();
    g_level_a = new LevelA();
    g_level_b = new LevelB();
    g_level_c = new LevelC();

    g_levels[0] = g_main_menu;
    g_levels[1] = g_level_a;
    g_levels[2] = g_level_b;
    g_levels[3] = g_level_c;
    
    // ————— LEVEL A SETUP ————— //
    
    switch_to_scene(g_levels[0]);
    
    // ————— BLENDING ————— //
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void process_input()
{
    g_current_scene->get_state().player->set_movement(glm::vec3(0.0f));
    
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // ————— KEYSTROKES ————— //
        switch (event.type) {
            // ————— END GAME ————— //
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_app_status = TERMINATED;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        // Quit the game with a keystroke
                        g_app_status = TERMINATED;
                        break;
                        
                    case SDLK_SPACE:
                        // ————— JUMPING ————— //
                        if (g_current_scene->get_state().player->get_collided_bottom() &&
                            g_current_scene->get_state().player->get_lives() > 0)
                        {
                            g_current_scene->get_state().player->jump();
                            Mix_PlayChannel(-1,  g_current_scene->get_state().jump_sfx, 0);
                        }
                         break;
                    case SDLK_RETURN:
                            g_current_scene->get_state().player->clicked_enter();
                        break;

                    case SDLK_1:
                            g_current_scene->set_next_scene(1);
                        break;

                    case SDLK_2:
                            g_current_scene->set_next_scene(2);
                        break;
                    case SDLK_3:
                        g_current_scene->set_next_scene(3);
                        break;

                        
                    default:
                        g_current_scene->get_state().player->clear_inputs();
                        break;
                }
                
            default:
                break;
        }
    }
    
    // ————— KEY HOLD ————— //
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    if (key_state[SDL_SCANCODE_LEFT])        g_current_scene->get_state().player->move_left();
    else if (key_state[SDL_SCANCODE_RIGHT])  g_current_scene->get_state().player->move_right();
    else if (key_state[SDL_SCANCODE_DOWN])   g_current_scene->get_state().player->move_down();
     
    if (glm::length( g_current_scene->get_state().player->get_movement()) > 1.0f)
        g_current_scene->get_state().player->normalise_movement();
 
}

void update()
{
    // ————— DELTA TIME / FIXED TIME STEP CALCULATION ————— //
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;
    
    delta_time += g_accumulator;
    
    if (delta_time < FIXED_TIMESTEP)
    {
        g_accumulator = delta_time;
        return;
    }
    
    while (delta_time >= FIXED_TIMESTEP) {
        // ————— UPDATING THE SCENE (i.e. map, character, enemies...) ————— //
        g_current_scene->update(FIXED_TIMESTEP);
        
        delta_time -= FIXED_TIMESTEP;
    }
    
    g_accumulator = delta_time;
    
    
    // ————— PLAYER CAMERA ————— //
    g_view_matrix = glm::mat4(1.0f);
    
    g_current_scene->move_camera(g_view_matrix);
}

void render()
{
    g_shader_program.set_view_matrix(g_view_matrix);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // ————— RENDERING THE SCENE (i.e. map, character, enemies...) ————— //
    g_current_scene->render(&g_shader_program);
    
    SDL_GL_SwapWindow(g_display_window);
}

void shutdown()
{    
    SDL_Quit();
    
    // ————— DELETING LEVEL A DATA (i.e. map, character, enemies...) ————— //
    delete g_main_menu;
    delete g_level_a;
    delete g_level_b;
    delete g_level_c;

    g_main_menu = nullptr;
    g_level_a = nullptr;
    g_level_b = nullptr;
    g_level_c = nullptr;
}

// ————— GAME LOOP ————— //
int main(int argc, char* argv[])
{
    initialise();
    
    while (g_app_status == RUNNING)
    {
        process_input();
        update();

        if (g_current_scene->get_next_scene_id() > 0) {
            g_levels[g_current_scene->get_next_scene_id()]->set_lives(g_current_scene->get_lives());
            switch_to_scene(g_levels[g_current_scene->get_next_scene_id()]); }

        render();
    }
    
    shutdown();
    return 0;
}
