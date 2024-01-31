#pragma once

#include "Debugger.h"

struct FrameBufferSpecification
{
	uint32_t width, height;
	uint32_t samples;

	bool swapChainTarget = false;
};

class FrameBuffer
{

public:

	FrameBuffer(FrameBufferSpecification specifcation);
	~FrameBuffer();

	void Validate();
	
	void Bind();
	void UnBind();

	void Resize(uint32_t width, uint32_t height);

	unsigned int& GetColorAttachmentId();
	unsigned int& GetRendererId();
	unsigned int& GetDepthAttachmentId();

	FrameBufferSpecification& GetSpecification();

private:

	unsigned int rendererId = 0;
	unsigned int colorAttachmentId = 0;
	unsigned int depthAttachmentId = 0;

	FrameBufferSpecification specification;

};

