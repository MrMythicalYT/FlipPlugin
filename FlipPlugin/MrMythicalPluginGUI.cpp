#include "pch.h"
#include "MrMythicalPlugin.h"

using namespace std;

void MrMythicalPlugin::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

std::string MrMythicalPlugin::GetPluginName() {
	return "Flip Indicator";
}

void MrMythicalPlugin::RenderSettings() {
	ImGui::TextUnformatted("This plugin will show you if you can flip or not.");
	
	CVarWrapper enablecvar = cvarManager->getCvar("FlipPlugin_enable");
	if (!enablecvar) { return; }
	bool enabled = enablecvar.getBoolValue();


	CVarWrapper txt_sizeCvar = cvarManager->getCvar("FlipPlugin_txt_size");
	if (!txt_sizeCvar) { return; }
	float txt_size = txt_sizeCvar.getFloatValue();

	CVarWrapper xAxisCvar = cvarManager->getCvar("FlipPlugin_xaxis");
	if (!xAxisCvar) { return; }
	int xAxis = xAxisCvar.getIntValue();

	CVarWrapper yAxisCvar = cvarManager->getCvar("FlipPlugin_yaxis");
	if (!yAxisCvar) { return; }
	int yAxis = yAxisCvar.getIntValue();

	CVarWrapper opacityCvar = cvarManager->getCvar("FlipPlugin_opacity");
	if (!opacityCvar) { return; }
	float opacity = opacityCvar.getFloatValue();

	if (ImGui::Checkbox("Enable", &enabled)) {
		enablecvar.setValue(enabled);
	};
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Enable plugin");
	}

	if (ImGui::SliderFloat("Text size", &txt_size, 0.25, 20)) {
		txt_sizeCvar.setValue(txt_size);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Set text size");
	}

	if (ImGui::SliderInt("X Axis", &xAxis, 0.25, 100)) {
		xAxisCvar.setValue(xAxis);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Set positioning of the text (x)");
	}

	if (ImGui::SliderInt("Y Axis", &yAxis, 0.25, 100)) {
		yAxisCvar.setValue(yAxis);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Set positioning of the text (y)");
	}

	if (ImGui::SliderFloat("Opacity", &opacity, 1, 255)) {
		opacityCvar.setValue(opacity);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Set opacity of the text");
	}
}



/*
// Do ImGui rendering here
void MrMythicalPlugin::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}

// Name of the menu that is used to toggle the window.
std::string MrMythicalPlugin::GetMenuName()
{
	return "MrMythicalPlugin";
}

// Title to give the menu
std::string MrMythicalPlugin::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void MrMythicalPlugin::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool MrMythicalPlugin::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool MrMythicalPlugin::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void MrMythicalPlugin::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void MrMythicalPlugin::OnClose()
{
	isWindowOpen_ = false;
}
*/
