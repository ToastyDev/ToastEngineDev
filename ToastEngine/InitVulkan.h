#pragma once
#define GLFW_INCLUDE_VULKAN

#include "GLFW\glfw3.h"

#include <iostream>
#include <array>
#include <vector>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = { "VK_LAYER_LUNARG_standard_validation" };

class InitVulkan
{
public:
	void Initialize();


private:
	void StartVulkan();
	void CleanupVulkam();
	void InitWindow();
	void CreateInstance();
	void SetupDebugCallback();
	void CreateSurface();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapchain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateDescriptorSetLayout();
	void CreateGraphicsPipeline();
	void CreateCommandPool();
	void CreateDepthResources();
	void CreateFrameBuffers();
	void CreateTextureImage();
	void CreateTextureImageView();
	void CreateTextureSampler();
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateUniformBuffer();
	void CreateDescriptorPool();
	void CreateDescriptorSet();
	void CreateCommandBuffers();
	void CreateSemaphores();

	void RecreateSwapchain();
	
};