/*
 * StratagusControl.h
 *
 *      Author: Andreas Volz
 */

#ifndef STRATAGUSCONTROL_H
#define STRATAGUSCONTROL_H

#include "OutputWorker.h"

#include <glibmm.h>

class StratagusControl
{
public:
  StratagusControl(OutputWorker &out);
  virtual ~StratagusControl();

  bool start();

  bool stop();

  bool restart();

  std::vector<Glib::ustring> enumerate_files(const Glib::ustring &path);

  std::string getRSITestDir();

  void writeRSIConfigContent(const std::string &lua);

private:
  Glib::Pid stratagusPid;
  OutputWorker &mOut;
};

#endif /* STRATAGUSCONTROL_H */
