#include "Panel.h"
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "FileSystem.h"
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Character.h"
#include "FileSystem.h"

static std::map<GLchar, Character> Characters;
static float baseScale = 1.0f;

void Panel::Init()
{
    // opengl settings about text rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void Panel::LoadFonts(const std::string& filePath)
{
    FT_Library ft;
    FT_Face face;
    if(FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FRETYPE: Could not init FreeType Library" << std::endl;
    }
    if(FT_New_Face(ft, filePath.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
    }

    // create gl texture for each characters
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    float maxSize = 1.0f;
    for(GLubyte c = 0; c < 128; c++) {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }
        GLuint texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<GLchar, Character>(c,character));
        maxSize = face->glyph->bitmap.width > maxSize?  face->glyph->bitmap.width : maxSize;
        maxSize = face->glyph->bitmap.rows > maxSize?  face->glyph->bitmap.rows : maxSize;
    }
    baseScale = 1.0f / maxSize;
    //clear the FreeType releated resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
Panel::~Panel()
{
    for(auto i : VAOs) {
        glDeleteVertexArrays(1, &i);
    }
    for(auto i : VBOs) {
        glDeleteBuffers(1, &i);
    }
    for(auto i : EBOs) {
        glDeleteBuffers(1, &i);
    }
}
Panel::Panel(std::shared_ptr<Shader> shader, const std::string& text, const glm::vec3& color)
        :mShader(shader), mText(text), mColor(color)
{
    GLfloat x = 0.0f;
    GLfloat y = 0.0f;
    // Iterate through all characters
    std::string::const_iterator c;
    for (c = mText.begin(); c != mText.end(); c++) 
    {
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);

        Character ch = Characters[*c];
        GLfloat xpos = x + ch.Bearing.x * baseScale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * baseScale;

        GLfloat w = ch.Size.x * baseScale;
        GLfloat h = ch.Size.y * baseScale;
        // Update VBO for each character
        GLfloat vertices[4][4] = {
            { xpos    , ypos + h, 0.0, 0.0 },            
            { xpos    , ypos    , 0.0, 1.0 },
            { xpos + w, ypos    , 1.0, 1.0 },
            { xpos + w, ypos + h, 1.0, 0.0 }           
        };
        unsigned int indecies[6] = {
            0, 1, 2,
            0, 3, 2
        };
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        VAOs.push_back(VAO);
        VBOs.push_back(VBO);
        EBOs.push_back(EBO);
        Textures.push_back(ch.TextureID);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * baseScale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    // unbind 
    glBindVertexArray(0);
    
    mShader->use();
    mShader->setVec3f("textColor", mColor);
}

void Panel::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    mShader->use();
    mShader->setMat4f("model", model);
    mShader->setMat4f("view", view);
    mShader->setMat4f("projection", projection);
    for(int i = 0; i < VAOs.size(); i++) {
        glBindVertexArray(VAOs[i]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Textures[i]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}
