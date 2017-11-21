#pragma once
#include <Windows.h>
#include "OBuffer.h"
#include <string>
#include <iostream>
#include <dirent.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <vector>
#include "DirectoryHandler.h"
#include "TreeElement.h"
#include <fstream>
#include <algorithm>

#define BOOST_FILESYSTEM_NO_DEPRECATED

namespace CLRGUITest1 {

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
			
		};
		void addOBuffer(OBuffer &obuffer);
		void addFilesToListView(String ^ folderPath)
		{
			//pictureBox1->Image->FromFile("C:\\users\\aszel\\desktop\\diller.png");
			msclr::interop::marshal_context^ context = gcnew msclr::interop::marshal_context(); //Creates marshal_context to convert String^ to char*
			const char * _folderPath = context->marshal_as<const char*>(folderPath); //Converts given foldername to char* for use
			int lengthOfRoot = folderPath->LastIndexOf("\\") + 1;

			String^ folderName = folderPath->Remove(0, lengthOfRoot);

			std::vector<TreeElement> folderList = DirectoryHandler::getAllFolders(_folderPath); //Gets all folders within root dir (Recursively)	
			std::ofstream folderListLog("C:\\Programming Utilities\\folderlist.txt");
			folderList.emplace(folderList.begin(), TreeElement("", _folderPath));

			for (int i = 0; i < folderList.size(); i++) //Looping over all folders found from root dir
			{
				if (i == 0)
				{
					treeView1->Nodes->Add(makeNode(folderList[0], Color::LightBlue));
				}
				else
				{
					String^ parentname = msclr::interop::marshal_as<String^>(folderList[i].path); //Converts path of current directory to C# string
					parentname = parentname->Remove(parentname->LastIndexOf("\\")); //Gets path to parent of current directory

					cli::array<TreeNode^, 1>^ nodes = treeView1->Nodes->Find(parentname, true); //Finds matching directories based on nodes' Name attribute and places them in an array
					//ERROR HANDLING?

					nodes[0]->Nodes->Add(makeNode(folderList[i], Color::Pink));
				}
				folderListLog << folderList[i].path << std::endl;
			}		
			folderListLog.close();

			std::vector<std::string> fileList = DirectoryHandler::getAllFiles(folderList);		
			std::ofstream fileListLog("C:\\Programming Utilities\\filelist.txt");

			for(int i = 0; i < fileList.size(); i++)
			{
				String^ parentname = msclr::interop::marshal_as<String^>(fileList[i]); //Converts path of current directory to C# string
				parentname = parentname->Remove(parentname->LastIndexOf("\\")); //Gets path to parent of current directory

				cli::array<TreeNode^, 1>^ nodes = treeView1->Nodes->Find(parentname, true); //Finds matching directories based on nodes' Name attribute and places them in an array
				nodes[0]->Nodes->Add(makeNode(TreeElement(" ", fileList[i]), Color::LightGreen));

				std::string s = fileList[i].erase(0, lengthOfRoot);
				fileListLog << s << std::endl;
			}
			fileListLog.close();

			richTextBox1->Text += "Total of " + fileList.size() + " files.\n";

		}
		TreeNode^ makeNode(TreeElement element, Color color)
		{
			TreeNode^ node = gcnew TreeNode();
			
			node->Name = msclr::interop::marshal_as<String^>(element.path);
			node->Text = msclr::interop::marshal_as<String^>(element.name);

			node->BackColor = color;

			return node;			
		}
		void populateTreeViewFromFile()
		{
			std::string fileLogFilePath = "C:\\Programming Utilities\\filelist.txt";
			std::string folderLogFilePath = "C:\\Programming Utilities\\folderlist.txt";

			std::vector<std::string> filePaths;			
			std::ifstream fileLogIStream(fileLogFilePath);

			while (fileLogIStream.good())
			{
				char line[512];
				fileLogIStream.getline(line, 512);
				filePaths.push_back(line);
			}
			filePaths.pop_back();


			std::vector<std::string> folderPaths;
			std::ifstream folderLogIStream(folderLogFilePath);

			while (folderLogIStream.good())
			{
				char line[512];
				folderLogIStream.getline(line, 512);
				folderPaths.push_back(line);
			}
			folderPaths.pop_back();
			
			richTextBox1->Text += "Done";






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

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  btn_1;
	private: System::Windows::Forms::Button^  btn_2;
	private: System::Windows::Forms::Button^  btn_3;
	private: System::Windows::Forms::Button^  btn_a;
	private: System::Windows::Forms::Button^  btn_b;
	private: System::Windows::Forms::Button^  btn_6;
	private: System::Windows::Forms::Button^  btn_5;
	private: System::Windows::Forms::Button^  btn_4;
	private: System::Windows::Forms::Button^  btn_c;
	private: System::Windows::Forms::Button^  btn_9;
	private: System::Windows::Forms::Button^  btn_8;
	private: System::Windows::Forms::Button^  btn_7;
	private: System::Windows::Forms::Button^  btn_d;
	private: System::Windows::Forms::Button^  btn_hash;
	private: System::Windows::Forms::Button^  btn_0;
	private: System::Windows::Forms::Button^  btn_ast;

	protected:
		OBuffer* wBuffer;
	private: System::Windows::Forms::TabControl^  tabControl1;
	protected:
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage1;


	private: System::Windows::Forms::Button^  btn_pop;
	private: System::Windows::Forms::TreeView^  treeView1;
private: System::Windows::Forms::RichTextBox^  richTextBox1;
private: System::Windows::Forms::Button^  loadFromFileButton;



	private:
		//OBuffer* wBuffer;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->btn_1 = (gcnew System::Windows::Forms::Button());
			this->btn_2 = (gcnew System::Windows::Forms::Button());
			this->btn_3 = (gcnew System::Windows::Forms::Button());
			this->btn_a = (gcnew System::Windows::Forms::Button());
			this->btn_b = (gcnew System::Windows::Forms::Button());
			this->btn_6 = (gcnew System::Windows::Forms::Button());
			this->btn_5 = (gcnew System::Windows::Forms::Button());
			this->btn_4 = (gcnew System::Windows::Forms::Button());
			this->btn_c = (gcnew System::Windows::Forms::Button());
			this->btn_9 = (gcnew System::Windows::Forms::Button());
			this->btn_8 = (gcnew System::Windows::Forms::Button());
			this->btn_7 = (gcnew System::Windows::Forms::Button());
			this->btn_d = (gcnew System::Windows::Forms::Button());
			this->btn_hash = (gcnew System::Windows::Forms::Button());
			this->btn_0 = (gcnew System::Windows::Forms::Button());
			this->btn_ast = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->btn_pop = (gcnew System::Windows::Forms::Button());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->loadFromFileButton = (gcnew System::Windows::Forms::Button());
			this->tabControl1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(4, 5);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(84, 24);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Good Button";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// btn_1
			// 
			this->btn_1->Location = System::Drawing::Point(4, 60);
			this->btn_1->Margin = System::Windows::Forms::Padding(2);
			this->btn_1->Name = L"btn_1";
			this->btn_1->Size = System::Drawing::Size(56, 61);
			this->btn_1->TabIndex = 1;
			this->btn_1->Text = L"1";
			this->btn_1->UseVisualStyleBackColor = true;
			this->btn_1->Click += gcnew System::EventHandler(this, &MyForm::btn_1_Click);
			// 
			// btn_2
			// 
			this->btn_2->Location = System::Drawing::Point(65, 60);
			this->btn_2->Margin = System::Windows::Forms::Padding(2);
			this->btn_2->Name = L"btn_2";
			this->btn_2->Size = System::Drawing::Size(56, 61);
			this->btn_2->TabIndex = 2;
			this->btn_2->Text = L"2";
			this->btn_2->UseVisualStyleBackColor = true;
			this->btn_2->Click += gcnew System::EventHandler(this, &MyForm::btn_2_Click);
			// 
			// btn_3
			// 
			this->btn_3->Location = System::Drawing::Point(126, 60);
			this->btn_3->Margin = System::Windows::Forms::Padding(2);
			this->btn_3->Name = L"btn_3";
			this->btn_3->Size = System::Drawing::Size(56, 61);
			this->btn_3->TabIndex = 3;
			this->btn_3->Text = L"3";
			this->btn_3->UseVisualStyleBackColor = true;
			this->btn_3->Click += gcnew System::EventHandler(this, &MyForm::btn_3_Click);
			// 
			// btn_a
			// 
			this->btn_a->Location = System::Drawing::Point(187, 60);
			this->btn_a->Margin = System::Windows::Forms::Padding(2);
			this->btn_a->Name = L"btn_a";
			this->btn_a->Size = System::Drawing::Size(56, 61);
			this->btn_a->TabIndex = 4;
			this->btn_a->Text = L"A";
			this->btn_a->UseVisualStyleBackColor = true;
			this->btn_a->Click += gcnew System::EventHandler(this, &MyForm::btn_a_Click);
			// 
			// btn_b
			// 
			this->btn_b->Location = System::Drawing::Point(187, 126);
			this->btn_b->Margin = System::Windows::Forms::Padding(2);
			this->btn_b->Name = L"btn_b";
			this->btn_b->Size = System::Drawing::Size(56, 61);
			this->btn_b->TabIndex = 8;
			this->btn_b->Text = L"B";
			this->btn_b->UseVisualStyleBackColor = true;
			this->btn_b->Click += gcnew System::EventHandler(this, &MyForm::btn_b_Click);
			// 
			// btn_6
			// 
			this->btn_6->Location = System::Drawing::Point(126, 126);
			this->btn_6->Margin = System::Windows::Forms::Padding(2);
			this->btn_6->Name = L"btn_6";
			this->btn_6->Size = System::Drawing::Size(56, 61);
			this->btn_6->TabIndex = 7;
			this->btn_6->Text = L"6";
			this->btn_6->UseVisualStyleBackColor = true;
			this->btn_6->Click += gcnew System::EventHandler(this, &MyForm::btn_6_Click);
			// 
			// btn_5
			// 
			this->btn_5->Location = System::Drawing::Point(65, 126);
			this->btn_5->Margin = System::Windows::Forms::Padding(2);
			this->btn_5->Name = L"btn_5";
			this->btn_5->Size = System::Drawing::Size(56, 61);
			this->btn_5->TabIndex = 6;
			this->btn_5->Text = L"5";
			this->btn_5->UseVisualStyleBackColor = true;
			this->btn_5->Click += gcnew System::EventHandler(this, &MyForm::btn_5_Click);
			// 
			// btn_4
			// 
			this->btn_4->Location = System::Drawing::Point(4, 126);
			this->btn_4->Margin = System::Windows::Forms::Padding(2);
			this->btn_4->Name = L"btn_4";
			this->btn_4->Size = System::Drawing::Size(56, 61);
			this->btn_4->TabIndex = 5;
			this->btn_4->Text = L"4";
			this->btn_4->UseVisualStyleBackColor = true;
			this->btn_4->Click += gcnew System::EventHandler(this, &MyForm::btn_4_Click);
			// 
			// btn_c
			// 
			this->btn_c->Location = System::Drawing::Point(187, 192);
			this->btn_c->Margin = System::Windows::Forms::Padding(2);
			this->btn_c->Name = L"btn_c";
			this->btn_c->Size = System::Drawing::Size(56, 61);
			this->btn_c->TabIndex = 12;
			this->btn_c->Text = L"C";
			this->btn_c->UseVisualStyleBackColor = true;
			this->btn_c->Click += gcnew System::EventHandler(this, &MyForm::btn_c_Click);
			// 
			// btn_9
			// 
			this->btn_9->Location = System::Drawing::Point(126, 192);
			this->btn_9->Margin = System::Windows::Forms::Padding(2);
			this->btn_9->Name = L"btn_9";
			this->btn_9->Size = System::Drawing::Size(56, 61);
			this->btn_9->TabIndex = 11;
			this->btn_9->Text = L"9";
			this->btn_9->UseVisualStyleBackColor = true;
			this->btn_9->Click += gcnew System::EventHandler(this, &MyForm::btn_9_Click);
			// 
			// btn_8
			// 
			this->btn_8->Location = System::Drawing::Point(65, 192);
			this->btn_8->Margin = System::Windows::Forms::Padding(2);
			this->btn_8->Name = L"btn_8";
			this->btn_8->Size = System::Drawing::Size(56, 61);
			this->btn_8->TabIndex = 10;
			this->btn_8->Text = L"8";
			this->btn_8->UseVisualStyleBackColor = true;
			this->btn_8->Click += gcnew System::EventHandler(this, &MyForm::btn_8_Click);
			// 
			// btn_7
			// 
			this->btn_7->Location = System::Drawing::Point(4, 192);
			this->btn_7->Margin = System::Windows::Forms::Padding(2);
			this->btn_7->Name = L"btn_7";
			this->btn_7->Size = System::Drawing::Size(56, 61);
			this->btn_7->TabIndex = 9;
			this->btn_7->Text = L"7";
			this->btn_7->UseVisualStyleBackColor = true;
			this->btn_7->Click += gcnew System::EventHandler(this, &MyForm::btn_7_Click);
			// 
			// btn_d
			// 
			this->btn_d->Location = System::Drawing::Point(187, 258);
			this->btn_d->Margin = System::Windows::Forms::Padding(2);
			this->btn_d->Name = L"btn_d";
			this->btn_d->Size = System::Drawing::Size(56, 61);
			this->btn_d->TabIndex = 16;
			this->btn_d->Text = L"D";
			this->btn_d->UseVisualStyleBackColor = true;
			this->btn_d->Click += gcnew System::EventHandler(this, &MyForm::btn_d_Click);
			// 
			// btn_hash
			// 
			this->btn_hash->Location = System::Drawing::Point(126, 258);
			this->btn_hash->Margin = System::Windows::Forms::Padding(2);
			this->btn_hash->Name = L"btn_hash";
			this->btn_hash->Size = System::Drawing::Size(56, 61);
			this->btn_hash->TabIndex = 15;
			this->btn_hash->Text = L"#";
			this->btn_hash->UseVisualStyleBackColor = true;
			this->btn_hash->Click += gcnew System::EventHandler(this, &MyForm::btn_hash_Click);
			// 
			// btn_0
			// 
			this->btn_0->Location = System::Drawing::Point(65, 258);
			this->btn_0->Margin = System::Windows::Forms::Padding(2);
			this->btn_0->Name = L"btn_0";
			this->btn_0->Size = System::Drawing::Size(56, 61);
			this->btn_0->TabIndex = 14;
			this->btn_0->Text = L"0";
			this->btn_0->UseVisualStyleBackColor = true;
			this->btn_0->Click += gcnew System::EventHandler(this, &MyForm::btn_0_Click);
			// 
			// btn_ast
			// 
			this->btn_ast->Location = System::Drawing::Point(4, 258);
			this->btn_ast->Margin = System::Windows::Forms::Padding(2);
			this->btn_ast->Name = L"btn_ast";
			this->btn_ast->Size = System::Drawing::Size(56, 61);
			this->btn_ast->TabIndex = 13;
			this->btn_ast->Text = L"*";
			this->btn_ast->UseVisualStyleBackColor = true;
			this->btn_ast->Click += gcnew System::EventHandler(this, &MyForm::btn_ast_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Location = System::Drawing::Point(9, 10);
			this->tabControl1->Margin = System::Windows::Forms::Padding(2);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(425, 581);
			this->tabControl1->TabIndex = 17;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->loadFromFileButton);
			this->tabPage2->Controls->Add(this->richTextBox1);
			this->tabPage2->Controls->Add(this->treeView1);
			this->tabPage2->Controls->Add(this->btn_pop);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Margin = System::Windows::Forms::Padding(2);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(2);
			this->tabPage2->Size = System::Drawing::Size(417, 555);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Test";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(284, 33);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(128, 96);
			this->richTextBox1->TabIndex = 3;
			this->richTextBox1->Text = L"";
			// 
			// treeView1
			// 
			this->treeView1->Location = System::Drawing::Point(4, 3);
			this->treeView1->Margin = System::Windows::Forms::Padding(2);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(275, 552);
			this->treeView1->TabIndex = 2;
			this->treeView1->NodeMouseDoubleClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &MyForm::treeView1_NodeMouseDoubleClick);
			// 
			// btn_pop
			// 
			this->btn_pop->Location = System::Drawing::Point(283, 3);
			this->btn_pop->Margin = System::Windows::Forms::Padding(2);
			this->btn_pop->Name = L"btn_pop";
			this->btn_pop->Size = System::Drawing::Size(62, 25);
			this->btn_pop->TabIndex = 1;
			this->btn_pop->Text = L"Populate";
			this->btn_pop->UseVisualStyleBackColor = true;
			this->btn_pop->Click += gcnew System::EventHandler(this, &MyForm::btn_pop_Click);
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->btn_d);
			this->tabPage1->Controls->Add(this->btn_1);
			this->tabPage1->Controls->Add(this->btn_hash);
			this->tabPage1->Controls->Add(this->btn_2);
			this->tabPage1->Controls->Add(this->btn_0);
			this->tabPage1->Controls->Add(this->btn_3);
			this->tabPage1->Controls->Add(this->btn_ast);
			this->tabPage1->Controls->Add(this->btn_a);
			this->tabPage1->Controls->Add(this->btn_c);
			this->tabPage1->Controls->Add(this->btn_4);
			this->tabPage1->Controls->Add(this->btn_9);
			this->tabPage1->Controls->Add(this->btn_5);
			this->tabPage1->Controls->Add(this->btn_8);
			this->tabPage1->Controls->Add(this->btn_6);
			this->tabPage1->Controls->Add(this->btn_7);
			this->tabPage1->Controls->Add(this->btn_b);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Margin = System::Windows::Forms::Padding(2);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(2);
			this->tabPage1->Size = System::Drawing::Size(417, 555);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"DTMFTest";
			// 
			// loadFromFileButton
			// 
			this->loadFromFileButton->Location = System::Drawing::Point(284, 135);
			this->loadFromFileButton->Name = L"loadFromFileButton";
			this->loadFromFileButton->Size = System::Drawing::Size(75, 23);
			this->loadFromFileButton->TabIndex = 4;
			this->loadFromFileButton->Text = L"From File";
			this->loadFromFileButton->UseVisualStyleBackColor = true;
			this->loadFromFileButton->Click += gcnew System::EventHandler(this, &MyForm::loadFromFileButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(445, 600);
			this->Controls->Add(this->tabControl1);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->tabControl1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		openFileDialog1->InitialDirectory = "c:\\";
		
		openFileDialog1->ShowDialog();
		MessageBox::Show(openFileDialog1->FileName);

	}

	private: System::Void btn_1_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(0);
	}
	private: System::Void btn_2_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(1);
	}
	private: System::Void btn_3_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(2);
	}
	private: System::Void btn_a_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(3);
	}
	private: System::Void btn_4_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(4);
	}
	private: System::Void btn_5_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(5);
	}
	private: System::Void btn_6_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(6);
	}
	private: System::Void btn_b_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(7);
	}
	private: System::Void btn_7_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(8);
	}
	private: System::Void btn_8_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(9);
	}
	private: System::Void btn_9_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(10);
	}
	private: System::Void btn_c_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(11);
	}
	private: System::Void btn_ast_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(12);
	}
	private: System::Void btn_0_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(13);
	}
	private: System::Void btn_hash_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(14);
	}
	private: System::Void btn_d_Click(System::Object^  sender, System::EventArgs^  e) {
		wBuffer->put(15);
	}
	private: System::Void btn_pop_Click(System::Object^  sender, System::EventArgs^  e) {
		FolderBrowserDialog folderBrowserDialog1;
		folderBrowserDialog1.ShowDialog();
		addFilesToListView(folderBrowserDialog1.SelectedPath);
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {		
	}
	private: System::Void treeView1_NodeMouseDoubleClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e)
	{
		//MessageBox::Show(e->Node->FullPath);
		System::Diagnostics::Process::Start(e->Node->FullPath);		
		//e->Node->Parent->Nodes->Add(TreeNode("hest"));
	}			 
private: System::Void loadFromFileButton_Click(System::Object^  sender, System::EventArgs^  e) 
{
	populateTreeViewFromFile();
}
};
}
