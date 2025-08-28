#pragma region INCLUDE
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <memory>
#include <vector>

#include "Classes/AnimManager.h"
#include "Classes/FBXModel.h"
#include "Classes/FrameTimer.h"
#include "Classes/Model3DManager.h"
#include "Classes/General/Texture.h"
#include "Util/UtilityFunctions.h"
#include "Enums/UpdateState.h"
//#include <fstream>
#pragma endregion
//--------------------------------------------------------------------
#pragma region LIB
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")
#pragma endregion
//--------------------------------------------------------------------
#pragma region DEFINE
#define WINDOW_TITLE "CG-Assignment (Robot)"
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define aspectRatio WINDOW_WIDTH/WINDOW_HEIGHT
#define fbxToOpenGLPosRatio 1.0 / 6
#define robotHeadFilePath "FBXModels/Head.fbx"
#define robotTorsoFilePath "FBXModels/Torso.fbx"
#define robotLeftArmFilePath "FBXModels/LeftArm.fbx"
#define robotLeftLowerArmFilePath "FBXModels/LeftLowerArm.fbx"
#define robotRightArmFilePath "FBXModels/RightArm.fbx"
#define robotRightLowerArmFilePath "FBXModels/RightLowerArm.fbx"
#define robotLeftLegFilePath "FBXModels/LeftLeg.fbx"
#define robotLeftLowerLegFilePath "FBXModels/LeftLowerLeg.fbx"
#define robotRightLegFilePath "FBXModels/RightLeg.fbx"
#define robotRightLowerLegFilePath "FBXModels/RightLowerLeg.fbx"
#define robotFilePath "FBXModels/Robot.fbx"
#define gunFilePath "FBXModels/gun.fbx"
#define robotBaseTexture1FilePath "Materials/RobotMat/Robot_Base_color.bmp"
#define robotBaseTexture2FilePath "Materials/RobotMat/Robot_Base_color 2.bmp"
#define robotBaseTexture3FilePath "Materials/RobotMat/Robot_Base_color 3.bmp"
#define robotBaseTexture4FilePath "Materials/RobotMat/Robot_Base_color 4.bmp"
#define robotBaseTexture5FilePath "Materials/RobotMat/Robot_Base_color 5.bmp"
#define robotBaseTexture6FilePath "Materials/RobotMat/Robot_Base_color 6.bmp"
#define robotBaseTexture7FilePath "Materials/RobotMat/Robot_Base_color 7.bmp"
#define gunBaseTextureFilePath "Materials/GunMat/M9_BaseColor.bmp"
#define robotDefaultTransform Transform(Position(0,.25,0), Rotation(), Scale())
#define robotHeadDefaultTransform Transform(Position(0,1.70645 * fbxToOpenGLPosRatio ,0.36121 * fbxToOpenGLPosRatio), Rotation(0,0,0), Scale())
#define robotLeftArmDefaultTransform Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(), Scale())
#define robotRightArmDefaultTransform Transform(Position(1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(), Scale())
#define robotLeftLegDefaultTransform Transform(Position(-0.528081 * fbxToOpenGLPosRatio,-1.62491 * fbxToOpenGLPosRatio,0.110221 * fbxToOpenGLPosRatio), Rotation(), Scale())
#define robotRightLegDefaultTransform Transform(Position(0.528081 * fbxToOpenGLPosRatio,-1.62491 * fbxToOpenGLPosRatio,0.110221 * fbxToOpenGLPosRatio), Rotation(), Scale())

#define robotLeftLowerArmDefaultTransform Transform(Position(-0.949841  * fbxToOpenGLPosRatio,-1.25498 * fbxToOpenGLPosRatio,-0.122987 * fbxToOpenGLPosRatio), Rotation(), Scale())
#define robotRightLowerArmDefaultTransform Transform(Position(0.949841  * fbxToOpenGLPosRatio,-1.25498 * fbxToOpenGLPosRatio,-0.122987 * fbxToOpenGLPosRatio), Rotation(), Scale())
#define robotLeftLowerLegDefaultTransform Transform(Position(-0.846325  * fbxToOpenGLPosRatio,-1.81632  * fbxToOpenGLPosRatio,0.198768  * fbxToOpenGLPosRatio), Rotation(), Scale())
#define robotRightLowerLegDefaultTransform Transform(Position(0.846325  * fbxToOpenGLPosRatio,-1.81632  * fbxToOpenGLPosRatio,0.198768  * fbxToOpenGLPosRatio), Rotation(), Scale())

#define gunDefaultTransform Transform(Position(-0.672437 ,-3.11801 ,1.27277 , true), Rotation(-120,0,180), Scale(100))

#pragma endregion
//--------------------------------------------------------------------
#pragma region GLOBALS
//light stuff
bool lightsToggled = false;
bool ambOrDiffuseLight = true; // true for ambient, false for diffuse lighting
GLfloat ambientLightPos[3] = {0,1,0};
GLfloat ambientLightColor[3] = {1,1,1};
GLfloat diffuseLightPos[3] = {1,1,1};
GLfloat diffuseLightColor[3] = {1,1,1};
float lightPosChangeSpeed = .1f;


//3dmodel stuff
Texture robotBaseTexture[7] = {	Texture(robotBaseTexture1FilePath), Texture(robotBaseTexture2FilePath), Texture(robotBaseTexture3FilePath),
								Texture(robotBaseTexture4FilePath), Texture(robotBaseTexture5FilePath), Texture(robotBaseTexture6FilePath),
								Texture(robotBaseTexture7FilePath)};
unsigned int textureSelected = 6;
//	Texture gunBaseTexture = Texture(gunBaseTextureFilePath);

std::shared_ptr<FBXModel> robotModel = Model3DManager::CreateFBXModel(robotTorsoFilePath, robotDefaultTransform);
	std::shared_ptr<FBXModel> robotHeadModel = Model3DManager::CreateChildFBXModel(robotModel, robotHeadFilePath, robotHeadDefaultTransform);
	std::shared_ptr<FBXModel> robotLeftArmModel = Model3DManager::CreateChildFBXModel(robotModel, robotLeftArmFilePath, robotLeftArmDefaultTransform);
		std::shared_ptr<FBXModel> robotLeftLowerArmModel = Model3DManager::CreateChildFBXModel(robotLeftArmModel, robotLeftLowerArmFilePath, robotLeftLowerArmDefaultTransform);
			std::shared_ptr<FBXModel> gunModel = Model3DManager::CreateChildFBXModel(robotLeftLowerArmModel, gunFilePath, gunDefaultTransform);
	std::shared_ptr<FBXModel> robotRightArmModel = Model3DManager::CreateChildFBXModel(robotModel, robotRightArmFilePath, robotRightArmDefaultTransform);
		std::shared_ptr<FBXModel> robotRightLowerArmModel = Model3DManager::CreateChildFBXModel(robotRightArmModel, robotRightLowerArmFilePath, robotRightLowerArmDefaultTransform);
	std::shared_ptr<FBXModel> robotLeftLegModel = Model3DManager::CreateChildFBXModel(robotModel, robotLeftLegFilePath, robotLeftLegDefaultTransform);
		std::shared_ptr<FBXModel> robotLeftLowerLegModel = Model3DManager::CreateChildFBXModel(robotLeftLegModel, robotLeftLowerLegFilePath, robotLeftLowerLegDefaultTransform);
	std::shared_ptr<FBXModel> robotRightLegModel = Model3DManager::CreateChildFBXModel(robotModel, robotRightLegFilePath, robotRightLegDefaultTransform);
		std::shared_ptr<FBXModel> robotRightLowerLegModel = Model3DManager::CreateChildFBXModel(robotRightLegModel, robotRightLowerLegFilePath, robotRightLowerLegDefaultTransform);



// Camera
double camX = 0, camY = 0, camZ = 2;
double camTargetX = 0.0, camTargetY = 0.0, camTargetZ = 0.0;	 // Look-at target
double camUpX = 0.0, camUpY = 1.0, camUpZ = 0.0;	 // Rotate Camera(always keep camUpY = 1.0f)
double projectionNear = 0.1, projectionFar = 5, projectionLeft = -1, projectionRight = 1, projectionTop = 1, projectionBottom = -1;
float cameraUpdateSpeed = 0.05f;
float maxZoomInRange = camZ - 1.25;
float maxZoomOutRange = projectionFar - 0.5f;
bool isOrtho = true;
double cameraRadius = camZ;
double cameraAzimuth = 90.0;	//	horizontal orbit rotation angle
float cameraOrbitSpeed = 5.0f;

//	Frame Timer
FrameTimer* frameTimer = new FrameTimer();

//	Animations
std::shared_ptr<Animation> awakeAnim = AnimManager::CreateAnimation();
std::shared_ptr<Animation> walkAnim = AnimManager::CreateAnimation();
std::shared_ptr<Animation> shootAnim = AnimManager::CreateAnimation();

//testing variables
double testRotationSpeed = 2;
UpdateState updatePosState = UPDATE_CAMERA_POS;
unsigned long long polygonCount = 0;
unsigned long long triangleCount = 0;
unsigned long long quadCount = 0;
unsigned long long otherCount = 0;
std::shared_ptr<FBXModel> modelToUpdateTransform;
Color backgroundColor = Color(.6,.6,.6);	// gray background color

#pragma endregion
//--------------------------------------------------------------------

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case 'L':	//toggle lighting
				lightsToggled = !lightsToggled;
				break;
			case 'K':	//switch between ambient and diffuse lighting
				ambOrDiffuseLight = !ambOrDiffuseLight;
				break;
			case VK_OEM_PLUS:
				switch(updatePosState)
				{
					case UPDATE_CAMERA_POS:
						if(camZ > maxZoomInRange || cameraRadius > maxZoomInRange)
						{
							camZ -= cameraUpdateSpeed; // Move Camera forward
							cameraRadius -= cameraUpdateSpeed;	//	Cam orbit radius
						}
						break;
					case UPDATE_LIGHT_POS:
						diffuseLightPos[2] += lightPosChangeSpeed;
						break;
					case UPDATE_TRANSFORM_HEAD:
					case UPDATE_TRANSFORM_TORSO:
					case UPDATE_TRANSFORM_LEFTARM:
					case UPDATE_TRANSFORM_LEFTLOWERARM:
					case UPDATE_TRANSFORM_RIGHTARM:
					case UPDATE_TRANSFORM_RIGHTLOWERARM:
					case UPDATE_TRANSFORM_LEFTLEG:
					case UPDATE_TRANSFORM_LEFTLOWERLEG:
					case UPDATE_TRANSFORM_RIGHTLEG:
					case UPDATE_TRANSFORM_RIGHTLOWERLEG:
						modelToUpdateTransform->transform.position.z += .01;
						break;
				}
				break;
			case VK_OEM_MINUS:
				switch(updatePosState)
				{
					case UPDATE_CAMERA_POS:
						if(camZ < maxZoomOutRange || cameraRadius < maxZoomOutRange)
							{
								camZ += cameraUpdateSpeed; // Move Camera backward
								cameraRadius += cameraUpdateSpeed;	//	Cam orbit radius
							}
						break;
					case UPDATE_LIGHT_POS:
						diffuseLightPos[2] -= lightPosChangeSpeed;
						break;
					case UPDATE_TRANSFORM_HEAD:
					case UPDATE_TRANSFORM_TORSO:
					case UPDATE_TRANSFORM_LEFTARM:
					case UPDATE_TRANSFORM_LEFTLOWERARM:
					case UPDATE_TRANSFORM_RIGHTARM:
					case UPDATE_TRANSFORM_RIGHTLOWERARM:
					case UPDATE_TRANSFORM_LEFTLEG:
					case UPDATE_TRANSFORM_LEFTLOWERLEG:
					case UPDATE_TRANSFORM_RIGHTLEG:
					case UPDATE_TRANSFORM_RIGHTLOWERLEG:
						modelToUpdateTransform->transform.position.z -= .01;
							break;
				}
				break;
			case VK_LEFT:
				switch(updatePosState)
				{
					case UPDATE_CAMERA_POS:
						camX -= cameraUpdateSpeed; // Move Camera left
						camTargetX -= cameraUpdateSpeed;
						break;
					case UPDATE_LIGHT_POS:
						diffuseLightPos[0] -= lightPosChangeSpeed;
						break;
					case UPDATE_TRANSFORM_HEAD:
					case UPDATE_TRANSFORM_TORSO:
					case UPDATE_TRANSFORM_LEFTARM:
					case UPDATE_TRANSFORM_LEFTLOWERARM:
					case UPDATE_TRANSFORM_RIGHTARM:
					case UPDATE_TRANSFORM_RIGHTLOWERARM:
					case UPDATE_TRANSFORM_LEFTLEG:
					case UPDATE_TRANSFORM_LEFTLOWERLEG:
					case UPDATE_TRANSFORM_RIGHTLEG:
					case UPDATE_TRANSFORM_RIGHTLOWERLEG:
						modelToUpdateTransform->transform.rotation.x += 2;
						modelToUpdateTransform->transform.rotation.y += 2;
						modelToUpdateTransform->transform.rotation.z += 2;
						if (modelToUpdateTransform->transform.rotation.x >= 360)
							modelToUpdateTransform->transform.rotation.x -= 360;
						if (modelToUpdateTransform->transform.rotation.y >= 360)
							modelToUpdateTransform->transform.rotation.y -= 360;
						if (modelToUpdateTransform->transform.rotation.z >= 360)
							modelToUpdateTransform->transform.rotation.z -= 360;
						break;
				}
				break;
			case VK_RIGHT:
				switch(updatePosState)
				{
					case UPDATE_CAMERA_POS:
						camX += cameraUpdateSpeed; // Move Camera right
						camTargetX += cameraUpdateSpeed;
						break;
					case UPDATE_LIGHT_POS:
						diffuseLightPos[0] += lightPosChangeSpeed;
						break;
					case UPDATE_TRANSFORM_HEAD:
					case UPDATE_TRANSFORM_TORSO:
					case UPDATE_TRANSFORM_LEFTARM:
					case UPDATE_TRANSFORM_LEFTLOWERARM:
					case UPDATE_TRANSFORM_RIGHTARM:
					case UPDATE_TRANSFORM_RIGHTLOWERARM:
					case UPDATE_TRANSFORM_LEFTLEG:
					case UPDATE_TRANSFORM_LEFTLOWERLEG:
					case UPDATE_TRANSFORM_RIGHTLEG:
					case UPDATE_TRANSFORM_RIGHTLOWERLEG:
						modelToUpdateTransform->transform.rotation.x -= 2;
						modelToUpdateTransform->transform.rotation.y -= 2;
						modelToUpdateTransform->transform.rotation.z -= 2;
						if (modelToUpdateTransform->transform.rotation.x < 0)
							modelToUpdateTransform->transform.rotation.x += 360;
						if (modelToUpdateTransform->transform.rotation.y < 0)
							modelToUpdateTransform->transform.rotation.y += 360;
						if (modelToUpdateTransform->transform.rotation.z < 0)
							modelToUpdateTransform->transform.rotation.z += 360;
						break;
				}
				break;
			case VK_UP:
				switch(updatePosState)
				{
					case UPDATE_CAMERA_POS:
						camY += cameraUpdateSpeed; // Move Camera up
						camTargetY += cameraUpdateSpeed;
						break;
					case UPDATE_LIGHT_POS:
						diffuseLightPos[1] += lightPosChangeSpeed;
						break;
					case UPDATE_TRANSFORM_HEAD:
					case UPDATE_TRANSFORM_TORSO:
					case UPDATE_TRANSFORM_LEFTARM:
					case UPDATE_TRANSFORM_LEFTLOWERARM:
					case UPDATE_TRANSFORM_RIGHTARM:
					case UPDATE_TRANSFORM_RIGHTLOWERARM:
					case UPDATE_TRANSFORM_LEFTLEG:
					case UPDATE_TRANSFORM_LEFTLOWERLEG:
					case UPDATE_TRANSFORM_RIGHTLEG:
					case UPDATE_TRANSFORM_RIGHTLOWERLEG:
						modelToUpdateTransform->transform.scale.x += .01;
							modelToUpdateTransform->transform.scale.y += .01;
							modelToUpdateTransform->transform.scale.z += .01;
						break;
				}
				break;
			case VK_DOWN:
				switch(updatePosState)
				{
					case UPDATE_CAMERA_POS:
						camY -= cameraUpdateSpeed; // Move Camera down
						camTargetY -= cameraUpdateSpeed;
						break;
					case UPDATE_LIGHT_POS:
						diffuseLightPos[1] -= lightPosChangeSpeed;
						break;
					case UPDATE_TRANSFORM_HEAD:
					case UPDATE_TRANSFORM_TORSO:
					case UPDATE_TRANSFORM_LEFTARM:
					case UPDATE_TRANSFORM_LEFTLOWERARM:
					case UPDATE_TRANSFORM_RIGHTARM:
					case UPDATE_TRANSFORM_RIGHTLOWERARM:
					case UPDATE_TRANSFORM_LEFTLEG:
					case UPDATE_TRANSFORM_LEFTLOWERLEG:
					case UPDATE_TRANSFORM_RIGHTLEG:
					case UPDATE_TRANSFORM_RIGHTLOWERLEG:
						modelToUpdateTransform->transform.scale.x -= .01;
							modelToUpdateTransform->transform.scale.y -= .01;
							modelToUpdateTransform->transform.scale.z -= .01;
							break;
				}
				break;
				//	PROJECTION
			case 'O':
				isOrtho = true;
				break;
			case 'P':
				isOrtho = false;
				break;
				//	ORBIT
			case 'A':
				cameraAzimuth -= cameraOrbitSpeed;	//	orbit left
				break;
			case 'D':
				cameraAzimuth += cameraOrbitSpeed;	//	orbit right
				break;
				//	UPDATE STATES
			case 'Z':
				updatePosState = UPDATE_CAMERA_POS;
				break;
			case 'X':
				updatePosState = UPDATE_LIGHT_POS;
				break;
			case 'C':
				updatePosState = UPDATE_TRANSFORM_HEAD;
				modelToUpdateTransform = robotHeadModel;
				break;
			case 'V':
				updatePosState = UPDATE_TRANSFORM_TORSO;
				modelToUpdateTransform = robotModel;
				break;
			case 'B':
				updatePosState = UPDATE_TRANSFORM_LEFTARM;
				modelToUpdateTransform = robotLeftArmModel;
				break;
			case 'N':
				updatePosState = UPDATE_TRANSFORM_LEFTLOWERARM;
				modelToUpdateTransform = robotLeftLowerArmModel;
				break;
			case 'M':
				updatePosState = UPDATE_TRANSFORM_RIGHTARM;
				modelToUpdateTransform = robotRightArmModel;
				break;
			case 'J':
				updatePosState = UPDATE_TRANSFORM_RIGHTLOWERARM;
				modelToUpdateTransform = robotRightLowerArmModel;
				break;
			case 'H':
				updatePosState = UPDATE_TRANSFORM_LEFTLEG;
				modelToUpdateTransform = robotLeftLegModel;
				break;
			case 'G':
				updatePosState = UPDATE_TRANSFORM_LEFTLOWERLEG;
				modelToUpdateTransform = robotLeftLowerLegModel;
				break;
			case 'F':
				updatePosState = UPDATE_TRANSFORM_RIGHTLEG;
				modelToUpdateTransform = robotRightLegModel;
				break;
			case 'R':
				updatePosState = UPDATE_TRANSFORM_RIGHTLOWERLEG;
				modelToUpdateTransform = robotRightLowerLegModel;
				break;
			//	Texture Switching
			case 0x31:	//'1' key
				textureSelected = 0;
				break;
			case 0x32:	//'2' key
				textureSelected = 1;
				break;
			case 0x33:	//'3' key
				textureSelected = 2;
				break;
			case 0x34:	//'4' key
				textureSelected = 3;
				break;
			case 0x35:	//'5' key
				textureSelected = 4;
				break;
			case 0x36:	//'6' key
				textureSelected = 5;
				break;
			case 0x37:	//'7' key
				textureSelected = 6;
				break;
			//	ANIMATION CONTROLS
			case VK_SPACE:
				AnimManager::TogglePause(AnimManager::currentAnim,!awakeAnim->isPaused);	//	toggle pause or resume for anim1
				break;
			case 0x38:	//'8' key:
				AnimManager::ToggleAnimation(0,true);	//Awake Animation
				gunModel->isActive = false;
				break;
			case 0x39:	//'9' key:
				AnimManager::ToggleAnimation(1,true);	//Walking Animation
				gunModel->isActive = false;
				break;
			case 0x30:	//'0' key:
				AnimManager::ToggleAnimation(2,true);	//Shooting Animation
				gunModel->isActive = true;
				break;
			case VK_RETURN :	// Enter key to reset all transforms
				AnimManager::ToggleOffAllAnimations();	//	turn off all anims
				robotModel->transform = robotDefaultTransform ; 
				robotHeadModel->transform = robotHeadDefaultTransform ;
				robotLeftArmModel->transform = robotLeftArmDefaultTransform ;
				robotRightArmModel->transform = robotRightArmDefaultTransform ;
				robotLeftLegModel->transform = robotLeftLegDefaultTransform ;
				robotRightLegModel->transform = robotRightLegDefaultTransform ;
				robotLeftLowerArmModel->transform = robotLeftLowerArmDefaultTransform ;
				robotRightLowerArmModel->transform = robotRightLowerArmDefaultTransform;
				robotLeftLowerLegModel->transform = robotLeftLowerLegDefaultTransform ;
				robotRightLowerLegModel->transform = robotRightLowerLegDefaultTransform ;
				break;
				
			}

				
		
			
			break;
		}
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void ConfigureSceneLighting()
{
	if (lightsToggled)
	{
		glEnable(GL_LIGHTING);

		if(ambOrDiffuseLight)
		{
			//(Ambient light)
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightColor);
			glLightfv(GL_LIGHT0, GL_POSITION, ambientLightPos);
			glEnable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
		}else
		{
			// (Diffuse light)
			glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightColor);
			glLightfv(GL_LIGHT1, GL_POSITION, diffuseLightPos);
			glEnable(GL_LIGHT1);
			glDisable(GL_LIGHT0);
		}
		
	}
	else 
	{
		glDisable(GL_LIGHTING);
	}

	
}
//--------------------------------------------------------------------

void ConfigureCamera(bool is_ortho)
{
	// Set up the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(is_ortho)
	{
		glOrtho(projectionLeft,projectionRight,projectionBottom,projectionTop,projectionNear,projectionFar);
	}
	else
	{
		glFrustum(projectionLeft/10,projectionRight/10,projectionBottom/10,projectionTop/10,projectionNear,projectionFar);
		//gluPerspective(fovY, aspectRatio, 0.1, 100.0);
	}


	// Set up the view (camera) matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	double camXTemp = camX, camYTemp = camY,camZTemp = camZ;
	double* cameraXptr = &camXTemp;
	double* cameraYptr = &camYTemp;
	double* cameraZptr = &camZTemp;
	UtilityFunctions::UpdateCameraOrbitPosition(cameraAzimuth,camTargetX,camTargetY,camTargetZ,cameraRadius,cameraXptr,cameraYptr,cameraZptr);
	camX = *cameraXptr;
	camY = *cameraYptr;
	camZ = *cameraZptr;
	
	gluLookAt(camX, camY, camZ,  // Camera position
			  camTargetX, camTargetY, camTargetZ,  // Look-at position
			  camUpX, camUpY, camUpZ); // Up vector
}
//--------------------------------------------------------------------

void display()
{
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	ConfigureCamera(isOrtho);
	ConfigureSceneLighting();

	robotBaseTexture[textureSelected].ConfigureTexture();
	//	DEMO_ROTATION
	// robotModel->transform.rotation.y += testRotationSpeed;
	// if(robotModel->transform.rotation.y >= 360.0)
	// 	robotModel->transform.rotation.y -= 360.0;
	Model3DManager::DrawFBXModelWithTransform(robotModel);
	
	robotBaseTexture[textureSelected].ClearTexture();
	
	glEnd();
}
//--------------------------------------------------------------------

void Init()
{
	//count all polygons
	for(auto& model : Model3DManager::sceneModels)
	{
		polygonCount += model->polygons.size();

		for(auto& polygon : model->polygons)
		{
			if(polygon.vertices.size() == 3)
				triangleCount += 1;
			else if(polygon.vertices.size() == 4)
				quadCount += 1;
			else
				otherCount += 1;
		}
	}
	
	frameTimer->Init(60);

	// AWAKE_ANIM
	{
		awakeAnim->isLooped = false;
		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key1Transforms;
		key1Transforms[robotLeftArmModel] = Transform(Position(-1.21773, 0.698849, 0 , true), Rotation(0,13.3065,0), Scale());
		key1Transforms[robotLeftLowerArmModel] = Transform(Position(-.949841, -1.25498 ,-.122987 , true), Rotation(-75.723,-2.95504,-8.45875), Scale());
		
		key1Transforms[robotRightArmModel] = Transform(Position(1.21773, 0.698849, 0, true), Rotation(0,-13.3065,0), Scale());
		key1Transforms[robotRightLowerArmModel] = Transform(Position(.949841, -1.25498 ,-.122987 , true), Rotation(-75.723,2.95504,8.45875), Scale());
		
		key1Transforms[robotLeftLegModel] = Transform(Position(-0.528081 , -1.62491  ,0.110221 , true), Rotation(-137.312,0,0), Scale());
		key1Transforms[robotLeftLowerLegModel] = Transform(Position(-.846325 , -1.81632  ,.198768 , true), Rotation(139.284,0,0), Scale());
		
		key1Transforms[robotRightLegModel] = Transform(Position(0.528081 , -1.62491  ,0.110221 , true), Rotation(-137.312,0,0), Scale());
		key1Transforms[robotRightLowerLegModel] = Transform(Position(.846325 , -1.81632  ,.198768 , true ), Rotation(139.284,0,0), Scale());
		
		key1Transforms[robotHeadModel] = Transform(Position(0 , 1.70645  ,0.36121 , true), Rotation(24.8144,0,0), Scale());
		AnimManager::CreateKeyframe(awakeAnim, key1Transforms, 0.0f);	// create a keyframe for anim1

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key2Transforms;
		key2Transforms[robotLeftArmModel] = Transform(Position(-1.21773, 0.698849, 0 , true), Rotation(0,12.08,0), Scale());
		key2Transforms[robotLeftLowerArmModel] = Transform(Position(-.949841, -1.25498 ,-.122987 , true), Rotation(-71.1282,-2.77573,-7.94548), Scale());
		
		key2Transforms[robotRightArmModel] = Transform(Position(1.21773, 0.698849, 0, true), Rotation(0,-12.08,0), Scale());
		key2Transforms[robotRightLowerArmModel] = Transform(Position(.949841, -1.25498 ,-.122987 , true), Rotation(-71.1282,2.77573,7.94548), Scale());
		
		key2Transforms[robotLeftLegModel] = Transform(Position(-0.528081 , -1.62491  ,0.110221 , true), Rotation(-128.971,0,0), Scale());
		key2Transforms[robotLeftLowerLegModel] = Transform(Position(-.846325 , -1.81632  ,.198768 , true), Rotation(126.43,0,0), Scale());
		
		key2Transforms[robotRightLegModel] = Transform(Position(0.528081 , -1.62491  ,0.110221 , true), Rotation(-128.971,0,0), Scale());
		key2Transforms[robotRightLowerLegModel] = Transform(Position(.846325 , -1.81632  ,.198768 , true ), Rotation(126.43,0,0), Scale());
		
		AnimManager::CreateKeyframe(awakeAnim, key2Transforms, 30.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key3Transforms;
		key3Transforms[robotLeftArmModel] = Transform(Position(-1.21773, 0.698849, 0 , true), Rotation(0,6.65405,0), Scale());
		key3Transforms[robotLeftLowerArmModel] = Transform(Position(-.949841, -1.25498 ,-.122987 , true), Rotation(-49.0722,-1.91501,-5.48168), Scale());
		
		key3Transforms[robotRightArmModel] = Transform(Position(1.21773, 0.698849, 0, true), Rotation(0,-6.65405,0), Scale());
		key3Transforms[robotRightLowerArmModel] = Transform(Position(.949841, -1.25498 ,-.122987 , true), Rotation(-49.0722,1.91501,5.48168), Scale());
		
		key3Transforms[robotLeftLegModel] = Transform(Position(-0.528081 , -1.62491  ,0.110221 , true), Rotation(-88.9785,0,0), Scale());
		key3Transforms[robotLeftLowerLegModel] = Transform(Position(-.846325 , -1.81632  ,.198768 , true), Rotation(69.642,0,0), Scale());
		
		key3Transforms[robotRightLegModel] = Transform(Position(0.528081 , -1.62491  ,0.110221 , true), Rotation(-88.9785,0,0), Scale());
		key3Transforms[robotRightLowerLegModel] = Transform(Position(.846325 , -1.81632  ,.198768 , true ), Rotation(69.642,0,0), Scale());

		key3Transforms[robotHeadModel] = Transform(Position(0 , 1.70645  ,0.36121 , true), Rotation(-0.620001,0,0), Scale());
		AnimManager::CreateKeyframe(awakeAnim, key3Transforms, 80.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key4Transforms;
		key4Transforms[robotLeftArmModel] = Transform(Position(-1.21773, 0.698849, 0 , true), Rotation(0,2.07939,0), Scale());
		key4Transforms[robotLeftLowerArmModel] = Transform(Position(-.949841, -1.25498 ,-.122987 , true), Rotation(-26.6565,-1.04025,-2.9777), Scale());
		
		key4Transforms[robotRightArmModel] = Transform(Position(1.21773, 0.698849, 0, true), Rotation(0,-2.07939,0), Scale());
		key4Transforms[robotRightLowerArmModel] = Transform(Position(.949841, -1.25498 ,-.122987 , true), Rotation(-26.6565,1.04025,2.9777), Scale());
		
		key4Transforms[robotLeftLegModel] = Transform(Position(-0.528081 , -1.62491  ,0.110221 , true), Rotation(-48.334,0,0), Scale());
		key4Transforms[robotLeftLowerLegModel] = Transform(Position(-.846325 , -1.81632  ,.198768 , true), Rotation(21.7631,0,0), Scale());
		
		key4Transforms[robotRightLegModel] = Transform(Position(0.528081 , -1.62491  ,0.110221 , true), Rotation(-48.334,0,0), Scale());
		key4Transforms[robotRightLowerLegModel] = Transform(Position(.846325 , -1.81632  ,.198768 , true ), Rotation(21.7631,-21.105,0), Scale());

		key4Transforms[robotHeadModel] = Transform(Position(0 , 1.70645  ,0.36121 , true), Rotation(10,-21.105,0), Scale());
		AnimManager::CreateKeyframe(awakeAnim, key4Transforms, 120.0f/60.0f);	
		
		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key5Transforms;
		key5Transforms[robotLeftArmModel] = robotLeftArmDefaultTransform;
		key5Transforms[robotRightArmModel] = robotRightArmDefaultTransform;
		
		key5Transforms[robotLeftLowerLegModel] = robotLeftLowerLegDefaultTransform;
		key5Transforms[robotRightLowerLegModel] = robotRightLowerLegDefaultTransform;

		key5Transforms[robotLeftLegModel] = Transform(Position(-0.528081 , -1.62491  ,0.110221 , true), Rotation(-14.2805,0,0), Scale());
		key5Transforms[robotRightLegModel] = Transform(Position(0.528081 , -1.62491  ,0.110221 , true), Rotation(-14.2805,0,0), Scale());
		
		key5Transforms[robotLeftLowerLegModel] = Transform(Position(-.846325 , -1.81632  ,.198768 , true), Rotation(-7.87578,-0.307347,-0.879777), Scale());
		key5Transforms[robotRightLowerArmModel] = Transform(Position(.949841, -1.25498 ,-.122987 , true), Rotation(-7.87578,0.307347,0.879777), Scale());

		key5Transforms[robotHeadModel] = Transform(Position(0 , 1.70645  ,0.36121 , true), Rotation(-2.85909,13.9083,4.46796), Scale());
		AnimManager::CreateKeyframe(awakeAnim, key5Transforms, 160.0f/60.0f);
		
		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key6Transforms;
		key6Transforms[robotLeftLowerArmModel] = robotLeftLowerArmDefaultTransform;
		key6Transforms[robotRightLowerArmModel] = robotRightLowerArmDefaultTransform;
		
		key6Transforms[robotLeftLegModel] = robotLeftLegDefaultTransform;
		key6Transforms[robotRightLegModel] = robotRightLegDefaultTransform;
		key6Transforms[robotHeadModel] = Transform(Position(0 , 1.70645  ,0.36121 , true), Rotation(-15.7182,48.9215,8.93591), Scale());
		AnimManager::CreateKeyframe(awakeAnim, key6Transforms, 200.0f/60.0f);
		
		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key7Transforms;
		key7Transforms[robotHeadModel] = robotHeadDefaultTransform;
		AnimManager::CreateKeyframe(awakeAnim, key7Transforms, 210.0f/60.0f);
		
		
	
		//	animIndex = 0 for the first anim you initialized up in the GLOBAL_VARIABLES
		AnimManager::ToggleAnimation(0, true);	//	turn on animation
	}

	// WALK_ANIM
	{
		walkAnim->isLooped = true;
		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key1Transforms;
		key1Transforms[robotHeadModel] = Transform(Position(0,1.70645, 0.36121, true), Rotation(-6.06039/2, 20.7792/2, -8.3935/2), Scale());

		key1Transforms[robotLeftArmModel] = Transform(Position(-1.21773,0.698849, 0, true), Rotation(-22.5591, 0, 0), Scale());
		key1Transforms[robotRightArmModel] = Transform(Position(1.21773,0.698849, 0, true), Rotation(22.5646, 0, 0), Scale());

		key1Transforms[robotLeftLowerArmModel] = Transform(Position(-.949841,-1.25498, -.122987, true), Rotation(-14.6759, 0, 0), Scale());
		key1Transforms[robotRightLowerArmModel] = Transform(Position(.949841,-1.25498, -.122987, true), Rotation(40.437, 0, 0), Scale());
		
		key1Transforms[robotLeftLegModel] = Transform(Position(-0.528081,-1.62491, 0.110221, true), Rotation(-31.6861, 0, 0), Scale());
		key1Transforms[robotRightLegModel] = Transform(Position(0.528081,-1.62491, 0.110221, true), Rotation(16.1255, 0, 0), Scale());

		key1Transforms[robotLeftLowerLegModel] = Transform(Position(-.846325,-1.81632, .198768, true), Rotation(10.7211, 0, 0), Scale());
		key1Transforms[robotRightLowerLegModel] = Transform(Position(.846325,-1.81632, .198768, true), Rotation(27.7343, 0, 0), Scale());
		AnimManager::CreateKeyframe(walkAnim, key1Transforms, 0.0f);	// create a keyframe for anim1

		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key2Transforms;
		key2Transforms[robotHeadModel] = Transform(Position(0,1.70645, 0.36121, true), Rotation(-0.620001/2, -30.1226/2, 0), Scale());

		key2Transforms[robotRightArmModel] = Transform(Position(1.21773,0.698849, 0, true), Rotation(-22.5591, 0, 0), Scale());
		key2Transforms[robotLeftArmModel] = Transform(Position(-1.21773,0.698849, 0, true), Rotation(22.5646, 0, 0), Scale());

		key2Transforms[robotRightLowerArmModel] = Transform(Position(.949841,-1.25498, -.122987, true), Rotation(-14.6759, 0, 0), Scale());
		key2Transforms[robotLeftLowerArmModel] = Transform(Position(-.949841,-1.25498, -.122987, true), Rotation(40.437, 0, 0), Scale());
		
		key2Transforms[robotRightLegModel] = Transform(Position(0.528081,-1.62491, 0.110221, true), Rotation(-31.6861, 0, 0), Scale());
		key2Transforms[robotLeftLegModel] = Transform(Position(-0.528081,-1.62491, 0.110221, true), Rotation(16.1255, 0, 0), Scale());

		key2Transforms[robotRightLowerLegModel] = Transform(Position(.846325,-1.81632, .198768, true), Rotation(10.7211, 0, 0), Scale());
		key2Transforms[robotLeftLowerLegModel] = Transform(Position(-.846325,-1.81632, .198768, true), Rotation(27.7343, 0, 0), Scale());
		AnimManager::CreateKeyframe(walkAnim, key2Transforms, 0.5f);

		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key3Transforms;
		key3Transforms[robotHeadModel] = Transform(Position(0,1.70645, 0.36121, true), Rotation(-6.06039/2, 20.7792/2, -8.3935/2), Scale());

		key3Transforms[robotLeftArmModel] = Transform(Position(-1.21773,0.698849, 0, true), Rotation(-22.5591, 0, 0), Scale());
		key3Transforms[robotRightArmModel] = Transform(Position(1.21773,0.698849, 0, true), Rotation(22.5646, 0, 0), Scale());

		key3Transforms[robotLeftLowerArmModel] = Transform(Position(-.949841,-1.25498, -.122987, true), Rotation(-14.6759, 0, 0), Scale());
		key3Transforms[robotRightLowerArmModel] = Transform(Position(.949841,-1.25498, -.122987, true), Rotation(40.437, 0, 0), Scale());
		
		key3Transforms[robotLeftLegModel] = Transform(Position(-0.528081,-1.62491, 0.110221, true), Rotation(-31.6861, 0, 0), Scale());
		key3Transforms[robotRightLegModel] = Transform(Position(0.528081,-1.62491, 0.110221, true), Rotation(16.1255, 0, 0), Scale());

		key3Transforms[robotLeftLowerLegModel] = Transform(Position(-.846325,-1.81632, .198768, true), Rotation(10.7211, 0, 0), Scale());
		key3Transforms[robotRightLowerLegModel] = Transform(Position(.846325,-1.81632, .198768, true), Rotation(27.7343, 0, 0), Scale());
		AnimManager::CreateKeyframe(walkAnim, key3Transforms, 1.0f);	

		
		AnimManager::ToggleAnimation(1, false);	//	make sure to turn off animation
	}

	// SHOOT_ANIM
	{
		shootAnim->isLooped = true;
		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key1Transforms;
		key1Transforms[robotHeadModel] = robotHeadDefaultTransform;

		key1Transforms[robotLeftArmModel] = robotLeftArmDefaultTransform;
		key1Transforms[robotRightArmModel] = robotRightArmDefaultTransform;

		key1Transforms[robotLeftLowerArmModel] = robotLeftLowerArmDefaultTransform;
		key1Transforms[robotRightLowerArmModel] = robotRightLowerArmDefaultTransform;
		
		key1Transforms[robotLeftLegModel] = robotLeftLegDefaultTransform;
		key1Transforms[robotRightLegModel] = robotRightLegDefaultTransform;

		key1Transforms[robotLeftLowerLegModel] = robotLeftLowerLegDefaultTransform;
		key1Transforms[robotRightLowerLegModel] = robotRightLowerLegDefaultTransform;
		key1Transforms[gunModel] = gunDefaultTransform;
		AnimManager::CreateKeyframe(shootAnim, key1Transforms, 0.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key2Transforms;
		key2Transforms[robotLeftArmModel] = Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(-60,18,0), Scale());
		AnimManager::CreateKeyframe(shootAnim, key2Transforms, 10.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key3Transforms;
		key3Transforms[robotLeftArmModel] = Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(-60,18,0), Scale());
		AnimManager::CreateKeyframe(shootAnim, key3Transforms, 20.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key4Transforms;
		key4Transforms[robotLeftArmModel] = Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(-97.2683,18,0), Scale());
		AnimManager::CreateKeyframe(shootAnim, key4Transforms, 25.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key5Transforms;
		key5Transforms[robotLeftArmModel] = Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(-60,18,0), Scale());
		AnimManager::CreateKeyframe(shootAnim, key5Transforms, 30.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key6Transforms;
		key6Transforms[robotLeftArmModel] = Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(-97.2683,18,0), Scale());
		AnimManager::CreateKeyframe(shootAnim, key6Transforms, 35.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key7Transforms;
		key7Transforms[robotLeftArmModel] = Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(-60,18,0), Scale());
		AnimManager::CreateKeyframe(shootAnim, key7Transforms, 40.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key8Transforms;
		key8Transforms[robotLeftArmModel] = Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(-97.2683,18,0), Scale());
		AnimManager::CreateKeyframe(shootAnim, key8Transforms, 45.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key9Transforms;
		key9Transforms[robotLeftArmModel] = Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(-60,18,0), Scale());
		AnimManager::CreateKeyframe(shootAnim, key9Transforms, 50.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key10Transforms;
		key10Transforms[robotLeftArmModel] = Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(-97.2683,18,0), Scale());
		AnimManager::CreateKeyframe(shootAnim, key10Transforms, 55.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key11Transforms;
		key11Transforms[robotLeftArmModel] = Transform(Position(-1.21773 * fbxToOpenGLPosRatio,0.698849 * fbxToOpenGLPosRatio,0), Rotation(-60,18,0), Scale());
		AnimManager::CreateKeyframe(shootAnim, key11Transforms, 60.0f/60.0f);

		//	===============================================================================================================
		std::unordered_map<std::shared_ptr<FBXModel>,Transform> key12Transforms;
		key12Transforms[robotLeftArmModel] = robotLeftArmDefaultTransform;
		AnimManager::CreateKeyframe(shootAnim, key12Transforms, 80.0f/60.0f);


		AnimManager::ToggleAnimation(2, false);	//	make sure to turn off animation

	}

	gunModel->isActive = false;
}

//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		600, 600,WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	Init();
	
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		int framesToUpdate = frameTimer->GetFramesToUpdate();
		float deltaTime = frameTimer->GetDeltaTime();
		//update animations
		if(framesToUpdate >= 1)
			AnimManager::UpdateAnimations(deltaTime);
		
		//render
		display();

		SwapBuffers(hdc);
	}
}
//--------------------------------------------------------------------