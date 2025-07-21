#ifndef  TEXTURE_H
#define TEXTURE_H

#include <string>

#pragma once
/// <summary>
/// Contains all Texture Data.
/// </summary>
struct Texture
{
	unsigned int id;
	std::string type; //REVIEW : Could be an enum
	std::string path;
};
#endif