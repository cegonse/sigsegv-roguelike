const char *screen_filter_vs_shader = "#version 330\n \
in vec3 vertexPosition;\n \
in vec2 vertexTexCoord;\n \
in vec3 vertexNormal;\n \
in vec4 vertexColor;\n \
uniform mat4 mvp;\n \
uniform vec2 texSize;\n \
out vec2 fragTexCoord;\n \
out vec4 fragColor;\n \
void main()\n \
{\n \
    fragTexCoord = vertexTexCoord * texSize;\n \
    fragColor = vertexColor;\n \
    gl_Position = mvp*vec4(vertexPosition, 1.0);\n \
}\n";

const char *screen_filter_fs_shader = "#version 330\n \
in vec2 fragTexCoord;\n \
in vec4 fragColor;\n \
uniform sampler2D texture0;\n \
uniform vec4 colDiffuse;\n \
uniform vec2 texSize;\n \
uniform float texelsPerPixel;\n \
out vec4 finalColor;\n \
\n \
void main()\n \
{\n \
    float factor = 1.0f/texelsPerPixel;\n \
    vec4 texelColor = texture(texture0, fragTexCoord);\n \
    vec2 locationWithinTexel = fract(fragTexCoord);\n \
    vec2 interpolationAmount = clamp(locationWithinTexel / factor, 0, 0.5) + clamp((locationWithinTexel - 1) / factor + 0.5, 0, 0.5);\n \
    vec2 finalTextureCoords = (floor(fragTexCoord) + interpolationAmount) / texSize;\n \
    finalColor = texture(texture0, finalTextureCoords)*colDiffuse;\n \
}\n";

const char *Shader_GetScreenFilterVertexShader(void) {
  return screen_filter_vs_shader;
}

const char *Shader_GetScreenFilterFragmentShader(void) {
  return screen_filter_fs_shader;
}
