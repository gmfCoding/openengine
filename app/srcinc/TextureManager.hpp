#ifndef TEXTUREMANAGER_INCLUDE_H
#define TEXTUREMANAGER_INCLUDE_H


#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <map>
#include <set>
#include <vector>
#endif


#include "LoadGlad.h"
#include "gmfc_image.hpp"
#include <glm.hpp>
#include "CommonData.hpp"


class TextureManager
{

    static std::map<std::string, Image*> images;
    static std::map<std::string, int> imageToGpuID;
    public:
    static std::tuple<unsigned int, Image*> LoadTextureGPU(const std::string& path);

    /// Creates a texture atlas (one large texture) from multiple input texture file
    /// Each input texture must be square and and they all must have the same resolution

    /// Takes an Image and name and uploads the iamge to the GPU returning a GPU Texture ID and mapping the ID to the name
    static GLuint UploadNamedTexture(Image* image, const std::string& name);
    /// Takes a gpu texture (already uploaded) and adds it to the NameToGPUTextureID map
    static void MapGPUTexture(GLuint textureID, const std::string& name);
    /// Uploads an Image to the GPU returning GPU Texture ID
    static GLuint UploadTexture(Image* image);
    static GLuint GetNamedTexture(const std::string& name);
    static void CreateAtlasFromFiles(std::set<std::string> files, int &pixelsX,int &pixelsY, PixelData* &pixels, std::map<std::string, RectUV> &uvTrackMap);
};
#endif