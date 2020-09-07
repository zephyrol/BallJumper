/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextRendering.cpp
 * Author: Morgenthaler S
 * 
 * Created on ? mai 2020, ??:??
 */

#include "TextRendering.h"
#include "ShaderProgram.h"

TextRendering::TextRendering(const std::vector<unsigned char>& characters,
                             unsigned int height):
    _alphabet(initAlphabet(characters,height)),
    _fontHeight(height),
    _displayQuad(),
    _spFont(Shader (GL_VERTEX_SHADER,   vsshaderFont),
            Shader (GL_FRAGMENT_SHADER, fsshaderFont)),
    _charactersTransforms{}
{

}

bool TextRendering::initFreeTypeAndFont() {

    if (FT_Init_FreeType(&ftLib)) {
        std::cerr << "Error: Impossible to init FreeType Lib..." << std::endl;
        return false;
    }

    std::string fontFileToOpenV1 = "fonts/Cousine-Regular.ttf";
    std::string fontFileToOpenV2 = "bin/fonts/Cousine-Regular.ttf";
    const std::vector<std::string> fileNames {
        std::move(fontFileToOpenV1), std::move(fontFileToOpenV2)};

    bool foundFile = false;
    for (size_t i = 0; i < fileNames.size() && !foundFile; ++i) {
        if(FT_New_Face(ftLib,fileNames.at(i).c_str(),
                   0,&fontFace) == 0) {
            foundFile = true;
        }
    }
    if (!foundFile) {
        std::cerr << "Error: Impossible to load the font" <<
                     "Cousine-Regular.ttf ... " << std::endl;
        JBTypesMethods::displayInstallError();
        FT_Done_FreeType(ftLib);
        return false;
    } else  {
        return true;
    }

}

void TextRendering::clearFreeTypeRessources() {
    FT_Done_Face(fontFace);
    FT_Done_FreeType(ftLib);
}

std::map<unsigned char, TextRendering::Character> TextRendering::initAlphabet(
        const std::vector<unsigned char>& characters, unsigned int height)
{
    std::map<unsigned char, TextRendering::Character> alphabet;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    FT_Set_Pixel_Sizes(fontFace,0,height);
    for (const unsigned char& character : characters) {

        if (!FT_Load_Char(fontFace,character,FT_LOAD_RENDER)) {

            GLuint textureID;
            glGenTextures(1,&textureID);
            glBindTexture(GL_TEXTURE_2D,textureID);

            constexpr GLint levelOfDetail = 0;
            glTexImage2D(GL_TEXTURE_2D, levelOfDetail, GL_RED,
                         fontFace->glyph->bitmap.width,
                         fontFace->glyph->bitmap.rows, 0, GL_RED,
                         GL_UNSIGNED_BYTE,
                         fontFace->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            
            float width;
            if (character == ' ') {
                width = static_cast<float>(height);
            } else {
                width = static_cast<float>(height) *
                    fontFace->glyph->bitmap.width/ fontFace->glyph->bitmap.rows;
            }
            const TextRendering::Character graphicChar {
                textureID,
                {fontFace->glyph->bitmap.width/width,
                    fontFace->glyph->bitmap.rows/static_cast<float>(height)},
                {fontFace->glyph->bitmap_left/width,
                    fontFace->glyph->bitmap_top/static_cast<float>(height)}
            };
            alphabet[character] = graphicChar;
        }
        else {
            std::cerr << "Error... Impossible to load glyph " << character <<
                         std::endl;
        }
    }
    return alphabet;
}

void TextRendering::render(const Label& label, const glm::vec3& color ) const {
    _spFont.use();
    _displayQuad.bind();
    for (size_t i = 0; i < label.message().size(); ++i) {
        const char& c = label.message().at(i);
        _spFont.bindUniformTexture("characterTexture", 0,
                                   _alphabet.at(c).texture);
        _spFont.bindUniform("fontColor",color);
        _spFont.bindUniform("M",_charactersTransforms.at(i));
        _displayQuad.draw();
    }
}

void TextRendering::update(const Label& label, float offsetY)
{
    JBTypes::vec2f position = label.position();
    if (!label.isFixed()) {
        position.y += offsetY;
    }

    const float pitch = label.width()/label.message().size();
    float offsetX = -label.width()/2.f + pitch/2.f;
    const glm::mat4 biasMatrix  = glm::mat4{ 1.f, 0.f,  0.f, 0.f,
                                             0.f,  1.f, 0.f, 0.f,
                                             0.f,  0.f,  1.f, 0.f,
                                             -1.f, -1.f, 0.f, 1.f} ;

    _charactersTransforms.clear();
    constexpr float biasScalar = 2.f; //To multiply the translation by 2
    for (const char& c : label.message()) {
        const glm::vec3 scale = glm::vec3{pitch * _alphabet.at(c).localScale.x,
                label.height() * _alphabet.at(c).localScale.y ,0.f};

        const glm::mat4 scaleMatrix = glm::scale(scale);

        const glm::mat4 translate =
           glm::translate( biasScalar *
               glm::vec3{ position.x+ offsetX +
                          _alphabet.at(c).localTranslate.x *
                          scale.x,
                           position.y -
                          (1.f-_alphabet.at(c).localTranslate.y) * scale.y,
                          0.f}
                         );
        _charactersTransforms.push_back(biasMatrix * translate * scaleMatrix);

        offsetX += pitch;
    }
}

unsigned int TextRendering::fontHeight() const {
    return _fontHeight;
}

FT_Library TextRendering::ftLib;
FT_Face TextRendering::fontFace;


const std::string TextRendering::vsshaderFont = "shaders/fontVs.vs";
const std::string TextRendering::fsshaderFont = "shaders/fontFs.fs";

