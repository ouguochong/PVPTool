#include <Windows.h>
#include <string>

#include "MainFRM.h"
#include "Definitions.h"

using namespace PVPTool;
using namespace std;

void Main(void)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MainFRM());
    Application::Exit();
}

// Sending Packets
extern void WINAPI msSendPacketA(__in LPCSTR lpPacketStr);
void SendPacket(String^ dataString)
{
	int Random = rand()%16;	
	String^ Packet = dataString;
	String^ Packet2 = Packet->Replace(L" ", String::Empty);
	String^ Packet3 = Packet2->Replace(L"*", Random.ToString("X"));
	LPCSTR StringA = (LPCSTR)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Packet3).ToPointer());
	msSendPacketA(StringA);
}

// Reading Pointer
unsigned long ReadPointer(unsigned long ulBase, int iOffset)
{
   __try { return *(unsigned long*)(*(unsigned long*)ulBase + iOffset); }
   __except (EXCEPTION_EXECUTE_HANDLER) { return 0; }
}

// Writing Pointer
bool WritePointer(unsigned long ulBase, int iOffset, int iValue)
{
   __try { *(int*)(*(unsigned long*)ulBase + iOffset) = iValue; return true; }
   __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

// =====================================================================
// =====================================================================
// Functions Protype
void ConvertSkillHex(int x);
void GetPVPMode(int x);
void GetKeyboardKey(int x);
void GetKeyboardKey2(int x);
void Teleport(int x, int y);

// Variables
int Skill;
int SkillLevel;

LPCSTR GameMode = "";
LPCSTR skillHEX = "";
DWORD KeyboardKey = VK_CONTROL; // give key a default value

bool KOExploitToggle = false;

int OptionValue = 1; // 1 == radioButton1, 2 = radioButton2
DWORD KeyboardKey2 = VK_CONTROL;
// =========

// ================
// 1 Hit KO Exploit

Void MainFRM::timer1_Tick(System::Object^  sender, System::EventArgs^  e)
{
	// Get current Skill
	Skill = System::Convert::ToInt32(comboBox1->SelectedIndex);
	ConvertSkillHex(Skill); // get current Skill's Hexidecimal
	// Get current Skill's Level
	SkillLevel = System::Convert::ToInt32(numericUpDown1->Value);
	// Get Game Mode
	GetPVPMode(System::Convert::ToInt32(comboBox2->SelectedIndex));
	// Get current Keyboard Key
	GetKeyboardKey(System::Convert::ToInt32(comboBox3->SelectedIndex));


	// Update Maximum Skill Level
	switch (Skill)
	{
	case 1: // Ice Breath
		numericUpDown1->Maximum = 20;
		break;
	case 2: // Fire Breath
		numericUpDown1->Maximum = 20;
		break;
	case 3: // Corkscrew Blow
		numericUpDown1->Maximum = 20;
		break;
	case 4: // Corkscrew Blow
		numericUpDown1->Maximum = 20;
		break;
	case 5: // Big Bang
		numericUpDown1->Maximum = 30;
		break;
	case 6: // Big Bang
		numericUpDown1->Maximum = 30;
		break;
	case 7: // Big Bang
		numericUpDown1->Maximum = 30;
		break;
	case 8: // Piercing Arrow
		numericUpDown1->Maximum = 30;
		break;

	default : numericUpDown1->Maximum = 30; // No Skill
	}
}

void ConvertSkillHex(int x)
{
	switch (x)
	{
	case 1:
		skillHEX = "28 8A 51 01 "; // EVAN's Fire Breath
		break;
	case 2:
		skillHEX = "59 FF 51 01 "; // EVAN's Fire Breath
		break;
	case 3:
		skillHEX = "CC D5 4D 00 "; // Infighter's CockScrew Blow
		break;
	case 4:
		skillHEX = "4B 6C E6 00 "; // Striker's CockScrew Blow
		break;
	case 5:
		skillHEX = "29 5D 20 00 "; // Fire_ArchMage's BigBang
		break;
	case 6:
		skillHEX = "C9 E3 21 00 "; // Ice_ArchMage's BigBang
		break;
	case 7:
		skillHEX = "69 6A 23 00 "; // Bishop's BigBang
		break;
	case 8:
		skillHEX = "09 26 31 00 "; // Cross-Bowmaster's Piercing Arrow
		break;
	}
}

void GetPVPMode(int x)
{
	switch (x)
	{
	case 0:
		GameMode = "77 35 94 00 "; // FFA / Team / CTF
		break;
	case 1:
		GameMode = "28 23 00 00 "; // Ice Knight
		break;
	}
}

void GetKeyboardKey(int x)
{
	switch (x)
	{
	case 0:
		KeyboardKey = VK_CONTROL; // Control
		break;
	case 1:
		KeyboardKey = VK_SHIFT; // Shift
		break;
	case 2:
		KeyboardKey = 0x43; // C
		break;
	case 3:
		KeyboardKey = 0x56; // V
		break;
	case 4:
		KeyboardKey = 0x42; // B
		break;
	default : KeyboardKey = VK_CONTROL;
	}
}

void SendKOPackets()
{
	array<Byte>^bytes = BitConverter::GetBytes(SkillLevel);
	char skillLevelx[2];
	sprintf(skillLevelx, "%02X", bytes[0]);

	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 01 00 00 00 00 00 00 00");
	Sleep(25);
	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 02 00 00 00 00 00 00 00");
	Sleep(25);
	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 03 00 00 00 00 00 00 00");
	Sleep(25);
    SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 04 00 00 00 00 00 00 00");
	Sleep(25);
    SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 05 00 00 00 00 00 00 00");
	Sleep(25);
    SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 06 00 00 00 00 00 00 00");
	Sleep(25);
    SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 07 00 00 00 00 00 00 00");
	Sleep(25);
    SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 08 00 00 00 00 00 00 00");
	Sleep(25);
	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 09 00 00 00 00 00 00 00");
	Sleep(25);
	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 0A 00 00 00 00 00 00 00");
	Sleep(25);
	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 0B 00 00 00 00 00 00 00");
	Sleep(25);
	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 0C 00 00 00 00 00 00 00");
	Sleep(25);
	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 0D 00 00 00 00 00 00 00");
	Sleep(25);
	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 0E 00 00 00 00 00 00 00");
	Sleep(25);
	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 0F 00 00 00 00 00 00 00");
	Sleep(25);
	SendPacket("35 00 " +  gcnew String(skillHEX) + gcnew String(skillLevelx) + " " + gcnew String(GameMode) + "00 00 00 00 00 10 00 00 00 00 00 00 00");
}

// =====================================================================

// =================

void KOExploitFunc()
{
	while (KOExploitToggle)
	{
		if(GetAsyncKeyState(KeyboardKey)&1)
		{
	        SendKOPackets();
		}
	}
	ExitThread(0);
}

Void MainFRM::checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (checkBox1->Checked)
	{
		if (comboBox1->Text == "" || comboBox2->Text == "" || comboBox3->Text == "")
		{
			MessageBox::Show("Your 'Skill', 'KeyBoard Key' or 'Game Mode' is empty");
			checkBox1->Checked = false;
			KOExploitToggle = false;
		}
		else
		{
		    KOExploitToggle = true;
		    NewThread(KOExploitFunc);
		}
	}
	else
	{
		KOExploitToggle = false;
	}
}


// ====================================================================

// =====================
// HP Exploit

Void MainFRM::timer2_Tick(System::Object^  sender, System::EventArgs^  e)
{
	if (radioButton1->Checked)
	{
		OptionValue = 1;
		panel1->Visible = true;
		panel2->Visible = false;
	}
	else if (radioButton2->Checked)
	{
		OptionValue = 2;
		panel1->Visible = false;
		panel2->Visible = true;
	}

	// Get Keyboard Key
	GetKeyboardKey2(comboBox4->SelectedIndex);

	// ====
	int CurrentHPValue;
	int DesiredHPValue;

	CurrentHPValue = ReadPointer(StatAddy, HPOffset);
	DesiredHPValue = System::Convert::ToInt32(numericUpDown2->Value);

	if (checkBox2->Checked)
	{
		WritePointer(SettingAddy, HPAlertOffset, 20);
		// Auto
		if (OptionValue == 1)
		{
			if (CurrentHPValue < DesiredHPValue)
			{
				Teleport(99999, 99999);
				Sleep(1000);
			}
		}
		// Manual
		else if (OptionValue == 2)
		{
			if(GetAsyncKeyState(KeyboardKey)&1)
		    {
	            Teleport(99999, 99999); 
				Sleep(1000);
		    } 
		}
	}
}

void GetKeyboardKey2(int x)
{
	switch (x)
	{
	case 0:
		KeyboardKey2 = VK_CONTROL; // Control
		break;
	case 1:
		KeyboardKey2 = VK_SHIFT; // Shift
		break;
	case 2:
		KeyboardKey2 = 0x43; // C
		break;
	case 3:
		KeyboardKey2 = 0x56; // V
		break;
	case 4:
		KeyboardKey2 = 0x42; // B
		break;
	default : KeyboardKey2 = VK_CONTROL;
	}
}

void Teleport(int x, int y)
{
	WritePointer(CharAddy, TeleXOffset, x);
	WritePointer(CharAddy, TeleYOffset, y);
	WritePointer(CharAddy, TeleOffset, 1);
}

// =====================================================================
// =====================================================================
Void MainFRM::suggestionsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	ShellExecute(NULL, "open", "http://www.gamersoul.com/forums/member.php?96764-deyi", NULL, NULL, SW_SHOWNORMAL);
}