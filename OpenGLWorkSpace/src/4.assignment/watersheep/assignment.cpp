#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>

#include <iostream>
#include <string>
#include <assignment/texture_loc.h>

#define PI 3.14159265

// Box coordinate with 36 vertices.
// Every 3 coordinates will form 1 triangle.
// The last 2 columns represent texture coordinate for mapping.
float box[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
unsigned int loadTexture(char const * path);

void register_tex_pack(unsigned int * tex, std::string path, int size, const std::string pack[]);
void draw_models(Shader *ourShader, glm::mat4 view, glm::mat4 projection, Shader lamp_shader);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

//texture packs for models
unsigned int sven_tex[SVEN_SIZE], sheep_tex[SHEEP_SIZE], light_tool_tex[2], heli_tex[2];
unsigned int tex_wood_diffuse, tex_street_diffuse, tex_grass_diffuse, tex_marble_diffuse, tex_curtin_diffuse, tex_sky_diffuse;
unsigned int tex_wood_specular, tex_street_specular, tex_grass_specular, tex_marble_specular, tex_curtin_specular;
//vertex buffers allow global access for ease
unsigned int VBO_box[2], VAO_box[2];
unsigned int VAO_light;

//lighting starting position
glm::vec3 light_pos(0.0f, 0.4f, 3.0f);

// camera
glm::vec3 camera_pos   = glm::vec3(0.0f, 0.9f,  3.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);
glm::vec3 last_placed_light;
glm::vec3 last_pos;
glm::mat4 prev_view;
glm::vec3 sheep_direction;//global to allow sheep last direction to be stored

//mouse settings
bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

// timing
float delta_time = 0.0f;	// time between current frame and last frame
float last_frame = 0.0f;
float jump_frame = 0.0f;
int delay_jump = 0;
bool isJump = false;
bool descend = false;
float move_sheep = 0.0f;

//Toggle (Animation or states)
bool BUTTON_PRESSED = false;
int BUTTON_DELAY = 0;
bool BUTTON_CLOSE_ENOUGH = false;
bool LIGHT_IGNITED = true;
bool LIGHTING_ACTIVE = true;

//for collision detect
bool PICKUP_LIGHT = false;
bool LIGHT_TOUCHED =false;
bool TORCH_NEAR = false;
bool SVEN_NEAR = false;
bool SVEN_TOUCHED = false;
bool PICKUP_SVEN = false;
bool PLAYER_DEAD = false;

bool SHOW_COORDINATE = false;
int SHOW_DELAY = 0;
bool isPerspec = true;

//Animation Variables
float curtin_rotate_y = 0.0;
float curtin_translate_y = 0.0;

//illuminations variables
float LINEAR_ATT = 0.35;
float QUAD_ATT = 0.44;

// Countdown until the button trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_delay()
{
	if(BUTTON_DELAY > 0) BUTTON_DELAY -= 1;
	if(SHOW_DELAY > 0) SHOW_DELAY -= 1;
}

void jump_button_delay()
{
	if(delay_jump > 0)
		delay_jump -= 1;
}

//function for incremental rise when jump button pressed
//makes jumping look more realistic rather than teleport
void jump_rise()
{
	//only rise when space (jump button) is pressed
	if(isJump)
	{
		//difference between current last frame
		// and frame since pressing space is less than 0.2
		//then increment camera y position upwards
		if((last_frame - jump_frame) <= 0.2)
		{
			camera_pos.y += 0.1f;
		}
		else//other wise jump is at peak, being descend
		{
			delay_jump = 40;
			descend = true;
			isJump = false;
		}
	}
}

//function to bring or keep camera at ground level/prevent flying
void down_gravity()
{
	if(camera_pos.y >= 0.9 && descend)
	{
		if((camera_pos.y - 0.1) > 0.9)
		{
			camera_pos.y -= (0.055);
		}
		else
		{
			camera_pos.y = 0.9;
			isJump = false;
			descend = false;
		}
	}

	if(isJump == false && descend == false)
	{
		camera_pos.y = 0.9;
	}
}


// Toggle button pressing only if the camera is close enough.
void toggle_button_distance(glm::vec3 button_pos)
{
	if(glm::length(camera_pos - button_pos) <= 1.6f)
		BUTTON_CLOSE_ENOUGH = true;
	else
		BUTTON_CLOSE_ENOUGH = false;
}

//function to find if distance between camera and specified coord is near
//specified range
bool obj_near(glm::vec3 obj_pos, float nearDist)
{
    bool isNear = false;
    if(glm::length(camera_pos - obj_pos) <= nearDist)
        isNear = true;

    return isNear;
}

float walk_animation(float rotDelta, int obj_pos)
{
	float rot;
	if(obj_pos % 2 == 0)
	{
		rot = glm::sin(glfwGetTime() * 20.0f) * rotDelta;
		// std::cout << "time " << glfwGetTime() << std::endl;
		// std::cout << "sine " << glm::sin(glfwGetTime() * 20.0f) << std::endl;
		// std::cout << "Rot " << rot << std::endl;
	}
	else
	{
		rot = -(glm::sin(glfwGetTime() * 20.0f) * rotDelta);
		// std::cout << glfwGetTime() << std::endl;
	}
	// std::cout << rot << std::endl;

	return rot;
}

//function for helping decide movement speed of watersheep
//the amount the scalar value is incremented depends on distance of sheep to camera
void sheep_mover(glm::vec3 watSheep)
{	
	//when getting distance, ignore the y axis since it never changes. keeping it may cause inaccuracy
	float dist = glm::distance(glm::vec3(camera_pos.x, 0.0f, camera_pos.z), glm::vec3(watSheep.x, 0.0f, watSheep.z));
	std::cout << "cam x " << camera_pos.x << std::endl;
	std::cout << "direction x " << watSheep.x << std::endl;
	// std::cout << "cam y " << camera_pos.y << std::endl;
	// std::cout << "direction y"  << watSheep.y << std::endl;
	std::cout << "cam z " << camera_pos.z << std::endl;
	std::cout << "direction z" << watSheep.z << std::endl;
	std::cout << "total dist " << dist << std::endl;

	//if close enough to player, then player is dead
	if(dist < 0.8f)
	{
		PLAYER_DEAD = true;
	}
	if(obj_near(watSheep, 2.0f) && !PLAYER_DEAD)
	{
		move_sheep += 0.005f; //increase scalar value
	}
	else if(glm::length(camera_pos - watSheep) > 2.0f && !PLAYER_DEAD)
	{
		move_sheep += 0.0015f;	
	}
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement for OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Water Sheep", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	// glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader *ourShader;//pointer to shader, makes switching between dark and bright shaders easier without having to create a new instance each render
	Shader darkShader("./lighting.vs", "./lighting.fs");//default which is dark scenery
	Shader brightShader("./noLighting.vs", "./noLighting.fs");// switch to bright scene
	Shader lamp_shader("./lamp.vs", "./lamp.fs");


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	glGenVertexArrays(2, VAO_box);
	glGenBuffers(2, VBO_box);

	//defaultbox
	glBindVertexArray(VAO_box[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);

	//vertex coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//normal vectors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//use boxes coordinates that have textures that are position the same on the sides
	//unlike box for tutorial which has textures rotated differently
	glBindVertexArray(VAO_box[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(box), same_side_box, GL_STATIC_DRAW);

	//vertex coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//normal vectors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &VAO_light);
	glBindVertexArray(VAO_light);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box[1]);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//normal vectors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// load and create a texture 
	// -------------------------
	// unsigned int tex_wood_diffuse, tex_street_diffuse, tex_grass_diffuse, tex_marble_diffuse, tex_curtin_diffuse, tex_sky_diffuse;
	// unsigned int tex_wood_specular, tex_street_specular, tex_grass_specular, tex_marble_specular, tex_curtin_specular;

	unsigned int tex_red_dark_diffuse, tex_red_bright_diffuse, tex_red_diffuse, tex_green_diffuse, tex_blue_diffuse;
	unsigned int tex_red_dark_specular, tex_red_bright_specular, tex_red_specular, tex_green_specular, tex_blue_specular;

	tex_wood_diffuse = loadTexture(FileSystem::getPath("resources/textures/wood2.jpg").c_str());
	tex_wood_specular = loadTexture(FileSystem::getPath("resources/textures/wood2_specular.jpg").c_str());
	tex_street_diffuse = loadTexture(FileSystem::getPath("resources/textures/street.png").c_str());
	tex_street_specular = loadTexture(FileSystem::getPath("resources/textures/street_specular.png").c_str());
	tex_grass_diffuse = loadTexture(FileSystem::getPath("resources/textures/grass.jpg").c_str());
	tex_grass_specular = loadTexture(FileSystem::getPath("resources/textures/grass_specular.jpg").c_str());
	tex_marble_diffuse = loadTexture(FileSystem::getPath("resources/textures/marble.jpg").c_str());
	tex_marble_specular = loadTexture(FileSystem::getPath("resources/textures/marble_specular.jpg").c_str());
	tex_curtin_diffuse = loadTexture(FileSystem::getPath("resources/textures/curtin.jpg").c_str());
	tex_curtin_specular = loadTexture(FileSystem::getPath("resources/textures/curtin_specular.jpg").c_str());
	tex_sky_diffuse = loadTexture(FileSystem::getPath("resources/textures/night_sky.jpg").c_str());

	tex_red_dark_diffuse = loadTexture(FileSystem::getPath("resources/textures/red_dark.jpg").c_str());
	tex_red_dark_specular = loadTexture(FileSystem::getPath("resources/textures/red_dark_specular.jpg").c_str());
	tex_red_bright_diffuse = loadTexture(FileSystem::getPath("resources/textures/red_bright.jpg").c_str());
	tex_red_bright_specular = loadTexture(FileSystem::getPath("resources/textures/red_bright_specular.jpg").c_str());
	tex_red_diffuse = loadTexture(FileSystem::getPath("resources/textures/red.jpg").c_str());
	tex_red_specular = loadTexture(FileSystem::getPath("resources/textures/red_specular.jpg").c_str());
	tex_green_diffuse = loadTexture(FileSystem::getPath("resources/textures/green.jpg").c_str());
	tex_green_specular = loadTexture(FileSystem::getPath("resources/textures/green_specular.jpg").c_str());
	tex_blue_diffuse = loadTexture(FileSystem::getPath("resources/textures/blue.jpg").c_str());
	tex_blue_specular = loadTexture(FileSystem::getPath("resources/textures/blue_specular.jpg").c_str());
	// register_texture(&sven_body,"resources/sven_textures/" + sven_files[6]);

	//register textures packs, 4th param can be found in includes/assignment/texture_loc.h header file
	register_tex_pack(sven_tex,"resources/sven_textures/", SVEN_SIZE, sven_files);
    register_tex_pack(sheep_tex,"resources/sheep_textures/", SHEEP_SIZE, sheep_files);
    register_tex_pack(light_tool_tex,"resources/lightTool_textures/", 2, light_tool);
    register_tex_pack(heli_tex,"resources/heli_textures/", 2, helicopter);


	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	// ourShader->use();
	// ourShader->setInt("material.diffuse", 0);
	// ourShader->setInt("material.specular", 1);
	// pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
	// -----------------------------------------------------------------------------------------------------------

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{

		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		delta_time = currentFrame - last_frame;
		last_frame = currentFrame;

		// std::cout << currentFrame << std::endl;

		//update delay countdown
		update_delay();
		jump_button_delay();//countdown jump delay since first jump
		
		// input
		// -----
		process_input(window);
		jump_rise();//method to make jump look more realistic by small increments of y
		down_gravity();//method to keep player camera grounded(prevent flying)

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


		// select and activate shader
		if(LIGHTING_ACTIVE)
		{
			ourShader = &darkShader; //use the darkShader (shader utilising lighting), by pointing to address
			ourShader->use();
			ourShader->setInt("material.diffuse", 0);
			ourShader->setInt("material.specular", 1);

	       	ourShader->setVec3("light.position", light_pos);
	       	ourShader->setVec3("light.ambient", 0.1f, 0.1f, 0.1f);

	       	if(LIGHT_IGNITED == true)
			{
				ourShader->setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
				ourShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
			}
			else
			{
				ourShader->setVec3("light.diffuse", 0.0f, 0.0f, 0.0f);
				ourShader->setVec3("light.specular", 0.0f, 0.0f, 0.0f);
			}
			ourShader->setFloat("light.constant", 1.0f);
			ourShader->setFloat("light.linear", LINEAR_ATT);
			ourShader->setFloat("light.quadratic", QUAD_ATT);

			ourShader->setFloat("material.shininess", 65.0f);
		}
		else
		{
			ourShader = &brightShader;//use bright shader (shader not utilising lighting)
			ourShader->use();
		}

		ourShader->setVec3("viewPos", camera_pos);

       //projection transformation
        glm::mat4 projection; 
        if(isPerspec)
        {
            projection= glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
        }
        else
        {
            projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, 200.0f);
        }
        ourShader->setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
		ourShader->setMat4("view", view);

		//declare transformation matrix
		glm::mat4 model = glm::mat4();
		/*
		//example (remember, it is in column matrix position, so the order is reversed.)
		model = glm::translate(model, glm::vec3(1.0f, 2.0f, 3.0f)); 			// translate by (1.0, 2.0, 3.0)
		model = glm::scale(model, glm::vec3(2.0f, 5.0f, 3.0f)); 			// scale by (2.0, 5.0, 3.0) on X, Y, and Z respectively.
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));	// rotate 45 degree about Y-axis (0,1,0)
		*/

		//Draw objects
		//------------------------------------------------------------------------------------------
		
		//Sky
		// glBindVertexArray(VAO_box[0]);//This does not have to binded every time after first call, but just for consistency.

		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, tex_sky_diffuse);

		// model = glm::mat4();
		// model = glm::scale(model, glm::vec3(200.0f, 200.0f, 200.0f));

		// ourShader->setMat4("model", model);

		// glDrawArrays(GL_TRIANGLES, 0, 36);


		//Coordinate System
		if(SHOW_COORDINATE == true)
		{
			
			glm::vec3 coord_scales[] = {
				glm::vec3( 100.0f,  0.02f,  0.02f),	//X
				glm::vec3( 0.02f,  100.0f,  0.02f),	//Y
				glm::vec3( 0.02f,  0.02f,  100.0f),	//Z
			};

			glBindVertexArray(VAO_box[0]);

			glActiveTexture(GL_TEXTURE0);

			for(int tab = 0; tab < 3; tab++)
			{	
				if(tab == 0) glBindTexture(GL_TEXTURE_2D, tex_red_diffuse); 	//X
				if(tab == 1) glBindTexture(GL_TEXTURE_2D, tex_green_diffuse);	//Y
				if(tab == 2) glBindTexture(GL_TEXTURE_2D, tex_blue_diffuse);	//Z

				model = glm::mat4();
				model = glm::scale(model, coord_scales[tab]);

				ourShader->setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}


		//Street
		glBindVertexArray(VAO_box[0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_street_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_street_specular);

		model = glm::mat4();
		model = glm::scale(model, glm::vec3(3.0f, 0.001f, 7.0f));

		ourShader->setFloat("material.shininess", 10.0f);
		ourShader->setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);



		//Grass
		glBindVertexArray(VAO_box[0]);
		//this results in a 200 x 200 terrain grid
		//generate terrain grid by creating and translate multiple grass models
		float gridX = 100.0f;// state point for terrain at x axis
		float gridZ = 100.0f;//start point for terrain at z axis
		for(int i = 0; i < 20; i++)//add column
		{
			for(int j = 0; j < 20; j++)//add row
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_grass_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_grass_specular);

				model = glm::mat4();
				// move to desired gridX and gridZ positions
				model = glm::translate(model, glm::vec3(gridX, -0.01f, gridZ));
				model = glm::scale(model, glm::vec3(10.0f, 0.001f, 10.0f));

				ourShader->setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
				gridZ -= 10.0f;// move up ten on z axis
			}

			gridX -= 10.0f;//move 10 to left of x axis
			gridZ = 100.0f;//start at 50 again on z axis to add row at (gridX - 10)
		}


		//Table (4 tall boxes for legs & 1 thin box as table top)
		glm::vec3 table_scales[] = {
			glm::vec3( 1.0f,  0.1f,  1.0f),	//top
			glm::vec3( 0.1f,  0.5f,  0.1f),//near left
			glm::vec3( 0.1f,  0.5f,  0.1f),	//near right
			glm::vec3( 0.1f,  0.5f,  0.1f),//far left
			glm::vec3( 0.1f,  0.5f,  0.1f),	//far right
		};
		glm::vec3 table_positions[] = {
			glm::vec3( 0.0f,  0.5f,  0.0f),		//top
			glm::vec3(-0.45f, 0.0f,  0.45f),	//near left
			glm::vec3( 0.45f, 0.0f,  0.45f),	//near right
			glm::vec3(-0.45f, 0.0f, -0.45f),	//far left
			glm::vec3( 0.45f, 0.0f, -0.45f),	//far right
		};

		glBindVertexArray(VAO_box[0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_wood_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_wood_specular);

		for(int tab = 0; tab < 5; tab++)
		{	
			model = glm::mat4();
			model = glm::translate(model, table_positions[tab]);
			model = glm::scale(model, table_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			ourShader->setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//function to draw sven,light source, water sheep and any other model
		//this is just to make while loop less cluttered
        draw_models(ourShader, view, projection, lamp_shader);

		//Button on table (1 big box & 1 small box as button)
		glm::vec3 button_scales[] = {
			glm::vec3( 0.2f,  0.12f,  0.2f),		//case
			glm::vec3( 0.12f,  0.12f,  0.12f),		//button
		};

		float red_button_height = 0.05f;
		if(BUTTON_PRESSED == true) {red_button_height -= 0.02f;}

		glm::vec3 button_positions[] = {
			glm::vec3( 0.0f,  0.0f,  0.0f),			//case
			glm::vec3( 0.0f,  red_button_height,  0.0f),	//button
		};

		glm::vec3 button_final_location = glm::vec3(0.0f, 0.56f, 0.25f);
		toggle_button_distance(button_final_location); 

		glBindVertexArray(VAO_box[0]);
		
		for(int tab = 0; tab < 2; tab++)
		{	
			glActiveTexture(GL_TEXTURE0);
			if(tab == 0)
			{	
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_marble_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_marble_specular);
			}
			else
			{
				if(BUTTON_PRESSED == false) 	// Not Pressed
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tex_red_dark_diffuse);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, tex_red_dark_specular);
				}
				else				// Pressed
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tex_red_bright_diffuse);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, tex_red_bright_specular);
				}
			}

			model = glm::mat4();
			model = glm::translate(model, button_final_location);
			model = glm::translate(model, button_positions[tab]);
			model = glm::scale(model, button_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			ourShader->setFloat("material.shininess", 65.0f);
			ourShader->setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		//Curtin Logo
		glBindVertexArray(VAO_box[0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_curtin_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_curtin_specular);

		//transformation for animation
		if(BUTTON_PRESSED == true)
		{
			curtin_translate_y += 1.0f;
			curtin_rotate_y += 1.0f;
			if(abs(curtin_translate_y - 360.0f) <= 0.1f) curtin_translate_y = 0.0f;
			if(abs(curtin_rotate_y - 360.0f) <= 0.1f) curtin_rotate_y = 0.0f;
		}

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 0.9f + (0.1f * sin(curtin_translate_y * PI / 180.f)), -0.35f));
		model = glm::rotate(model, glm::radians(curtin_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.001f));

		ourShader->setFloat("material.shininess", 100.0f);
		ourShader->setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);


		
		if(LIGHT_IGNITED == true) lamp_shader.setFloat("intensity", 5.0);
		else lamp_shader.setFloat("intensity", 0.3);

		



		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(2, VAO_box);
	glDeleteBuffers(2, VBO_box);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, true);

	float cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		cameraSpeed = 2.5 * delta_time; 
	else
		cameraSpeed = 2.5 * delta_time * 2;	// double speed with "Shift" pressed

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
		camera_pos += cameraSpeed * camera_front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_pos -= cameraSpeed * camera_front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;

	//jump
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !isJump && delay_jump == 0)
	{
		jump_frame = glfwGetTime();
		isJump = true;
	}

	//toggle red button
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && BUTTON_DELAY == 0 && BUTTON_CLOSE_ENOUGH == true)
	{
		BUTTON_DELAY = 20;
		if(BUTTON_PRESSED == false) 		
			BUTTON_PRESSED = true;
		else
			BUTTON_PRESSED = false;

		PICKUP_LIGHT = false;
		LIGHT_TOUCHED =false;
		TORCH_NEAR = false;
		SVEN_NEAR = false;
		SVEN_TOUCHED = false;
		PICKUP_SVEN = false;
		PLAYER_DEAD = false;
		sheep_direction = glm::vec3(0.0f, 0.0f, 0.0f);
		move_sheep = 0.0f;
		camera_pos   = glm::vec3(0.0f, 0.9f,  3.0f);
		camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
		camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);
		light_pos = glm::vec3(0.0f, 0.4f, 3.0f);
	}

	//toggle coordinate visibility
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && SHOW_DELAY == 0)
	{
		SHOW_DELAY = 20;
		if(SHOW_COORDINATE == false) 		
			SHOW_COORDINATE = true;
		else
			SHOW_COORDINATE = false;
	}

	//pick up light source
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && SHOW_DELAY == 0 && TORCH_NEAR)
    {
        SHOW_DELAY = 30;
        LIGHT_TOUCHED = true;
        if(PICKUP_LIGHT == false)
        {
            PICKUP_LIGHT = true;
        }
        else
        {
            //place light down if looking at ground
            if(pitch >= -60.0f && pitch < -52.0f)
            {
               PICKUP_LIGHT = false;
               last_placed_light =  camera_pos + camera_front;
            }
        }
    }

    //pickup sven
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && SHOW_DELAY == 0 && SVEN_NEAR)
    {
        SHOW_DELAY = 30;
        if(PICKUP_SVEN == false)
        {
            PICKUP_SVEN = true;
            SVEN_TOUCHED = true;
        }
    }

    //perspective or orthographic
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && SHOW_DELAY == 0)
    {
        SHOW_DELAY = 30;
        if(isPerspec)
        {
            isPerspec = false;
        }
        else
        {
            isPerspec = true;
        }
    }

    //ignite lightsaber
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && BUTTON_DELAY == 0 && PICKUP_LIGHT == true)
	{
		BUTTON_DELAY = 20;
		if(LIGHT_IGNITED == false) 		
			LIGHT_IGNITED = true;
		else
			LIGHT_IGNITED = false;
	}

	//decrease attenuation brightness
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && BUTTON_DELAY == 0)
	{
		BUTTON_DELAY = 20;
		//if attributes are above 9, no point of decreasing further since it makes no difference
		if(LINEAR_ATT < 9.0f || QUAD_ATT < 1.0f)
		{
			LINEAR_ATT /= 0.8f;
			QUAD_ATT /= 0.8f;
		}
		std::cout << "LINEAR- " << LINEAR_ATT << std::endl;
		std::cout << "QUAD- " << QUAD_ATT << std::endl;
	}

	//increase attenuation brightness
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && BUTTON_DELAY == 0)
	{
		BUTTON_DELAY = 20;
		//multiply to make sure attributes never go negative
		if(LINEAR_ATT > 0.006f || QUAD_ATT > 0.008f)// no point decreasing futher since it makes no diff after these
		{
			LINEAR_ATT *= 0.8f;
			QUAD_ATT *= 0.8f;
		}
		std::cout << "LINEAR+ " << LINEAR_ATT << std::endl;
		std::cout << "QUAD+ " << QUAD_ATT << std::endl;
	}

		//switch dark and bright scenery
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && BUTTON_DELAY == 0)
	{
		BUTTON_DELAY = 20;
		if(LIGHTING_ACTIVE == false) 		
			LIGHTING_ACTIVE = true;
		else
			LIGHTING_ACTIVE = false;
	}
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -60.0f)
        pitch = -60.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front = glm::normalize(front);
    down_gravity();
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}



//registering a new texture. You can modify this function to allow for more configuration options.
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

//function to register bunch of textures from an array containing file names
void register_tex_pack(unsigned int * tex, std::string path, int size, const std::string pack[])
{
	int i;

	for(i = 0; i < size; i++)
	{
		glGenTextures(1, &tex[i]);

		int width, height, nrComponents;
	
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		unsigned char *data = stbi_load(FileSystem::getPath(path + pack[i]).c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, tex[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
}

//function to draw models, makes code look neater
void draw_models(Shader *ourShader, glm::mat4 view, glm::mat4 projection, Shader lamp_shader)
{
    //--------light source----------//
    glm::vec3 light_tool_scales[] = {
        glm::vec3( 0.03f,  0.09f,  0.03f), //hilt
        glm::vec3( 0.025f,  0.14f,  0.025f),// source
    };

    glm::vec3 light_tool_positions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),     //hilt
        glm::vec3(0.0f, 0.11f,  0.0f),    //source
    };

    glBindVertexArray(VAO_box[1]);
    float tempY = 0.0f;

    for(int tab = 0; tab < 2; tab++)
    {   
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, light_tool_tex[tab]);
        glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_curtin_specular);
        glm::mat4 lightSaber = glm::mat4();
        
        if(!PICKUP_LIGHT)
        {
            //if light has never been touched then put it at default location
            if(!LIGHT_TOUCHED)
            {
                lightSaber = glm::translate(lightSaber, glm::vec3(0.0f, 0.1f, 3.0f));  
                TORCH_NEAR = obj_near(glm::vec3(0.0f, 0.1f, 3.0f), 1.6f);//collision detection
            }
            else //otherwise light not at default location, render at last location placed
            {
                tempY = glm::abs(last_placed_light.y);//make sure position above ground
                
                if(tempY < 0.02f)
                    tempY += 0.03f;//makes sure object does go below ground

                // std::cout << tempY << std::endl;
                lightSaber = glm::translate(lightSaber, glm::vec3(last_placed_light.x, tempY + 0.01, last_placed_light.z));  
                light_pos = glm::vec3(last_placed_light.x, tempY + 0.4, last_placed_light.z);  
                TORCH_NEAR = obj_near(glm::vec3(last_placed_light.x, tempY, last_placed_light.z), 1.6f); //collision detection
            }
        }
        else//player carrying light
        {
            //inverse of view allows view camera matrix points to be used in model space
            //since the view matrix is inverse of model space, bringing model to view
            prev_view = glm::inverse(view);
            lightSaber = glm::translate(lightSaber, glm::vec3(0.1f, -0.1f, -0.3f));
            lightSaber =  prev_view * lightSaber; //bring the lightsaber to the view/camera space
            light_pos = glm::vec3(camera_pos.x, camera_pos.y, camera_pos.z);//light follow camera
        }
        //light source
	    if(tab == 1 && LIGHT_IGNITED)
	    {
        	// std::cout << tab << std::endl;
        	glBindVertexArray(VAO_light);
	        // Draw the light source
	        lamp_shader.use();
	    	lamp_shader.setMat4("projection", projection);
			lamp_shader.setMat4("view", view);
			
			lightSaber = glm::translate(lightSaber, light_tool_positions[tab]); //source model part positioning
			lightSaber = glm::scale(lightSaber, light_tool_scales[tab]); // light source scale
			lamp_shader.setMat4("model", lightSaber);
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        else if(tab != 1)//hilt
        {
	    	lightSaber = glm::translate(lightSaber, light_tool_positions[tab]); //model part positioning
	        lightSaber = glm::scale(lightSaber, light_tool_scales[tab]);//model scale
	        ourShader->use();
	        ourShader->setMat4("model", lightSaber);

	        glDrawArrays(GL_TRIANGLES, 0, 36);
	    }
    }


        //** sven the wolf **//
    glm::vec3 sven_scales[] = {
        glm::vec3( 0.2f,  0.18f,  0.15f),   //head
        glm::vec3( 0.3f,  0.25f,  0.2f),//collar
        glm::vec3( 0.2f,  0.2f,  0.4f), //body
        glm::vec3( 0.1f,  0.06f,  0.1f),//mouth
        glm::vec3( 0.07f,  0.09f,  0.02f),  //right ear
        glm::vec3( 0.07f,  0.09f,  0.02f),  //left ear
        glm::vec3( 0.05f,  0.06f,  0.2f),   //tail
        glm::vec3( 0.08f,  0.3f,  0.08f),   //right front leg
        glm::vec3( 0.08f,  0.3f,  0.08f),   //left front leg
        glm::vec3( 0.08f,  0.3f,  0.08f),   //right back leg
        glm::vec3( 0.08f,  0.3f,  0.08f),   //left back leg
        glm::vec3( 0.1f,  0.02f,  0.1f),//jaw
        glm::vec3( 0.02f,  0.02f,  0.02f),//nose
        glm::vec3( 0.05f,  0.03f,  0.0001f),//left eye
        glm::vec3( 0.05f,  0.03f,  0.0001f),//right eye
    };

    glm::vec3 sven_positions[] = {
        glm::vec3( 0.0f,  0.82f,  0.75f),       //1.head
        glm::vec3( 0.0f, 0.8f,  0.9f),  //2.collar
        glm::vec3( 0.0f, 0.8f,  1.2f),  //3.body
        glm::vec3(0.0f, 0.78f, 0.63f),  //4.mouth
        glm::vec3( 0.064f, 0.92f, 0.75f),   //5.right ear
        glm::vec3( -0.064f, 0.92f, 0.75f),  //6.left ear
        glm::vec3( -0.0f, 0.86f, 1.45f),    //7.tail
        glm::vec3( 0.05f, 0.6f, 0.92f), //8.right front leg
        glm::vec3( -0.05f, 0.6f, 0.92f),    //9.left front leg
        glm::vec3( 0.05f, 0.6f, 1.32f), //10.right back leg
        glm::vec3( -0.05f, 0.6f, 1.32f),    //11.left back leg
        glm::vec3(0.0f, 0.74f, 0.625f), //12. jaw
        glm::vec3(0.0f, 0.81f, 0.58f),  //13. nose
        glm::vec3(-0.05f, 0.825f, 0.674f),  //14. left_eye
        glm::vec3(0.05f, 0.825f, 0.674f),   //15. right_eye
    };

    ourShader->use();
    glBindVertexArray(VAO_box[0]);

    for(int tab = 0; tab < SVEN_SIZE; tab++)
    {   
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sven_tex[tab]);
        glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_grass_specular);

        // std::cout << tab << std::endl;
        //translate first then scale or rotate
        glm::mat4 sven = glm::mat4();
        
        
        if(PICKUP_SVEN == false)
        {
            sven = glm::translate(sven, glm::vec3(-2.0f, 0.1f, 0.0f));  
            SVEN_NEAR = obj_near(glm::vec3(-2.0f, 0.3f, 0.0f), 1.6f);//collision detection
            // std::cout << SVEN_NEAR << std::endl;
            sven = glm::rotate(sven, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));//sven laying down
        }
        else
        {     
            //inverse of view allows view camera matrix points to be used in model space
            //since the view matrix is inverse of model space, bringing model to view
            prev_view = glm::inverse(view);

            
            sven = glm::translate(sven, glm::vec3(-0.3f, -0.1f, -0.4f));   
            sven = glm::rotate(sven, glm::radians(-95.0f), glm::vec3(0.0f, 1.0f, 0.0f));         
            sven = glm::scale(sven, glm::vec3(0.5f, 0.5f, 0.5f));
            sven =  prev_view * sven; //bring sven to the view/camera space
        }

        sven = glm::translate(sven, glm::vec3(0.0f, -0.8f, -1.2f));// move to origin 
        sven = glm::translate(sven, sven_positions[tab]);
        sven = glm::scale(sven, sven_scales[tab]);
        if(tab == 13)//eyes
        {
            sven = glm::rotate(sven, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        }
        else if(tab == 14)
        {
            sven = glm::rotate(sven, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));   
        }

        ourShader->setMat4("model", sven);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    //** water sheep **//
    glm::vec3 sheep_scales[] = {
        glm::vec3( 0.35f,  0.25f,  0.55f),  //body
        glm::vec3( 0.2f,  0.2f,  0.2f),//wool head
        glm::vec3( 0.16f,  0.16f,  0.02f),//head face
        glm::vec3( 0.16f,  0.16f,  0.001f),//face
        glm::vec3( 0.14f,  0.14f,  0.14f),  //right front leg
        glm::vec3( 0.14f,  0.14f,  0.14f),//left front leg
        glm::vec3( 0.14f,  0.14f,  0.14f),  //right back leg
        glm::vec3( 0.14f,  0.14f,  0.14f),  //left back leg
        glm::vec3( 0.1f,  0.12f,  0.1f),  //lower leg
    };

    glm::vec3 sheep_positions[] = {
        glm::vec3( 0.0f,  0.5f,  4.0f),     //1.body
        glm::vec3( 0.0f, 0.65f,  3.75f),    //2.wool head
        glm::vec3( 0.0f, 0.65f,  3.64f),    //3.head face
        glm::vec3( 0.0f, 0.65f,  3.6297f),    //4.face
        glm::vec3( 0.08f, 0.328f,  3.85f),  //5. r front leg
        glm::vec3(-0.08f, 0.328f, 3.85f),   //6. l front leg
        glm::vec3( 0.08f, 0.328f,  4.18f),  //7. r back leg
        glm::vec3( -0.08f, 0.328f,  4.18f), //8. l back leg
        glm::vec3( 0.08f, 0.215f,  3.85f),  //9. r front low leg
        glm::vec3( -0.08f, 0.218f,  3.85f),  //10. l front low leg
        glm::vec3( 0.08f, 0.218f,  4.18f),  //11. r back low leg
        glm::vec3( -0.08f, 0.218f,  4.18f), //12. l back low leg
    };

    glBindVertexArray(VAO_box[0]);

    //specify sheep start location in world
    glm::vec3 sheep_start_location = glm::vec3(2.08f, 0.1f, -2.32f);

    for(int tab = 0; tab < 12; tab++)
    {   
        glm::mat4 sheep = glm::mat4();
        
        if(PICKUP_SVEN)
        {
        	glm::vec3 direction = glm::normalize(glm::vec3(camera_pos - sheep_start_location));
        	float angle = glm::atan(direction.x, direction.z);

	        // if player is not dead then sheep follows player
	        if(!PLAYER_DEAD)
	        {	
	        	//add sheep starting position to direction matrix, result of this will give the actual 
	        	//position of the sheep instead of direction and which will help get correct distance
	        	//between the camera and sheep
	        	sheep_mover(sheep_direction  + sheep_start_location);//calculate move_sheep scalar variable
	        	sheep_direction = glm::vec3(direction.x, 0.0f, direction.z) * move_sheep; 
	        	sheep = glm::translate(sheep, sheep_direction);
	        }
	        else //player is dead, sheep will be at location since hitting player
	        {
	        	//adding direction and start direction gives current position of sheep
	        	direction = glm::normalize(glm::vec3(camera_pos - (sheep_direction + sheep_start_location)));
	        	sheep = glm::translate(sheep, sheep_direction);
	        	angle = glm::atan(direction.x, direction.z);
	        }
	        
  			//opengl column vector, must do opposite order of row vector
		    sheep = glm::translate(sheep, sheep_start_location);//put to desired starting place in the world
		    sheep = glm::rotate(sheep, angle, glm::vec3(0.0f, 1.0f, 0.0f)); //rotate accordingly when camera pos moves
		    
		    sheep= glm::rotate(sheep, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));//make sheep face the camera
	    }
	    else//default location
	   	{
	   		sheep = glm::translate(sheep, sheep_start_location);//put to desired starting place in the world
	   		sheep= glm::rotate(sheep, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	   	}

	   	
        sheep = glm::translate(sheep, glm::vec3(0.08f, -0.25f, -4.18f));//move to origins
        sheep = glm::translate(sheep, sheep_positions[tab]);//start

        //walk animation when chasing player
        if(tab > 7 && !PLAYER_DEAD && PICKUP_SVEN)// lower leg
        {
        	sheep = glm::translate(sheep, glm::vec3( 0.0f,  0.15f,  0.0f));//move back to previous y
        	sheep= glm::rotate(sheep, walk_animation(0.3f, tab), glm::vec3(1.0, 0.0, 0.0));//do rotaton animation
        	sheep = glm::translate(sheep, glm::vec3( 0.0f,  -0.15f,  0.0f));//move top of leg to origin y
        }
        if(tab > 3 && tab < 8 && !PLAYER_DEAD && PICKUP_SVEN)// upper leg
        {
        	sheep= glm::rotate(sheep, walk_animation(0.4f, tab), glm::vec3(1.0, 0.0, 0.0));
        }
        // if(tab == 3)
        // {
        	glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
        // }

        if(tab < 9)
        {
             sheep = glm::scale(sheep, sheep_scales[tab]);
             glActiveTexture(GL_TEXTURE0);
             glBindTexture(GL_TEXTURE_2D, sheep_tex[tab]);
        }
        else //index above 7 then reuse lower leg model
        {
            sheep = glm::scale(sheep, sheep_scales[8]); 
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, sheep_tex[8]);  
        }

        ourShader->setMat4("model", sheep);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

        /**Helicopter**/
	glm::vec3 table_scales[] = {
		glm::vec3( 0.85f,  0.8f,  1.0f),	//body
		glm::vec3( 3.0f,  0.02f,  0.1f),	//top blade
		glm::vec3( 0.1f,  0.5f,  0.1f),//near left
		glm::vec3( 0.1f,  0.5f,  0.1f),	//near right
		glm::vec3( 0.1f,  0.5f,  0.1f),//far left
		glm::vec3( 0.1f,  0.5f,  0.1f),	//far right
		glm::vec3( 0.11f,  0.05f,  1.5f),	//far left landing
		glm::vec3( 0.11f,  0.05f,  1.5f),	//far right landing
		glm::vec3( 0.05f,  0.1f,  1.5f),	//tail
		glm::vec3( 0.05f,  0.4f,  0.05f),	//top rotor
		glm::vec3( 0.1f,  0.4f,  0.1f),	//fin
		glm::vec3( 0.3f,  0.03f,  0.03f),	//rear rotor
		glm::vec3( 0.009f,  0.4f,  0.05f),	//rear blade
	};
	glm::vec3 table_positions[] = {
		glm::vec3( 0.0f,  0.8f,  0.0f),		//body0
		glm::vec3( 0.0f,  1.45f,  0.0f),		//top blade1
		glm::vec3(-0.3f, 0.3f,  0.2f),	//near left2
		glm::vec3( 0.3f, 0.3f,  0.2f),	//near right3
		glm::vec3(-0.3f, 0.3f, -0.2f),	//far left4
		glm::vec3( 0.3f, 0.3f, -0.2f),	//far right5
		glm::vec3(-0.33f, 0.05f, 0.0f),	//far left landing6
		glm::vec3( 0.33f, 0.05f, 0.0f),	//far right landing7
		glm::vec3( 0.0f,  0.8f,  1.18f),	//tail8
		glm::vec3( 0.0f,  1.32f,  0.0f),		//top rotor9
		glm::vec3( 0.0f,  0.92f,  1.95f),	//fin10
		glm::vec3( 0.0f,  0.82f,  1.9f),	//rear rotor11
		glm::vec3( -0.1f,  0.82f,  1.9f),	//rear blade12
	};

	glBindVertexArray(VAO_box[0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_wood_diffuse);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_wood_specular);

	for(int tab = 0; tab < 13; tab++)
	{
		glm::mat4 heli = glm::mat4();
		heli = glm::translate(heli, glm::vec3(4.0f, 0.0f, 4.0f));
		// heli = glm::translate(heli, glm::vec3(0.0f, 0.5f, 0.0f));
		heli = glm::translate(heli, table_positions[tab]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, heli_tex[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_curtin_specular);

		//note: front of helicopter facing towards -ve z axis
		if(tab == 10)
		{
			//matrix for shearing but there is a function call...
			// glm::mat4 aMat4 = glm::mat4(1.0, 0.0, 0.0, 0.0,  // 1. column
			// 			                  0.0, 1.0, 0.5, 0.0,  // 2. column
			// 			                  0.0, 0.0, 1.0, 0.0,  // 3. column
			// 			                  0.0, 0.0, 0.0, 1.0); // 4. column
			//heli *= aMat4;
			heli = glm::shearZ3D(heli, 0.0f, 0.5f);// shear body by z axis by 0.5
		}
		else if(tab == 0)
		{
			heli = glm::shearZ3D(heli, 0.0f, 0.2f);// shearing by z axis by 0.2 
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, heli_tex[1]);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_curtin_specular);
		}

		if(tab == 12)
		{
			heli = glm::rotate(heli, (float)glfwGetTime() * 20.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if(tab == 1)
		{
			heli = glm::rotate(heli, (float)glfwGetTime() * 20.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		heli = glm::scale(heli, table_scales[tab]);
		ourShader->setMat4("model", heli);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}    
}
