#include "LevelC.h"
#include "Utility.h"
#define LEVELC_LEFT_EDGE 6.0f
#define LEVELC_RIGHT_EDGE 10.0f
#define LEVELC_BOTTOM_EDGE -12.5f

GLuint g_font_texture_id_C;

#define LEVEL_WIDTH 72
#define LEVEL_HEIGHT 18

bool player_won = false;
bool game_over_C = false;

constexpr char FONTSHEET_FILEPATH[] = "assets/font1.png",
           SPRITESHEET_FILEPATH[] = "assets/sonic_spritesheet.png",
           PLATFORM_FILEPATH[]    = "assets/platform.png",
           ENEMY_FILEPATH[]       = "assets/koopa.png";

unsigned int LEVEL_DATA_C[] =
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,16,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,16,16,16,17,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,41,0,0,0,0,0,0,
41,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,15,16,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,
8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,
8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,11,12,13,0,
8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,43,0,15,16,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,44,45,46,0,
8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,43,15,16,16,16,16,16,17,0,0,43,0,0,0,0,0,0,43,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,76,77,78,79,80,
8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,43,0,0,0,43,0,0,0,0,0,43,0,0,0,0,0,0,43,0,0,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,109,110,111,112,113,
8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,43,0,0,0,43,0,0,0,0,0,43,0,0,15,16,16,16,17,0,0,43,0,0,0,0,0,0,0,0,0,0,0,15,16,16,16,16,17,0,0,0,0,0,0,0,0,0,0,3,0,142,143,144,145,146,
8,0,1,1,1,1,1,1,1,1,0,15,16,16,16,17,0,43,0,0,0,43,0,0,0,0,0,43,0,0,0,0,10,0,43,0,0,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
8,0,1,1,1,1,1,1,1,1,0,0,0,10,0,0,0,43,0,0,0,43,0,0,0,0,0,43,0,0,0,0,43,0,43,0,0,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,43,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1


};

LevelC::~LevelC()
{
    delete[] m_game_state.enemies;
    m_game_state.enemies = nullptr;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelC::initialise()
{
    GLuint map_texture_id = Utility::load_texture("assets/marioset.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_DATA_C, map_texture_id, 1.0f, 33, 28);
    
    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);
    int player_walking_animation[4][4] =
    {
        { 7, 6, 5, 4},  // Left
        { 0, 1, 2, 3},  // Right
        { 8, 9, 10, 11 }, // for George to move upwards,
        { 12, 13, 14, 15 }   // for George to move downwards
    };

    glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);

    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        8.0f,                      // speed
        acceleration,              // acceleration
        5.0f,                      // jumping power
        player_walking_animation,  // animation index sets
        0.0f,                      // animation time
        4,                         // animation frame amount
        0,                         // current animation index
        4,                         // animation column amount
        4,                         // animation row amount
        1.0f,                      // width
        1.0f,                       // height
        PLAYER
    );
    m_game_state.player->set_lives(lives);
    m_game_state.player->set_position(glm::vec3(1.5f, -13.0f, 0.0f));

    // Jumping
    m_game_state.player->set_jumping_power(6.0f);
    
    /** --------------------/ ENEMIES /--------------------  **/
    GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);
    GLuint platform_texture_id = Utility::load_texture(PLATFORM_FILEPATH);

    // ENEMIES
    m_game_state.enemies = new Entity[ENEMY_COUNT];
    
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i] = Entity(enemy_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, GUARD, IDLE);
        m_game_state.enemies[i].set_movement(glm::vec3(0.0f));
        m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    }

    

    m_game_state.enemies[0].set_position(glm::vec3(45.0f, -9.0f, 0.0f));
    m_game_state.enemies[0].set_ai_type(FLYER);
    m_game_state.enemies[1].set_position(glm::vec3(56.0f, -12.0f, 0.0f));
    m_game_state.enemies[1].set_ai_type(FLYER);

    // PLATFORMS
    m_game_state.platforms = new Entity[PLATFORM_COUNT];

    m_game_state.platforms[0] = Entity(enemy_texture_id, 1.0f, 1.0f, 1.0f, PLATFORM, GUARD, IDLE);
    m_game_state.platforms[0].set_width(3.0f);
    m_game_state.platforms[0].set_scale(glm::vec3(3.0f, 1.0f, 1.0f));
    m_game_state.platforms[0].set_acceleration(glm::vec3(0.0f));
    m_game_state.platforms[0].set_position(glm::vec3(0.0f, -0.0f, 0.0f));
    

    m_game_state.platforms[1] = Entity(platform_texture_id, 1.0f, 1.0f, 1.0f, PLATFORM, GUARD, IDLE);
    m_game_state.platforms[1].set_width(3.0f);
    m_game_state.platforms[1].set_scale(glm::vec3(3.0f, 1.0f, 1.0f));
    m_game_state.platforms[1].set_acceleration(glm::vec3(0.0f));
    m_game_state.platforms[1].set_position(glm::vec3(0.0f, -10.0f, 0.0f));

    

    /**
     BGM and SFX
     */
    g_font_texture_id_C = Utility::load_texture(FONTSHEET_FILEPATH);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_game_state.bgm = Mix_LoadMUS("assets/bgm.mp3");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(10);

    m_game_state.jump_sfx = Mix_LoadWAV("assets/jump.wav");
    Mix_VolumeChunk(
        m_game_state.jump_sfx,     // Set the volume of the bounce sound...
        10  // ... to 1/4th.
    );

    m_game_state.death_sfx = Mix_LoadWAV("assets/death.wav");
    Mix_VolumeChunk(
        m_game_state.death_sfx,     // Set the volume of the bounce sound...
        10  // ... to 1/4th.
    );

    m_game_state.win_sfx = Mix_LoadWAV("assets/win.wav");
    Mix_VolumeChunk(
        m_game_state.win_sfx,     // Set the volume of the bounce sound...
        100  // ... to 1/4th.
    );


    m_game_state.next_scene_id = 0;
}

void LevelC::update(float delta_time)
{   

    if (player_won || game_over_C) return;

    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
    
    /* IF PLAYER WAS HIT OR FELL OFF MAP */
    if (m_game_state.player->get_was_hit() || m_game_state.player->get_position().y < LEVELC_BOTTOM_EDGE-6.0f) {
        
        this->set_lives(lives - 1);
        Mix_PlayChannel(-1, m_game_state.death_sfx, 0);

        if (this->get_lives() <= 0) {
            game_over_C = true;
            
            m_game_state.player->set_lives(0);
            m_game_state.player->deactivate();

            for (int i = 0; i < ENEMY_COUNT; i++) {
                m_game_state.enemies[i].deactivate();
            }
            return;
        }


        m_game_state.next_scene_id = 3;
    }
    
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
    }

    for (int i = 0; i < PLATFORM_COUNT; i++) {
        m_game_state.platforms[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
        if (m_game_state.platforms[i].get_entity_type() == PLATFORM)
        {
            printf("%i: position: (%f, %f, %f); \nvelocity: (%f, %f, %f); \nacceleration: (%f, %f, %f)\n\n",
                m_game_state.platforms[i].get_id(),
                m_game_state.platforms[i].get_position().x,
                m_game_state.platforms[i].get_position().y,
                m_game_state.platforms[i].get_position().z,
                m_game_state.platforms[i].get_velocity().x,
                m_game_state.platforms[i].get_velocity().y,
                m_game_state.platforms[i].get_velocity().z,
                m_game_state.platforms[i].get_acceleration().x,
                m_game_state.platforms[i].get_acceleration().y,
                m_game_state.platforms[i].get_acceleration().z);
        }
    }

    if (m_game_state.player->get_position().x > 65.0f) { player_won = true; Mix_PlayChannel(-1, m_game_state.win_sfx, 0);}
}


void LevelC::render(ShaderProgram *g_shader_program)
{
    m_game_state.map->render(g_shader_program);
    m_game_state.player->render(g_shader_program);
    for (int i = 0; i < ENEMY_COUNT; i++)
        m_game_state.enemies[i].render(g_shader_program);

    for (int i = 0; i < PLATFORM_COUNT; i++) m_game_state.platforms[i].render(g_shader_program);
    
    /* DRAW NUMBER OF LIVES AT TOP LEFT */
    glm::vec3 lives_text_location = glm::vec3(0.0f);

    if (m_game_state.player->get_position().x > LEVELC_LEFT_EDGE)
        lives_text_location.x = m_game_state.player->get_position().x - 6.0f;
    else lives_text_location.x = LEVELC_LEFT_EDGE - 6.0f;

    if (m_game_state.player->get_position().y > LEVELC_BOTTOM_EDGE)
        lives_text_location.y = m_game_state.player->get_position().y + 4.3f;
    else lives_text_location.y = LEVELC_BOTTOM_EDGE + 4.3f;
    
    Utility::draw_text(g_shader_program, g_font_texture_id_C,
        "Lives: " + std::to_string((m_game_state.player->get_lives())),
        0.5f, 0.0f, lives_text_location);


    if (player_won) {
        Utility::draw_text(g_shader_program, g_font_texture_id_C,
            "You Won!",
            1.0f, 0.0f, glm::vec3(m_game_state.player->get_position().x - 3.5f, m_game_state.player->get_position().y + 2.0f, 0.0f));
    }


    if (this->get_lives() <= 0) {
        glm::vec3 game_over_text_location = glm::vec3(0.0f);

        if (m_game_state.player->get_position().x > LEVELC_LEFT_EDGE)
            game_over_text_location.x = m_game_state.player->get_position().x - 4.3f;
        else game_over_text_location.x = LEVELC_LEFT_EDGE - 4.3f;

        if (m_game_state.player->get_position().y > LEVELC_BOTTOM_EDGE)
            game_over_text_location.y = m_game_state.player->get_position().y + 2.0f;
        else game_over_text_location.y = LEVELC_BOTTOM_EDGE + 2.0f;

        Utility::draw_text(g_shader_program, g_font_texture_id_C,
            "Game Over",
            1.0f, 0.0f, game_over_text_location);
    }

}

void LevelC::move_camera(glm::mat4& g_view_matrix) {
    if (m_game_state.player->get_position().x > LEVELC_LEFT_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-m_game_state.player->get_position().x, 0, 0));
    }
    else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-LEVELC_LEFT_EDGE, 0, 0));
    }

    if (m_game_state.player->get_position().y > LEVELC_BOTTOM_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(0.0f, -m_game_state.player->get_position().y, 0.0f));
    }
    else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(0, -LEVELC_BOTTOM_EDGE, 0));
    }

}