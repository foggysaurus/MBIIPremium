#include "ReadWrite.h"

ReadWrite::ReadWrite(Input* _input) : input(_input)
{
	ReadOpenJK();
	ReadConfig();
}
ReadWrite::~ReadWrite()
{

}
std::wstring ReadWrite::StringToWString(const std::string& str) 
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
	std::wstring wstr(size_needed, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], size_needed);
	return wstr;
}

std::string ReadWrite::WStringToString(const std::wstring& wstr) 
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), NULL, 0, NULL, NULL);
	std::string str(size_needed, '\0');
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), &str[0], size_needed, NULL, NULL);
	return str;
}
bool ReadWrite::CreateDirectoryIfNeeded(const std::wstring& path)
{
	std::wstring directoryPath = path.substr(0, path.find_last_of(L"\\"));

	if (!CreateDirectoryW(directoryPath.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		return true;
	}
	return false;
}
std::wstring ReadWrite::GetCurrentDirectoryWString()
{
	constexpr DWORD MAX_BUFFER_SIZE = MAX_PATH;
	wchar_t buffer[MAX_BUFFER_SIZE];

	DWORD result = GetCurrentDirectoryW(MAX_BUFFER_SIZE, buffer);
	if (result == 0) 
	{
		throw std::runtime_error("Failed to get current directory.");
	}
	return std::wstring(buffer);
}
void ReadWrite::InsertBind(const std::string& line, const MyBindsEnum& bind)
{
	size_t firstQuotePos = line.find('"');
	std::string buttonValue;
	for (int i = firstQuotePos + 1; i < line.size(); i++)
	{
		if (line[i] != '"')
			buttonValue += line[i];
		else
			break;
	}



	auto it = mbiiKeysLookupTable.find(buttonValue);

	if (it != mbiiKeysLookupTable.end())
	{
		std::pair<MyBindsEnum, Bind> pair;
		Bind b;
		b.name = buttonValue;
		b.id = it->second;
		pair.first = bind;
		pair.second = b;
		myBinds.insert(pair);
	}
}
void ReadWrite::ReadOpenJK()
{
	gameDataPath = GetCurrentDirectoryWString();
	std::wstring openJKPath = gameDataPath + L"\\MBII\\openjk.cfg";
	std::string filename(openJKPath.begin(), openJKPath.end());
	std::ifstream infile(filename);
	std::string line;

	if (infile.is_open())
	{
		while (std::getline(infile, line))
		{
			if (line.find("\"+attack\"") != std::string::npos)
			{
				InsertBind(line, MyBindsEnum::ATTACK_BIND);
			}
			else if (line.find("\"+altattack\"") != std::string::npos)
			{
				InsertBind(line, MyBindsEnum::ALTATTACK_BIND);
			}
			else if (line.find("\"+forward\"") != std::string::npos)
			{
				InsertBind(line, MyBindsEnum::W_BIND);
			}
			else if (line.find("\"+moveleft\"") != std::string::npos)
			{
				InsertBind(line, MyBindsEnum::A_BIND);
			}
			else if (line.find("\"+moveright\"") != std::string::npos)
			{
				InsertBind(line, MyBindsEnum::D_BIND);
			}
			else if (line.find("\"+back\"") != std::string::npos)
			{
				InsertBind(line, MyBindsEnum::S_BIND);
			}
			else if (line.find("\"+moveup\"") != std::string::npos)
			{
				InsertBind(line, MyBindsEnum::JUMP_BIND);
			}
			else if (line.find("\"+speed\"") != std::string::npos)
			{
				InsertBind(line, MyBindsEnum::SHIFT_BIND);
			}
			else if (line.find("\"+movedown\"") != std::string::npos)
			{
				InsertBind(line, MyBindsEnum::CROUCH_BIND);
			}
		}
	}
}
void ReadWrite::AppendLine(const std::string& lineToAppend, const std::wstring& filePath)
{

	std::string filename(filePath.begin(), filePath.end());
	std::string line;
	bool isEmpty = true;


	std::ofstream file(filePath, std::ios::app);
	if (file.is_open())
	{
		file << lineToAppend << std::endl;
		file.close();
	}

}
void ReadWrite::WriteNameList()
{
	unsigned char maxNameLength = 60;
	std::string filename(playerListPath.begin(), playerListPath.end());
	std::ofstream file(playerListPath, std::ios::out | std::ios::trunc);
	// Open in write mode and truncate 
	if (file.is_open())
	{
		for (auto&pair: nameList)
		{
			int extraSpacesAmount = maxNameLength - pair.first.size();
			std::string spaces(extraSpacesAmount, ' ');
			std::string line = pair.first + spaces +pair.second;

			file << line << std::endl;
		}
		file.close();
	}
}
void ReadWrite::ReadNameList()
{
	std::string filename(playerListPath.begin(), playerListPath.end());
	std::ifstream file(playerListPath);
	std::string line;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			size_t spacesLocation = line.find("  ");
			std::string key;
			std::string value;
			if (spacesLocation != std::string::npos)
			{
				key = line.substr(0, spacesLocation);
			}
			size_t spacesLastLocation = line.rfind("  ");
			if (spacesLastLocation != std::string::npos)
			{
				value = line.substr(spacesLastLocation+2);
			}
			nameList[key] = value;
		} 

		file.close();
	}
}
void ReadWrite::AppendUniqueLine(const std::string& lineToAppend, const std::wstring& filePath)
{
	std::string filename(filePath.begin(), filePath.end());
	std::ifstream infile(filename);
	std::string line;
	std::vector<std::string> lines;

	if (infile.is_open())
	{
		while (std::getline(infile, line))
		{
			if (line == "")
				continue;
			lines.push_back(line);
		}
	}

	for (auto& l : lines)
	{
		if (l == lineToAppend)
			return;
	}

	std::ofstream file(filePath, std::ios::app);
	if (file.is_open())
	{
		file << lineToAppend << std::endl;
		file.close();
	}
}
std::string ExtractStringFromThisSeparator(const std::string& input, const char& separatorOpen, const char& separatorClose)
{
	size_t start = input.find(separatorOpen);
	size_t end = input.find(separatorClose);

	if (start != std::string::npos && end != std::string::npos && start < end) {
		// Extract the substring between the brackets
		return input.substr(start + 1, end - start - 1);
	}
	else
		return "";
}
std::string ReadWrite::ParseKeyValues(const std::string& str)
{
	std::string edit = ExtractStringFromThisSeparator(str, '[', ']');
	if (edit.empty())
		return "";
	return edit;
}
std::vector<float> ReadWrite::ParseColorValues(const std::string& str)
{
	std::string edit = ExtractStringFromThisSeparator(str, '[', ']');
	std::vector<float> values(4);
	if (edit.empty())
		return values;


	std::istringstream iss(edit.c_str());
	std::string token;

	int index = 0;
	while (std::getline(iss, token, ',') && index < 4)
	{
		values[index] = stof(token);
		index++;
	}
	return values;
}
void ReadWrite::ReadConfig()
{
	hackConfigPath = hackLocationPath + L"\\epicHax\\config.txt";
	playerListPath = hackLocationPath + L"\\epicHax\\playerList.txt";
	signaturesPath = hackLocationPath + L"\\epicHax\\signatures.txt";
	isHitscanPath = hackLocationPath + L"\\epicHax\\isHitscan.txt";
	mapFolderPath = hackLocationPath + L"\\epicHax\\maps\\";
	onPlayerDeathMessagePath = hackLocationPath + L"\\epicHax\\onKillMessage.txt";

	CreateDirectoryW(LPCWSTR((hackLocationPath + L"\\epicHax").c_str()), NULL);

	std::wifstream infile(hackConfigPath);
	std::wstring line;

	static int coutner = 0;
	coutner++;

	//keys.clear();
	if (infile.is_open())
		while (std::getline(infile, line))
		{
			//std::string lineStr;
			std::string value;
			std::string key;

			if (line.empty())
				continue;
			size_t nameStartPos = line.find(L":");

			value = WStringToString(line.substr(nameStartPos + 2));
			key = WStringToString(line.substr(0, nameStartPos));

			if (key.find("_keys") != std::string::npos)
			{
				if (key.find("Aim") != std::string::npos) { input->GetKeys(MyKeysEnum::AIM_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("TK") != std::string::npos) { input->GetKeys(MyKeysEnum::TK_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("Exit") != std::string::npos) { input->GetKeys(MyKeysEnum::EXIT_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("friend") != std::string::npos) { input->GetKeys(MyKeysEnum::MAKE_FRIEND_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("target") != std::string::npos) { input->GetKeys(MyKeysEnum::MAKE_TARGET_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("Save map") != std::string::npos) { input->GetKeys(MyKeysEnum::SAVE_MAP_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("Add new cell") != std::string::npos) { input->GetKeys(MyKeysEnum::ADD_CELL_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("Delete cell_") != std::string::npos) { input->GetKeys(MyKeysEnum::DELETE_CELL_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("Switch editor-normal mode") != std::string::npos) { input->GetKeys(MyKeysEnum::SWITCH_MODE_EDITOR_NORMAL_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("Delete island_") != std::string::npos) { input->GetKeys(MyKeysEnum::DELETE_ISLAND_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("Switch cell type left_") != std::string::npos) { input->GetKeys(MyKeysEnum::SWITCH_CELL_TYPE_LEFT_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("Switch cell type right_") != std::string::npos) { input->GetKeys(MyKeysEnum::SWITCH_CELL_TYPE_RIGHT_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("Reload map_") != std::string::npos) { input->GetKeys(MyKeysEnum::RELOAD_MAP_KEYS, ParseKeyValues(value)); continue; }
				else if (key.find("Create elevator_") != std::string::npos) { input->GetKeys(MyKeysEnum::CREATE_ELEVATOR_KEYS, ParseKeyValues(value)); continue; }
			}
			else if (key.find("configFlags") != std::string::npos)
			{
				configFlags = std::stoi(value);
			}
			else if (key.find("wallHackFlags") != std::string::npos)
			{
				wallHackFlags = std::stoi(value);
			}
			else if (key.find("botConfigFlags") != std::string::npos)
			{
				botConfigFlags = std::stoi(value);
			}
			else if (key.find("_col") != std::string::npos)
			{
				if (key.find("allies") != std::string::npos) { colors[Colors::COL_ALLIES] = ParseColorValues(value); continue; }
				else if (key.find("enemies") != std::string::npos) { colors[Colors::COL_ENEMIES] = ParseColorValues(value); continue; }
				else if (key.find("friends") != std::string::npos) { colors[Colors::COL_FRIENDS] = ParseColorValues(value); continue; }
				else if (key.find("targets") != std::string::npos) { colors[Colors::COL_TARGETS] = ParseColorValues(value); continue; }
				else if (key.find("prediction point") != std::string::npos) { colors[Colors::COL_PREDICTION_POINT] = ParseColorValues(value); continue; }
			}
			else if (key.find("_meshcol") != std::string::npos)
			{
				if (key.find("walkable") != std::string::npos) { meshColors[MeshColors::WALKABLE_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("edge_") != std::string::npos) { meshColors[MeshColors::EDGE_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("edge2_") != std::string::npos) { meshColors[MeshColors::EDGE2_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("edge3_") != std::string::npos) { meshColors[MeshColors::EDGE3_COLOR] = ParseColorValues(value); continue; } 
				else if (key.find("mover_meshcol") != std::string::npos) { meshColors[MeshColors::MOVER_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("banned_") != std::string::npos) { meshColors[MeshColors::BANNED_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("mycell_") != std::string::npos) { meshColors[MeshColors::MY_CELL_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("elevator_cell_meshcol") != std::string::npos) { meshColors[MeshColors::ELEVATOR_CELL_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("bridge_cell_meshcol") != std::string::npos) { meshColors[MeshColors::BRIDGE_CELL_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("column_cell_meshcol") != std::string::npos) { meshColors[MeshColors::COLUMN_CELL_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("jump_cell_meshcol") != std::string::npos) { meshColors[MeshColors::JUMP_CELL_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("down_only_cell_meshcol") != std::string::npos) { meshColors[MeshColors::DOWN_PNLY_CELL_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("up_only_cell_meshcol") != std::string::npos) { meshColors[MeshColors::UP_PNLY_CELL_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("highcost_meshcol") != std::string::npos) { meshColors[MeshColors::HIGHCOST_CELL_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("elevator_button_meshcol") != std::string::npos) { meshColors[MeshColors::ELEVATOR_BUTTON_CELL_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("elevator_button_2_meshcol") != std::string::npos) { meshColors[MeshColors::ELEVATOR_BUTTON_2_CELL_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("elevator_button_call_meshcol") != std::string::npos) { meshColors[MeshColors::ELEVATOR_BUTTON_CALL_CELL_COLOR] = ParseColorValues(value); continue; }
			}
			else if (key.find("_graphcol") != std::string::npos)
			{
				if (key.find("tile_graphcol") != std::string::npos) { graphColors[GraphColors::TILE_GRAPH_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("connector_graphcol") != std::string::npos) { graphColors[GraphColors::CONNECTOR_GRAPH_COLOR] = ParseColorValues(value); continue; }
				else if (key.find("bbox_graphcol") != std::string::npos) { graphColors[GraphColors::BBOX_GRAPH_COLOR] = ParseColorValues(value); continue; }
			}
			else if (key.find("meshTransparency") != std::string::npos)
			{
				meshTransparency = std::stof(value);
			}
			else if (key.find("graphTransparency") != std::string::npos)
			{
				graphTransparency = std::stof(value);
			}
		}

	input->GetAllPossibleKeys();

	if (meshTransparency != 0)
		for (auto&mCol: meshColors)
		{
			mCol.second[3] = meshTransparency;
		}
	if (graphTransparency != 0)
		for (auto& gCol : graphColors)
		{
			gCol.second[3] = graphTransparency;
		}

	if (meshColors.size() < (int)MeshColors::COUNT_COLOR)
	{
		int a = 3;
	}

	infile.close();

	OnPlayerDeathMessage();
}
bool ReadWrite::ReadSignatureList(std::unordered_map <AddressesNames, uintptr_t>& addressesMap)
{
	std::string filename(signaturesPath.begin(), signaturesPath.end());
	std::ifstream infile(filename);
	std::string line;

	if (infile.is_open())
	{
		int counter = 0;
		while (std::getline(infile, line))
		{
			size_t place = line.find(" ");
			if (place == std::string::npos)
				continue;
			else
				counter++;
			std::string first = line.substr(0, place);
			std::string second = line.substr(place + 1);
			addressesMap[(AddressesNames)std::stoi(first)] = std::stoi(second);
		}

		if (counter == (int)AddressesNames::ADD_ENUM_COUNT)
		{
			return true;
		}
		else
			return false;
	}

	return false;
}
void ReadWrite::OnPlayerDeathMessage()
{
	std::string filename(onPlayerDeathMessagePath.begin(), onPlayerDeathMessagePath.end());
	std::ifstream file(onPlayerDeathMessagePath);
	std::string line;

	onKillMessages.clear();

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			onKillMessages.push_back(line);
		}

		file.close();
	}
}