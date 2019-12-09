#include <GL/glui.h>
#include "globalvar.h"

int sysStatus = 1;

////////// SYSTEM VARIABLES //////////
int debugLevel;
int frameCount;
float emitterRadius;
float emitterRate;
int timingStepsPerSec;
int timingFramesPerSec;
float fireCoolRate;
float fireRiseRate;
float fireTurbulenceAmp;
float fireTurbulenceScale;
float fireWindX;
float fireWindY;
float fireWindZ;
float cameraPosX;
float cameraPosY;
float cameraPosZ;
float cameraLookAtX;
float cameraLookAtY;
float cameraLookAtZ;
float cameraFOV;
float cameraAspect;
float cameraNear;
float cameraFar;
int programDrawParticles;
int programWriteParticles;
int programWriteRenders;
char programParticleFilename[] = "./frames/parts-";
char programRenderFilename[] = "./frames/rends-";

////////// GUI CONTROLS //////////
GLUI *glui;
GLUI_Spinner* debugLevelSpinner;
GLUI_EditText* frameCountEdit;
GLUI_Rollout* particleSettingsRollout;
GLUI_Button* defaultButton;
GLUI_Panel* emitterPanel;
GLUI_Spinner* emitterRadiusSpinner;
GLUI_Spinner* emitterRateSpinner;
GLUI_Panel* timingPanel;
GLUI_Spinner* timingTimeStepsSpinner;
GLUI_Spinner* timingFramesSpinner;
GLUI_Rollout* fireSettingsRollout;
GLUI_Spinner* fireCoolRateSpinner;
GLUI_Spinner* fireRiseRateSpinner;
GLUI_Spinner* fireTurbulenceAmpSpinner;
GLUI_Spinner* fireTurbulenceScaleSpinner;
GLUI_Spinner* fireWindXSpinner;
GLUI_Spinner* fireWindYSpinner;
GLUI_Spinner* fireWindZSpinner;
GLUI_Rollout* cameraSettingsRollout;
GLUI_Spinner* cameraXPosSpinner;
GLUI_Spinner* cameraYPosSpinner;
GLUI_Spinner* cameraZPosSpinner;
GLUI_Spinner* cameraLookAtXSpinner;
GLUI_Spinner* cameraLookAtYSpinner;
GLUI_Spinner* cameraLookAtZSpinner;
GLUI_Spinner* cameraFOVSpinner;
GLUI_Spinner* cameraAspectSpinner;
GLUI_Spinner* cameraNearSpinner;
GLUI_Spinner* cameraFarSpinner;
GLUI_Rollout* programControlRollout;
GLUI_Checkbox* programDrawParticlesCheckbox;
GLUI_Checkbox* programWriteParticlesCheckbox;
GLUI_EditText* programParticleFilenameText;
GLUI_Checkbox* programWriteRendersCheckbox;
GLUI_EditText* programRenderFilenameText;
GLUI_Button* startButton;
GLUI_Button* stopButton;
GLUI_Button* resetButton;
GLUI_Button* quitButton;

void resetVar() {
	debugLevel = 0;
	emitterRadius = 1.0;
	emitterRate = 25.0;
	timingStepsPerSec = 24;
	timingFramesPerSec = 24;
	fireCoolRate = 1.0;
	fireRiseRate = 0.01;
	fireTurbulenceAmp = 0.5;
	fireTurbulenceScale = 8.0;
	fireWindX = 0.0;
	fireWindY = 0.0;
	fireWindZ = 0.0;
	cameraPosX = -1.00;
	cameraPosY = 5.00;
	cameraPosZ = 10.0;
	cameraLookAtX = -1.00;
	cameraLookAtY = 5.00;
	cameraLookAtZ = 0.00;
	cameraFOV = 90.0;
	cameraAspect = (float)1600/950;
	cameraNear = 0.001;
	cameraFar = 100.0;
	programDrawParticles = 1;
	programWriteParticles = 0;
	programWriteRenders = 0;
}

void defaultCallback() {
	resetVar();
	glui->sync_live();
}

void updateReset() {
	frameCount = 0;
	fireSystem.resetSystem();
}

void startSys() {
	sysStatus = 1;
}

void stopSys() {
	sysStatus = 0;
}

void callback(int id) {
	switch(id) {
		case SET_DEFAULT_ID:
			defaultCallback();
			break;
		case START_ID:
			startSys();
			break;
		case STOP_ID:
			stopSys();
			break;
		case RESET_ID:
			updateReset();
			break;
		default:
			break;
	}
}

void initGlui() {
	glui = GLUI_Master.create_glui_subwindow(mainWindow, GLUI_SUBWINDOW_LEFT);
	debugLevelSpinner = glui->add_spinner("Debug Level",GLUI_SPINNER_INT, &debugLevel);
	frameCountEdit = glui->add_edittext("Frame Count", GLUI_EDITTEXT_INT, &frameCount);
	particleSettingsRollout = glui->add_rollout("Particle System Settings", true);
	defaultButton = glui->add_button_to_panel(particleSettingsRollout, "Defaults - Basic", SET_DEFAULT_ID, callback);
	emitterPanel = glui->add_panel_to_panel(particleSettingsRollout, "Emitter", GLUI_PANEL_EMBOSSED);
	emitterRadiusSpinner = glui->add_spinner_to_panel(emitterPanel, "Radius", GLUI_SPINNER_FLOAT, &emitterRadius);
	emitterRateSpinner = glui->add_spinner_to_panel(emitterPanel, "Rate", GLUI_SPINNER_FLOAT, &emitterRate);
	timingPanel = glui->add_panel_to_panel(particleSettingsRollout, "Timing", GLUI_PANEL_EMBOSSED);
	timingTimeStepsSpinner = glui->add_spinner_to_panel(timingPanel, "Time Steps Per Second", GLUI_SPINNER_INT, &timingStepsPerSec);
	timingFramesSpinner = glui->add_spinner_to_panel(timingPanel, "Frames Per Second", GLUI_SPINNER_INT, &timingFramesPerSec);
	fireSettingsRollout = glui->add_rollout_to_panel(particleSettingsRollout, "Fire Settings", true);
	fireCoolRateSpinner = glui->add_spinner_to_panel(fireSettingsRollout, "Cool Rate", GLUI_SPINNER_FLOAT, &fireCoolRate);
	fireRiseRateSpinner = glui->add_spinner_to_panel(fireSettingsRollout, "Rise Rate", GLUI_SPINNER_FLOAT, &fireRiseRate);
	fireTurbulenceAmpSpinner = glui->add_spinner_to_panel(fireSettingsRollout, "Turbulence Amplitude", GLUI_SPINNER_FLOAT, &fireTurbulenceAmp);
	fireTurbulenceScaleSpinner = glui->add_spinner_to_panel(fireSettingsRollout, "Turbulence Scale", GLUI_SPINNER_FLOAT, &fireTurbulenceScale);
	fireWindXSpinner = glui->add_spinner_to_panel(fireSettingsRollout, "Wind X", GLUI_SPINNER_FLOAT, &fireWindX);
	fireWindYSpinner = glui->add_spinner_to_panel(fireSettingsRollout, "Wind Y", GLUI_SPINNER_FLOAT, &fireWindY);
	fireWindZSpinner = glui->add_spinner_to_panel(fireSettingsRollout, "Wind Z", GLUI_SPINNER_FLOAT, &fireWindZ);
	cameraSettingsRollout = glui->add_rollout("Camera Settings", true);
	cameraXPosSpinner = glui->add_spinner_to_panel(cameraSettingsRollout, "X Position", GLUI_SPINNER_FLOAT, &cameraPosX);
	cameraYPosSpinner = glui->add_spinner_to_panel(cameraSettingsRollout, "Y Position", GLUI_SPINNER_FLOAT, &cameraPosY);
	cameraZPosSpinner = glui->add_spinner_to_panel(cameraSettingsRollout, "Z Position", GLUI_SPINNER_FLOAT, &cameraPosZ);
	cameraLookAtXSpinner = glui->add_spinner_to_panel(cameraSettingsRollout, "X LookAt", GLUI_SPINNER_FLOAT, &cameraLookAtX);
	cameraLookAtYSpinner = glui->add_spinner_to_panel(cameraSettingsRollout, "Y LookAt", GLUI_SPINNER_FLOAT, &cameraLookAtY);
	cameraLookAtZSpinner = glui->add_spinner_to_panel(cameraSettingsRollout, "Z LookAt", GLUI_SPINNER_FLOAT, &cameraLookAtZ);
	cameraFOVSpinner = glui->add_spinner_to_panel(cameraSettingsRollout, "Field of View", GLUI_SPINNER_FLOAT, &cameraFOV);
	cameraAspectSpinner = glui->add_spinner_to_panel(cameraSettingsRollout, "Aspect Ratio", GLUI_SPINNER_FLOAT, &cameraAspect);
	cameraNearSpinner = glui->add_spinner_to_panel(cameraSettingsRollout, "Near Clip Plane", GLUI_SPINNER_FLOAT, &cameraNear);
	cameraFarSpinner = glui->add_spinner_to_panel(cameraSettingsRollout, "Far Clip Plane", GLUI_SPINNER_FLOAT, &cameraFar);
	programControlRollout = glui->add_rollout("Program Control", true);
	programDrawParticlesCheckbox = glui->add_checkbox_to_panel(programControlRollout, "Draw Particles", &programDrawParticles);
	glui->add_separator_to_panel(programControlRollout);
	programWriteParticlesCheckbox = glui->add_checkbox_to_panel(programControlRollout, "Write Particles to Files", &programWriteParticles);
	programParticleFilenameText = glui->add_edittext_to_panel(programControlRollout, "Base Filename", GLUI_EDITTEXT_TEXT, &programParticleFilename);
	glui->add_separator_to_panel(programControlRollout);
	programWriteRendersCheckbox = glui->add_checkbox_to_panel(programControlRollout, "Write Renders to Files", &programWriteRenders);
	programRenderFilenameText = glui->add_edittext_to_panel(programControlRollout, "Base Filename", GLUI_EDITTEXT_TEXT, &programRenderFilename);
	glui->add_separator_to_panel(programControlRollout);
	startButton = glui->add_button_to_panel(programControlRollout, "Start", START_ID, callback);
	stopButton = glui->add_button_to_panel(programControlRollout, "Stop", STOP_ID, callback);
	resetButton = glui->add_button_to_panel(programControlRollout, "Reset and Update", RESET_ID, callback);
	quitButton = glui->add_button("Quit", 0, (GLUI_Update_CB)exit);
}

void adjustGlui() {
	float speed = 0.1;
	frameCountEdit->disable();
	emitterRadiusSpinner->set_speed(speed);
	emitterRateSpinner->set_speed(speed);
	timingTimeStepsSpinner->set_speed(speed);
	timingFramesSpinner->set_speed(speed);
	fireCoolRateSpinner->set_speed(speed);
	fireRiseRateSpinner->set_speed(speed);
	fireTurbulenceAmpSpinner->set_speed(speed);
	fireTurbulenceScaleSpinner->set_speed(speed);
	fireWindXSpinner->set_speed(speed);
	fireWindYSpinner->set_speed(speed * 0.1);
	fireWindZSpinner->set_speed(speed);
	cameraXPosSpinner->set_speed(speed);
	cameraYPosSpinner->set_speed(speed);
	cameraZPosSpinner->set_speed(speed);
	cameraLookAtXSpinner->set_speed(speed);
	cameraLookAtYSpinner->set_speed(speed);
	cameraLookAtZSpinner->set_speed(speed);
	cameraFOVSpinner->set_speed(speed);
	cameraAspectSpinner->set_speed(speed);
	cameraNearSpinner->set_speed(speed);
	cameraFarSpinner->set_speed(speed);
	debugLevelSpinner->set_int_limits(0, 1, GLUI_LIMIT_CLAMP);
	emitterRadiusSpinner->set_float_limits(0.01, 10.0, GLUI_LIMIT_CLAMP);
	emitterRateSpinner->set_float_limits(0.01, 50.0, GLUI_LIMIT_CLAMP);
	timingTimeStepsSpinner->set_int_limits(1, 120, GLUI_LIMIT_CLAMP);
	timingFramesSpinner->set_int_limits(1, 60, GLUI_LIMIT_CLAMP);
	fireCoolRateSpinner->set_float_limits(0.001, 1.0, GLUI_LIMIT_CLAMP);
	fireRiseRateSpinner->set_float_limits(0.001, 1.0, GLUI_LIMIT_CLAMP);
	fireTurbulenceAmpSpinner->set_float_limits(0.0, 10.0, GLUI_LIMIT_CLAMP);
	fireTurbulenceScaleSpinner->set_float_limits(0.0, 10.0, GLUI_LIMIT_CLAMP);
	fireWindXSpinner->set_float_limits(-1.0, 1.0, GLUI_LIMIT_CLAMP);
	fireWindYSpinner->set_float_limits(-1.0, 1.0, GLUI_LIMIT_CLAMP);
	fireWindZSpinner->set_float_limits(-10.0, 10.0, GLUI_LIMIT_CLAMP);
}

