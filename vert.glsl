#version 130

uniform mat4 uModel;
uniform mat4 uModelInvTr;
uniform mat4 uViewProj;

in vec4 vPos;
in vec4 vNor;
in vec4 vCol;

out vec4 fPos;
out vec4 fNor;
out vec4 fCol;

out vec4 fLightVec;
const vec4 vLightVec = normalize(vec4(-1,-1,-1,0));

void main() {
	fPos = vPos;
	fCol = vCol;

	fNor = vec4((mat3(uModelInvTr) * vec3(vNor)), 0);

	fLightVec = vLightVec;

	gl_Position = vPos; //uViewProj * (uModel * vPos);
}