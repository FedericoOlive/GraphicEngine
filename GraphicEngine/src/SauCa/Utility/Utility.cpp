#include "Utility.h"

const float Utility::deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;
const float Utility::rad2deg = 360.0f / (glm::pi<float>() * 2.0f);

glm::mat4 Utility::ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
{
	glm::mat4 to;
	//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
	to[0][0] = from.a1;
	to[1][0] = from.a2;
	to[2][0] = from.a3;
	to[3][0] = from.a4;
	to[0][1] = from.b1;
	to[1][1] = from.b2;
	to[2][1] = from.b3;
	to[3][1] = from.b4;
	to[0][2] = from.c1;
	to[1][2] = from.c2;
	to[2][2] = from.c3;
	to[3][2] = from.c4;
	to[0][3] = from.d1;
	to[1][3] = from.d2;
	to[2][3] = from.d3;
	to[3][3] = from.d4;
	return to;
}

glm::vec3 Utility::GetGLMVec(const aiVector3D& vec)
{
	return glm::vec3(vec.x, vec.y, vec.z);
}

glm::quat Utility::GetGLMQuat(const aiQuaternion& pOrientation)
{
	return glm::quat(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
}

glm::quat Utility::EulerToQuat(glm::vec3 euler)
{
	euler *= deg2rad;
	float cy = cos(euler.z * 0.5f);
	float sy = sin(euler.z * 0.5f);
	float cp = cos(euler.x * 0.5f);
	float sp = sin(euler.x * 0.5f);
	float cr = cos(euler.y * 0.5f);
	float sr = sin(euler.y * 0.5f);
	glm::quat q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = cr * sp * cy + sr * cp * sy;
	q.y = sr * cp * cy - cr * sp * sy;
	q.z = cr * cp * sy - sr * sp * cy;
	return q;
}

glm::vec3 Utility::QuatToVec(glm::quat quat, glm::vec3 vec)
{
	float x2 = quat.x * 2.f;
	float y2 = quat.y * 2.f;
	float z2 = quat.z * 2.f;
	float xx2 = quat.x * x2;
	float yy2 = quat.y * y2;
	float zz2 = quat.z * z2;
	float xy2 = quat.x * y2;
	float xz2 = quat.x * z2;
	float yz2 = quat.y * z2;
	float wx2 = quat.w * x2;
	float wy2 = quat.w * y2;
	float wz2 = quat.w * z2;
	glm::vec3 res;
	res.x = (1.f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
	res.y = (xy2 + wz2) * vec.x + (1.f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
	res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.f - (xx2 + yy2)) * vec.z;
	return res;
}

glm::vec3 Utility::QuatToEuler(glm::quat rot)
{
	float sqw = rot.w * rot.w;
	float sqx = rot.x * rot.x;
	float sqy = rot.y * rot.y;
	float sqz = rot.z * rot.z;
	float unit = sqx + sqy + sqz + sqw;
	float test = rot.x * rot.w - rot.y * rot.z;
	glm::vec3 v = glm::vec3();
	if (test > 0.4995f * unit)
	{
		v.y = 2.f * atan2(rot.y, rot.x);
		v.x = glm::pi<float>() / 2.f;
		v.z = 0.f;
		return NormalizeAngles(v * rad2deg);
	}
	if (test < -0.4995f * unit)
	{
		v.y = -2.f * atan2(rot.y, rot.x);
		v.x = -glm::pi<float>() / 2.f;
		v.z = 0.f;
		return NormalizeAngles(v * rad2deg);
	}
	glm::vec4 q = glm::vec4(rot.w, rot.z, rot.x, rot.y);
	v.y = atan2(2.f * q.x * q.w + 2.f * q.y * q.z, 1.f - 2.f * (q.z * q.z + q.w * q.w));
	v.x = asin(2.f * (q.x * q.z - q.w * q.y));
	v.z = atan2(2.f * q.x * q.y + 2.f * q.z * q.w, 1.f - 2.f * (q.y * q.y + q.z * q.z));
	return NormalizeAngles(v * 57.29578f);
}

glm::vec3 Utility::NormalizeAngles(glm::vec3 angles)
{
	angles.x = NormalizeAngle(angles.x);
	angles.y = NormalizeAngle(angles.y);
	angles.z = NormalizeAngle(angles.z);
	return angles;
}

float Utility::NormalizeAngle(float angle)
{
	while (angle > 360.f)
		angle -= 360.f;
	while (angle < 0.f)
		angle += 360.f;
	return angle;
}