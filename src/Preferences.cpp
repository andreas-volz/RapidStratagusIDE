#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// system
#include <iostream>

#include "Preferences.h"

using namespace std;

Preferences::Preferences()
{

};

Preferences::~Preferences()
{

}

Preferences &Preferences::getInstance()
{
  static Preferences instance;
  return instance;
}

std::string Preferences::getStratagusGameDir()
{
  string dir("/home/andreas/src/git/stargus/stargus");

  return dir;
}

std::string Preferences::getStratagusGameDataDir()
{
  string dir("/home/andreas/.stratagus/data.Stargus");

  return dir;
}

std::string Preferences::getRSIConfigDir()
{
  string game_dir("home/andreas/.stratagus/sc");
  string rsi_dir("rsi_testscenario");
  string dir(game_dir + "/" + rsi_dir);

  return dir;
}

std::string Preferences::getStratagusBinary()
{
  string stratagus_dir("/home/andreas/src/git/stratagus/stratagus");
  string stratagus_bin("stratagus-dbg");
  string stratagus_path(stratagus_dir + "/" + stratagus_bin);

  return stratagus_path;
}
