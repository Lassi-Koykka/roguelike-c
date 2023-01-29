#include <raylib.h>

Camera2D InitCamera(Vector2 pos, int screenWidth, int screenHeight);

void UpdateCameraCenter(Camera2D *camera, Vector2 pos, int width, int height);
