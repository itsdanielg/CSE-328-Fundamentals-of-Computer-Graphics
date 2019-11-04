#include "particlesystem.cpp"

////////// CALLBACK IDs //////////
#define SET_DEFAULT_ID	100
#define START_ID		200
#define STOP_ID			201
#define RESET_ID		202

////////// INIT VARIABLES //////////
extern int mainWindow;
extern int windowWidth;
extern int windowHeight;
extern float aspectRatio;
extern int windowPosX;
extern int windowPosY;
extern int sysStatus;

////////// SYSTEM VARIABLES //////////
extern int debugLevel;
extern int frameCount;
extern float emitterRadius;
extern float emitterRate;
extern float timingStepsPerSec;
extern float timingFramesPerSec;
extern float fireCoolRate;
extern float fireRiseRate;
extern float fireTurbulenceAmp;
extern float fireTurbulenceScale;
extern float fireWindX;
extern float fireWindY;
extern float fireWindZ;
extern float cameraPosX;
extern float cameraPosY;
extern float cameraPosZ;
extern float cameraLookAtX;
extern float cameraLookAtY;
extern float cameraLookAtZ;
extern float cameraFOV;
extern float cameraAspect;
extern float cameraNear;
extern float cameraFar;
extern int programDrawParticles;
extern int programWriteParticles;
extern int programWriteRenders;
extern char programParticleFilename[];
extern char programRenderFilename[];

////////// PARTICLE VARIABLES //////////
extern ParticleSystem particleSystem;

////////// GUI CONTROLS //////////
extern GLUI *glui;
extern GLUI_Spinner* debugLevelSpinner;
extern GLUI_EditText* frameCountEdit;
extern GLUI_Rollout* particleSettingsRollout;
extern GLUI_Button* defaultButton;
extern GLUI_Panel* emitterPanel;
extern GLUI_Spinner* emitterRadiusSpinner;
extern GLUI_Spinner* emitterRateSpinner;
extern GLUI_Panel* timingPanel;
extern GLUI_Spinner* timingTimeStepsSpinner;
extern GLUI_Spinner* timingFramesSpinner;
extern GLUI_Rollout* fireSettingsRollout;
extern GLUI_Spinner* fireCoolRateSpinner;
extern GLUI_Spinner* fireRiseRateSpinner;
extern GLUI_Spinner* fireTurbulenceAmpSpinner;
extern GLUI_Spinner* fireTurbulenceScaleSpinner;
extern GLUI_Spinner* fireWindXSpinner;
extern GLUI_Spinner* fireWindYSpinner;
extern GLUI_Spinner* fireWindZSpinner;
extern GLUI_Rollout* cameraSettingsRollout;
extern GLUI_Spinner* cameraXPosSpinner;
extern GLUI_Spinner* cameraYPosSpinner;
extern GLUI_Spinner* cameraZPosSpinner;
extern GLUI_Spinner* cameraLookAtXSpinner;
extern GLUI_Spinner* cameraLookAtYSpinner;
extern GLUI_Spinner* cameraLookAtZSpinner;
extern GLUI_Spinner* cameraFOVSpinner;
extern GLUI_Spinner* cameraAspectSpinner;
extern GLUI_Spinner* cameraNearSpinner;
extern GLUI_Spinner* cameraFarSpinner;
extern GLUI_Rollout* programControlRollout;
extern GLUI_Checkbox* programDrawParticlesCheckbox;
extern GLUI_Checkbox* programWriteParticlesCheckbox;
extern GLUI_EditText* programParticleFilenameText;
extern GLUI_Checkbox* programWriteRendersCheckbox;
extern GLUI_EditText* programRenderFilenameText;
extern GLUI_Button* startButton;
extern GLUI_Button* stopButton;
extern GLUI_Button* resetButton;
extern GLUI_Button* quitButton;