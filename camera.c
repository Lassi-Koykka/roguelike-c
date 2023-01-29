#include <raylib.h>

Camera2D InitCamera(Vector2 pos, int screenWidth, int screenHeight) {
    Camera2D camera = { 0 };
    camera.target = pos;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    return camera;
}

void UpdateCameraCenter(Camera2D *camera, Vector2 pos, int width, int height)
{
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    camera->target = pos;
}
