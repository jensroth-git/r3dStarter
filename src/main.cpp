#include <r3d.h>
#include <raylib.h>
#include <raymath.h>
#include <vector>

static R3D_Mesh meshSphere = {0};
static R3D_Material matDefault = {0};
static Camera3D camDefault = {0};

int main()
{
	// Initialize raylib window
	const auto window_width = 1280;
	const auto window_height = 720;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(window_width, window_height, "Hello Raylib!");
	SetTargetFPS(60);

	if (!IsWindowReady()) {
		TraceLog(LOG_ERROR, "Window failed to initialize");
		return 1;
	}

	R3D_Init(window_width, window_height);

	camDefault = (Camera3D) {
		.position = (Vector3) {0, 2, 2},
		.target = (Vector3) {0, 0, 0},
		.up = (Vector3) {0, 1, 0},
		.fovy = 60,
	};

	R3D_Light light = R3D_CreateLight(R3D_LIGHT_DIR);
	{
		R3D_SetLightDirection(light, (Vector3) {0, -1, 0});
		R3D_SetLightActive(light, true);
	}

	const int xInstances = 7;
	const int yInstances = 7;

	const int instanceCount = xInstances * yInstances;

	const float spacing = 1.0f;

	R3D_InstanceBuffer instances = R3D_LoadInstanceBuffer(
		xInstances * yInstances, R3D_INSTANCE_POSITION | R3D_INSTANCE_ROTATION | R3D_INSTANCE_SCALE | R3D_INSTANCE_COLOR
	);

	Vector3 *positions = (Vector3 *)R3D_MapInstances(instances, R3D_INSTANCE_POSITION);
	Quaternion *rotations = (Quaternion *)R3D_MapInstances(instances, R3D_INSTANCE_ROTATION);
	Vector3 *scales = (Vector3 *)R3D_MapInstances(instances, R3D_INSTANCE_SCALE);
	Color *colors = (Color *)R3D_MapInstances(instances, R3D_INSTANCE_COLOR);

	// center the instances
	const float offsetX = (xInstances - 1) * spacing / 2;
	const float offsetZ = (yInstances - 1) * spacing / 2;


	for (int x = 0; x < xInstances; x++) {
		for (int y = 0; y < yInstances; y++) {

			positions[y * xInstances + x] = (Vector3) {x * spacing - offsetX, 0, y * spacing - offsetZ};
			rotations[y * xInstances + x] = QuaternionIdentity();
			scales[y * xInstances + x] = (Vector3) {1, 1, 1};
			colors[y * xInstances + x] = (Color) {255, 255, 255, 255};
		}
	}

	R3D_UnmapInstances(
		instances, R3D_INSTANCE_POSITION | R3D_INSTANCE_ROTATION | R3D_INSTANCE_SCALE | R3D_INSTANCE_COLOR
	);

	meshSphere = R3D_GenMeshSphere(0.25f, 64, 64);
	matDefault = R3D_GetDefaultMaterial();
	{
		matDefault.albedo.color = (Color) {255, 255, 255, 255};
	}

	while (!WindowShouldClose()) {

		UpdateCamera(&camDefault, CAMERA_ORBITAL);

		BeginDrawing();

		R3D_Begin(camDefault);
		R3D_DrawMeshInstanced(meshSphere, matDefault, instances, instanceCount);
		R3D_End();

		const auto text = "Hello, Raylib and R3D!";
		const auto text_width = MeasureText(text, 20);
		const auto text_height = 20;

		DrawText(text, window_width / 2 - text_width / 2, window_height / 2 - text_height / 2, text_height, RED);
		EndDrawing();
	}

	R3D_UnloadInstanceBuffer(instances);
	R3D_UnloadMaterial(matDefault);
	R3D_UnloadMesh(meshSphere);
	R3D_Close();

	CloseWindow();
	return 0;
}
