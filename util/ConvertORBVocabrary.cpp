#include <chrono>
#include <memory>

#include "DBoW2/FORB.h"
#include "DBoW2/TemplatedVocabulary.h"

typedef DBoW2::TemplatedVocabulary<DBoW2::FORB::TDescriptor, DBoW2::FORB> ORBVocabulary;

class Timer {
public:
  Timer() {
    start_ = std::chrono::system_clock::now();
  }
  virtual ~Timer() = default;

  double getMilliSec() {
    const auto dur = std::chrono::system_clock::now() - start_;
    const auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    return msec;
  }

private:
  std::chrono::system_clock::time_point start_;
};

void loadAsText(const std::unique_ptr<ORBVocabulary>& vocab, const std::string& in_file) {
  Timer t;
  vocab->loadFromTextFile(in_file);
  printf("Loading from text: %.0fms\n", t.getMilliSec());
}

void loadAsBinary(const std::unique_ptr<ORBVocabulary>& vocab, const std::string& in_file) {
  Timer t;
  vocab->loadFromBinaryFile(in_file);
  printf("Loading from binary: %.0fms\n", t.getMilliSec());
}

void saveAsText(const std::unique_ptr<ORBVocabulary>& vocab, const std::string& out_file) {
  Timer t;
  vocab->saveToTextFile(out_file);
  printf("Saving as text: %.0fms\n", t.getMilliSec());
}

void saveAsBinary(const std::unique_ptr<ORBVocabulary>& vocab, const std::string& out_file) {
  Timer t;
  vocab->saveToBinaryFile(out_file);
  printf("Saving as binary: %.0fms\n", t.getMilliSec());
}

void showUsage(char **argv) {
  std::cout << "Usage:" << std::endl;
  std::cout << argv[0] << " "
            << "INPUT_TYPE:(txt|bin) "
            << "OUTPUT_TYPE:(txt|bin) "
            << "INPUT_FILEPATH "
            << "OUTPUT_FILEPATH"
            << std::endl;
}

int main(int argc, char **argv) {
  cv::CommandLineParser parser(argc, argv,
    "{@in-ext||extension of input vocab}"
    "{@out-ext||extension of output vocab}"
    "{@in-file||filepath of input vocab}"
    "{@out-file||filepath of output vocab}"
    "{h help||show usage}");

  std::cout << "ORB Vocabulary Converter for DBoW2" << std::endl;

  if (parser.has("h") || parser.has("help")) {
    showUsage(argv);
    return 0;
  }

  if (!parser.has("@in-ext") || !parser.has("@out-ext")
      || !parser.has("@in-file") || !parser.has("@out-file")) {
    showUsage(argv);
    return 0;
  }

  const std::string in_ext = parser.get<std::string>("@in-ext");
  const std::string out_ext = parser.get<std::string>("@out-ext");
  const std::string in_file = parser.get<std::string>("@in-file");
  const std::string out_file = parser.get<std::string>("@out-file");

  if ((in_ext != "txt" && in_ext != "bin")
      || (out_ext != "txt" && out_ext != "bin")){
    showUsage(argv);
    return 0;
  }

  std::cout << "INPUT(" << in_ext << "): " << in_file << std::endl;
  std::cout << "OUTPUT(" << out_ext << "): " << out_file << std::endl;
 
  auto vocab = std::unique_ptr<ORBVocabulary>(new ORBVocabulary());

  if (in_ext == "txt") {
    loadAsText(vocab, in_file);
  }
  else if (in_ext == "bin") {
    loadAsBinary(vocab, in_file);
  }
  else {
    throw std::runtime_error("Unknown extension: " + in_ext);
  }

  if (out_ext == "txt") {
    saveAsText(vocab, out_file);
  }
  else if (out_ext == "bin") {
    saveAsBinary(vocab, out_file);
  }
  else {
    throw std::runtime_error("Unknown extension: " + in_ext);
  }

  return 0;
}
