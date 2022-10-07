#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec3 crntPos;
out vec2 texCoord;
uniform mat4 translate;

void main()
{
	crntPos = vec3(translate * vec4(aPos, 1.0f));
	texCoord = aTex;
	gl_Position = vec4(crntPos, 1.0f);
}