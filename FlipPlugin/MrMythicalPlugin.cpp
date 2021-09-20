#include "pch.h"
#include "MrMythicalPlugin.h"
#include <string>
using namespace std;


BAKKESMOD_PLUGIN(MrMythicalPlugin, "Flip Indicator Plugin", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void MrMythicalPlugin::onLoad()
{
	
	_globalCvarManager = cvarManager;
	cvarManager-> log("MrMythicalPlugin loaded!");
	cvarManager->registerCvar("FlipPlugin_enable", "0", "Enable Plugin", true, true, 0, true, 1);
	cvarManager->registerCvar("FlipPlugin_xaxis", "10", "X Position", true);
	cvarManager->registerCvar("FlipPlugin_yaxis", "10", "Y Position", true);
	cvarManager->registerCvar("FlipPlugin_txt_size", "2.0", "Text Size", true, true, 0.25, true, 20.0);
	cvarManager->registerCvar("FlipPlugin_opacity", "255", "Opacity", true, true, 1, true, 255);
		gameWrapper->RegisterDrawable(bind(&MrMythicalPlugin::RenderTxt, this, placeholders::_1));	
}

void MrMythicalPlugin::onUnload()
{
}


void MrMythicalPlugin::RenderTxt(CanvasWrapper canvas) {
	if (!gameWrapper->IsInGame() && !gameWrapper->IsInReplay()) return;
	if (!cvarManager->getCvar("FlipPlugin_enable")) { return; }
	if (!cvarManager->getCvar("FlipPlugin_enable").getBoolValue()) { return; }
	if (cvarManager->getCvar("FlipPlugin_xaxis").IsNull()) { return; }
	if (cvarManager->getCvar("FlipPlugin_yaxis").IsNull()) { return; }
	if (cvarManager->getCvar("FlipPlugin_txt_size").IsNull()) { return; }
	if (cvarManager->getCvar("FlipPlugin_opacity").IsNull()) { return; }
	int xaxis = cvarManager->getCvar("FlipPlugin_xaxis").getIntValue();
	int yaxis = cvarManager->getCvar("FlipPlugin_yaxis").getIntValue();
	xaxis = (canvas.GetSize().X / 100) * xaxis;
	yaxis = (canvas.GetSize().Y / 100) * yaxis;
	float txt_size = cvarManager->getCvar("FlipPlugin_txt_size").getIntValue();
	float opacity = cvarManager->getCvar("FlipPlugin_opacity").getFloatValue();
	ServerWrapper server = gameWrapper->GetCurrentGameState();
	if (!server) { return; }
	CarWrapper car = gameWrapper->GetLocalCar();
	if (!car) { return; }
	canvas.SetPosition(Vector2{ xaxis, yaxis });
	if (car.HasFlip()) canvas.SetColor(LinearColor{ 0.0, 255, 0.0, opacity });
	else canvas.SetColor(LinearColor{ 255, 0.0, 0.0, opacity });
	car.HasFlip() ? canvas.DrawString("Got flip", txt_size, txt_size, false) : canvas.DrawString("No flip", txt_size, txt_size, false);
}