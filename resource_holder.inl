#include <SFML/Graphics.hpp>

template <typename Resource, typename Identifier>
sf::Texture& ResourceHolder<Resource,
	Identifier>::get(Identifier id)
{
	auto found = mTextureMap.find(id);
	assert(found != mTextureMap.end());
	return *found->second;
}
template <typename Resource, typename Identifier>
const sf::Texture& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = mTextureMap.find(id);
	assert(found != mTextureMap.end());
	return *found->second;
}
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
	const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to"
			load " + filename");
	auto inserted = mResourceMap.insert(
			std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

