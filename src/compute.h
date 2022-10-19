//
// Created by josue on 2022-10-19.
//

#ifndef MATERIEL_COMPUTE_H
#define MATERIEL_COMPUTE_H

#include "glad/gl.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <array>
#include <string>
#include <iostream>


class ComputeShader {

};

const char *compute_shader_source = "#version 460\n\nlayout(local_size_x=32, local_size_y=32) in;\n\nlayout(binding=0, rgba8) uniform image2D ColorImg;\n\n#define MAX_ITERATION 100\nuniform vec4 CompWindow = vec4(0, 0, 1, 1);\nuniform uint Width = 512;\nuniform uint Height = 512;\n\nuint mandelbrot(vec2 c) {\n    vec2 z = vec2(0.0);\n    uint i = 0;\n    while (i < MAX_ITERATION && (z.x * z.x + z.y * z.y) < 4.0) {\n        z = vec2(z.x * z.x - z.y * z.y + c.x, 2 * z.x * z.y + c.y);\n        i++;\n    }\n    return i;\n}\n\nvoid main() {\n    float dx = (CompWindow.z - CompWindow.x) / Width;\n    float dy = (CompWindow.w - CompWindow.y) / Height;\n    \n//    vec2 c = vec2( \n//        dx * gl_GlobalInvocationID.x + CompWindow.x,\n//        dy * gl_GlobalInvocationID.y + CompWindow.y\n//    );\n//    \n//    uint i = mandelbrot(c);\n//    vec4 color = vec4(0.0, 0.5, 0.5, 1.0);\n//    if( i < MAX_ITERATION ) {\n//        if ( i < 5 ) color = vec4(float(i) / 5.0, 0.0, 0.0, 1.0);\n//        else if ( i < 10 ) color = vec4(float(i) - 5.0 / 5.0, 1.0, 0.0, 1.0);\n//        else if ( i < 15 ) color = vec4(1.0, 0.0, (float(i)-10.0)/5.0, 1.0);\n//        else color = vec4(0.0, 0.0, 1.0, 1.0);\n//    } else color = vec4(0.0, 0.0, 0.0, 1.0);\n    \n    color = vec4(dx, dy, 0.0, 1.0);\n    \n    imageStore(ColorImg, ivec2(gl_GlobalInvocationID.xy), color);\n}";

void testNoiseShader() {
    // Create a texture and bind it a Texture bind point 0
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 512, 412);
    glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);

    GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shader, 1, &compute_shader_source, nullptr);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(program);
    glDispatchCompute(512/32, 512/32, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    uint8_t data[512*512];
    glGetTextureImage(texture, 0, GL_RGBA, GL_UNSIGNED_SHORT, 512 * 512 * sizeof(uint8_t), &data);

    const char *filename = "test_image.png";
    stbi_write_png(filename, 512, 512, 4, &data, 512);
}

#endif //MATERIEL_COMPUTE_H
