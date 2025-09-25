#include "srsran/srslog/srslog.h"
#include "srsran/common/common_helper.h"
#include "srsran/srsran.h"
#include "srsran/version.h"
#include "pkt-dissector/hdr/constants.h"
#include <unistd.h>
#include <iostream>

using namespace srsran;

static srslog::sink*     log_sink       = nullptr;

int main(int argc, char* argv[])
{
  // Setup logging.
  //log_sink = (args.log.filename == "stdout")
                 // ? srslog::create_stdout_sink()
                 // : srslog::create_file_sink(args.log.filename, fixup_log_file_maxsize(args.log.file_max_size));
  log_sink = srslog::create_stdout_sink();

  if (!log_sink) {
    return SRSRAN_ERROR;
  }

  srslog::log_channel* chan = srslog::create_log_channel("main_channel", *log_sink);
  if (!chan) {
    return SRSRAN_ERROR;
  }
  srslog::set_default_sink(*log_sink);

  // Start the log backend.
  srslog::init();

  srslog::fetch_basic_logger("ALL").set_level(srslog::basic_levels::warning);
  srsran::log_args(argc, argv, "ARGS");
  srslog::basic_logger& main_logger = srslog::fetch_basic_logger("MAIN");
  main_logger.info(GREEN "HELLO WORLD!!!" GREEN);


  std::cout << "---  exiting  ---" << std::endl;
  return SRSRAN_SUCCESS;
}
