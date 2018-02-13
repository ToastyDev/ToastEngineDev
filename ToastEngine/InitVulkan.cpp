#include "InitVulkan.h"

void InitVulkan::Initialize()
{
	InitWindow();
	StartVulkan();
}

void InitVulkan::StartVulkan()
{

}

//Cleans up Vulkan processes and data cleanly
void InitVulkan::CleanupVulkan()
{

}

//Creates the GLFW window for use in the program
void InitVulkan::InitWindow(GLFWwindow* window, int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr); //width, height, title, monitor, share
}

//Handles resizing the window
void InitVulkan::WindowResize(GLFWwindow* window, int width, int height)
{
	if (width == 0 || height == 0) return;
}

//Creates the instance of Vulkan
void InitVulkan::CreateInstance()
{

}

void InitVulkan::SetupDebugCallback()
{
	if (!enableValidationLayers) return;
}

void InitVulkan::CreateSurface()
{

}

//Chooses which GPU to use and calculate on
void InitVulkan::PickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		throw std::runtime_error("Failed to find a GPU that supports Vulkan.");
	}

	std::vector<VkPhysicalDevice>devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (IsDeviceSuitable(device))
		{
			physicalDevice = device;
			break;
		}
		if (physicalDevice == VK_NULL_HANDLE)
		{
			throw std::runtime_error("Failed to find a suitable GPU to use.");
		}
	}
}

void InitVulkan::CreateLogicalDevice()
{

}

void InitVulkan::CreateSwapchain()
{

}

void InitVulkan::CreateImageViews()
{

}

void InitVulkan::CreateRenderPass()
{

}

void InitVulkan::CreateDescriptorSetLayout()
{

}

void InitVulkan::CreateGraphicsPipeline()
{

}

void InitVulkan::CreateCommandPool()
{

}

void InitVulkan::CreateDepthResources()
{

}

void InitVulkan::CreateFrameBuffers()
{

}

void InitVulkan::CreateTextureImage()
{

}

void InitVulkan::CreateTextureImageView()
{

}

void InitVulkan::CreateTextureSampler()
{

}

void InitVulkan::CreateVertexBuffer()
{

}

void InitVulkan::CreateIndexBuffer()
{

}

void InitVulkan::CreateUniformBuffer()
{

}

void InitVulkan::CreateDescriptorPool()
{

}

void InitVulkan::CreateDescriptorSet()
{

}

void InitVulkan::CreateCommandBuffers()
{

}

void InitVulkan::CreateSemaphores()
{

}

//Recreates the swapchain when new dimensions are presented
void InitVulkan::RecreateSwapchain()
{

}

////HELPER FUNCTIONS////

//Checks to see if the GPU is suitable for game needs
bool IsDeviceSuitable(VkPhysicalDevice device)
{
	QueueFamilyIndices indices = FindQueueFamilies(device);
	bool extensionSupported = CheckDeviceExtensionSupport(device);

	bool swapchainAdequate = false;
	if (extensionSupported)
	{
		SwapchainSupportDetails swapchainSupport = QuerySwapchainSupport(device);
		swapchainAdequate = !swapchainSupport.formats.empty() && !swapchainSupport.presentModes.empty();
	}

	VkPhysicalDeviceFeatures supportedFeatures;
	vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

	return indices.isComplete() && extensionSupported && swapchainAdequate && supportedFeatures.samplerAnisotropy;
}

//Checks for supported extensions on the chosen GPU
bool CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

//Finds queue families on a particular GPU
QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

		if (queueFamily.queueCount > 0 && presentSupport)
		{
			indices.presentFamily = i;
		}

		if (indices.isComplete)
		{
			break;
		}

		i++;
	}
	return indices;
}

//Finds the swap surface formats and present modes for use in the swap chain
SwapchainSupportDetails QuerySwapchainSupport(VkPhysicalDevice device)
{
	SwapchainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
	if (formatCount != 0)
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}

	uint32_t presentCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentCount, nullptr);
	if (presentCount != 0)
	{
		details.presentModes.resize(presentCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentCount, details.presentModes.data());
	}
	return details;
}

//Chooses the color formats for the swap surface object
VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
	{
		return { VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}

	for (const auto& availableFormat : availableFormats)
	{
		if (availableFormat.format == VK_FORMAT_R8G8B8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return availableFormat;
		}
	}
	return availableFormats[0];
}

//
VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

	for (const auto& availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
		else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
			bestMode = availablePresentMode;
	}
	return bestMode;
}

//
VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		return capabilities.currentExtent;
	}
	else
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		VkExtent2D actualExtent = { width, height };

		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}

//
std::vector<const char*> GetRequiredExtensions()
{

}