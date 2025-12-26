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
        LK_CORE_INFO("OpenGLVertexArray constructor starting");
        glGenVertexArrays(1, &m_RendererID);
        LK_CORE_INFO("glGenVertexArrays done, ID={0}", m_RendererID);
        glBindVertexArray(m_RendererID);
        LK_CORE_INFO("glBindVertexArray done");
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        LK_PROFILE_FUNCTION()

        glDeleteVertexArrays(1, &m_RendererID);
    }

    void Like::OpenGLVertexArray::Bind() const
    {
        LK_PROFILE_FUNCTION()

        glBindVertexArray(m_RendererID);
    }
    
    void Like::OpenGLVertexArray::Unbind() const
    {
        LK_PROFILE_FUNCTION()

        glDeleteVertexArrays(1, &m_RendererID);
    }
    
    void Like::OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        LK_PROFILE_FUNCTION()

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
        LK_PROFILE_FUNCTION()

        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();
    
        m_IndexBuffer = indexBuffer;
    }
}
