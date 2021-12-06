#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "VBO.h"
#include <GL/glew.h>

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO()
	{
		glGenVertexArrays(1, &ID);
	};

	// Links a VBO Attribute such as a position or color to the VAO
	void LinkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
	{
		VBO.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	};
	// Binds the VAO
	void Bind()
	{
		glBindVertexArray(ID);
	};
	// Unbinds the VAO
	void Unbind()
	{
		glBindVertexArray(0);
	};
	// Deletes the VAO
	void Delete()
	{
		glDeleteVertexArrays(1, &ID);
	};
};

#endif