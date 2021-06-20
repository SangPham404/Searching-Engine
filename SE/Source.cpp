#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define SIZES -1
#define ELI 500
#define ELISIZE 700
#define NUMWENELI 300
#define COUNTFILE -1
#include <iostream>
#include <fstream>
#include <cstring>
#include <cwchar>
#include <vector>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <stdlib.h>
#include <sstream>
#include <codecvt>
using namespace std;
namespace fs = std::filesystem;
struct tube
{
	wstring datas;
	int cnt;
};
vector<tube> Stopwords;
struct node
{
	vector<tube> datak;
	wstring link;
};
struct Staic
{
	wstring link;
	int count;
	vector<int> datal;
	int sum = 0;
};
// Marsr
void merge(vector<tube>& arr, int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	//tube L[n1], R[n2];
	tube* L = new tube[n1];
	tube* R = new tube[n2];

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i].cnt >= R[j].cnt) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of
	// L[], if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(vector<tube>& arr, int l, int r) {
	if (l >= r) {
		return;//returns recursively
	}
	int m = l + (r - l) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);
	merge(arr, l, m, r);
}

//
bool invector(vector<tube>& ksl,wstring temp)
{
	for (int i = 0; i < ksl.size(); i++)
	{
		if (wcscmp(ksl[i].datas.c_str(), temp.c_str()) == 0)
		{
			ksl[i].cnt++;
			return true;
		}
	}
	return false;
}
bool invectorA(vector<tube>& ksl, wstring temp)
{
	for (int i = 0; i < ksl.size(); i++)
	{
		if (wcscmp(ksl[i].datas.c_str(), temp.c_str()) == 0)
		{
			
			return true;
		}
	}
	return false;
}
void sort(vector<tube>& ksl)
{
	for (int i = 0; i < ksl.size() - 1; i++)
	{
		for (int j = i + 1; j < ksl.size(); j++)
		{
			if (ksl[i].cnt < ksl[j].cnt)
			{
				tube temp = tube{ ksl[i].datas,ksl[i].cnt };
				ksl[i] = ksl[j];
				ksl[j] = temp;
			}
		}
	}
}
void GetSW()
{
	FILE* g;
	//_wfopen_s(&f, L"Stopwords.txt", L"r+");
	_wfopen_s(&g, L"Stopwords-enc.txt", L"w,ccs=UTF-8");
	//fstream k;
	//k.open("Stopwords-enc.txt", ios::out);
	std::wifstream f(L"Stopwords.txt", std::ios::binary);
	f.imbue(std::locale(f.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	wstring line;
	//vector<tube> ksl;

	while (!f.eof())
	{

		//wchar_t* as = new wchar_t[100];
		//fwscanf_s(f, as,100);
		std::getline(f, line);
		if (wcscmp(line.c_str(), L"") == 0) continue;
		wstring temp = L"";
		wstring temp1 = L"";
		for (int i = 0; i <line.length(); i++)
		{
			if (int(line[i]) == int(' '))
			{
				if (!invector(Stopwords, temp))
				{
					Stopwords.emplace_back(tube{ temp,1 });
					mergeSort(Stopwords,0,Stopwords.size()-1);
				}

				temp = L"";

			}
			else
			{
				temp = temp + wstring{ towlower(line[i]) };
				temp1 = temp1 + wstring{ towlower(line[i]) };
			}
		}

		//fwprintf_s(g,  temp1.c_str());
		//fwprintf_s(g, L"\n");

	}
	//cout << "[";
	//for (int i = 0; i < Stopwords.size(); i++)
	//{
	//	wcout << Stopwords[i].datas << ": " << Stopwords[i].cnt << ",";
	//	//fwprintf_s(g, L"%s : %d \n", ksl[i].datas.c_str(), ksl[i].cnt);
	//}
	//cout << "]" << endl;
	f.close();
	//fwprintf_s(g, L"%s\n", path_string.c_str());
	fwprintf_s(g, L"%s", L"[");
	for (int i = 0; i < Stopwords.size(); i++)
	{
		//wcout << ksl[i].datas << ": " << ksl[i].cnt << ",";
		//fwprintf_s(g, L"%s : %d,", ksl[i].datas.c_str(), ksl[i].cnt);
		if (wcscmp(Stopwords[i].datas.c_str(), L"\r") != 0)
			fwprintf_s(g, L"%s,", Stopwords[i].datas.c_str());
	}
	fwprintf(g, L"%s\n", L"]");
	fclose(g);
	//k.close();
	//fclose(g);

}
bool Comma(wchar_t inp)
{
	for (int i = 33; i <47; i++)

	{
		if(i!=39)
		if (int(inp) == i)return true;
	}
	for (int i = 58; i <= 64; i++)
	{
		if (int(inp) == i)return true;
	}
	for (int i = 91; i <= 96; i++)
	{
		if (int(inp) == i)return true;
	}
	for (int i = 123; i <= 126; i++)
	{
		if (int(inp) == i)return true;
	}
	for (int i = 147; i <= 148; i++)
	{
		if (int(inp) == i)return true;
	}
	if (int(inp)== int ("\r"))return true;
	return false;
}
vector<tube> Dupcate(vector<tube>& ksl)
{
	ksl.erase(ksl.begin() +ELI, ksl.begin() + ksl.size() - 1);
		return ksl;
}
void Encode(wstring pathin,wstring fileout,vector<tube> &cata)
{
	FILE *g;
	
	std::wstring path = pathin;
	/* wstring name[2][3000];*/
	//std::wifstream f("Hask.txt");
	_wfopen_s(&g,fileout.c_str(), L"w+,ccs=UTF-8");
	int count = 0;
	for (const auto& entry : fs::directory_iterator(path))
	{
				//wstring path12 = L"C:/Users/Sang/Desktop/Search engine/SearchEngine/SE/Nhac/";
		vector<tube> ksl;
		if (count == SIZES)break;
		//if (count == SIZES) break;
		//if (ksl.size()>= NUMWENELI ) ksl = Dupcate(ksl);
		filesystem::path path1{ entry.path() };
		std::wstring path_string{ path1.wstring() };
		wcout << path_string;
		std::wifstream f(path_string, std::ios::binary);
		//std::wifstream f(L"Hask.txt", std::ios::binary);
		f.imbue(std::locale(f.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));
		if (!f.is_open()) {
			std::cout << "failed to open " << '\n';
			continue;
		}
		 
		
		//_wfopen_s(&f, path_string.c_str(), L"r+");
		//_wfopen_s(&f, L"Hask.txt", L"r+");
		
		
		
		//_wfopen_s(&g, (path_string + L".inp").c_str(), L"w+");
		//fstream k;
		//k.open("Stopwords-enc.txt", ios::out);
		wstring line;
		

		while (!f.eof())
		{
			
			//wchar_t* as;
			
			{
				//std::wstring s;
				std::getline(f, line);
				
			}
		
			//std::getline(f, line);
			//wchar_t* as=new wchar_t[1000];
			//wcscpy_s(as,1000, L"");
			//fwscanf_s(f, as,100);
			//if (fgetws(as, 1000, f) != NULL) fputws(as, stdout);
			//fwscanf_s(f, L"%[^]s", as,_countof(as));
			//
			//as=fgetws(lam, 1000, f);
			//fgetws(as, 1000, f);
			if (wcscmp(line.c_str(), L"") == 0) continue;
			wstring temp = L"";
			//wstring temp1 = L"";
			//wcout << u8 line << endl;
			for (int i = 0; i < line.length()+1; i++)
			{
				if (int(line[i]) == int(' ')||int(line[i])==0 ||Comma(line[i]))
				{
					if (!invectorA(Stopwords, temp)&& (wcscmp(temp.c_str(), L"") != 0))
					//if (wcscmp(temp.c_str(), L"") != 0)
					{
						if (!invector(ksl, temp))
						{
							ksl.emplace_back(tube{ temp,1 });
							//sort(ksl);
						}
						else
						{
							sort(ksl);
							//mergeSort(ksl, 0, ksl.size()-1);
						}
						//wcout << temp << " " << endl;
						
					}
					temp = L"";
				}
				else
				{
					//if(!Comma(line[i]))
					temp = temp + wstring{ towlower(line[i]) };
					//temp1 = temp1 + wstring{ line[i] };
				}
			}

			//fwprintf_s(g,  temp1.c_str());
			//fwprintf_s(g, L"\n");

		}
		//cout << "[";
		
		//cout << "]" << endl;
		f.close();
		//k.close();int n = ksl.size();
		
		
		fwprintf_s(g, L"%s\n", path_string.c_str());
		fwprintf_s(g, L"%s", L"[");
		for (int i = 0; i < ksl.size(); i++)
		{
			//wcout << ksl[i].datas << ": " << ksl[i].cnt << ",";
			//fwprintf_s(g, L"%s : %d,", ksl[i].datas.c_str(), ksl[i].cnt);
			if (wcscmp(ksl[i].datas.c_str(), L"\r") != 0)
			{
				if (!invector(cata, ksl[i].datas))
				{
					cata.emplace_back(tube{ ksl[i].datas,1 });
					//sort(ksl);
				}
				else
				{
					sort(cata);
					//mergeSort(ksl, 0, ksl.size()-1);
				}
				if (cata.size() > ELISIZE) cata = Dupcate(cata);
				fwprintf_s(g, L"%s,", ksl[i].datas.c_str());
			}
		}
		fwprintf(g, L"%s\n", L"]");
		
		cout << "---- Completed -- "<<count << endl;
		++count;
	}
	fclose(g);
}
wstring Search()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	wchar_t wstr[1000];
	
	char mb_str[1000 * 3 + 1];

	unsigned long read;
	void* con = GetStdHandle(STD_INPUT_HANDLE);

	ReadConsole(con, wstr, 1000, &read, NULL);

	int size = WideCharToMultiByte(CP_UTF8, 0, wstr, read, mb_str, sizeof(mb_str), NULL, NULL);
	mb_str[size] = 0;

	std::printf("ENTERED: %s\n", mb_str);
	wstring line;
	for (int i = 0; int(wstr[i]) != int('\r'); i++)
	{
		line += wstring{ towlower(wstr[i]) };
	}
	return line;

}
vector<tube> LineToTube(wstring line )
{
	vector<tube> iaso;
	wstring temp = L"";
	for (int i = 0; i < line.length() + 1; i++)
	{
		if (int(line[i]) == int(' ') || int(line[i]) == 0 || Comma(line[i]))
		{
			if (!invectorA(Stopwords, temp) && (wcscmp(temp.c_str(), L"") != 0))
				//if (wcscmp(temp.c_str(), L"") != 0)
			{
				if (!invector(iaso, temp))
				{
					iaso.emplace_back(tube{ temp,1 });
					//sort(ksl);
				}
				else
				{
					sort(iaso);
					//mergeSort(ksl, 0, ksl.size()-1);
				}
				//wcout << temp << " " << endl;

			}
			temp = L"";
		}
		else
		{
			//if(!Comma(line[i]))
			temp = temp + wstring{ towlower(line[i]) };
			//temp1 = temp1 + wstring{ line[i] };
		}
	}
	return iaso;
}
int FindPlace(vector<tube>& ksl,wstring temp)
{
	for (int i = 0; i < ksl.size(); i++)
	{
		if (wcscmp(ksl[i].datas.c_str(), temp.c_str()) == 0)
		{
			return i;
		}
	}
	return -1;
}
void Output(wstring link)
{
	wcout << link << endl;
}
void Display(wstring link)
{
	wstring kal = L"";
	for (int i = 0; i < link.length()-1; i++)
	{
		kal += link[i];
	}
	std::wifstream f(kal, std::ios::binary);
	//std::wifstream f(L"Hask.txt", std::ios::binary);
	f.imbue(std::locale(f.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));
	wstring line;
	while (!f.eof())
	{
		getline(f, line);
		//wcout << line << endl;
		//wchar_t wstr[1000];

		char mb_str[1000 * 3 + 1];

		unsigned long read=line.length();
		//void* con = GetStdHandle(STD_INPUT_HANDLE);

		//ReadConsole(con, line.c_str(), 1000, &read, NULL);

		int size = WideCharToMultiByte(CP_UTF8, 0, line.c_str(), read, mb_str, sizeof(mb_str), NULL, NULL);
		mb_str[size] = 0;

		if(strcmp(mb_str,"")!=0)
		std::printf("----> %s\n", mb_str);
	}
}
void mergever2(vector<Staic>& arr, int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	//tube L[n1], R[n2];
	Staic * L = new Staic[n1];
	Staic* R = new Staic[n2];

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i].count >= R[j].count) {
			if (L[i].count == R[j].count)
			{
				if (L[i].sum < R[j].sum)
				{
					arr[k] = L[i];
					i++;
				}
				else
				{
					arr[k] = R[j];
					j++;
				}
			}
			else
			{
				arr[k] = L[i];
				i++;
			}
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of
	// L[], if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSortver2(vector<Staic>& arr, int l, int r) {
	if (l >= r) {
		return;//returns recursively
	}
	int m = l + (r - l) / 2;
	mergeSortver2(arr, l, m);
	mergeSortver2(arr, m + 1, r);
	mergever2(arr, l, m, r);
}
void ReadFiletoTube(vector<tube>&ksl,wstring namefile)
{
	std::wifstream f(namefile, std::ios::binary);
	f.imbue(std::locale(f.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	wstring linelink,linetube;
	vector<node> storegate;
	while (!f.eof())
	{
		getline(f, linelink);
		if (wcscmp(linelink.c_str(), L"") == 0) break;
		getline(f, linetube);
		wstring temp = L"";
		vector<tube> temptube;
		for (int i = 1; i < linetube.length(); i++)
		{
			if (Comma(linetube[i]))
			{
				temptube.emplace_back(tube{ temp,1 });
				temp = L"";
			}
			else
			{
				temp += wstring{ linetube[i] };
			}
		}
		storegate.emplace_back(node{ temptube,linelink });
		temptube.clear();
	}
	vector<Staic> SortTakc;
	for (int i = 0; i < storegate.size(); i++)
	{
		vector<int> temp;
		int sum = 0;
		int count = 0;
		for (int j = 0; j < ksl.size(); j++)
		{
			int n = FindPlace(storegate[i].datak, ksl[j].datas);
			if ((n != -1  )&&(n<=storegate[i].datak.size()/2))
			{
				sum += n;
				temp.emplace_back(n);
				++count;
			}
		}
		if (count!=0)
		SortTakc.emplace_back(Staic{ storegate[i].link ,count,temp,sum });
		temp.clear();
		/*if (count !=0)
		{
			Output(storegate[i].link);
			Display(storegate[i].link);
		}*/
	}
	mergeSortver2(SortTakc, 0, SortTakc.size() - 1);
	int k = SortTakc.size();
	if (k > 10) k = 10;
	for (int i = 0; i <k; i++)
	{
		Output(SortTakc[i].link);
		Display(SortTakc[i].link);

	}

}

void ReadSW(vector<tube>& ksl, wstring filename)
{
	std::wifstream f(filename, std::ios::binary);
	f.imbue(std::locale(f.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	wstring  linetube;
	getline(f, linetube);
	wstring temp = L"";
	
	for (int i = 1; i < linetube.length(); i++)
	{
		if (Comma(linetube[i]))
		{
			ksl.emplace_back(tube{ temp,1 });
			temp = L"";
		}
		else
		{
			temp += wstring{ linetube[i] };
		}

	}
}
void WriteSystem(FILE*&g,vector<tube>& cata,wstring name)
{
	
	fwprintf_s(g, L"%s\n", name.c_str());
	fwprintf_s(g, L"%s", L"[");
	for (int i = 0; i < cata.size(); i++)
	{
		//wcout << ksl[i].datas << ": " << ksl[i].cnt << ",";
		//fwprintf_s(g, L"%s : %d,", ksl[i].datas.c_str(), ksl[i].cnt);
		if (wcscmp(cata[i].datas.c_str(), L"\r") != 0)
			fwprintf_s(g, L"%s,", cata[i].datas.c_str());
	}
	fwprintf(g, L"%s\n", L"]");
	
	cata.clear();
}
wstring FindCata(vector<tube> &search)
{
	std::wifstream f(L"SysSe.txt", std::ios::binary);
	f.imbue(std::locale(f.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	wstring linelink, linetube;
	vector<node> storegate;
	while (!f.eof())
	{
		getline(f, linelink);
		if (wcscmp(linelink.c_str(), L"") == 0) break;
		getline(f, linetube);
		wstring temp = L"";
		vector<tube> temptube;
		for (int i = 1; i < linetube.length(); i++)
		{
			if (Comma(linetube[i]))
			{
				temptube.emplace_back(tube{ temp,1 });
				temp = L"";
			}
			else
			{
				temp += wstring{ linetube[i] };
			}
		}
		storegate.emplace_back(node{ temptube,linelink });
		temptube.clear();
	}
	vector<Staic> SortTakc;
	for (int i = 0; i < storegate.size(); i++)
	{
		vector<int> temp;
		int sum = 0;
		int count = 0;
		for (int j = 0; j < search.size(); j++)
		{
			int n = FindPlace(storegate[i].datak, search[j].datas);
			if ((n != -1) && (n <= storegate[i].datak.size() / 2))
			{
				sum += n;
				temp.emplace_back(n);
				++count;
			}
		}
		if (count != 0)
		{
			wstring Aname = L"";
			for (int j = 0; j < storegate[i].link.length(); j++)
			{
				if (storegate[i].link[j] != '\r')
				{
					Aname += storegate[i].link[j];
				}
			}
			storegate[i].link = Aname;
			SortTakc.emplace_back(Staic{ storegate[i].link ,count,temp,sum });
		}
		temp.clear();
		/*if (count !=0)
		{
			Output(storegate[i].link);
			Display(storegate[i].link);
		}*/
	}
	mergeSortver2(SortTakc, 0, SortTakc.size() - 1);
	/*int k = SortTakc.size();
	if (k > 10) k = 10;
	for (int i = 0; i < k; i++)
	{
		Output(SortTakc[i].link);
		Display(SortTakc[i].link);

	}*/
	return SortTakc[0].link;

}
void FullFileEnc()
{
	vector<tube> cata;
	{
		FILE* g;
		_wfopen_s(&g, L"SysSe.txt", L"w+,ccs=UTF-8");
		std::wstring path = L"C:/Users/Sang/Desktop/Search engine/VanBangTV/new train/";
		/* wstring name[2][3000];*/
		int count = 0;
		for (const auto& entry : fs::directory_iterator(path))
		{
			if (count == COUNTFILE)break;
			//std::wcout << entry.path() << std::endl;
			fs::path path1{ entry.path() };
			std::wstring path_string{ path1.wstring() };
			wcout << path_string << endl;
			wstring name = L"";
			int n;
			for (int i = path_string.length(); path_string[i] != L'/'; i--)
			{
				n = i;
			}
			for (int i = n; i < path_string.length(); i++)
			{
				if (path_string[i] != ' ')
					name += path_string[i];
			}
			name += L".txt";
			wcout << name << endl;
			Encode(path_string + L"/", name, cata);
			WriteSystem(g, cata, name);
			++count;
		}
		fclose(g);
	}
}
int main()
{
	//GetSW();
	ReadSW(Stopwords, L"Stopwords-enc.txt");
	
	//FullFileEnc();

	vector<tube>ksl = LineToTube(Search());
	ReadFiletoTube(ksl,FindCata(ksl));
	return 0;
}