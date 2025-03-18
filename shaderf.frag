#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 0) out vec4 outColor;

void main() {
    float aberrationAmount = 0.02;  // Chromatic aberration strength

    // Offset UV coordinates for red and blue channels
    vec2 redOffset = vec2(aberrationAmount, 0.0);
    vec2 blueOffset = vec2(-aberrationAmount, 0.0);

    // Sample texture with offsets
    float r = texture(texSampler, fragTexCoord + redOffset).r;
    float g = texture(texSampler, fragTexCoord).g;
    float b = texture(texSampler, fragTexCoord + blueOffset).b;

    vec3 color = vec3(r, g, b);

    // Convert to grayscale (perceived brightness)
    float luminance = dot(color, vec3(0.299, 0.587, 0.114));

    // **Increase Saturation**: Push color further from grayscale
    float saturationAmount = 3;  // 1.0 = no change, >1.0 = more saturated
    color = mix(vec3(luminance), color, saturationAmount);

    outColor = vec4(color, 1.0);
}
