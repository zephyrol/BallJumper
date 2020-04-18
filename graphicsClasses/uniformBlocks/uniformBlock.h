/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   uniformBlock.h
 * Author: Morgenthaler S 
 *
 * Created on 22 décembre 2019, 12:22
 */

#ifndef UNIFORMBLOCK_H
#define UNIFORMBLOCK_H
#include <Types.h>
#include <iostream>
#include <map>
#include <vector>
#include "../Shader.h"
#include "../ShaderProgram.h"

class UniformBlock {
public:

    //--CONSTRUCTORS & DESTRUCTORS--//
    UniformBlock                      (  const std::vector<std::string>& 
                                                                variablesNames);
    

    UniformBlock                      ( const UniformBlock& 
                                                uniformBlock);
    
    virtual ~UniformBlock             ();                                    
    

    //---------CONSTANTS------------//
    static constexpr size_t           sizeVec3f           = 3 * sizeof(GLfloat);


    //----------METHODS------------//
    UniformBlock&                     operator=( const UniformBlock& 
                                                        uniformBlock);
    virtual void                      bind( const std::string& name,
                                            const ShaderProgram& sp)        = 0;


    //--------STATIC METHODS-------//
    static std::vector<const char*>   getStringsStoredLinearly( 
                                                const std::vector<std::string>&
                                                  strNames);
    static std::vector<const char*>   copyVariablesNamesInfo( 
                                                const std::vector<const char*>& 
                                                  varNamesInfo);
    
protected:

    //--------ATTRIBUTES-----------//
    std::vector<GLchar>               _dataBuffer;


    //-------CONST METHODS----------//
    const std::vector<const char*>&   variablesNames()                    const;
    const std::vector<GLuint>&        variablesIndices()                  const;
    const std::vector<GLint>&         variablesOffsets()                  const;
    const std::vector<GLchar>&        dataBuffer()                        const;
    GLint                             blockSize()                         const;
    GLuint                            uboHandle()                         const;


    //----------METHODS------------//
    void                              configureDataBuffer(
                                                const ShaderProgram& sp,
                                                const std::string& name); 


private:

    //--------ATTRIBUTES-----------//
    const std::vector<const char*>    _variablesNames;
    std::vector<GLuint>               _variablesIndices;
    std::vector<GLint>                _variablesOffsets;
    GLint                             _blockSize;
    GLuint                            _uboHandle;

    //----------METHODS------------//
    void                              deleteVariablesNamesInfo();
};

#endif /* UNIFORMBLOCK_H */

