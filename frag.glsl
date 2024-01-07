#version 130

in vec4 fPos;
in vec4 fNor;
in vec4 fCol;
in vec4 fLightVec;

out vec4 outCol;

// lambertion reflection model
void main() {
	vec4 diffuseCol = fCol;

	vec4 diffuseTerm = dot(normalize(fNor), normalize(fLightVec));
	diffuseTerm = clamp(diffuseTerm,0,1);

	float ambientTerm = 0.2;
	float intensity = diffuseTerm + ambientTerm;

	//outCol = vec4(diffuseCol.rgb * intensity, diffuseCol.a);
	outCol=vec4(0.f,0.f,1.f,1.f);
}