#pragma once
#include "math.h"
#include "iostream"
class vec3
{
public:
	float e[3];
	vec3() {}
	vec3(float x,float y,float z)
	{
		e[0] = x;
		e[1] = y;
		e[2] = z;
	}
	inline float x()const { return e[0]; }
	inline float y()const { return e[1]; }
	inline float z()const { return e[2]; }
	inline float r()const { return e[0]; }
	inline float g()const { return e[1]; }
	inline float b()const { return e[2]; }

	inline const vec3& operator+()const
	{
		return *this;
	}
	vec3 operator-()const { return vec3(-e[0], -e[1], -e[2]); }
	float operator[](int i)const { return e[i]; }
	float& operator[](int i){ return e[i]; };




	vec3& operator+=(const vec3 &v2);
	vec3& operator-=(const vec3 &v2);
	vec3& operator*=(const vec3 &v2);
	vec3& operator/=(const vec3 &v2);
	vec3& operator*=(const float t);
	vec3& operator/=(const float t);
	vec3& operator=(const vec3&vt);
	float length()const
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	float squared_length()const
	{
		return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}


	
}; 
inline std::istream & operator>>(std::istream &is, vec3 &t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream & operator<<(std::ostream &os,const vec3 &t)
{
	os << t.e[0] <<" "<< t.e[1] <<" "<< t.e[2];
	return os;
}

inline float dot(const vec3 &v1,const vec3 &v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
	return vec3(
		v1[1] * v2[2] - v1[2] * v2[1],
		v1[2] * v2[0] - v1[0] * v2[2],
		v1[0] * v2[1] - v1[1] * v2[0]
	);
}
inline vec3 make_unit_vector(vec3 e)
{
	float sqrt_r = sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] /= sqrt_r;
	e[1] /= sqrt_r;
	e[2] /= sqrt_r;
	return e;

}

inline vec3 operator +(vec3 vec1, vec3 v2) 
{
	return vec3(vec1[0] + v2[0], vec1[1] + v2[1], vec1[2] + v2[2]);
}
inline vec3 operator -(vec3 vec1, vec3 v2)
{
	return vec3(vec1[0] - v2[0], vec1[1] - v2[1], vec1[2] - v2[2]);
}
inline vec3 operator *(vec3 vec1, vec3 v2)
{
	return vec3(vec1[0] * v2[0], vec1[1] * v2[1], vec1[2] * v2[2]);
}
inline vec3 operator /(vec3 vec1, vec3 v2)
{
	return vec3(vec1[0] / v2[0], vec1[1] / v2[1], vec1[2] / v2[2]);
}

inline vec3 operator *(vec3 vec1,float t)
{
	return vec3(vec1[0] * t, vec1[1] * t, vec1[2] * t);
}

inline vec3 operator *( float t, vec3 vec1)
{
	return vec3(vec1[0] * t, vec1[1] * t, vec1[2] * t);
}

inline vec3 operator /(vec3 vec1, float t)
{
	return vec3(vec1[0] / t, vec1[1] / t, vec1[2] / t);
}