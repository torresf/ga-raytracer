#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;

out vec2 vFragTexture;

uniform mat3 uModelMatrix;

mat3 rotate(float a) {
	a = radians(a);
	return mat3(vec3(cos(a), sin(a), 0), vec3(-sin(a), cos(a), 0), vec3(0, 0, 1));
}

void main() {
	vFragTexture = aVertexTexture;
	gl_Position = vec4((uModelMatrix * vec3(aVertexPosition, 1)).xy, 0, 1);
};
