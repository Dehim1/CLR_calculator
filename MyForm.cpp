#include "MyForm.h"
#include <string>
#include "stringCalc.h"
#include <msclr\marshal_cppstd.h>

System::Void CLRProtject1::MyForm::textBox1_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	wchar_t a = e->KeyChar;
	/*
	if(a == 'p') // replace number arround cursor with 3.141592653589793;
	if(a == 'e') // replace number arround cursor with 2.718281828459;
	*/
	e->Handled = !(((a >= '(') & (a <= '+')) | ((a >= '-') & (a <= '9')) | (a == '^') | (a == 8) | (a==22) | (a==3));
}

System::String^ CLRProtject1::MyForm::calc(System::String^ in)
{
	std::string a = msclr::interop::marshal_as<std::string>(in);
	return gcnew String(stringCalc(a).c_str());
}

System::Void CLRProtject1::MyForm::textBox1_KeyUp(System::Object ^ sender, System::Windows::Forms::KeyEventArgs ^ e)
{
	label1->Text = calc(textBox1->Text);
}

System::Void CLRProtject1::MyForm::textBox1_KeyDown(System::Object ^ sender, System::Windows::Forms::KeyEventArgs ^ e)
{
	if(e->KeyCode == Keys::Up)
	{
		e->Handled = true;
		if(currentHistory == 0) history[historyIter] = textBox1->Text;
		if(currentHistory < NoEntries)
		{
			++currentHistory;
			textBox1->Text = history[(historyIter + currentHistory) % historyLength];
			textBox1->SelectionStart = textBox1->Text->Length;
			textBox1->SelectionLength = 0;
			return System::Void();
		}
		return System::Void();
	}

	if (e->KeyCode == Keys::Down)
	{
		e->Handled = true;
		if (currentHistory > 0)
		{
			--currentHistory;
			textBox1->Text = history[(historyIter + currentHistory) % historyLength];
			textBox1->SelectionStart = textBox1->Text->Length;
			textBox1->SelectionLength = 0;
			return System::Void();
		}
		return System::Void();
	}
	
	if(e->KeyCode == Keys::Enter && textBox1->Text->Length > 0)
	{
		e->Handled = true;
		currentHistory = 0;

		history[historyIter] = textBox1->Text;
		textBox1->Text = calc(history[historyIter]);
		textBox1->SelectionStart = 0;
		textBox1->SelectionLength = textBox1->Text->Length;

		if (NoEntries < historyLength - 1) ++NoEntries;

		if(historyIter > 0)
		{
			--historyIter;
			return System::Void();
		}
		historyIter = historyLength - 1;
		return System::Void();
	}
	
}
