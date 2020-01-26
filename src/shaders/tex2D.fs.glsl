#version 330 core

in vec2 vFragTexture;
uniform vec3 uColor;
uniform sampler2D uTexture;

out vec3 fFragColor;

void main() {
	// fFragColor = vec3(vFragTexture, 1);
	// fFragColor = uColor;
	fFragColor = (texture(uTexture, vFragTexture)).xyz; // * (.5*uColor) + vec3(.1,.1,.1);
};
