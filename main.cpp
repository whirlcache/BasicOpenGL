#include "Global.h"

#include <GLFW/glfw3.h>

#include "GameObject.h"
#include "ObjLoader.h"

void frameBufferSizeCallback(GLFWwindow*, int, int);
void processKeyboardEvents(GLFWwindow*);
void mousePosMoveCallback(GLFWwindow*, double, double);
void processMouseEvents(GLFWwindow*, int, int, int);

// 鼠标左键是否按下
bool isMousePress = GL_FALSE;
glm::vec2 mouseClickPos;

const int SCENE_WIDTH = 800;
const int SCENE_HEIGHT = 600;
double deltaTime = 0.0f;
double lastTime = 0.0f;

glm::vec3 lightPos = glm::vec3(-3.0f, 3.0f, 6.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCENE_WIDTH / (float)SCENE_HEIGHT, 0.1f, 100.0f);

int main(int argc, char** argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCENE_WIDTH, SCENE_HEIGHT, "Basic OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetCursorPosCallback(window, mousePosMoveCallback);
	glfwSetMouseButtonCallback(window, processMouseEvents);

	glewInit();

	// 立方体
	std::vector<glm::vec3> cubeVertes;
	std::vector<glm::vec3> cubeNormals;
	std::vector<glm::vec2> cubeUVs;
	// 平面
	std::vector<glm::vec3> planeVertes;
	std::vector<glm::vec3> planeNormals;
	std::vector<glm::vec2> planeUVs;

	LoadFromFile("./Cube.obj", cubeVertes, cubeUVs, cubeNormals);
	LoadFromFile("./Plane.obj", planeVertes, planeUVs, planeNormals);

	Mesh cubeMesh = Mesh(cubeVertes, cubeNormals, cubeUVs);
	Mesh cube2Mesh = Mesh(cubeVertes, cubeNormals, cubeUVs);
	Mesh planeMesh = Mesh(planeVertes, planeNormals, planeUVs);

	Shader cubeShader = Shader("./Shader/basic.vs", "./Shader/basic.fs");
	Shader cube2Shader = Shader("./Shader/basic.vs", "./Shader/basic.fs");
	Shader planeShader = Shader("./Shader/basic.vs", "./Shader/basic.fs");

	Material cubeMat = Material(cubeShader);
	Material cube2Mat = Material(cube2Shader);
	Material planeMat = Material(planeShader);

	GameObject cubeModel = GameObject(cubeMesh, cubeMat);
	GameObject cube2Model = GameObject(cube2Mesh, cube2Mat);
	GameObject planeModel = GameObject(planeMesh, planeMat);

	cubeModel.UpdateMaterialVec3("lightPos", lightPos);
	cubeModel.UpdateMaterialVec3("lightColor", lightColor);

	cube2Model.UpdateMaterialVec3("lightPos", lightPos);
	cube2Model.UpdateMaterialVec3("lightColor", lightColor);

	planeModel.UpdateMaterialVec3("lightPos", lightPos);
	planeModel.UpdateMaterialVec3("lightColor", lightColor);

	
	//cubeModel.SetTexture("./texture.png");
	cube2Model.SetTexture("./texture.png");
	planeModel.SetTexture("./marble.png");
	


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glDepthFunc(GL_ALWAYS);
	//glCullFace(GL_FRONT);

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processKeyboardEvents(window);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.5f));
		cubeModel.UpdateMaterialMat4("model", model);
		cubeModel.UpdateMaterialMat4("view", view);
		cubeModel.UpdateMaterialMat4("projection", projection);
		cubeModel.Render();

		model = glm::translate(model, glm::vec3(1.5f, 0.0f, -2.5f));
		cube2Model.UpdateMaterialMat4("model", model);
		cube2Model.UpdateMaterialMat4("view", view);
		cube2Model.UpdateMaterialMat4("projection", projection);
		cube2Model.Render();
		

		glm::mat4 pModel = glm::mat4(1.0f);
		pModel = glm::translate(pModel, glm::vec3(0.0f, -1.1f, 0.0f));
		pModel = glm::scale(pModel, glm::vec3(4.0f, 4.0f, 4.0f));

		planeModel.UpdateMaterialMat4("model", pModel);
		planeModel.UpdateMaterialMat4("view", view);
		planeModel.UpdateMaterialMat4("projection", projection);
		planeModel.Render();


		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

void processKeyboardEvents(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	float cameraSpeed = (float)(2.5f * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		cameraPos += cameraFront * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		cameraPos -= cameraFront * cameraSpeed;
	}
}

void processMouseEvents(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		isMousePress = GL_TRUE;
		GLdouble xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		mouseClickPos.x = (float)xpos;
		mouseClickPos.y = (float)ypos;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		isMousePress = GL_FALSE;
	}
}

void mousePosMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (isMousePress)
	{
		float offsetX = xpos - mouseClickPos.x;
		float offsetY = ypos - mouseClickPos.y;
		//glm::vec3 cameraRight = glm::cross(cameraUp, cameraFront);
		float cameraSpeed = (float)(0.025f * deltaTime);
		cameraPos.x -= offsetX * cameraSpeed;
		cameraPos.y += offsetY * cameraSpeed;
	}
}

void frameBufferSizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}