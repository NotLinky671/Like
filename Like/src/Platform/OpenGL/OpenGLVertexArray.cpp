#include "lkpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Like
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case Like::ShaderDataType::Float:    return GL_FLOAT;
            case Like::ShaderDataType::Float2:   return GL_FLOAT;
            case Like::ShaderDataType::Float3:   return GL_FLOAT;
            case Like::ShaderDataType::Float4:   return GL_FLOAT;
            case Like::ShaderDataType::Mat3:     return GL_FLOAT;
            case Like::ShaderDataType::Mat4:     return GL_FLOAT;
            case Like::ShaderDataType::Int:      return GL_INT;
            case Like::ShaderDataType::Int2:     return GL_INT;
            case Like::ShaderDataType::Int3:     return GL_INT;
            case Like::ShaderDataType::Int4:     return GL_INT;
            case Like::ShaderDataType::Bool:     return GL_BOOL;
        }
    		
        LK_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
    
    Like::OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void Like::OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }
    
    void Like::OpenGLVertexArray::Unbind() const
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }
    
    void Like::OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        LK_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
    
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();
    
        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);
            index++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }
    
    void Like::OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();
    
        m_IndexBuffer = indexBuffer;
    }
}
