#include <chrono>

#include "DBoW2/FORB.h"
#include "DBoW2/TemplatedVocabulary.h"

typedef DBoW2::TemplatedVocabulary<DBoW2::FORB::TDescriptor, DBoW2::FORB> orb_vocab;

class timer {
public:
  timer() {
    start_ = std::chrono::system_clock::now();
  }
  virtual ~timer() = default;

  double get_msec() {
    const auto dur = std::chrono::system_clock::now() - start_;
    const auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    return msec;
  }

private:
  std::chrono::system_clock::time_point start_;
};

void load_as_text(orb_vocab* voc, const std::string& in_file) {
  timer t;
  voc->loadFromTextFile(in_file);
  printf("Loading from text: %.0fms\n", t.get_msec());
}

void load_as_binary(orb_vocab* voc, const std::string& in_file) {
  timer t;
  voc->loadFromBinaryFile(in_file);
  printf("Loading from binary: %.0fs\n", t.get_msec());
}

void save_as_text(orb_vocab* voc, const std::string& out_file) {
  timer t;
  voc->saveToTextFile(out_file);
  printf("Saving as text: %.0fms\n", t.get_msec());
}

void save_as_binary(orb_vocab* voc, const std::string& out_file) {
  timer t;
  voc->saveToBinaryFile(out_file);
  printf("Saving as binary: %.0fms\n", t.get_msec());
}

void show_usage(char **argv) {
  std::cout << "Usage:" << std::endl;
  std::cout << argv[0] << " "
            << "INPUT_TYPE:(txt|bin) "
            << "OUTPUT_TYPE:(txt|bin) "
            << "INPUT_FILEPATH "
            << "OUTPUT_FILEPATH"
            << std::endl;
  std::cout << std::endl;
}

int main(int argc, char **argv) {
  cv::CommandLineParser parser(argc, argv,
    "{@in-ext||extension of input vocab}"
    "{@out-ext||extension of output vocab}"
    "{@in-file||filepath of input vocab}"
    "{@out-file||filepath of output vocab}"
    "{h help||show usage}");

  std::cout << "DBoW2 Vocabulary Converter" << std::endl;
  std::cout << std::endl;

  if (parser.has("h") || parser.has("help")) {
    show_usage(argv);
    return 0;
  }

  if (!parser.has("@in-ext") || !parser.has("@out-ext")
      || !parser.has("@in-file") || !parser.has("@out-file")) {
    show_usage(argv);
    return 0;
  }

  const std::string in_ext = parser.get<std::string>("@in-ext");
  const std::string out_ext = parser.get<std::string>("@out-ext");
  const std::string in_file = parser.get<std::string>("@in-file");
  const std::string out_file = parser.get<std::string>("@out-file");

  if ((in_ext != "txt" && in_ext != "bin")
      || (out_ext != "txt" && out_ext != "bin")){
    show_usage(argv);
    return 0;
  }

  std::cout << "INPUT(" << in_ext << "): " << in_file << std::endl;
  std::cout << "OUTPUT(" << out_ext << "): " << out_file << std::endl;
  std::cout << std::endl;
 
  orb_vocab* vocab = new orb_vocab();

  if (in_ext == "txt") {
    load_as_text(vocab, in_file);
  }
  else if (in_ext == "bin") {
    load_as_binary(vocab, in_file);
  }
  else {
    throw std::runtime_error("Unknown extension: " + in_ext);
  }

  if (out_ext == "txt") {
    save_as_text(vocab, out_file);
  }
  else if (out_ext == "bin") {
    save_as_binary(vocab, out_file);
  }
  else {
    throw std::runtime_error("Unknown extension: " + in_ext);
  }

  std::cout << std::endl;

  return 0;
}
