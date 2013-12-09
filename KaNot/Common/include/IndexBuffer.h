#pragma once
#ifndef INDEX_BUFFER_H_SCIOTO
#define	INDEX_BUFFER_H_SCIOTO

#include <vector>

namespace Scioto
{
	class IndexBuffer
	{
	public:

		IndexBuffer();

		IndexBuffer(const IndexBuffer& indexBuffer);

		~IndexBuffer();

		const std::vector<unsigned int>& indices() const;

		void addIndex(const unsigned int index);

		void addIndices(const std::vector<unsigned int>& indices);

		void clear();

	private:

		std::vector<unsigned int> _indices;
	};
}

#endif