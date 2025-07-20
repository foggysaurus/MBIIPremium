#pragma once
#include <glad/glad.h>
#include <stdio.h>
#include "string"
#include <windows.h>
#include "Addresses.h"
#include "Vectors.h"
#include <unordered_map>
#include "UI.h"
#include "Utils.h"
#include "NavMesh.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>


//#define DRAW_CUBED_MESH
#define DRAW_FLAT_MESH

class Font;
class Draw
{
public:

	struct RefDef
	{
		Vec2 fov;
		Vec3 cameraPos;
		Vec3 pitchYawRoll;
		Vec3 vfwd;
		Vec3 vright;
		Vec3 vup;
	};



	Draw();
	~Draw();
	void Init(Addresses* _a);

	void Render(HDC& hDc);
	bool CreateContext(HDC& hDc);
	void RestoreContext(HDC& hDc);
	void DrawUI(UI& ui);
	void DrawFilledPolygon(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& p4, const GLfloat color[4]);
	void DrawRotatedBBox(const Vec3& _bottom, const Vec3& _top, const Vec3& min,
		const Vec3& max, const float& yaw, const float& lineWidth, const GLfloat color[4]);
	void DrawBBox(const Vec3& _bottom, const Vec3& _top, const Vec3& min,
		const Vec3& max, const float& lineWidth, const GLfloat color[4]);
	void DrawTrajectory(const std::vector<Vec3>& vertices, const float& lineWidth, const GLfloat color[4]);
	void DrawLine(const Vec3& start, const Vec3& end, const float& lineWidth, const GLfloat color[4]);
	void DrawLine(const Vertex2& start, const Vertex2& end, const float& lineWidth, const GLfloat color[4]);
	void DrawFilledBox(const std::vector<Vertex2>& vertices, const GLfloat color[4]);
	bool WTS(const Vec3& worldPoint, Vertex2& screenPoint);
	bool WTSrotated(const Vec3& point, Vertex2& result, const Vertex2& rotateRelativeTo);
	void CreateCircle(const float& radius, const int& numSegments, std::vector<Vec3>& points);
	void TransformFigure(const Vec3& origin, std::vector<Vec3>& points, const Vec3& normal);
	void GetScreenFigurePoints(const std::vector<Vec3>& points, std::vector<Vertex2>& screenPoints);
	void DrawLineFigure(std::vector<Vec3>& points, const float& lineWidth, const GLfloat color[4]);
	void DrawLineFigure(const std::vector<Vertex2>& screenPoints, const float& lineWidth, const GLfloat color[4]);
	void DrawImpactFigure(const Vec3& finalPoint, const Vec3& normal, const float& radius, GLfloat color[4]);

	void DrawWorld(World* world, const Vec3& origin, const CellCoordinates& myLocation,
		const CellCoordinates& myFactualLocation, std::unordered_map<MeshColors, std::vector<float>>& meshColors);
	void DrawGraph(const std::unordered_map<uintptr_t, GraphNode*>& graph, const Vec3& myPos, const uint32_t& flags, 
		std::unordered_map<GraphColors, std::vector<float>>& graphColors);
	void DrawPath(const std::unordered_map<uintptr_t, GraphNode*>& graph, const std::vector<uintptr_t>& navigationPath, const uint32_t& flags);
	void DrawPath(const std::vector<Vec3>& navigationPath, const uint32_t& flags);

	Font* regular24 = nullptr;
	Font* bold28 = nullptr;
	Vec2 screenPosAdjustment{0,0};
	RefDef refDef;
	GLint viewport[4];
private:

	void GetMenuSize(const Vertex2& loc, int& width, int& height);
	void CalculateScreenAdjustment();
	void DrawMenuItem(MenuItem& item);
	void DrawMenuBlock(MenuBlock& mb);

	HGLRC old_context;
	HGLRC new_context;


	Utils::MrTimer perfTimer;

	Addresses* a = nullptr;

	Vec2 mouseCrd;
	Vec2 screenProportions;
	Vec2 screenCenter;
	Vec2 fovAdjustment;

	bool isMenuOpen = false;
};

namespace RGB
{
	const GLfloat red[4] = { 0.9, 0.1, 0.1, 1 };
	const GLfloat pink[4] = { 0.7, 0.3, 0.3, 1 };
	const GLfloat salmon[4] = { 0.95, 0.38, 0.44, 1 };
	const GLfloat green[4] = { 0.05, 0.8, 0.1, 1 };
	const GLfloat yellow[4] = { 1, 0.8, 0 , 1 };
	const GLfloat lightYellow[4] = { 0.8, 0.65, 0.2 , 1 };
	const GLfloat lightGreen[4] = { 0, 0.3, 0.15 , 1 };
	const GLfloat gray[4] = { 0.2, 0.2, 0.2 , 1 };
	const GLfloat lightGray[4] = { 0.8, 0.8, 0.8, 1 };
	const GLfloat black[4] = { 0, 0, 0 , 1 };
	const GLfloat purple[4] = { 0.8, 0, 0.8 , 1 };
	const GLfloat blue[4] = { 0, 0, 1, 1 };
	const GLfloat white[4] = { 1, 1, 1 , 1 };
	const GLfloat cyan[4] = { 0.1, 0.9, 0.9 , 1 };
	const GLfloat orange[4] = { 1, 0.75, 0 , 1 };
}
namespace CELL_TYPE_COLORS
{
	const GLfloat downOnly[4] = { 0.3,0.7, 0.3,0.8 };
	const GLfloat upOnly[4] = { 0.7,0.3, 0.3,0.8 };
	const GLfloat regular[4] = { 0.3,0.3, 0.7,0.8 };
	const GLfloat banned[4] = { 0.7,0.3, 0.7,0.8 };
	const GLfloat jump[4] = { 0.7,0.7, 0.3,0.8 };
}


constexpr size_t maxTextLength = 100;
class Font
{
public:
	Font(int height, bool bold, bool italic, std::string font, HDC& hdc);
	~Font();
	void InitializeFont(int height, bool bold, bool italic, std::string font, HDC& hdc);
	void Print(const float& x, const float& y, const float color[4], const std::string& print);
	void Print(const Vertex2& pos, const float color[4], const std::string& print);
	void CenterPrint(const float& x, const float& y, const float& charWidth, float color[4], const std::string& print);
private:
	void PrintFast(float x, float y, const float color[4], const char* format, ...);
	unsigned int base = 0;
};
