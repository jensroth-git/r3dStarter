#include <raylib.h>
#include <raymath.h>
#include <r3d/r3d.h>

static R3D_Mesh meshSphere = {};
static R3D_Material matDefault = {};
static R3D_InstanceBuffer instanceBuffer = {};
static Camera3D camDefault = {};

int main()
{
	// Initialize raylib window
	const auto window_width = 1280;
	const auto window_height = 720;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

	InitWindow(window_width, window_height, "Hello Raylib!");

	if (!IsWindowReady()) {
		TraceLog(LOG_ERROR, "Window failed to initialize");
		return 1;
	}

	R3D_Init(window_width, window_height, 0);

	camDefault = (Camera3D) {
		.position = (Vector3) {0, 2, 2},
		.target = (Vector3) {0, 0, 0},
		.up = (Vector3) {0, 1, 0},
		.fovy = 60,
	};

    R3D_Light light = R3D_CreateLight(R3D_LIGHT_DIR);
    {
        R3D_SetLightDirection(light, (Vector3) { 0, -1, 0 });
        R3D_SetLightActive(light, true);
    }

	const int xInstances = 7;
	const int yInstances = 7;

	instanceBuffer = R3D_LoadInstanceBuffer(xInstances*xInstances, R3D_INSTANCE_POSITION);
	auto* positions = static_cast<Vector3*>(R3D_MapInstances(instanceBuffer, R3D_INSTANCE_POSITION));

	// center the instances
	const float spacing = 1.0f;
	const float offsetX = (xInstances - 1) * spacing / 2;
	const float offsetZ = (yInstances - 1) * spacing / 2;

	for (int x = 0; x < xInstances; x++) {
		for (int y = 0; y < yInstances; y++) {
			positions[y * xInstances + x] = { x * spacing - offsetX, 0, y * spacing - offsetZ };
		}
	}
	R3D_UnmapInstances(instanceBuffer, R3D_INSTANCE_POSITION);

    meshSphere = R3D_GenMeshSphere(0.25f, 64, 64);
	matDefault = R3D_GetDefaultMaterial();
    {
        matDefault.albedo.color = (Color){255, 255, 255, 255};
    }

	R3D_ENVIRONMENT_SET(background.color, (Color){0, 0, 255, 255});
	R3D_ENVIRONMENT_SET(ambient.color, DARKGRAY);

	while (!WindowShouldClose()) {
		
		UpdateCamera(&camDefault, CAMERA_ORBITAL);

		BeginDrawing();

		R3D_Begin(camDefault);
		R3D_DrawMeshInstanced(meshSphere, matDefault, instanceBuffer, xInstances*yInstances);
		R3D_End();

		const auto text = "Hello, Raylib and R3D!";
		const auto text_width = MeasureText(text, 20);
		const auto text_height = 20;

		DrawText(text, window_width / 2 - text_width / 2, window_height / 2 - text_height / 2, text_height, RED);
		EndDrawing();
	}
	
	R3D_UnloadInstanceBuffer(instanceBuffer);
	R3D_UnloadMesh(meshSphere);

	R3D_Close();
	CloseWindow();
	return 0;
}
