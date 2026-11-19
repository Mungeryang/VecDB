//
// Created by mungeryang on 2026/11/10.
//

#ifndef VECTORDB_FAISS_INDEX_H
#define VECTORDB_FAISS_INDEX_H

#include <faiss/Index.h>
#include <vector>

class FaissIndex {
public:
    //构造函数，接收一个指向FAISS索引对象的指针
    FaissIndex(faiss::Index* index);

    //公共成员函数，用于将向量和对应的标签写入索引中
    void insert_vectors(const std::vector<float>& data, uint64_t label);

    //公共成员函数，用于在索引中查询与待查询向量最近邻的k个向量
    //返回一个包含两个动态数组的pair，第一个动态数组是找到向量的标签，第二个动态数组是响应的距离
    std::pair<std::vector<faiss::idx_t>, std::vector<float>> search_vectors(const std::vector<float>& query, int k);

private:
    faiss::Index* index;//私有成员变量，存储指向FAISS索引对象的指针

};


#endif //VECTORDB_FAISS_INDEX_H
