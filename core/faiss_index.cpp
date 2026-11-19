//
// Created by mungeryang on 2026/11/10.
//

#include "faiss_index.h"
#include "logger.h"
#include "constants.h"
#include <iostream>
#include <vector>

FaissIndex::FaissIndex(faiss::Index* index) : index(index) {}

void FaissIndex::insert_vectors(const std::vector<float>& data, uint64_t label) {
    faiss::idx_t id = static_cast<faiss::idx_t>(label);//将标签转换为idx_t类型，符合FAISS索引的ID要求
    // 1表示写入单个向量，data.data()写入数据的指针，&id提供向量ID
    index->add_with_ids(1, data.data(), &id);
}

std::pair<std::vector<faiss::idx_t>, std::vector<float>> FaissIndex::search_vectors(const std::vector<float>& query, int k) {
    int dim = index->d;//从索引的维度属性中获取查询向量的维度
    int num_queries = query.size() / dim;//动态数组的长度除以每个向量的维度计算查询向量的个数
    //创建一个存储所有查询结果的动态数组，大小为查询向量的数量 * k
    std::vector<faiss::idx_t> indices(num_queries * k);
    //创建一个存储所有查询结果距离的动态数组，大小为查询向量的数量 * k
    std::vector<float> distances(num_queries * k);

    //执行查询操作，传入查询向量的数量，数据，k，距离和向量ID结果的指针
    index->search(num_queries, query.data(), k, distances.data(), indices.data());

    GlobalLogger->debug("Retrieved values:");
    for (size_t i = 0;i < indices.size();i++){
        if(indices[i] != -1){
            GlobalLogger->debug("ID: {}, Distance: {}", indices[i], distances[i]);
        }else {
            GlobalLogger->debug("No specific value found");
        }
    }
    return {indices,distances};
}