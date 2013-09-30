/**
 * @file IndexBuffer.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <vector>

namespace glframework
{
	typedef unsigned int INDEX;

	class IndexBuffer
	{
	public:

		IndexBuffer();

		IndexBuffer(const IndexBuffer& indexBuffer);

		~IndexBuffer();

		const std::vector<INDEX>& indices() const;

		void addIndex(const INDEX index);

		void addIndices(const std::vector<INDEX>& indices);

		void clear();

	private:

		std::vector<INDEX> _indices;
	};
}

#endif