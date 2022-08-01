#include <InfiniteCity.h>
#include <vector>
#include <textures.h>
#include <string>
#include <Camera.h>
#include <iostream>
#include <Shader.h>
#include <random>

using namespace std;

InfiniteCity::InfiniteCity(int width, int length, int sizeBlock, Camera newCam)
{
	cityLength = length;
	cityWidth = width;
	blockSize = sizeBlock;
	zSpawnFrontLocation = length/2;
	xSpawnFrontLocation = width/2;
    zSpawnBackLocation = - length/2;
    xSpawnBackLocation = - width/2;
    GenerateTextureArray();
	SpawnStartingBlocks();
    mainCamera = newCam; 
}

void InfiniteCity::GenerateTextureArray()
{
    std::string texturesPathPrefix = "assets/textures/";

    GLuint cityBlock1TextureID = loadTexture((texturesPathPrefix + "cityblock1.png").c_str());
    GLuint cityBlock2TextureID = loadTexture((texturesPathPrefix + "cityblock2.png").c_str());
    GLuint cityBlock3TextureID = loadTexture((texturesPathPrefix + "cityblock3.png").c_str());
    GLuint cityBlock4TextureID = loadTexture((texturesPathPrefix + "cityblock4.png").c_str());
    GLuint cityBlock5TextureID = loadTexture((texturesPathPrefix + "cityblock5.png").c_str());
    GLuint grassTextureID = loadTexture((texturesPathPrefix + "ground.png").c_str());

    cityBlockTextures[0] = cityBlock1TextureID;
    cityBlockTextures[1] = cityBlock2TextureID;
    cityBlockTextures[2] = cityBlock3TextureID;
    cityBlockTextures[3] = cityBlock4TextureID;
    cityBlockTextures[4] = grassTextureID;
}

void InfiniteCity::SpawnStartingBlocks()
{
    int rows, columns;

    if (cityWidth >= 10)
        rows = cityWidth / 2;
    else
        rows = cityWidth / 2 + 1;

    if (cityLength >= 10)
        columns = cityLength / 2;
    else           
        columns = cityLength / 2 + 1;

	for (int i = -cityWidth/2; i < rows; i++)
	{
		for (int j = -cityLength/2; j < columns; j++)
		{
			vec3 newBlockLocation = vec3(i*blockSize, 0.0f, j*blockSize);
			totalBlocks.push_back(CityBlock(blockSize, 3, newBlockLocation, cityBlockTextures[rand() % 5]));
		}
	}
}

void InfiniteCity::SpawnRowBlocks(int rowNumber, int direction, int frontColumns, int backColumns)
{
    for (int i = -backColumns; i < (frontColumns+1); i++)
    {
       vec3 newBlockLocation = vec3(direction*rowNumber*blockSize, 0.0f, i * blockSize);
       totalBlocks.push_back(CityBlock(blockSize, 3, newBlockLocation, cityBlockTextures[rand() % 5]));
    }
}

void InfiniteCity::SpawnColumnBlocks(int columnNumber, int direction, int frontRows, int backRows)
{
    for (int i = -backRows; i < (frontRows+1); i++)
    {
        vec3 newBlockLocation = vec3(i * blockSize, 0.0f, direction * columnNumber * blockSize);
        totalBlocks.push_back(CityBlock(blockSize, 3, newBlockLocation, cityBlockTextures[rand() % 5]));
    }
}

void InfiniteCity::DrawCity(GLFWwindow* window, GLuint sceneShaderProgram, GLuint shadowShaderProgram)
{
    planeVAO = createUnitPlane();
    int skyboxVAO = createUnitCubeReversed();

    int currentFrontRows = cityWidth / 2;
    int currentBackRows = cityWidth / 2;
    int currentFrontColumns = cityLength / 2;
    int currentBackColumns = cityLength / 2;

    float oceanHorizontalScale = 1000;

    GLuint depth_map_texture;
    glGenTextures(1, &depth_map_texture);

    GLuint depth_map_fbo;
    glGenFramebuffers(1, &depth_map_fbo);

    string texturesPathPrefix = "assets/textures/";
    string shadersPathPrefix = "assets/shaders/";

    GLuint skyboxShaderProgram = CreateShader(shadersPathPrefix+"SkyboxVertexShader.glsl", shadersPathPrefix + "SkyboxFragmentShader.glsl");


    GLuint groundTextureID = loadTexture((texturesPathPrefix + "ground.png").c_str());
    GLuint oceanTextureID = loadTexture((texturesPathPrefix + "ocean.jpg").c_str());
    GLuint oceanNightTextureID = loadTexture((texturesPathPrefix + "ocean_night.jpg").c_str());

    

    vector<std::string> dayFaces
    {
        texturesPathPrefix+"skybox/right.png",
        texturesPathPrefix+"skybox/left.png",
        texturesPathPrefix+"skybox/top.png",
        texturesPathPrefix+"skybox/bottom.png",
        texturesPathPrefix+"skybox/front.png",
        texturesPathPrefix+"skybox/back.png"
    };

    vector<std::string> nightFaces
    {
        texturesPathPrefix + "skybox/Night Skybox Textures/right.png",
        texturesPathPrefix + "skybox/Night Skybox Textures/left.png",
        texturesPathPrefix + "skybox/Night Skybox Textures/top.png",
        texturesPathPrefix + "skybox/Night Skybox Textures/bottom.png",
        texturesPathPrefix + "skybox/Night Skybox Textures/front.png",
        texturesPathPrefix + "skybox/Night Skybox Textures/back.png"
    };

    unsigned int cubemapTexture = loadCubemap(dayFaces);
    unsigned int cubemapTextureNight = loadCubemap(nightFaces);

    GLuint viewMatrixLocation = glGetUniformLocation(sceneShaderProgram, "viewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(sceneShaderProgram, "projectionMatrix");
    GLuint viewMatrixLocationS = glGetUniformLocation(skyboxShaderProgram, "viewMatrix");
    GLuint projectionMatrixLocationS = glGetUniformLocation(skyboxShaderProgram, "projectionMatrix");
    GLuint worldMatrixLocation1 = glGetUniformLocation(sceneShaderProgram, "worldMatrix");
    GLuint worldMatrixLocation2 = glGetUniformLocation(shadowShaderProgram, "worldMatrix");
    GLuint worldMatrixLocationS = glGetUniformLocation(skyboxShaderProgram, "worldMatrix");


    //Important Light Parameters
    const float ambient = 0.15f;
    const float diffuse = 0.6f;
    const float specular = 0.3f;

    //Useful City Parameters
    float dayNightCycleTime = 100.0f;
    float currentCityTime = 0;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // Other OpenGL states to set once
    // Enable Backface culling
    glEnable(GL_CULL_FACE);

    // @TODO 1 - Enable Depth Test
    glEnable(GL_DEPTH_TEST);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

	while (!glfwWindowShouldClose(window))
	{
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0 / double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        currentCityTime = dayNightCycleTime * sinf(currentTime);


        /*int WIDTH, HEIGHT;
        glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
        glViewport(0, 0, WIDTH, HEIGHT);

        glBindTexture(GL_TEXTURE_2D, depth_map_texture);
        // Create the texture - We want to make sure the dimensions of the texture match the dimension of the window to prevent any weirdness with the shadows. 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WIDTH, HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
            NULL);
        // Set texture sampler parameters.
        // Choose closest pixel to the provided texture coordinate
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // Here we are asking to ensure that the texture is properly clamped to the dimensions of the surface instead of tiling when it reaches the end of the texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map_texture, 0);
        glDrawBuffer(GL_NONE); // We're only interested in depth values, not colors. 


        // light parameters
        vec3 lightPosition = vec3(1000.0f, 1000.0f, -1000.0f); // the location of the light in 3D space, variable
        vec3 lightFocus = vec3(-1000.0f, -1000.0f, 1000.0f);      // the point in 3D space the light "looks" at
        vec3 lightDirection = normalize(lightFocus - lightPosition);

        float lightNearPlane = 1.0f;
        float lightFarPlane = 200000.0f;

        //Setting up the light projection matrix
        mat4 lightProjectionMatrix = frustum(-1.0f, 1.0f, -1.0f, 1.0f, lightNearPlane, lightFarPlane);
        mat4 lightViewMatrix = lookAt(lightPosition, lightFocus, vec3(0.0f, 1.0f, 0.0f));
        mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;

        float spotLightAngle = 360.0f;

        glUseProgram(sceneShaderProgram);
        // Set light cutoff angles on scene and textured shaders
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "light_cutoff_outer"), radians(spotLightAngle));


        // Set light color on scene and textured shaders
        glUniform3fv(glGetUniformLocation(sceneShaderProgram, "lightColor"), 1, value_ptr(vec3(1.0f, 1.0f, 1.0f)));


        glUniformMatrix4fv(glGetUniformLocation(sceneShaderProgram, "lightViewProjMatrix"), 1, GL_FALSE, &lightSpaceMatrix[0][0]);

        glUseProgram(shadowShaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shadowShaderProgram, "lightViewProjMatrix"), 1, GL_FALSE, &lightSpaceMatrix[0][0]);

        glUseProgram(sceneShaderProgram);
        // Set light far and near planes on scene and textured shaders
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "lightNearPlane"), lightNearPlane);


        glUniform1f(glGetUniformLocation(sceneShaderProgram, "lightFarPlane"), lightFarPlane);


        // Set light position on scene and textured shaders
        glUniform3fv(glGetUniformLocation(sceneShaderProgram, "lightPosition"), 1, value_ptr(lightPosition));


        // Set light direction on scene and textured shaders
        glUniform3fv(glGetUniformLocation(sceneShaderProgram, "lightDirection"), 1, value_ptr(lightDirection));

        //Initiate the shadow shader to calculate the shadow map for displaying shadows
        glUseProgram(shadowShaderProgram);
        

        // Resize support: Here we are constantly updating WIDTH and HEIGHT to make sure the window can 
        // resize without destroying how things look on screen (for eg, weird stretching of models)
        int dWidth, dHeight;
        glfwGetFramebufferSize(window, &dWidth, &dHeight);
        glViewport(0, 0, dWidth, dHeight);
        WIDTH = dWidth;
        HEIGHT = dHeight;

        glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);

        glClear(GL_DEPTH_BUFFER_BIT);*/

        

        if (mainCamera.newPosition.x > xSpawnFrontLocation)
        {
            currentFrontRows++;
            xSpawnFrontLocation += blockSize;
            SpawnRowBlocks(currentFrontRows, 1, currentFrontColumns, currentBackColumns);
        }

        if (mainCamera.newPosition.x < xSpawnBackLocation)
        {
            currentBackRows++;
            xSpawnBackLocation -= blockSize;
            SpawnRowBlocks(currentBackRows, -1, currentFrontColumns, currentBackColumns);

        }

        if (mainCamera.newPosition.z > zSpawnFrontLocation)
        {
            currentFrontColumns++;
            zSpawnFrontLocation += blockSize;
            SpawnColumnBlocks(currentFrontColumns, 1, currentFrontRows, currentBackRows);

        }

        if (mainCamera.newPosition.z < zSpawnBackLocation)
        {
            currentBackColumns++;
            zSpawnBackLocation -= blockSize;
            SpawnColumnBlocks(currentBackColumns, -1, currentFrontRows, currentBackRows);

        }

        //for (auto block: totalBlocks)
        //{
          //  block.DrawBlock(shadowShaderProgram, worldMatrixLocation2);
           // //std::cout << totalBlocks.size() << std::endl;
       // }


        // |---------------------------------------------------------------------------------------------------------------------------|
        //  End of first pass drawing for shadows. At this point, the shadow map is calculated using the light and objects positions.
        //  Now begins the second pass. Now we will actually use this shadow map to render the shadows along with the objects using shaders. 
        // |---------------------------------------------------------------------------------------------------------------------------|


       glUseProgram(sceneShaderProgram);
       //int width, height;
       //glfwGetFramebufferSize(window, &width, &height);
       //glViewport(0, 0, width, height);
       //// Bind screen as output framebuffer
       //glBindFramebuffer(GL_FRAMEBUFFER, 0);
       //// Clear color and depth data on framebuffer
       glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       glUseProgram(sceneShaderProgram);


        //Setting the values of ambient, diffuse and specular strengths in the activeShader
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "ambientStrength"), ambient);
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "diffuseStrength"), diffuse);
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "specularStrength"), specular);

        glUniform1i(glGetUniformLocation(sceneShaderProgram, "uvMultiplier"), 1);
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "time"), currentTime);
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "shouldScroll"), false);

        glActiveTexture(GL_TEXTURE0);
        GLuint textureLocation = glGetUniformLocation(sceneShaderProgram, "shadow_map");
        glBindTexture(GL_TEXTURE_2D, depth_map_texture);
        glUniform1i(textureLocation, 0);
        GLuint textureLocation1 = glGetUniformLocation(sceneShaderProgram, "actualTexture");

        glBindVertexArray(planeVAO);

        for (auto block : totalBlocks)
        {
            block.DrawBlock(sceneShaderProgram, worldMatrixLocation1);
        }
        
        glUniform1i(glGetUniformLocation(sceneShaderProgram, "uvMultiplier"), 1000);

        glUniform1f(glGetUniformLocation(sceneShaderProgram, "shouldScroll"), true);

        if(currentCityTime < 0)
            glBindTexture(GL_TEXTURE_2D, oceanNightTextureID);
        else
            glBindTexture(GL_TEXTURE_2D, oceanTextureID);
        glUniform1i(textureLocation1, 1);
        mat4 oceanWorldMatrix = translate(mat4(1.0f), vec3(0.0f, -2.0f, 0.0f)) 
            * scale(mat4(1.0f), vec3(10000.0f, 1.0f, 10000.0f));
        glUniformMatrix4fv(worldMatrixLocation1, 1, GL_FALSE, &oceanWorldMatrix[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        mat4 resetMatrix = lookAt(mainCamera.position, mainCamera.position + mainCamera.lookAt, mainCamera.cameraUp);

        glUniformMatrix4fv(worldMatrixLocation1, 1, GL_FALSE, &resetMatrix[0][0]);

        glBindVertexArray(0);

        

    //--Drawing Skybox (Should always be the last thing to be drawn in this render loop)-----------------------//

        glDepthFunc(GL_LEQUAL);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glUseProgram(skyboxShaderProgram);
        glFrontFace(GL_CW);

        mat4 projMat = glm::perspective(glm::radians(mainCamera.fov), 1024 * 1.0f / 768, 0.1f, 100.0f);
        mat4 viewMat = mat4(mat3(lookAt(mainCamera.position, mainCamera.position + mainCamera.lookAt, mainCamera.cameraUp)));
        glUniformMatrix4fv(viewMatrixLocationS, 1, GL_FALSE, &viewMat[0][0]);
        glUniformMatrix4fv(projectionMatrixLocationS, 1, GL_FALSE, &projMat[0][0]);

        glBindVertexArray(skyboxVAO);

        

        glActiveTexture(GL_TEXTURE0);
        GLuint textureLocationS = glGetUniformLocation(skyboxShaderProgram, "skyboxDay");
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glUniform1i(textureLocationS, 0);

        glActiveTexture(GL_TEXTURE0+1);
        textureLocationS = glGetUniformLocation(skyboxShaderProgram, "skyboxNight");
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureNight);
        glUniform1i(textureLocationS, 1);

        glUniform1f(glGetUniformLocation(skyboxShaderProgram, "time"), currentCityTime/dayNightCycleTime);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glFrontFace(GL_CCW);
        glDepthFunc(GL_LESS);
        //glDisable(GL_BLEND);

        // DO NOT DRAW ANYTHING AFTER THE SKYBOX, ONLY DRAW THINGS BEFORE THE SKYBOX

    //--End of Skybox Drawing----------------------------------------------------------------------------------//

        glUseProgram(sceneShaderProgram);



        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();           

        mainCamera.UpdateCamera(viewMatrixLocation, projectionMatrixLocation, window);

        
	}

    totalBlocks.clear();


}
