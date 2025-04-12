#include "LevelA.h"
#include "Utility.h"

#define LEVEL1_LEFT_EDGE 6.0f
#define LEVEL1_RIGHT_EDGE 10.0f
#define LEVEL1_BOTTOM_EDGE -12.5f

#define LEVEL_WIDTH 43
#define LEVEL_HEIGHT 18

bool game_over_A;
GLuint g_font_texture_id_A;

constexpr char FONTSHEET_FILEPATH[] = "assets/font1.png",
SPRITESHEET_FILEPATH[] = "assets/sonic_spritesheet.png",
ENEMY_FILEPATH[] = "assets/motobug2.png";

unsigned int LEVEL_DATA_A[] =
{
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,16,22,22,22,22,22,22,39, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,37,37,37,37,37,37,37,37, 0, 0, 0, 0, 0, 0, 0, 0, 0,400,401, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,416,417, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 22,22,22,22,22,22,22,22,22, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

LevelA::~LevelA()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelA::initialise()
{
    GLuint map_texture_id = Utility::load_texture("assets/Sonic_tileset.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_DATA_A, map_texture_id, 1.0f, 16, 28);

    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);

    int player_walking_animation[4][4] =
    {
        { 7, 6, 5, 4},  // Left
        { 0, 1, 2, 3},  // Right
        { 8, 9, 10, 11 }, // Upwards,
        { 12, 13, 14, 15 }   // Downwards
    };

    glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);

    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        6.0f,                      // speed
        acceleration,              // acceleration
        6.0f,                      // jumping power
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
    m_game_state.player->set_position(glm::vec3(6.0f, -12.0f, 0.0f));

    // Jumping
    m_game_state.player->set_jumping_power(6.0f);

    /**
     Enemies' stuff */
    GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);

    m_game_state.enemies = new Entity[ENEMY_COUNT];

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i] = Entity(enemy_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, GUARD, IDLE);
    }
    m_game_state.enemies[0].set_position(glm::vec3(20.0f, -11.0f, 0.0f));
    m_game_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    
    m_game_state.enemies[1].set_ai_type(WALKER);
    m_game_state.enemies[1].set_position(glm::vec3(19.5f, -7.0f, 0.0f));
    m_game_state.enemies[1].set_movement(glm::vec3(1.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].set_scale(glm::vec3(-1.0f, 1.0f, 1.0f));
    m_game_state.enemies[1].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));

    /**
     BGM and SFX
     */
    g_font_texture_id_A = Utility::load_texture(FONTSHEET_FILEPATH);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    m_game_state.bgm = Mix_LoadMUS("assets/bgm.mp3");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(10);

    m_game_state.jump_sfx = Mix_LoadWAV("assets/jump.wav");
    m_game_state.death_sfx = Mix_LoadWAV("assets/death.wav");
    Mix_VolumeChunk(m_game_state.jump_sfx,10);

    Mix_VolumeChunk(m_game_state.death_sfx, 10);
   
    m_game_state.next_scene_id = 0;
}

void LevelA::update(float delta_time)
{
    if (game_over_A) return;
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);

    /* IF PLAYER WAS HIT */
    if (m_game_state.player->get_was_hit()) {

        this->set_lives(lives - 1);
        Mix_PlayChannel(-1, m_game_state.death_sfx, 0);

        /* IF GAME OVER, DEACTIVATE PLAYER AND ENEMIES */
        if (this->get_lives() <= 0) {
            game_over_A = true;
            
            m_game_state.player->set_lives(0);
            m_game_state.player->deactivate();

            for (int i = 0; i < ENEMY_COUNT; i++) {
                m_game_state.enemies[i].deactivate();
            }

            return;
        }
        
        /* RESET SCENE */
        m_game_state.next_scene_id = 1;
    }

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
    }
    /* CONDITION TO GO TO NEXT STAGE */
    if (m_game_state.player->get_is_holding_down() &&
        m_game_state.player->get_collided_bottom() &&
        m_game_state.player->get_position().x > 33 &&
        m_game_state.player->get_position().x < 35)
        m_game_state.next_scene_id = 2;
}


void LevelA::render(ShaderProgram* g_shader_program)
{
    /* RENDER MAP, PLAYER, ENEMIES */
    m_game_state.map->render(g_shader_program);
    m_game_state.player->render(g_shader_program);
    for (int i = 0; i < ENEMY_COUNT; i++)
        m_game_state.enemies[i].render(g_shader_program);

    /* DRAW TEXT FOR NUMBER OF LIVES */
    Utility::draw_text(g_shader_program, g_font_texture_id_A, 
                        "Lives: " + std::to_string((m_game_state.player->get_lives())),
                        0.5f, 0.0f, glm::vec3(m_game_state.player->get_position().x-6.0f, m_game_state.player->get_position().y+4.3f, 0.0f));

    /* IF GAME OVER, WRITE GAME OVER */
    if (this->get_lives() <= 0) {
        Utility::draw_text(g_shader_program, g_font_texture_id_A,
            "Game Over",
            1.0f, 0.0f, glm::vec3(m_game_state.player->get_position().x - 4.3f, m_game_state.player->get_position().y + 3.0f, 0.0f));
    }
}

void LevelA::move_camera(glm::mat4& g_view_matrix) {
    if (m_game_state.player->get_position().x > LEVEL1_LEFT_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-m_game_state.player->get_position().x, 0, 0));
    }
    else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-LEVEL1_LEFT_EDGE, 0, 0));
    }

    if (m_game_state.player->get_position().y > LEVEL1_BOTTOM_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(0.0f, -m_game_state.player->get_position().y, 0.0f));
    }
    else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(0, -LEVEL1_BOTTOM_EDGE, 0));
    }

}