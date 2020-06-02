//
// Created by Chunel on 2020/5/23.
//

#ifndef CHUNELANN_HNSWPROC_H
#define CHUNELANN_HNSWPROC_H

#include <list>

#include "../hnswAlgo/hnswlib.h"
#include "../../AlgorithmProc.h"


using namespace hnswlib;

class HnswProc : public AlgorithmProc {

public:
    HnswProc();
    virtual ~HnswProc();

    ANN_RET_TYPE init(const ANN_MODE mode, const ANN_DISTANCE_TYPE distanceType,
                      const unsigned int dim, const char *modelPath, const unsigned int exLen);

    // train_mode
    ANN_RET_TYPE train(const char* dataPath, const unsigned int maxDataSize, const ANN_BOOL normalize, const float precision,
                       const unsigned int fastRank, const unsigned int realRank,
                       const unsigned int step, const unsigned int maxEpoch, const unsigned int showSpan);

    // process_mode
    ANN_RET_TYPE search(ANN_FLOAT *query, const unsigned int topK, ANN_SEARCH_TYPE searchType);
    /* label暂时没有使用，今后可以考虑，把label当做是词语标签之类的信息，添加进来 */
    ANN_RET_TYPE insert(const ANN_FLOAT *node, const char *label, const ANN_INSERT_TYPE insertType);
    ANN_RET_TYPE save(const char *modelPath);    // 默认写成是当前模型的
    ANN_RET_TYPE getResultSize(unsigned int& size);
    ANN_RET_TYPE getResult(char *result, unsigned int size);
    ANN_RET_TYPE ignore(const char *label);


protected:
    ANN_RET_TYPE reset();
    ANN_RET_TYPE loadDatas(const char *dataPath, std::vector<ANN_VECTOR_FLOAT> &datas);
    ANN_RET_TYPE trainModel(std::vector<ANN_VECTOR_FLOAT> &datas);
    ANN_RET_TYPE buildResult(const ANN_FLOAT *query, const std::list<unsigned int> &predIndex);
    ANN_RET_TYPE loadModel(const char *modelPath);
    ANN_RET_TYPE createDistancePtr();

public:
    static ANN_RET_TYPE createHnswSingleton(SpaceInterface<ANN_FLOAT>* distance_ptr, unsigned int maxDataSize, ANN_BOOL normalize);
    static ANN_RET_TYPE createHnswSingleton(SpaceInterface<ANN_FLOAT>* distance_ptr, const std::string &modelPath);
    static HierarchicalNSW<ANN_FLOAT>* getHnswSingleton();
    static ANN_RET_TYPE insertByAppend(const ANN_FLOAT *node, const char *label);
    static ANN_RET_TYPE insertByOverwrite(const ANN_FLOAT *node, const char *label);
    static ANN_RET_TYPE insertByDiscard(const ANN_FLOAT *node, const char *label);

    static HierarchicalNSW<ANN_FLOAT>*     hnsw_alg_ptr_;    // 考虑这里用static信息
    static RWLock                          lock_;

private:
    SpaceInterface<ANN_FLOAT>*             distance_ptr_;
};


#endif //CHUNELANN_HNSWPROC_H
