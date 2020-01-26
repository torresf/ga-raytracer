#version 300 es

precision mediump float;

in vec2 vFragTexture;
uniform vec3 uColor;
uniform sampler2D uTexture;

out vec3 fFragColor;

void main() {
	// fFragColor = vec3(vFragTexture, 1);
	// fFragColor = uColor;
	fFragColor = (texture(uTexture, vFragTexture)).xyz;
};
