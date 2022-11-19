#include "3D Platformer.h"

Game::Platformer_3D::Platformer_3D(const uint32_t window_width, const uint32_t window_height) :
	m_window_width(window_width), m_window_height(window_height)
{
	Init();
}

void mouse_position_callback(GLFWwindow* m_window, double xPos, double yPos) {
	Game::Platformer_3D* calling_function{ static_cast<Game::Platformer_3D*>(glfwGetWindowUserPointer(m_window)) };
	calling_function->GetPlayerObject()->UpdateCameraDirection((float)xPos, (float)yPos);
}

void Game::Platformer_3D::UpdateKeyboardInput() {
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_player->UpdatePlayerPosition(Objects::PlayerObject::W, time.dTime);
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		m_player->UpdatePlayerPosition(Objects::PlayerObject::S, time.dTime);
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_player->UpdatePlayerPosition(Objects::PlayerObject::A, time.dTime);
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		m_player->UpdatePlayerPosition(Objects::PlayerObject::D, time.dTime);
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_player->UpdatePlayerPosition(Objects::PlayerObject::SPACE, time.dTime);

	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
}

void Game::Platformer_3D::UpdateTime() {
	time.currentFrame = (float)glfwGetTime();
	time.dTime = time.currentFrame - time.lastFrame;
	time.lastFrame = time.currentFrame;
}

void Game::Platformer_3D::Init() {
	InitOpenGL();

	ImGui::CreateContext();
	ImGuiIO& IO{ ImGui::GetIO() };

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	Utility::ResourceManager::CreateShader("source/3D Platformer/Shaders/cube - vertex.glsl", "source/3D Platformer/Shaders/cube - fragment.glsl", "cube_shader");
	Utility::ResourceManager::GetShader("cube_shader").Use();

	glm::mat4 projection{ glm::perspective(glm::radians(90.0f), (float)m_window_width / (float)m_window_height, 0.1f, 100.0f) };
	Utility::ResourceManager::GetShader("cube_shader").SetMat4("projection", projection);

	m_gameObjects = new Objects::CubeArrayObject(glm::vec3(-1.0f, 1.0f, 1.0f), 15);
	m_player = new Objects::PlayerObject(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f));
}

void Game::Platformer_3D::InitOpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_window_width, m_window_height, "3D Platformer", nullptr, nullptr);
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return;

	glViewport(0,0, m_window_width, m_window_height);
	glEnable(GL_DEPTH_TEST);

	glfwSetWindowUserPointer(m_window, this);
	glfwSetCursorPosCallback(m_window, mouse_position_callback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Objects::PlayerObject* Game::Platformer_3D::GetPlayerObject() const {
	return m_player;
}

void Game::Platformer_3D::BeginImGui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Game::Platformer_3D::EndImGui() {
	ImGui::Begin("Debug Menu");
	ImGui::SetWindowSize(ImVec2(500.0f, 200.0f));
	ImGui::Text("Player position: %f, %f, %f", m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z);
	ImGui::Text("Player score: %i", m_player->GetScore());
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Game::Platformer_3D::RestartGame() {
	delete m_gameObjects;
	delete m_player;

	m_gameObjects = new Objects::CubeArrayObject(glm::vec3(-1.0f, 1.0f, 1.0f), 15);
	m_player = new Objects::PlayerObject(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f));
}

void Game::Platformer_3D::Update() {
	UpdateTime();
	m_player->UpdatePlayer(time.dTime, m_gameObjects);

	if (m_player->GetDeathStatus())
		RestartGame();
}

void Game::Platformer_3D::Run() {
	while (!glfwWindowShouldClose(m_window)) {
		Update();
		UpdateKeyboardInput();

		BeginImGui();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		m_gameObjects->DrawCubes(Utility::ResourceManager::GetShader("cube_shader"));

		EndImGui();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}