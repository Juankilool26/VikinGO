#pragma once

#include <iostream>
#include "Resource.hpp"

namespace LVGL{
    class ResourceShader : public Resource{

        public:
            ResourceShader() : Resource() {};
            ResourceShader(std::string v, std::string f){loadFile(v,f);}
            ~ResourceShader() { glDeleteProgram(ID); }
            void loadFile(std::string, std::string) override;

            unsigned int getShader(){return ID;}

            // activate the shader
            void use() { glUseProgram(ID); }
            
            // utility uniform functions
            void setBool(const std::string &name, bool value) const
            {         
                glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
            }

            void setInt(const std::string &name, int value) const
            { 
                glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
            }

            void setFloat(const std::string &name, float value) const
            { 
                glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
            }

            void setVec3(const std::string &name, const glm::vec3 &value) const
            { 
                glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
            }

            void setVec3(const std::string &name, float x, float y, float z) const
            { 
                glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
            }

            void setMat4(const std::string &name, const glm::mat4 &mat) const
            {
                glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
            }

        private:
            unsigned int ID;

            void checkCompileErrors(unsigned int shader, std::string type)
            {
                int success;
                char infoLog[1024];
                if (type != "PROGRAM")
                {
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                    if (!success)
                    {
                        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                    }
                }
                else
                {
                    glGetProgramiv(shader, GL_LINK_STATUS, &success);
                    if (!success)
                    {
                        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                    }
                }
            }
    };
}