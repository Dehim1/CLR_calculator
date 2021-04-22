#include "windows.h"
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CLRProtject1::MyForm());
}
