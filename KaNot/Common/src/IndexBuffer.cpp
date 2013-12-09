#include <IndexBuffer.h>

namespace Scioto
{
	IndexBuffer::IndexBuffer() { }

	IndexBuffer::IndexBuffer(const IndexBuffer& indexBuffer)
		: _indices(indexBuffer._indices) { }

	IndexBuffer::~IndexBuffer() { }

	const std::vector<unsigned int>& IndexBuffer::indices() const
	{
		return _indices;
	}

	void IndexBuffer::addIndex(const unsigned int index)
	{
		_indices.push_back(index);
	}

	void IndexBuffer::addIndices(const std::vector<unsigned int>& indices)
	{
		_indices.insert(_indices.end(), indices.begin(), indices.end());
	}

	void IndexBuffer::clear()
	{
		_indices.clear();
	}
}