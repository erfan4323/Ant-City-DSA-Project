// for enabling debug in console
#define DEBUG

// self includes
#include "Utils.h"
#include "File.h"
#include "Serialization.h"

// GUI headers
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raylib.h>

// method definition
void CustomLog(int msgType, const char* text, va_list args);
void SerializeLogic(char  encoderInputText[1024], Encoder& encode, Decoder& decode, string& decoderValues);
void GuiRender(char  encoderInputText[1024], Encoder& encode, Decoder& decode, string& decoderValues, string& data, char  textBoxText[128], bool& textBoxEditMode);

int main()
{
	int screenWidth = 635;
	int screenHeight = 450;

	SetTraceLogCallback(CustomLog);
	InitWindow(screenWidth, screenHeight, "Ant City DSA Project");

	// text box values
	bool textBoxEditMode = false;
	char textBoxText[128] = "";
	char encoderInputText[1024] = "";

	// project setup
	strvec parentTxtValues;
	GatherData(parentTxtValues);
	string data = joinStrings(parentTxtValues);

	Encoder encode;
	Decoder decode;

	string decoderValues;

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		// drawing GUI
		GuiRender(encoderInputText, encode, decode, decoderValues, data, textBoxText, textBoxEditMode);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void CustomLog(int msgType, const char* text, va_list args) { return; }

void SerializeLogic(char  encoderInputText[1024], Encoder& encode, Decoder& decode, string& decoderValues)
{
	strvec cityCitizens = splitString(string(encoderInputText));

	// Encoder :
	encode.Initialize();
	encode.GetCity(cityCitizens);
	encode.ValidateCity();
	encode.SaveToOrder();

	// Decoder :
	decode.ReadOrder();
	strvec decoderOut = decode.ValidatedCitizens();
	decoderValues = joinStrings(decoderOut);
}

void GuiRender(char  encoderInputText[1024], Encoder& encode, Decoder& decode, string& decoderValues, string& data, char  textBoxText[128], bool& textBoxEditMode)
{
	GuiGroupBox(Rectangle{ 24, 48, 584, 384 }, "Ant City");
	GuiGroupBox(Rectangle{ 248, 72, 168, 296 }, "Decoder Output:");

	if (GuiButton(Rectangle{ 424, 72, 168, 32 }, "Accept"))
		SerializeLogic(encoderInputText, encode, decode, decoderValues);

	GuiGroupBox(Rectangle{ 424, 120, 168, 248 }, "Parent.txt Values:");
	GuiLabel(Rectangle{ 432, 128, 152, 232 }, data.c_str());					// parent.txt values
	GuiLabel(Rectangle{ 256, 80, 152, 280 }, decoderValues.c_str());			// Decoder Standard Output
	GuiGroupBox(Rectangle{ 40, 72, 200, 296 }, "Encoder Input:");
	GuiLabel(Rectangle{ 40, 376, 64, 32 }, "Input:");

	if (GuiTextBox(Rectangle{ 128, 376, 464, 32 }, textBoxText, 128, textBoxEditMode)) {
		textBoxEditMode = !textBoxEditMode;

		if (IsKeyPressed(KEY_ENTER)) {
			strcat(encoderInputText, textBoxText);
			strcat(encoderInputText, "\n");

			strcpy(textBoxText, "");
		}
	}

	GuiLabel(Rectangle{ 48, 80, 184, 280 }, encoderInputText);
}