#pragma once
#include <windows.h>
#include <Tlhelp32.h>
#include <iomanip>  
#include <chrono>
#include <vector>
#include <random>

#include "Vectors.h"

typedef float vec3_t[3];


class Utils
{
public:
	class Error
	{
	public:
		Error();
		~Error();

		static void ShowError(const wchar_t* errorMessage, const wchar_t* title = L"Error")
		{
			MessageBox(
				NULL,               // Handle to the owner window (NULL for no owner)
				errorMessage,       // The message to display
				title,            // The title of the message box
				MB_ICONERROR | MB_OK // Message box style: Error icon + OK button
			);
			return;
		}

	private:

	};
	class MrTimer
	{
	public:
		MrTimer() {}
		~MrTimer() {}
		void  Start()
		{
			m_StartTime = std::chrono::high_resolution_clock::now();
		}
		void  Stop()
		{
			elapsedContLockTimer = false;
			m_EndTime = std::chrono::high_resolution_clock::now();
		}
		//milliseconds
		double ElapsedMs()
		{
			return  std::chrono::duration_cast<std::chrono::milliseconds>(m_EndTime - m_StartTime).count();
		}
		double ElapsedCurrentMs()
		{
			return  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_StartTime).count();
		}
		//microseconds
		double ElapsedMcs()
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(m_EndTime - m_StartTime).count();
		}
		//goes on until Stop() is called
		double ElapsedContinuous()
		{
			if (!elapsedContLockTimer)
			{
				m_StartTime = std::chrono::high_resolution_clock::now();
				elapsedContLockTimer = true;
			}
			std::chrono::duration<double, std::milli> elapsed = std::chrono::high_resolution_clock::now() - m_StartTime;
			return elapsed.count();
		}
		//returns true when period value is reached
		bool IsElapsedPeriod(const float& period)
		{
			if (!elapsedContLockTimer)
			{
				m_StartTime = std::chrono::high_resolution_clock::now();
				elapsedContLockTimer = true;
			}
			std::chrono::duration<double, std::milli> elapsed = std::chrono::high_resolution_clock::now() - m_StartTime;
			if (elapsed.count() > period)
			{
				elapsedContLockTimer = false;
				return true;
			}
			else
				return false;

		}
		//returns average of specified number of repetitions
		float ElapsedAverage(const int& howOften)
		{
			static int frameCounter = 0;
			frameCounter++;
			float elTime = std::chrono::duration_cast<std::chrono::microseconds>(m_EndTime - m_StartTime).count();
			elapsedVals.push_back(elTime);
			if (elapsedVals.size() > howOften)
			{
				totalTime_f = 0;
				for (auto& val : elapsedVals)
				{
					totalTime_f += val;
				}
				totalTime_f /= howOften;
				elapsedVals.clear();
				elapsedVals.reserve(howOften);
				return totalTime_f;

			}
			return totalTime_f;
		}
		
		//static std::string ConvertTimeToString(const float& time, const int& decimalPoint)
		//{
		//	std::ostringstream stream;
		//	stream << std::fixed << std::setprecision(decimalPoint) << time;
		//	return stream.str();
		//}

		static std::string RemoveTrailingZeros(const float& time, const int& decimalPoint) 
		{
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(decimalPoint) << time; // Adjust precision if needed
			std::string result = oss.str();

			// Remove trailing zeros and potential trailing dot
			result.erase(result.find_last_not_of('0') + 1, std::string::npos);
			if (!result.empty() && result.back() == '.') {
				result.pop_back();
			}

			return result;
		}


		const char* timerName;
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime, m_EndTime;
		std::vector<double> elapsedVals;
		bool elapsedContLockTimer = false;
		float totalTime_f;
	};
	class MrGameTimer
	{
	public:
		static int gameTime;


		MrGameTimer() {}
		~MrGameTimer() {}
		void  Start(const uintptr_t & gameTime)
		{
			m_StartTime = gameTime;
		}
		void  Stop(const uintptr_t& gameTime)
		{
			elapsedContLockTimer = false;
			m_EndTime = gameTime;
		}

		double Elapsed()
		{
			return  m_EndTime - m_StartTime;
		}
		double ElapsedCurrent(const uintptr_t& gameTime)
		{
			return gameTime - m_StartTime;
		}

		//goes on until Stop() is called
		double ElapsedContinuous(const uintptr_t& gameTime)
		{
			//if (!elapsedContLockTimer)
			//{
			//	m_StartTime = *(int*)gameTimeAddress;
			//	elapsedContLockTimer = true;
			//}
			//std::chrono::duration<double, std::milli> elapsed = std::chrono::high_resolution_clock::now() - m_StartTime;
			//return elapsed.count();
		}
		//returns true when period value is reached
		bool IsElapsedPeriod(const float& period)
		{
			//if (!elapsedContLockTimer)
			//{
			//	m_StartTime = std::chrono::high_resolution_clock::now();
			//	elapsedContLockTimer = true;
			//}
			//std::chrono::duration<double, std::milli> elapsed = std::chrono::high_resolution_clock::now() - m_StartTime;
			//if (elapsed.count() > period)
			//{
			//	elapsedContLockTimer = false;
			//	return true;
			//}
			//else
			//	return false;

		}

		const char* timerName;
	private:
		int m_StartTime, m_EndTime;
		bool elapsedContLockTimer = false;
		float totalTime_f;
	};


	typedef unsigned int(__cdecl* _SendConsoleCommand)(const char* str); 

	class Tracer
	{
	public:
		struct  cplane_t
		{
			Vec3	normal;
			float	dist;
			BYTE	type;			// for fast side tests: 0,1,2 = axial, 3 = nonaxial
			BYTE	signbits;		// signx + (signy<<1) + (signz<<2), used as lookup during collision
			BYTE	pad[2];
		};
		struct trace_t
		{
			BYTE		allsolid;	// if true, plane is not valid
			BYTE		startsolid;	// if true, the initial point was in a solid area
			short		entityNum;	// entity the contacted sirface is a part of

			float		fraction;	// time completed, 1.0 = didn't hit anything
			Vec3		endpos;		// final position
			cplane_t	plane;		// surface normal at impact, transformed to world space
			int			surfaceFlags;	// surface hit
			int			contents;	// contents on other side of surface 

		};

		typedef void* (__cdecl* _TraceLine)(trace_t* trace,  const Vec3& start, const Vec3& mins,
			const Vec3& maxs, const Vec3& end,
			 int skip,  int brushmask,  int setToZero); 


		typedef void* (__cdecl* _FastTraceLine)(trace_t* trace, const Vec3& start, const Vec3& end, const Vec3& mins,
			const Vec3& maxs, int skip, int brushmask);



		_TraceLine traceLine;
	    _FastTraceLine fastTrace;

	private:
	};

	static void CopyToClipboard(const std::string& str) 
	{ 
		const size_t len = str.size() + 1; 
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len); 
		memcpy(GlobalLock(hMem), str.c_str(), len);
		GlobalUnlock(hMem); 
		OpenClipboard(0); 
		EmptyClipboard(); 
		SetClipboardData(CF_TEXT, hMem); 
		CloseClipboard(); 
	}

	static void GetMbiiId(std::vector<unsigned int>& mbiiPIDs)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		int curProc = GetCurrentProcessId();
		if (hSnapshot != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 procEntry;
			procEntry.dwSize = sizeof(procEntry);
			if (Process32First(hSnapshot, &procEntry))
			{
				do
				{
					if (!_wcsicmp(procEntry.szExeFile, L"mbii.x86.exe"))
					{
						if (curProc != procEntry.th32ProcessID)
							mbiiPIDs.push_back(procEntry.th32ProcessID);
					}
				} while (Process32Next(hSnapshot, &procEntry));
			}
		}
		CloseHandle(hSnapshot);
	}

	static float GenerateRandomFloat(float min, float max)
	{
		std::random_device rd;
		std::uniform_real_distribution<float> distribution(min, max);
		std::default_random_engine engine(rd());

		return distribution(engine);
	}

	static int GenerateRandomInt(int min, int max)
	{
		std::random_device rd; 
		std::mt19937 engine(rd()); 
		std::uniform_int_distribution<int> distribution(min, max);

		return distribution(engine); 
	}

	static bool RandomPercent(const float& chanceInPercent)
	{
		int min = 1; int max = 100.0f / chanceInPercent;

		if (max <= min)
			return false;

		std::random_device rd;
		std::mt19937 engine(rd());
		std::uniform_int_distribution<int> distribution(min, max);

		if (distribution(engine) == 1)
			return true;
		else
			return false;
	}
};

