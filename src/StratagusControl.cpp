/*
 * StratagusControl.cpp
 *
 *      Author: Andreas Volz
 */

#include "StratagusControl.h"
#include "Preferences.h"

// system
#include <iostream>
#include <fstream>
#include <gtkmm.h>

// platform specific
#include <sys/types.h>
#include <signal.h>

using namespace std;

StratagusControl::StratagusControl(OutputWorker &out) :
  stratagusPid(0),
  mOut(out)
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

  // TODO: a thread should read stdin/stderr and update a text info box
  int standard_output = 0;
  int standard_error = 0;



  Glib::SlotSpawnChildSetup setup;
  Glib::spawn_async_with_pipes(preferences.getStratagusGameDir(), argv, Glib::SPAWN_SEARCH_PATH, setup, &stratagusPid, &standard_output, &standard_error);

  mOut.setOutputSteams(standard_output, standard_error);

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

std::vector<Glib::ustring> StratagusControl::enumerate_files(const Glib::ustring &path)
{

  Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(path);
  Glib::RefPtr<Gio::FileEnumerator> child_enumeration = file->enumerate_children();
  std::vector<Glib::ustring> file_names;
  Glib::RefPtr<Gio::FileInfo> file_info;

  while ((file_info = child_enumeration->next_file()))
  {
    string name(file_info->get_name());
    if(name.substr(0, 7) == "rsi_tc_")
    {
      file_names.push_back(name);
    }
  }
  return file_names;
}

std::string StratagusControl::getRSITestDir()
{
  string user_dir(Glib::get_home_dir ());

  user_dir += "/.stratagus/sc/rsi_testscenario";

  return user_dir;
}

void StratagusControl::writeRSIConfigContent(const std::string &lua)
{
  string luaString("Load(\"rsi_testscenario/" + lua + "\")");

  std::ofstream rsi_config_file(getRSITestDir() + "/rsi_configuration.lua");

  rsi_config_file << luaString;
}
