#include <efanna2e/index_taumng.h>
#include <efanna2e/util.h>
#include <fstream>

using namespace efanna2e;

void load_data(const char* filename, float*& data, unsigned& num,
               unsigned& dim) {  // load data with sift10K pattern
  std::ifstream in(filename, std::ios::binary);
  if (!in.is_open()) {
    std::cout << "open file error" << std::endl;
    exit(-1);
  }
  in.read((char*)&dim, 4);
  in.seekg(0, std::ios::end);
  std::ios::pos_type ss = in.tellg();
  size_t fsize = (size_t)ss;
  num = (unsigned)(fsize / (dim + 1) / 4);
  data = new float[(size_t)num * (size_t)dim];

  in.seekg(0, std::ios::beg);
  for (size_t i = 0; i < num; i++) {
    in.seekg(4, std::ios::cur);
    in.read((char*)(data + i * dim), dim * 4);
  }
  in.close();
}



int main(int argc, char** argv) {
  if (argc != 9) {
    std::cout << argv[0] << " data_file nn_graph_path L R C angle tau save_graph_file "
              << std::endl;
    exit(-1);
  }
  float* data_load = NULL;
  unsigned points_num, dim;
  std::string dataFileName = argv[1];
  // std::string dataFileName = "/home/hadoop/wzy/dataset/"+dataset+"/"+dataset+"_base.fvecs";
  load_data(dataFileName.c_str(), data_load, points_num, dim);

  std::string nn_graph_path(argv[2]);
  unsigned L = (unsigned)atoi(argv[3]);
  unsigned R = (unsigned)atoi(argv[4]);
  unsigned C = (unsigned)atoi(argv[5]);
  float angle = atof(argv[6]);
  float tau = atof(argv[7]);

  IndexTauMNG index(dim, points_num, L2, nullptr);

  auto s = std::chrono::high_resolution_clock::now();
  Parameters paras;
  paras.Set<unsigned>("L", L);
  paras.Set<unsigned>("R", R);
  paras.Set<unsigned>("C", C);
  paras.Set<std::string>("nn_graph_path", nn_graph_path);

  index.ang = angle;
  index.tau = tau;

  index.Build(points_num, data_load, paras);
  auto e = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = e - s;

  std::cout << "indexing time: " << diff.count() << "\n";
  std::string saveFileName = argv[8];

  index.Save(saveFileName.c_str());

  return 0;
}
