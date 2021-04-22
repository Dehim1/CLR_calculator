#pragma once

namespace CLRProtject1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		//attributes////////////////////////////////////////////////////////////////////////////
		const unsigned int historyLength = 2048;
		array<String^>^ history = gcnew array<String^>(historyLength);
		unsigned int historyIter;
		unsigned int currentHistory;
		unsigned int NoEntries;

		System::Windows::Forms::Label^  label1;
		System::Windows::Forms::TextBox^  textBox1;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			for each (String ^%s in history)
			{
				s = gcnew String("");
			}
			this->historyIter = historyLength - 1;
			this->currentHistory = 0;
			this->NoEntries = 0;

			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(12, 38);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(1251, 22);
			this->label1->TabIndex = 4;
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 13);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(1251, 22);
			this->textBox1->TabIndex = 5;
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox1_KeyDown);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox1_KeyPress);
			this->textBox1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox1_KeyUp);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1275, 68);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Text = L"Calculator";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		System::String^ calc(System::String^ in);
		System::Void textBox1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
		System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	};
}
