#include "pch.h"
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	DSprojGUI::MyForm form;
	Application::Run(% form);

}

