/*
 * StratagusControl.h
 *
 *      Author: Andreas Volz
 */

#ifndef STRATAGUSCONTROL_H
#define STRATAGUSCONTROL_H

#include <glibmm.h>

class StratagusControl
{
public:
  StratagusControl();
  virtual ~StratagusControl();

  bool start();

  bool stop();

  bool restart();

private:
  Glib::Pid stratagusPid;
};

#endif /* STRATAGUSCONTROL_H */
