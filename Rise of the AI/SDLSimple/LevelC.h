#include "Scene.h"

class LevelC : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //

    int ENEMY_COUNT = 2;
    int PLATFORM_COUNT = 2;
    
    // ————— DESTRUCTOR ————— //
    ~LevelC();
    
    // ————— METHODS ————— //
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
    void move_camera(glm::mat4& g_view_matrix) override;

};
