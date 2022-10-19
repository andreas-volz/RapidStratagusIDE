/*
 * StratagusControl.cpp
 *
 *      Author: Andreas Volz
 */

#include "StratagusControl.h"
#include "Preferences.h"

#include <iostream>

// platform specific
#include <sys/types.h>
#include <signal.h>

using namespace std;

StratagusControl::StratagusControl() :
  stratagusPid(0)
{

}

StratagusControl::~StratagusControl()
{
  stop();
}

bool StratagusControl::start()
{
  Preferences &preferences = Preferences::getInstance();

  std::cout << "Start stratagus" << std::endl;

  std::vector<std::string> argv;

  argv.push_back(preferences.getStratagusBinary());
  argv.push_back("-d");
  argv.push_back(preferences.getStratagusGameDataDir());

  Glib::SlotSpawnChildSetup setup;
  Glib::spawn_async(preferences.getStratagusGameDir(), argv, Glib::SPAWN_SEARCH_PATH, setup, &stratagusPid);

  printf("\n\npid: %d\n\n", stratagusPid);

  return stratagusPid;
}

bool StratagusControl::stop()
{
  int kill_ret = 0;

  cout << "Stop stratagus" << endl;

  if(stratagusPid)
  {
    kill_ret = kill(stratagusPid, 2);

    Glib::spawn_close_pid(stratagusPid);
    stratagusPid = 0;
  }

  return (kill_ret == 0);
}

bool StratagusControl::restart()
{
  cout << "Restart stratagus" << endl;

  stop();

  bool result = start();

  return result;
}
