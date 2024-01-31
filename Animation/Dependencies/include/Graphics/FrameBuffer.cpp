#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(FrameBufferSpecification specifcation)
{
	this->specification = specifcation;
	Validate();
}

FrameBuffer::~FrameBuffer()
{
	GLCALL(glDeleteFramebuffers(1, &rendererId));
	GLCALL(glDeleteTextures(1, &colorAttachmentId));
	GLCALL(glDeleteTextures(1, &depthAttachmentId));
}

void FrameBuffer::Validate()
{
	if (rendererId != 0)
	{
		GLCALL(glDeleteFramebuffers(1, &rendererId));
		GLCALL(glDeleteTextures(1, &colorAttachmentId));
		GLCALL(glDeleteTextures(1, &depthAttachmentId));
	}

	GLCALL(glCreateFramebuffers(1, &rendererId));
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, rendererId));

	GLCALL(glCreateTextures(GL_TEXTURE_2D,1, &colorAttachmentId));
	GLCALL(glBindTexture(GL_TEXTURE_2D, colorAttachmentId));
	GLCALL(glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, specification.width, specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachmentId, 0));

	GLCALL(glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachmentId));
	GLCALL(glBindTexture(GL_TEXTURE_2D, depthAttachmentId));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, specification.width, specification.height, 0,
		GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL));
	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachmentId, 0));
	
	GLCALL(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));


}

void FrameBuffer::Bind()
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, rendererId));
}

void FrameBuffer::UnBind()
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::Resize(uint32_t width, uint32_t height)
{
	specification.width = width;
	specification.height = height;

	Validate();
}

unsigned int& FrameBuffer::GetColorAttachmentId()
{
	return colorAttachmentId;
}

unsigned int& FrameBuffer::GetRendererId()
{
	return rendererId;
}

unsigned int& FrameBuffer::GetDepthAttachmentId()
{
	return depthAttachmentId;
}

FrameBufferSpecification& FrameBuffer::GetSpecification()
{
	return specification;
}
