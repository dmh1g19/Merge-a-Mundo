#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 transform;

void main()
{
   gl_Position = transform * vec4(aPos, 1.0);
};

//#version 330 core
//
//layout (location = 0) in vec3 aPos;
//
//void main()
//{
//   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
//};