#version 330 core

in vec2 vFragTexture;
uniform vec3 uColor;
uniform vec3 uIntensity;
uniform sampler2D uTexture;

out vec3 fFragColor;

vec3 fillBlackPixel() {
	vec3 color;
	int kernelSize = 3;
	int min_bound;
	int max_bound;
	int moyenneDiv = 0;
	while (color == vec3(0., 0., 0.) && moyenneDiv < 9) {
		kernelSize += 2;
		min_bound = -(kernelSize-1) / 2;
		max_bound = +(kernelSize-1) / 2;
		for (int i = min_bound; i <= max_bound; i++) {
			for (int j = min_bound; j <= max_bound; j++) {
				if (i != 0 || j != 0) {
					if (
						vFragTexture.x + i/512. >= 0. &&
						vFragTexture.x + i/512. <= 1. &&
						vFragTexture.y + j/512. >= 0. &&
						vFragTexture.y + j/512. <= 1.
						) {
						if ((textureOffset(uTexture, vFragTexture, ivec2(i, j))).xyz != vec3(0., 0., 0.)) {
							color += (textureOffset(uTexture, vFragTexture, ivec2(i, j))).xyz;
							moyenneDiv += 1;
						}
					}
				}
			}
		}
	}
	return color / moyenneDiv;
}

void main() {
	if ((texture(uTexture, vFragTexture)).xyz == vec3(0., 0., 0.)) {
		fFragColor = fillBlackPixel() * uColor * uIntensity;
	} else {
		fFragColor = (texture(uTexture, vFragTexture)).xyz * uColor * uIntensity;
	}
};
