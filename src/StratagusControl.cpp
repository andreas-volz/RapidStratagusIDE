/*
 * StratagusControl.cpp
 *
 *      Author: Andreas Volz
 */

#include "StratagusControl.h"

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
  std::cout << "Start stratagus" << std::endl;

  string working_dir("/home/andreas/src/git/stargus/stargus");
  string stratagus_dir("/home/andreas/src/git/stratagus/stratagus");
  string stratagus_bin("stratagus-dbg");
  string stratagus_datadir("/home/andreas/.stratagus/data.Stargus");

  std::vector<std::string> argv;

  argv.push_back(stratagus_dir + "/" + stratagus_bin);
  argv.push_back("-d");
  argv.push_back(stratagus_datadir);

  Glib::SlotSpawnChildSetup setup;
  Glib::spawn_async(working_dir, argv, Glib::SPAWN_SEARCH_PATH, setup, &stratagusPid);

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
