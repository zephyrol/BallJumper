#version 330 core

uniform sampler2D depthTexture;

uniform mat4  VP;
uniform mat4  VPStar;

uniform vec3 positionCamera;
uniform light {
              vec3  directionLight; 
              vec3  ambientLightIntensity;
              vec3  diffuseLightIntensity;
              vec3  specularLightIntensity;
              };

uniform float burningCoeff;
in vec3   fs_vertexColor;
in vec4   fs_vertexDepthMapSpace;
in vec3   fs_vertexNormal;
in vec3   fs_vertexPositionWorld;

out vec4  pixelColor;


void main() {

    const mat4 biasMatrix   = mat4(0.5f,0.f, 0.f, 0.f,
                               0.f, 0.5f,0.f, 0.f,
                               0.f, 0.f, 0.5f,0.f,
                               0.5f, 0.5f, 0.5f, 1.f);


    bool inShadow;
    vec4 fragStarSysCoord   = biasMatrix * fs_vertexDepthMapSpace;
    
    if ( texture(depthTexture, fragStarSysCoord.xy).x
          < ((fragStarSysCoord.z) - 0.001) )
        inShadow = true;
    else {
        inShadow = false;
    }

    const vec3 fireEffet    = vec3(10.f,.2f,0.f);

    vec3 ambientComponent   = ambientLightIntensity;
    vec3 composition = ambientComponent * 
        ((1.f - burningCoeff) * fs_vertexColor + (burningCoeff) * fireEffet);
    
    if (!inShadow) {

        vec3 toLight            = -directionLight;
        vec3 toCamera           = normalize(positionCamera - fs_vertexPositionWorld);
        vec3 reflection         = normalize(-toLight + 2.f * ( dot (toLight, fs_vertexNormal)) * fs_vertexNormal);
        vec3 diffuseComponent   = diffuseLightIntensity * max(0.f,dot(toLight,fs_vertexNormal));

        vec3 specularComponent  = specularLightIntensity * pow(max(0.f,dot(reflection,toCamera)),20.f);

        composition  += diffuseComponent + specularComponent;
    }
    pixelColor = vec4(composition,1.f);


}
