#pragma once
#include <cmath>

constexpr double PI = 3.14159265358979323846;
constexpr double RADIAN = 57.295779513082320876;
constexpr double DEGREE_TO_RAD = 0.017453292519943295769236907;

struct Vec3
{
	float x, y, z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
	Vec3(float x_) : x(x_), y(x_), z(x_) {}

	Vec3 operator+(const Vec3& other) const {
		return Vec3(x + other.x, y + other.y, z + other.z);
	}
	Vec3 operator-(const Vec3& other) const {
		return Vec3(x - other.x, y - other.y, z - other.z);
	}
	Vec3 operator-(float number) const {
		return Vec3(x - number, y - number, z - number);
	}
	Vec3 operator+(float number) const {
		return Vec3(x + number, y + number, z + number);
	}
	Vec3 operator*(const float& other) const {
		return Vec3(x * other, y * other, z * other);
	}
	Vec3 operator*(const Vec3& other) const {
		return Vec3(x * other.x, y * other.y, z * other.z);
	}
	Vec3 operator/(const float& other) const {
		return Vec3(x / other, y / other, z / other);
	}
	bool operator!=(const Vec3& other) const {
		return x != other.x || y != other.y || z != other.z;
	}
	bool operator==(const Vec3& other) const {
		return x == other.x && y == other.y && z == other.z;
	}
	Vec3& operator*=(const float& other) 
	{
		x *= other; y *= other; z *= other;
		return *this;
	}
	Vec3& operator+=(const Vec3& other) 
	{
		x += other.x; y += other.y; z += other.z;
		return *this;
	}
	Vec3& operator-=(const Vec3& other) 
	{
		x -= other.x; y -= other.y; z -= other.z;
		return *this;
	}
	Vec3& operator/=(const float& other) 
	{
		x /= other; y /= other; z /= other;
		return *this;
	}
	Vec3& operator+=(float number) 
	{
		x += number; y += number; z += number;
		return *this;
	}
	Vec3& operator-=(float number) 
	{
		x -= number; y -= number; z -= number;
		return *this;
	}

};

//TEST

struct Matrix3x3 {
	double m[3][3];

	Matrix3x3() {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				m[i][j] = 0.0;
			}
		}
	}

	static Matrix3x3 createYawRotationMatrixZUp(double yawRadians)
	{
		Matrix3x3 rotationMatrix;
		double cosYaw = cos(yawRadians);
		double sinYaw = sin(yawRadians);

		rotationMatrix.m[0][0] = cosYaw;
		rotationMatrix.m[0][1] = -sinYaw;
		rotationMatrix.m[0][2] = 0.0;

		rotationMatrix.m[1][0] = sinYaw;
		rotationMatrix.m[1][1] = cosYaw;
		rotationMatrix.m[1][2] = 0.0;

		rotationMatrix.m[2][0] = 0.0;
		rotationMatrix.m[2][1] = 0.0;
		rotationMatrix.m[2][2] = 1.0;

		return rotationMatrix;
	}

	static Matrix3x3 createPitchRotationMatrixZUp(double pitchRadians)
	{
		Matrix3x3 rotationMatrix;
		double cosPitch = cos(pitchRadians);
		double sinPitch = sin(pitchRadians);

		rotationMatrix.m[0][0] = 1.0;
		rotationMatrix.m[0][1] = 0.0;
		rotationMatrix.m[0][2] = 0.0;

		rotationMatrix.m[1][0] = 0.0;
		rotationMatrix.m[1][1] = cosPitch;
		rotationMatrix.m[1][2] = sinPitch;

		rotationMatrix.m[2][0] = 0.0;
		rotationMatrix.m[2][1] = -sinPitch;
		rotationMatrix.m[2][2] = cosPitch;

		return rotationMatrix;
	}

	Vec3 operator*(const Vec3& v) const {
		return Vec3(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
		);
	}
};



//TEST

struct Vec3_ui8
{
	unsigned char x, y, z;

	Vec3_ui8() : x(0), y(0), z{0} {}
	Vec3_ui8(unsigned char x_, unsigned char y_, unsigned char z_) : x(x_), y(y_), z(z_) {}
	bool operator!=(const Vec3_ui8& other) const {
		return x != other.x || y != other.y || z != other.z;
	}
};
struct Vec3_i8
{
	unsigned char x, y, z;

	Vec3_i8() : x(0), y(0), z{ 0 } {}
	Vec3_i8(unsigned char x_, unsigned char y_, unsigned char z_) : x(x_), y(y_), z(z_) {}
};
struct Vec2
{
	float x, y;

	Vec2() : x(0), y(0) {}
	Vec2(float x_, float y_) : x(x_), y(y_) {}
};
struct Vec2i
{
	int x, y;

	Vec2i() : x(0), y(0) {}
	Vec2i(int x_, int y_) : x(x_), y(y_) {}
};

struct Vertex2
{
public:
	int x;
	int y;

	Vertex2() {}
	Vertex2(int _x, int _y) : x(_x), y(_y) {}

	Vertex2 operator-(const Vertex2& other) const {
		return Vertex2(x - other.x, y - other.y);
	}
	Vertex2 operator+(const Vertex2& other) const {
		return Vertex2(x + other.x, y + other.y);
	}
	bool operator==(int value) const 
	{
		return value == 0 && x == 0 && y == 0;
	}
	bool operator==(const Vertex2& other) const 
	{
		return x == other.x && y == other.y;
	}
	bool operator!=(int value) const 
	{
		return !(*this == value);
	}
	bool operator!=(const Vertex2& other) const 
	{
		return !(*this == other);
	}

	inline bool IsNull()
	{
		if (!x || !y)
			return true;
		else
			return false;
	}
};

namespace vecs
{
	static inline const float VecMagnitude(const Vec3& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}
	static inline const Vec3 NormalizeVector(const Vec3& v)
	{
		float length = VecMagnitude(v);
		return v / length;
	}
	static inline const float DotProduct(const Vec3& vec1, const Vec3& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}
	static inline const Vec3 RotateVecX(const Vec3& in, float theta)
	{
		float s = std::sin(theta);
		float c = std::cos(theta);
		Vec3 out; out = in;

		out.y += out.y * c - out.z * s;
		out.z += out.y * s + out.z * c;
		return out;
	}
	static inline const Vec3 RotateVecY(const Vec3& in, float theta)
	{
		float s = std::sin(theta);
		float c = std::cos(theta);
		Vec3 out; out = in;

		out.x += out.x * c + out.z * s;
		out.z += -out.x * s + out.z * c;
		return out;
	}
	static inline const Vec3 RotateVecZ(const Vec3& in, float theta)
	{
			float s = std::sin(theta);
			float c = std::cos(theta);
			Vec3 out; out = in;

			out.x += out.x * c - out.y * s;
			out.y += out.x * s + out.y * c;
			return out;
	}
	static inline const Vec3 GetUnitVector(const float& pitch, const float& yaw)
	{
		Vec3 unitVector;

		float pitchRad = pitch * (DEGREE_TO_RAD);
		float yawRad = yaw * (DEGREE_TO_RAD);

		unitVector.x = std::cos(pitchRad) * std::cos(yawRad);
		unitVector.y = std::cos(pitchRad) * std::sin(yawRad);
		unitVector.z = -std::sin(pitchRad);

		// Normalize the vector to make it a unit vector
		return NormalizeVector(unitVector);
	}
	static inline const Vec3 ReflectVector(const Vec3& v, Vec3& normal)
	{
		return v - normal * 2 * (DotProduct(normal, v));
	}
	static inline const float VecDistance(const Vec3& start, const Vec3& end)
	{
		float crd0 = (end.x - start.x) * (end.x - start.x);
		float crd1 = (end.y - start.y) * (end.y - start.y);
		float crd2 = (end.z - start.z) * (end.z - start.z);

		return sqrt(crd0 + crd1 + crd2);
	}
	static inline const float VecDistance2(const Vec3& start, const Vec3& end)
	{
		float crd0 = (end.x - start.x) * (end.x - start.x);
		float crd1 = (end.y - start.y) * (end.y - start.y);

		return sqrt(crd0 + crd1);
	}
	static inline const float AngleBetweenVec(const Vec3& a, const Vec3& b)
	{
		float angleRet = abs(std::acos(DotProduct(a, b) / (VecMagnitude(a) * VecMagnitude(b))) * (RADIAN));
		if (std::isnan(angleRet))
			return 0;
		else
			return angleRet;
	}
	static inline const Vec3 CrossProduct(const Vec3& A, const Vec3& B)
	{
		return { A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z ,A.x * B.y - A.y * B.x };
	}
	static inline const void AngleVectors(const float& yaw, const float& pitch, Vec3& forward, Vec3& right, Vec3& up)
	{
		float		angle;
		float		sp, sy, cr, cp, cy;

		angle = yaw * (DEGREE_TO_RAD);
		sy = sinf(angle);
		cy = cosf(angle);
		angle = pitch * (DEGREE_TO_RAD);
		sp = sinf(angle);
		cp = cosf(angle);


		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;

		right.x = (-1 * -sy);
		right.y = (-1 * cy);
		right.z = 0;

		up.x = (cr * sp * cy);
		up.y = (cr * sp * sy);
		up.z = cr * cp;
	}
	static inline const void CalculateUnitVector(const float& pitch, const float& yaw, Vec3& unitVector)
	{
		float pitchRad = pitch * (DEGREE_TO_RAD);
		float yawRad = yaw * (DEGREE_TO_RAD);

		unitVector.x = std::cos(pitchRad) * std::cos(yawRad);
		unitVector.y = std::cos(pitchRad) * std::sin(yawRad);
		unitVector.z = -std::sin(pitchRad);

		NormalizeVector(unitVector);
	}

}