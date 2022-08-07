#include <InfiniteCity.h>
#include <vector>
#include <textures.h>
#include <string>
#include <Camera.h>
#include <iostream>
#include <Shader.h>
#include <random>
#include "Model.h"
#include <constants.hpp>
#include "Controls.h"


using namespace std;

InfiniteCity::InfiniteCity(int width, int length, int sizeBlock, int seed) {
    cityLength = length;
    cityWidth = width;
    blockSize = sizeBlock;
    zSpawnFrontLocation = blockSize * length/3;
    xSpawnFrontLocation = blockSize * width/3;
    zSpawnBackLocation = blockSize * -length/3;
    xSpawnBackLocation = blockSize * -width/3;
    GenerateTextureArray();
    SpawnStartingBlocks();
    citySeed = seed;
    mainCamera = Camera();

    InfinitePathRowFStartNumber = 0;
    InfinitePathRowFEndNumber = 0;

    InfinitePathRowBStartNumber = 0;
    InfinitePathRowBEndNumber = 0;

    InfinitePathColumnFStartNumber = 0;
    InfinitePathColumnFEndNumber = 0;

    InfinitePathColumnBStartNumber = 0;
    InfinitePathColumnBEndNumber = 0;

}

void InfiniteCity::GenerateTextureArray()
{
    string texturesPathPrefix = "assets/textures/";

    GLuint cityBlock1TextureID = loadTexture((texturesPathPrefix + "cityblock1.png").c_str());
    GLuint cityBlock2TextureID = loadTexture((texturesPathPrefix + "cityblock2.png").c_str());
    GLuint cityBlock3TextureID = loadTexture((texturesPathPrefix + "cityblock3.png").c_str());
    GLuint cityBlock4TextureID = loadTexture((texturesPathPrefix + "cityblock4.png").c_str());
    GLuint grassTextureID = loadTexture((texturesPathPrefix + "ground.png").c_str());
    GLuint sTowerBaseTextureID = loadTexture((texturesPathPrefix + "SpaceTowerBase.jpg").c_str());
    testTexture = loadTexture((texturesPathPrefix + "test.jpg").c_str());

    cityBlockTextures[0] = cityBlock1TextureID;
    cityBlockTextures[1] = cityBlock2TextureID;
    cityBlockTextures[2] = cityBlock3TextureID;
    cityBlockTextures[3] = cityBlock4TextureID;
    cityBlockTextures[4] = grassTextureID;
    cityBlockTextures[5] = sTowerBaseTextureID;
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

    InfinitePathRowFStartNumber = 0;
    InfinitePathRowFEndNumber = InfinitePathRowFStartNumber;

    InfinitePathRowBStartNumber = 0;
    InfinitePathRowBEndNumber = InfinitePathRowBStartNumber;

    InfinitePathColumnFStartNumber = 0;
    InfinitePathColumnFEndNumber = InfinitePathColumnFStartNumber;

    InfinitePathColumnBStartNumber = 0;
    InfinitePathColumnBEndNumber = InfinitePathColumnBStartNumber;


	for (int i = -cityWidth/2; i < rows; i++)
	{
		for (int j = -cityLength/2; j < columns; j++)
		{
            
			vec3 newBlockLocation = vec3(i*blockSize, 0.0f, j*blockSize);
            //srand(citySeed * (i * blockSize * j));
            int randomFactor = rand() % 5;
            if(i == 0 && j == 0)
                totalBlocks.push_back(CityBlock(5, blockSize, 3, newBlockLocation, cityBlockTextures[5], citySeed));
            else
            {
                if(j < 0 && i == InfinitePathRowFStartNumber)
                    totalBlocks.push_back(CityBlock(2, blockSize, 3, newBlockLocation, cityBlockTextures[2], citySeed));
                else if (j > 0 && i == InfinitePathRowBStartNumber)
                    totalBlocks.push_back(CityBlock(2, blockSize, 3, newBlockLocation, cityBlockTextures[2], citySeed));
                else if (i < 0 && j == InfinitePathColumnFStartNumber)                            
                    totalBlocks.push_back(CityBlock(2, blockSize, 3, newBlockLocation, cityBlockTextures[2], citySeed));
                else if (i > 0 && j == InfinitePathColumnBStartNumber)                            
                    totalBlocks.push_back(CityBlock(2, blockSize, 3, newBlockLocation, cityBlockTextures[2], citySeed));
                else
                    totalBlocks.push_back(CityBlock(randomFactor, blockSize, 3, newBlockLocation, cityBlockTextures[randomFactor], citySeed));
            }
                
		}
	}
}

void InfiniteCity::SpawnRowBlocks(int rowNumber, int direction, int frontColumns, int backColumns)
{
    if (direction == 1)
    {
        InfinitePathRowFEndNumber = InfinitePathRowFStartNumber + (rand() % (frontColumns + 1));
        InfinitePathRowFStartNumber = (-backColumns) + (1 + rand() % (InfinitePathColumnFStartNumber + 1));
    }
    else
    {
        InfinitePathRowBEndNumber = InfinitePathRowBStartNumber + (rand() % (frontColumns + 1));
        InfinitePathRowBStartNumber = (-backColumns) + (1 + rand() % (InfinitePathColumnBStartNumber + 1));
    }

    for (int i = -backColumns; i < (frontColumns+1); i++)
    {
       vec3 newBlockLocation = vec3(direction*rowNumber*blockSize, 0.0f, i * blockSize);
       //srand(citySeed + (rowNumber * blockSize * i * direction));
       int randomFactor = rand() % 5;
       if (direction == 1)
       {
           if (i >= InfinitePathRowFStartNumber && i <= InfinitePathRowFEndNumber)
               totalBlocks.push_back(CityBlock(2, blockSize, 3 , newBlockLocation, cityBlockTextures[2], citySeed));
           else
               totalBlocks.push_back(CityBlock(randomFactor, blockSize, 3, newBlockLocation, cityBlockTextures[randomFactor], citySeed));
       }
       else
       {
           if (i >= InfinitePathRowBStartNumber && i <= InfinitePathRowBEndNumber)
               totalBlocks.push_back(CityBlock(2, blockSize, 3, newBlockLocation, cityBlockTextures[2], citySeed));
           else
               totalBlocks.push_back(CityBlock(randomFactor, blockSize, 3, newBlockLocation, cityBlockTextures[randomFactor], citySeed));
       } 
    }
}

void InfiniteCity::SpawnColumnBlocks(int columnNumber, int direction, int frontRows, int backRows)
{
    if (direction == 1)
    {
        InfinitePathColumnFEndNumber = InfinitePathColumnFStartNumber + (rand() % (frontRows + 1));
        InfinitePathColumnFStartNumber = (-backRows) + (1 + rand() % (InfinitePathRowFStartNumber + 1));
    }
    else
    {
        InfinitePathColumnBEndNumber = InfinitePathColumnBStartNumber + (rand() % (frontRows + 1));
        InfinitePathColumnBStartNumber = (-backRows) + (1 + rand() % (InfinitePathRowBStartNumber + 1));
    }

    for (int i = -backRows; i < (frontRows+1); i++)
    {
        vec3 newBlockLocation = vec3(i * blockSize, 0.0f, direction * columnNumber * blockSize);
        //srand(citySeed + (columnNumber*blockSize*i*direction));
        int randomFactor = rand() % 5;
        if (direction == 1)
        {
            if (i >= InfinitePathColumnFStartNumber && i <= InfinitePathColumnFEndNumber)
                totalBlocks.push_back(CityBlock(2, blockSize, 3, newBlockLocation, cityBlockTextures[2], citySeed));
            else
                totalBlocks.push_back(CityBlock(randomFactor, blockSize, 3, newBlockLocation, cityBlockTextures[randomFactor], citySeed));
        }
        else
        {
            if (i >= InfinitePathColumnBStartNumber && i <= InfinitePathColumnBEndNumber)
                totalBlocks.push_back(CityBlock(2, blockSize, 3, newBlockLocation, cityBlockTextures[2], citySeed));
            else
                totalBlocks.push_back(CityBlock(randomFactor, blockSize, 3, newBlockLocation, cityBlockTextures[randomFactor], citySeed));
        }
    }
}

void InfiniteCity::DrawCity(GLFWwindow* window, GLuint sceneShaderProgram, GLuint shadowShaderProgram)
{
    const float PI = 3.1415926535f;
    Initialize();
    planeVAO = createUnitPlane();
    int skyboxVAO = createUnitCubeReversed();

    // Setting the number of rows in the city at the beginning of the program
    int currentFrontRows = cityWidth / 2;
    int currentBackRows = cityWidth / 2;
    int currentFrontColumns = cityLength / 2;
    int currentBackColumns = cityLength / 2;

    float oceanHorizontalScale = 1000; // Scale of the ocean, i.e how much the ocean plane scales into the distance from the city

    // Data for the Shadow Map
    GLuint depth_map_texture;
    glGenTextures(1, &depth_map_texture);

    GLuint depth_map_fbo;
    glGenFramebuffers(1, &depth_map_fbo);

    // Creating simple string variables to hold the path strings for the folders that contain the shaders and textures
    string texturesPathPrefix = "assets/textures/";
    string shadersPathPrefix = "assets/shaders/";

    // Creating the skybox shader with which we'll render the skybox
    GLuint skyboxShaderProgram = CreateShader(shadersPathPrefix+"SkyboxVertexShader.glsl", shadersPathPrefix + "SkyboxFragmentShader.glsl");

    // Creating all important textures required for the city
    GLuint groundTextureID = loadTexture((texturesPathPrefix + "ground.png").c_str());
    GLuint oceanTextureID = loadTexture((texturesPathPrefix + "ocean.jpg").c_str());
    GLuint oceanNightTextureID = loadTexture((texturesPathPrefix + "ocean_night.jpg").c_str());

    // Array of texture paths pertaining to the day skybox textures
    vector<std::string> dayFaces {
        texturesPathPrefix + "skybox/right.png",
        texturesPathPrefix + "skybox/left.png",
        texturesPathPrefix + "skybox/top.png",
        texturesPathPrefix + "skybox/bottom.png",
        texturesPathPrefix + "skybox/front.png",
        texturesPathPrefix + "skybox/back.png"
    };

    // Array of texture paths pertaining to the night skybox textures
    vector<std::string> nightFaces {
        texturesPathPrefix + "skybox/Night Skybox Textures/right.png",
        texturesPathPrefix + "skybox/Night Skybox Textures/left.png",
        texturesPathPrefix + "skybox/Night Skybox Textures/top.png",
        texturesPathPrefix + "skybox/Night Skybox Textures/bottom.png",
        texturesPathPrefix + "skybox/Night Skybox Textures/front.png",
        texturesPathPrefix + "skybox/Night Skybox Textures/back.png"
    };

    unsigned int cubemapTexture = loadCubemap(dayFaces);
    unsigned int cubemapTextureNight = loadCubemap(nightFaces);

    // Adding important memory locations for uniform shader variables
    GLuint viewMatrixLocation = glGetUniformLocation(sceneShaderProgram, "viewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(sceneShaderProgram, "projectionMatrix");
    GLuint viewMatrixLocationS = glGetUniformLocation(skyboxShaderProgram, "viewMatrix");
    GLuint projectionMatrixLocationS = glGetUniformLocation(skyboxShaderProgram, "projectionMatrix");
    GLuint worldMatrixLocation1 = glGetUniformLocation(sceneShaderProgram, "worldMatrix");
    GLuint worldMatrixLocation2 = glGetUniformLocation(shadowShaderProgram, "worldMatrix");
    GLuint worldMatrixLocationS = glGetUniformLocation(skyboxShaderProgram, "worldMatrix");
    GLuint actualTextureLocation = glGetUniformLocation(sceneShaderProgram, "actualTexture");

    //Important Light Parameters
    const float ambient = 0.15f;
    const float diffuse = 0.6f;
    const float specular = 0.3f;

    //Useful City Parameters
    float dayNightCycleTime = 100.0f; // Total time in each day of the life of Infinite City
    float currentCityTime = 0; // current time in the Infinite City

    // Disable the cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Other OpenGL states to set once
    // Enable Backface culling
    glEnable(GL_CULL_FACE);

    // Enable Depth Test
    glEnable(GL_DEPTH_TEST);

    // For framerate calculation

    float lastFrameTime = static_cast<float>(glfwGetTime());
    int nbFrames = 0;

	while (!glfwWindowShouldClose(window))
	{   
        float dt = static_cast<float>(glfwGetTime()) - lastFrameTime;
        lastFrameTime += dt;

        float currentTime = static_cast<float>(glfwGetTime());
        nbFrames++;
        if (currentTime - lastFrameTime >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0/double(nbFrames));
            nbFrames = 0;
            lastFrameTime += 1.0;
        }

        currentCityTime = dayNightCycleTime * sinf(currentTime*0.1f); // Update the time in the city

        int WIDTH, HEIGHT;
        glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
        glViewport(0, 0, WIDTH, HEIGHT);

        glBindTexture(GL_TEXTURE_2D, depth_map_texture);
        // Create the texture - We want to make sure the dimensions of the texture match the dimension of the window to prevent any weirdness with the shadows. 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, constant::SCREEN_WIDTH, constant::SCREEN_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
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
        //vec3 lightPosition = vec3(-100.0f * (dayNightCycleTime * sinf((currentTime * 0.1) + PI / 2)),
        //    100.0f*(dayNightCycleTime * sinf(currentTime * 0.1)), 
        //    0.0f); // the location of the light in 3D space, variable
        vec3 lightPosition = vec3(20.0f, 20.0f, 20.0f);
        vec3 lightFocus = vec3(0.0f, 0.0f, 1.0f);      // the point in 3D space the light "looks" at
        vec3 lightDirection = normalize(lightFocus - lightPosition);

        float lightNearPlane = 0.01f;
        float lightFarPlane = 8000.0f;

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

        glClear(GL_DEPTH_BUFFER_BIT);

        
        // The following if-statements handle the spawning of more blocks when the camera moves towards the edges of the city
        if (mainCamera.position.x > xSpawnFrontLocation)
        {
            currentFrontRows++;
            xSpawnFrontLocation += blockSize;
            SpawnRowBlocks(currentFrontRows, 1, currentFrontColumns, currentBackColumns);
        }
        if (mainCamera.position.x < xSpawnBackLocation)
        {
            currentBackRows++;
            xSpawnBackLocation -= blockSize;
            SpawnRowBlocks(currentBackRows, -1, currentFrontColumns, currentBackColumns);

        }
        if (mainCamera.position.z > zSpawnFrontLocation)
        {
            currentFrontColumns++;
            zSpawnFrontLocation += blockSize;
            SpawnColumnBlocks(currentFrontColumns, 1, currentFrontRows, currentBackRows);

        }
        if (mainCamera.position.z < zSpawnBackLocation)
        {
            currentBackColumns++;
            zSpawnBackLocation -= blockSize;
            SpawnColumnBlocks(currentBackColumns, -1, currentFrontRows, currentBackRows);

        }

        for (auto block: totalBlocks)
        {
            // Variables to calculate distance and dot product between the camera and the individual blocks
            vec3 cameraToBlock = block.blockLocation - mainCamera.position;
            float distanceFromCamera = length(vec3(cameraToBlock.x, 0.0f, cameraToBlock.z));

            // Render the the block only if its is within view (dotproduct) or if it is within 50.0f units from the camera
            // However, if the block is within 10.0f units from the camera, it will render no matter what. 
            if (distanceFromCamera < 500.0f)
            {
                glBindVertexArray(planeVAO);
                block.DrawBlock(shadowShaderProgram, worldMatrixLocation2, actualTextureLocation);
            }
        }


        // |---------------------------------------------------------------------------------------------------------------------------|
        //  End of first pass drawing for shadows. At this point, the shadow map is calculated using the light and objects positions.
        //  Now begins the second pass. Now we will actually use this shadow map to render the shadows along with the objects using shaders. 
        // |---------------------------------------------------------------------------------------------------------------------------|



       glUseProgram(sceneShaderProgram);
       int width, height;
       glfwGetFramebufferSize(window, &width, &height);
       glViewport(0, 0, width, height);
       //// Bind screen as output framebuffer
       glBindFramebuffer(GL_FRAMEBUFFER, 0);
       //// Clear color and depth data on framebuffer
       glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(sceneShaderProgram);


        // Setting the values of ambient, diffuse and specular strengths in the activeShader
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "ambientStrength"), ambient);
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "diffuseStrength"), diffuse);
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "specularStrength"), specular);

        glUniform1i(glGetUniformLocation(sceneShaderProgram, "uvMultiplier"), 1);
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "time"), currentTime);
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "shouldScroll"), false);

        // Assigning the respective textures to the shader
        glActiveTexture(GL_TEXTURE0);
        GLuint textureLocation = glGetUniformLocation(sceneShaderProgram, "shadow_map");
        glBindTexture(GL_TEXTURE_2D, depth_map_texture);
        glUniform1i(textureLocation, 0);
        glActiveTexture(GL_TEXTURE0 + 1);
        GLuint textureLocation1 = glGetUniformLocation(sceneShaderProgram, "actualTexture");
        glBindTexture(GL_TEXTURE_2D, testTexture);
        glUniform1i(textureLocation, 1);
        

        // Iterator to iterate through the totalBlocks array (array that contains all block of the city) and draw them one by one. 
        for (auto block : totalBlocks)
        {
            // Variables to calculate distance and dot product between the camera and the individual blocks
            vec3 cameraToBlock = block.blockLocation - mainCamera.position;
            float distanceFromCamera = length(vec3(cameraToBlock.x, 0.0f, cameraToBlock.z));

            // Render the the block only if its is within view (dotproduct) or if it is within 50.0f units from the camera
            // However, if the block is within 10.0f units from the camera, it will render no matter what. 
            if (distanceFromCamera < 500.0f)
            {
                glBindVertexArray(planeVAO);
                
       
                if(block.blockLocation.x == 0 && block.blockLocation.z == 0)
                    glUniform1i(glGetUniformLocation(sceneShaderProgram, "affectedByLighting"), false);
                    
                block.DrawBlock(sceneShaderProgram, worldMatrixLocation1, actualTextureLocation);

                if (block.blockLocation.x == 0 && block.blockLocation.z == 0)
                    glUniform1i(glGetUniformLocation(sceneShaderProgram, "affectedByLighting"), true);
            }
        }

        // Here we start drawing the ocean plane
        glBindVertexArray(planeVAO);

        glUniform1i(glGetUniformLocation(sceneShaderProgram, "uvMultiplier"), 1000); // Repeating the ocean texture on the ocean plane
        glUniform1f(glGetUniformLocation(sceneShaderProgram, "shouldScroll"), true); // Turning on texture scrolling to give the ocean the illusion of movement. 

        // Switch between night and day version of the ocean texture depending on the time (currentCityTime)
        if(currentCityTime <= 0) // Night
            glBindTexture(GL_TEXTURE_2D, oceanNightTextureID);
        else // Day
            glBindTexture(GL_TEXTURE_2D, oceanTextureID);
        glUniform1i(textureLocation1, 1);

        // World matrix to position and scale the ocean plane
        mat4 oceanWorldMatrix = translate(mat4(1.0f), vec3(mainCamera.position.x, -2.0f, mainCamera.position.z))
             * scale(mat4(1.0f), vec3(10000.0f, 1.0f, 10000.0f));
        glUniformMatrix4fv(worldMatrixLocation1, 1, GL_FALSE, &oceanWorldMatrix[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 6); // Draw the plane

        // This resets the view matrix of the shader so the city blocks aren't affected by the view matrix we set above for the ocean plane. 
        mat4 resetMatrix = lookAt(mainCamera.position, mainCamera.position + mainCamera.lookAt, mainCamera.cameraUp);
        glUniformMatrix4fv(worldMatrixLocation1, 1, GL_FALSE, &resetMatrix[0][0]);

        glBindVertexArray(0);

        

    //--Drawing Skybox (Should always be the last thing to be drawn in this render loop)-----------------------//

        glDepthFunc(GL_LEQUAL);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glUseProgram(skyboxShaderProgram);
        glFrontFace(GL_CW);

        mat4 projMat = glm::perspective(mainCamera.fov, constant::SCREEN_WIDTH * 1.0f / constant::SCREEN_HEIGHT, 0.1f, 100.0f);
        mat4 viewMat = mat4(mat3(lookAt(mainCamera.position,
            mainCamera.position + mainCamera.lookAt,
            mainCamera.cameraUp)));
            //* rotate(mat4(1.0f), -0.01f * currentTime, vec3(0.0f, 0.0f, 1.0f));
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

        
        Controls::globalControls(window);
        Controls::firstPersonControls(window, dt);
        mainCamera.updateCamera(viewMatrixLocation, projectionMatrixLocation, window);

        
	}

    totalBlocks.clear(); // Empty the blocks array once the render loop is over and the program is being closed. 


}
