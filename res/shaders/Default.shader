#shader vertex
#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec2 tc;

void main(void)
{
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
    tc = texCoords;
}

#shader fragment
#version 430

layout(binding = 0) uniform sampler2D tex;

in vec2 tc;
out vec4 color;

void main(void) {
    color = texture(tex, tc);
    //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}