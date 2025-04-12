#include "LevelB.h"
#include "Utility.h"

#define LEVELB_LEFT_EDGE 6.0f
#define LEVELB_RIGHT_EDGE 10.0f
#define LEVELB_BOTTOM_EDGE -12.5f

#define LEVEL_WIDTH 66
#define LEVEL_HEIGHT 18

constexpr char FONTSHEET_FILEPATH[] = "assets/font1.png",
           SPRITESHEET_FILEPATH[] = "assets/sonic_spritesheet.png",
           ENEMY_FILEPATH[]       = "assets/goomba.png";

GLuint g_font_texture_id_B;
bool game_over_B = false;

unsigned int LEVEL_DATA_B[] =
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,5,0,0,0,2,5,2,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,0,0,0,39,40,0,0,0,0,0,0,0,0,0,0,0,0,2,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,0,0,39,40,0,0,0,0,39,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,
0,39,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,39,40,0,0,0,39,40,0,0,0,0,39,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,

};

LevelB::~LevelB()
{
    delete [] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelB::initialise()
{
    GLuint map_texture_id = Utility::load_texture("assets/marioset.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_DATA_B, map_texture_id, 1.0f, 33, 28);
    
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
    m_game_state.player->set_position(glm::vec3(1.5f, -13.0f, 0.0f));

    // Jumping
    m_game_state.player->set_jumping_power(6.0f);
    
    /** Enemies' stuff */
    GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);

    m_game_state.enemies = new Entity[ENEMY_COUNT];

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i] =  Entity(enemy_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, WALKER, IDLE);
        m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
        m_game_state.enemies[i].set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));
    }


    m_game_state.enemies[0].set_position(glm::vec3(16.0f, -15.0f, 0.0f));
    m_game_state.enemies[1].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].set_ai_type(GUARD);
    m_game_state.enemies[1].set_position(glm::vec3(31.0f, -15.0f, 0.0f));
    m_game_state.enemies[2].set_position(glm::vec3(50.0f, -8.0f, 0.0f));


    /**
     BGM and SFX
     */
    g_font_texture_id_B = Utility::load_texture(FONTSHEET_FILEPATH);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_game_state.bgm = Mix_LoadMUS("assets/bgm.mp3");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(10);
    
    m_game_state.jump_sfx = Mix_LoadWAV("assets/jump.wav");
    Mix_VolumeChunk(m_game_state.jump_sfx, 10);

    m_game_state.death_sfx = Mix_LoadWAV("assets/death.wav");
    Mix_VolumeChunk(m_game_state.death_sfx, 10);

    m_game_state.next_scene_id = 0;
}

void LevelB::update(float delta_time)
{
    if (game_over_B) return;
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);

    /* IF PLAYER WAS HIT OR FELL OFF MAP */
    if (m_game_state.player->get_was_hit() || m_game_state.player->get_position().y < LEVELB_BOTTOM_EDGE - 6.0f) {

        this->set_lives(lives - 1);
        Mix_PlayChannel(-1, m_game_state.death_sfx, 0);

        /* IF GAME OVER, DEACTIVATE PLAYER AND ENEMIES*/
        if (this->get_lives() <= 0) {
            game_over_B = true;
            m_game_state.player->set_lives(0);
            m_game_state.player->deactivate();
            for (int i = 0; i < ENEMY_COUNT; i++) {
                m_game_state.enemies[i].deactivate();
            }
            return;
        }
        

        /* RESET STAGE */
        m_game_state.next_scene_id = 2;
    }
    
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
    }

    /* CONDITION TO GO TO NEXT STAGE */
    if (m_game_state.player->get_position().x > 64.0f) m_game_state.next_scene_id = 3;
}


void LevelB::render(ShaderProgram *g_shader_program)
{
    m_game_state.map->render(g_shader_program);
    m_game_state.player->render(g_shader_program);
    for (int i = 0; i < m_number_of_enemies; i++)
            m_game_state.enemies[i].render(g_shader_program);
    
    /* WRITE NUMBER OF LIVES ON THE TOP LEFT */
    glm::vec3 text_location = glm::vec3(0.0f);

    if (m_game_state.player->get_position().x > LEVELB_LEFT_EDGE)
        text_location.x = m_game_state.player->get_position().x - 6.0f;
    else text_location.x = LEVELB_LEFT_EDGE - 6.0f;

    if (m_game_state.player->get_position().y > LEVELB_BOTTOM_EDGE)
        text_location.y = m_game_state.player->get_position().y + 4.3f;
    else text_location.y = LEVELB_BOTTOM_EDGE + 4.3f;

    Utility::draw_text(g_shader_program, g_font_texture_id_B,
        "Lives: " + std::to_string((m_game_state.player->get_lives())),
        0.5f, 0.0f, text_location);

    /* IF GAME OVER, WRITE GAME OVER */
    if (this->get_lives() <= 0) {
        glm::vec3 game_over_text_location = glm::vec3(0.0f);

        if (m_game_state.player->get_position().x > LEVELB_LEFT_EDGE)
            game_over_text_location.x = m_game_state.player->get_position().x - 4.3f;
        else game_over_text_location.x = LEVELB_LEFT_EDGE - 4.3f;

        if (m_game_state.player->get_position().y > LEVELB_BOTTOM_EDGE)
            game_over_text_location.y = m_game_state.player->get_position().y + 2.0f;
        else game_over_text_location.y = LEVELB_BOTTOM_EDGE + 2.0f;

        Utility::draw_text(g_shader_program, g_font_texture_id_B,
            "Game Over",
            1.0f, 0.0f, game_over_text_location);
    }
}

void LevelB::move_camera(glm::mat4& g_view_matrix) {
    if (m_game_state.player->get_position().x > LEVELB_LEFT_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-m_game_state.player->get_position().x, 0, 0));
    }
    else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-LEVELB_LEFT_EDGE, 0, 0));
    }

    if (m_game_state.player->get_position().y > LEVELB_BOTTOM_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(0.0f, -m_game_state.player->get_position().y, 0.0f));
    }
    else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(0, -LEVELB_BOTTOM_EDGE, 0));
    }

}
