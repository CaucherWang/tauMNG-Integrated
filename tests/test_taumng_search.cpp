
#include <efanna2e/index_taumng.h>
#include <efanna2e/util.h>
#include <set>
#include <map>
#include <bits/stdc++.h> 
#include <math.h>


void load_data(const char* filename, float*& data, unsigned& num,
               unsigned& dim) {  
  std::ifstream in(filename, std::ios::binary);
  if (!in.is_open()) {
    std::cout << "open file error" << std::endl;
    exit(-1);
  }
  in.read((char*)&dim, 4);
  std::cout << "data dimension: " << dim << std::endl;
  in.seekg(0, std::ios::end);
  std::ios::pos_type ss = in.tellg();
  size_t fsize = (size_t)ss;
  num = (unsigned)(fsize / (dim + 1) / 4);
  data = new float[num * dim * sizeof(float)];

  in.seekg(0, std::ios::beg);
  for (size_t i = 0; i < num; i++) {
    in.seekg(4, std::ios::cur);
    in.read((char*)(data + i * dim), dim * 4);
  }
  in.close();
}



std::vector<std::vector<int> > load_ground_truth(const char* filename) {
  std::ifstream in(filename, std::ios::binary);
  if (!in.is_open()) {
    std::cout << "open file error (in load_ground_truth)" << std::endl;
    exit(-1);
  }

  unsigned dim, num;

  in.read((char*)&dim, 4);
  std::cout << "data dimension: " << dim << std::endl;
  in.seekg(0, std::ios::end);
  std::ios::pos_type ss = in.tellg();
  size_t fsize = (size_t)ss;
  num = (unsigned)(fsize / (dim + 1) / 4);

  int* data = new int[num * dim * sizeof(int)];

  in.seekg(0, std::ios::beg);
  for (size_t i = 0; i < num; i++) {
    in.seekg(4, std::ios::cur);
    in.read((char*)(data + i * dim), dim * 4);
  }
  in.close();

  std::vector<std::vector<int> > res;
  for (int i = 0; i < num; i++) {
    std::vector<int> a;
    for (int j = i*dim; j < (i+1)*dim; j++) {
      a.push_back(data[j]);
    }
    res.push_back(a);
  }

  return res;
}



int main(int argc, char** argv) {
  if (argc != 10) {
    std::cout << argv[0]
              << " dataset queryset gt tauMNG_path search_L search_K p stopL segmentSize"
              << std::endl;
    exit(-1);
  }


  // std::string dataset = argv[1];

  float* data_load = NULL;
  unsigned points_num, dim;
  std::string dataFileName = argv[1];
  load_data(dataFileName.c_str(), data_load, points_num, dim);

  float* query_load = NULL;
  unsigned query_num, query_dim;
  std::string queryFileName = argv[2];
  load_data(queryFileName.c_str(), query_load, query_num, query_dim);
  assert(dim == query_dim);


  // float* uT = NULL;
  // unsigned uTrowNum, uTcolNum;
  // std::string uTFile = "/tmp/"+dataset+"/uT.fvecs";
  // load_data(uTFile.c_str(), uT, uTrowNum, uTcolNum);


  // std::vector<std::vector<float> > uT2;
  // for (int i = 0; i < uTrowNum; i++) {
  //   std::vector<float> tmp;
  //   for (int j = 0; j < uTcolNum; j++) {
  //     tmp.push_back(uT[i*uTcolNum + j]);
  //   }
  //   uT2.push_back(tmp);
  // }
  // std::cout << "uT load done" << std::endl;
  

  // float* trans_data_load = NULL;
  // unsigned qnum, qdim;
  // std::string transDataFileName = "/tmp/"+dataset+"/"+dataset+"_base.trans.fvecs";
  // load_data(transDataFileName.c_str(), trans_data_load, qnum, qdim);
 

  // std::vector<std::vector<float> > trans_data;
  // for (int xx = 0; xx < qnum; xx++) {
  //   std::vector<float> node;
  //   for (int yy = 0; yy < qdim; yy++) {
  //     node.push_back( (trans_data_load + xx*qdim)[yy] );
  //   }
  //   trans_data.push_back(node);
  // }
  // std::cout << "trans_data done" << std::endl;


  std::vector<std::vector<int> > perm_list; std::vector<int> pivots;

  
  unsigned L = (unsigned)atoi(argv[5]);
  unsigned K = (unsigned)atoi(argv[6]);
  // float kperc = atof(argv[5]);
  // unsigned stopL = (unsigned)atoi(argv[6]);
  // int stepSize = atoi(argv[7]);



  if (L < K) {
    std::cout << "search_L cannot be smaller than search_K!" << std::endl;
    exit(-1);
  }


  IndexTauMNG index(dim, points_num, INNER_PRODUCT, nullptr);
  std::string saveFileName = argv[4];
  index.Load(saveFileName.c_str());

  Parameters paras;
  paras.Set<unsigned>("L_search", L);
  // paras.Set<float>("kperc", kperc);
  // paras.Set<unsigned>("stopL", stopL);
  // paras.Set<int>("stepSize", stepSize);

  std::string gtFileName = argv[3];
  std::vector<std::vector<int> > gts = load_ground_truth(gtFileName.c_str());

  // std::vector<std::vector<float> > step_sum;
  // float * step_sum_ptr;
  // unsigned step_sum_num, step_sum_dim;
  // std::string stepSumFile = "/tmp/"+dataset+"/"+dataset+"_base.trans.sumstep"+std::to_string(stepSize)+".fvecs";
  // load_data(stepSumFile.c_str(), step_sum_ptr, step_sum_num, step_sum_dim);




  auto s = std::chrono::high_resolution_clock::now();
  std::vector<std::vector<unsigned> > res;
  

  int qcnt = 0;
  index.NDC = 0;
  index.hops = 0;
  // Q * uT2 Q: n * dim uT2: dim * dim
  for (unsigned i = 0; i < query_num; i++) {

    // std::vector<float> trans_query;
    // for (int j = 0; j < dim; j++) {
    //   std::vector<float> row = uT2[j];

    //   float inner_prod = 0; // inner product of the i-th query and uT2[j]
    //   for (int m = 0; m < dim; m++) {
    //     inner_prod += (query_load[i * dim + m] * row[m]);
    //   }
    //   trans_query.push_back(inner_prod);
    // }


    //compute step_sum for q
    // std::vector<float> q_step_sum;
    // int last_one = -1;
    // for (int j = 0; j < dim/stepSize; j++) {
    //   float cur_step_sum = 0;
    //   for (int o = 0; o < stepSize; o++) {
    //     cur_step_sum += (trans_query[j*stepSize+o] * trans_query[j*stepSize+o]);
    //     last_one = j*stepSize+o;
    //   }
    //   if (q_step_sum.size() == 0) {
    //     q_step_sum.push_back(cur_step_sum);
    //   }
    //   else {
    //     q_step_sum.push_back(cur_step_sum + q_step_sum[q_step_sum.size()-1]);
    //   }
    // }
    // if (dim/stepSize < ((float)dim/stepSize)) {
    //   float cur_step_sum = 0;
    //   for (int o = last_one+1; o < dim; o++) {
    //     cur_step_sum += (trans_query[o] * trans_query[o]);
    //   }
    //   q_step_sum.push_back(cur_step_sum + q_step_sum[q_step_sum.size()-1]);
    // }


    std::vector<unsigned> tmp(K);
    index.Search(query_load + i * dim, data_load, K, paras, tmp.data());
    // index.Search(query_load + i * dim, data_load, K, paras, tmp.data(), perm_list, gts[i][0], trans_query.data(), trans_data_load);
    //index.Search_QEO_PDP(query_load + i * dim, data_load, K, paras, tmp.data(), perm_list, gts[i][0], trans_query.data(), trans_data_load);
    // index.Search3_QEO_PDP_PII(query_load + i * dim, data_load, K, paras, tmp.data(), uT2, trans_query.data(), trans_data_load, step_sum_ptr, q_step_sum);
    // for(int j = 0;j < K; ++j )  std::cout << tmp[j] <<",";
    res.push_back(tmp);
    // std::cout << std::endl << res.size() << std::endl;

    qcnt++;
  }
  
  auto e = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = e - s;

  
  float recall = index.eval_recall(res, gts, K);
  std::cout << "recall " << recall << std::endl;

  std::cout <<"NDC = " << (double)index.NDC / query_num << std::endl;
  std::cout <<"nhops = " << (double)index.hops / query_num << std::endl;



  return 0;
}
