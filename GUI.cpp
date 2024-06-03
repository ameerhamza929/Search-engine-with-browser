#pragma once
#include "SearchEngine.h"
#include <msclr/marshal_cppstd.h>

namespace DSprojGUI {

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
			engine = new SearchEngine;
			engine->workofmain();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete engine;
		}

	private:
		System::Windows::Forms::Button^ button1;
		System::Windows::Forms::TextBox^ textBox1;
		System::Windows::Forms::ListBox^ listBox1;
		SearchEngine* engine;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;

		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->button4 = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->button5 = (gcnew System::Windows::Forms::Button());
			   this->button6 = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();
			   // 
			   // button1
			   // 
			   this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->button1->Location = System::Drawing::Point(665, 29);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(75, 23);
			   this->button1->TabIndex = 0;
			   this->button1->Text = L"Search";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button1_MouseClick);
			   this->button1->MouseHover += gcnew System::EventHandler(this, &MyForm::button1_MouseHover);
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(127, 29);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(506, 22);
			   this->textBox1->TabIndex = 1;
			   // 
			   // listBox1
			   // 
			   this->listBox1->FormattingEnabled = true;
			   this->listBox1->ItemHeight = 16;
			   this->listBox1->Location = System::Drawing::Point(127, 57);
			   this->listBox1->Name = L"listBox1";
			   this->listBox1->Size = System::Drawing::Size(506, 68);
			   this->listBox1->TabIndex = 2;
			   this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			   // 
			   // button2
			   // 
			   this->button2->Location = System::Drawing::Point(2, 28);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(49, 23);
			   this->button2->TabIndex = 3;
			   this->button2->Text = L"<-";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			   // 
			   // button3
			   // 
			   this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->button3->Location = System::Drawing::Point(57, 28);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(49, 23);
			   this->button3->TabIndex = 4;
			   this->button3->Text = L"->";
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			   // 
			   // textBox2
			   // 
			   this->textBox2->Location = System::Drawing::Point(127, 265);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(506, 22);
			   this->textBox2->TabIndex = 5;
			   // 
			   // button4
			   // 
			   this->button4->Location = System::Drawing::Point(665, 264);
			   this->button4->Name = L"button4";
			   this->button4->Size = System::Drawing::Size(75, 23);
			   this->button4->TabIndex = 6;
			   this->button4->Text = L"search";
			   this->button4->UseVisualStyleBackColor = true;
			   this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Mistral", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label1->Location = System::Drawing::Point(194, 151);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(405, 95);
			   this->label1->TabIndex = 7;
			   this->label1->Text = L"DSA PROJECT";
			   // 
			   // button5
			   // 
			   this->button5->Location = System::Drawing::Point(2, 513);
			   this->button5->Name = L"button5";
			   this->button5->Size = System::Drawing::Size(75, 23);
			   this->button5->TabIndex = 8;
			   this->button5->Text = L"History";
			   this->button5->UseVisualStyleBackColor = true;
			   this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			   // 
			   // button6
			   // 
			   this->button6->Location = System::Drawing::Point(704, 513);
			   this->button6->Name = L"button6";
			   this->button6->Size = System::Drawing::Size(75, 23);
			   this->button6->TabIndex = 9;
			   this->button6->Text = L"clear history";
			   this->button6->UseVisualStyleBackColor = true;
			   this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(780, 539);
			   this->Controls->Add(this->button6);
			   this->Controls->Add(this->button5);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->button4);
			   this->Controls->Add(this->textBox2);
			   this->Controls->Add(this->button3);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->listBox1);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->button1);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	private: System::Void button1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		PerformSearch();
	}

	private: System::Void PerformSearch() {
		String^ query = textBox1->Text;
		vector<string> results = engine->search(msclr::interop::marshal_as<std::string>(query));
		listBox1->Items->Clear();
		for (const auto& result : results)
		{
			listBox1->Items->Add(gcnew String(result.c_str()));
		}
		engine->maintainbackstack(msclr::interop::marshal_as<std::string>(query));
		//engine->maintainforstack(msclr::interop::marshal_as<std::string>(query));
	}

	private: System::Void button1_MouseHover(System::Object^ sender, System::EventArgs^ e) {
		// Show tooltip when hovering over the button
		System::Windows::Forms::ToolTip^ tooltip = gcnew System::Windows::Forms::ToolTip();
		tooltip->SetToolTip(button1, "Click me!"); // Set the tooltip text
	}

	private: System::Void listBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (listBox1->SelectedItem != nullptr) {
			String^ selectedItem = listBox1->SelectedItem->ToString();
			// Open the selected file
			System::Diagnostics::Process::Start("notepad.exe", selectedItem);
		}
	}

	private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (listBox1->SelectedItem != nullptr) {
			String^ selectedItem = listBox1->SelectedItem->ToString();
			// Open the selected file
			System::Diagnostics::Process::Start("notepad.exe", selectedItem);
		}
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string result = engine->displaybackstack();
		engine->maintainforstack(result);
		textBox1->Text = gcnew System::String(result.c_str());
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string result = engine->displayfrontstack();
		textBox1->Text = gcnew System::String(result.c_str());
	}

	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ query = textBox2->Text->Trim();
		System::Diagnostics::Process::Start("https://www.google.com/search?q=" + query);
	}

	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		engine->saveHistoryToFile();
		vector<string> results = engine->loadHistoryFromFile();
		listBox1->Items->Clear();
		for (const auto& result : results)
		{
			listBox1->Items->Add(gcnew String(result.c_str()));
		}
	}

	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		engine->clearHistory();
		listBox1->Items->Clear();
	}

	protected:
		virtual bool ProcessCmdKey(Message% msg, Keys keyData) override
		{
			if (keyData == Keys::Enter)
			{
				PerformSearch();
				return true;
			}
			else if (keyData == (Keys::Control | Keys::H))
			{
				button5_Click(nullptr, nullptr);
				return true;
			}
			return Form::ProcessCmdKey(msg, keyData);
		}
	};
}
