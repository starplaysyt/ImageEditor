#include "Form1.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array < String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(0);
    ImageRedactor::Form1 form;
    Application::Run(% form);
}