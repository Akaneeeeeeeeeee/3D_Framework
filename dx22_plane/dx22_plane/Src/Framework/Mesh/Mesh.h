#pragma once
#include	<vector>
#include	"renderer.h"

class Mesh {
protected:
	std::vector<VERTEX_3D>		m_vertices;		// 頂点座標群
	std::vector<unsigned int>	m_indices;		// インデックスデータ群
public:
	// 頂点データ取得
	const std::vector<VERTEX_3D>& GetVertices() {
		return m_vertices;
	}

	// インデックスデータ取得
	const std::vector<unsigned int>& GetIndices() {
		return m_indices;
	}

	// 法線データ逆転(SkyDome実装用)
	void InvertNormals() {
		for (auto& vertex : m_vertices) {
			vertex.normal = -vertex.normal; // 法線ベクトルを逆転
		}
		// インデックスの順序を反転させる例
		std::reverse(m_indices.begin(), m_indices.end());
	}
};

